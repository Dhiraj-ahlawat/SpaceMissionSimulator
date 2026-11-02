#include "../include/FileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

int FileManager::totalSaveOperations = 0;

int FileManager::getTotalSaveOperations() {
    return totalSaveOperations;
}

std::vector<std::string> FileManager::splitString(const std::string& str, char delimiter) const {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

MissionState FileManager::parseState(const std::string& str) const {
    if (str == "PREPARING") return MissionState::PREPARING;
    if (str == "READY") return MissionState::READY;
    if (str == "LAUNCHED") return MissionState::LAUNCHED;
    if (str == "IN SPACE") return MissionState::IN_SPACE;
    if (str == "COMPLETED") return MissionState::COMPLETED;
    if (str == "FAILED") return MissionState::FAILED;
    if (str == "ABORTED") return MissionState::ABORTED;
    throw std::runtime_error("Invalid mission state in save file: " + str);
}

bool FileManager::saveMission(const Mission& mission, const std::string& filename) {
    try {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Save file could not be opened.");
        }

        file << "MISSION_NAME=" << mission.getMissionName() << "\n";
        file << "DESTINATION=" << mission.getDestination().getName() << "\n";
        file << "DESTINATION_DIST=" << mission.getDestination().getDistance() << "\n";
        file << "DESTINATION_FUEL=" << mission.getDestination().getRequiredFuel() << "\n";
        file << "DESTINATION_DIFF=" << mission.getDestination().getDifficulty() << "\n";
        
        file << "STATE=" << mission.getStateString() << "\n";
        file << "STAGE=" << mission.getCurrentStage() << "\n";
        file << "TOTAL_STAGES=" << mission.getTotalStages() << "\n\n";

        const Spacecraft& ship = mission.getSpacecraft();
        file << "SPACECRAFT_NAME=" << ship.getName() << "\n";
        file << "FUEL=" << ship.getFuel() << "\n";
        file << "OXYGEN=" << ship.getOxygen() << "\n";
        file << "HULL=" << ship.getHullIntegrity() << "\n\n";

        const auto& crew = mission.getCrew();
        file << "CREW_COUNT=" << crew.size() << "\n";
        for (const auto& mem : crew) {
            // Save as: CREW=Role|Name|Health
            file << "CREW=" << mem->getRoleName() << "|" << mem->getName() << "|" << mem->getHealth() << "\n";
        }
        file << "\n";

        const auto& history = mission.getEventHistory();
        file << "HISTORY_COUNT=" << history.size() << "\n";
        for (const auto& evt : history) {
            file << "HISTORY=" << evt << "\n";
        }

        file.close();
        totalSaveOperations++;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        return false;
    }
}

bool FileManager::loadMission(Mission& mission, const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Save file could not be opened.");
        }

        std::string line;
        
        std::string mName = "Unknown";
        std::string destName = "Unknown";
        double destDist = 0, destFuel = 0;
        int destDiff = 1;
        MissionState state = MissionState::PREPARING;
        int stage = 0, totStages = 4;
        
        std::string shipName = "Unknown Ship";
        double fuel = 0, oxy = 0, hull = 0;
        
        std::vector<std::string> parsedCrew;
        std::vector<std::string> parsedHistory;

        while (std::getline(file, line)) {
            if (line.empty()) continue;
            auto pos = line.find('=');
            if (pos == std::string::npos) continue;
            
            std::string key = line.substr(0, pos);
            std::string val = line.substr(pos + 1);

            if (key == "MISSION_NAME") mName = val;
            else if (key == "DESTINATION") destName = val;
            else if (key == "DESTINATION_DIST") destDist = std::stod(val);
            else if (key == "DESTINATION_FUEL") destFuel = std::stod(val);
            else if (key == "DESTINATION_DIFF") destDiff = std::stoi(val);
            else if (key == "STATE") state = parseState(val);
            else if (key == "STAGE") stage = std::stoi(val);
            else if (key == "TOTAL_STAGES") totStages = std::stoi(val);
            
            else if (key == "SPACECRAFT_NAME") shipName = val;
            else if (key == "FUEL") fuel = std::stod(val);
            else if (key == "OXYGEN") oxy = std::stod(val);
            else if (key == "HULL") hull = std::stod(val);
            
            else if (key == "CREW") parsedCrew.push_back(val);
            else if (key == "HISTORY") parsedHistory.push_back(val);
        }
        
        file.close();

        // Validation
        if (fuel < 0 || oxy < 0 || hull < 0 || hull > 100) {
            throw std::runtime_error("Save file contains invalid spacecraft data.");
        }
        if (stage < 0 || totStages <= 0) {
            throw std::runtime_error("Invalid mission stage data.");
        }

        // Reconstruct Mission
        Destination loadedDest(destName, destDist, destFuel, destDiff);
        Spacecraft loadedShip(shipName, fuel, oxy, hull);
        
        Mission tempMission(mName, loadedDest, loadedShip);
        tempMission.restoreMissionState(state, stage, totStages);
        
        for (const auto& val : parsedCrew) {
            auto tokens = splitString(val, '|');
            if (tokens.size() == 3) {
                std::string role = tokens[0];
                std::string name = tokens[1];
                int health = std::stoi(tokens[2]);
                
                if (health < 0 || health > 100) throw std::runtime_error("Invalid crew data.");
                
                if (role == "Commander") tempMission.addAstronaut(std::make_unique<Commander>(name, health, 90));
                else if (role == "Pilot") tempMission.addAstronaut(std::make_unique<Pilot>(name, health, 90));
                else if (role == "Scientist") tempMission.addAstronaut(std::make_unique<Scientist>(name, health, 90));
                else if (role == "Engineer") tempMission.addAstronaut(std::make_unique<Engineer>(name, health, 90));
            }
        }
        
        for (const auto& val : parsedHistory) {
            tempMission.addEventToHistory(val);
        }
        
        mission = std::move(tempMission);
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        return false;
    }
}
