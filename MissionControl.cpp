#include "../include/MissionControl.h"
#include "../include/MissionReport.h"
#include "../include/Destination.h"
#include "../include/Spacecraft.h"
#include "../include/Astronaut.h"
#include <iostream>
#include <limits>
#include <stdexcept>

MissionControl::MissionControl() : currentMission(nullptr) {}

int MissionControl::getIntInput(const std::string& prompt) const {
    int value;
    std::string line;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) {
            if (std::cin.eof()) throw std::runtime_error("EOF reached");
            std::cin.clear();
            std::cout << "Invalid input.\n";
            continue;
        }
        if (line.empty()) continue;
        try {
            size_t pos;
            value = std::stoi(line, &pos);
            if (pos == line.length()) return value;
        } catch (...) {}
        std::cout << "Invalid input. Please enter a valid number.\n";
    }
}

double MissionControl::getDoubleInput(const std::string& prompt) const {
    double value;
    std::string line;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) {
            if (std::cin.eof()) throw std::runtime_error("EOF reached");
            std::cin.clear();
            std::cout << "Invalid input.\n";
            continue;
        }
        if (line.empty()) continue;
        try {
            size_t pos;
            value = std::stod(line, &pos);
            if (pos == line.length()) {
                if (value >= 0) return value;
                std::cout << "Value cannot be negative.\n";
                continue;
            }
        } catch (...) {}
        std::cout << "Invalid input. Please enter a valid non-negative number.\n";
    }
}

std::string MissionControl::getStringInput(const std::string& prompt) const {
    std::string line;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) {
            if (std::cin.eof()) throw std::runtime_error("EOF reached.");
            std::cin.clear();
            std::cout << "Invalid input.\n";
            continue;
        }
        if (!line.empty()) return line;
        std::cout << "Input cannot be empty.\n";
    }
}

void MissionControl::displayMenu() const {
    std::cout << "\n==================================================\n"
              << "          SPACE MISSION SIMULATOR\n"
              << "==================================================\n\n"
              << "1. Create New Mission\n"
              << "2. View Mission Details\n"
              << "3. Manage Crew\n"
              << "4. View Spacecraft Status\n"
              << "5. Launch / Continue Mission\n"
              << "6. View Mission Report\n"
              << "7. Save Mission\n"
              << "8. Load Mission\n"
              << "9. Abort Mission\n"
              << "0. Exit\n\n"
              << "==================================================\n";
}

void MissionControl::run() {
    std::cout << "\n==================================================\n"
              << "       WELCOME TO SPACE MISSION SIMULATOR\n"
              << "==================================================\n\n"
              << "Mission Control System Online.\n\n"
              << "Press Enter to continue...";
    std::string dummy;
    std::getline(std::cin, dummy);

    bool running = true;
    while (running) {
        displayMenu();
        int choice = getIntInput("Enter your choice: ");
        
        switch (choice) {
            case 1: createNewMission(); break;
            case 2: viewMissionDetails(); break;
            case 3: manageCrew(); break;
            case 4: viewSpacecraftStatus(); break;
            case 5: launchOrContinueMission(); break;
            case 6: viewMissionReport(); break;
            case 7: saveCurrentMission(); break;
            case 8: loadMission(); break;
            case 9: abortCurrentMission(); break;
            case 0:
                running = false;
                std::cout << "\n==================================================\n"
                          << "      SPACE MISSION SIMULATOR\n"
                          << "==================================================\n\n"
                          << "Thank you for using Mission Control.\n\n"
                          << "Mission Control shutting down...\n\n"
                          << "Goodbye, Commander.\n";
                break;
            default:
                std::cout << "\nInvalid input. Please enter a valid choice.\n";
                break;
        }
        
        if (running) {
            std::cout << "\nPress Enter to continue...";
            std::getline(std::cin, dummy);
        }
    }
}

void MissionControl::createNewMission() {
    std::cout << "\n--- Create New Mission ---\n";
    std::string mName = getStringInput("Enter mission name:\n");

    std::cout << "\nSelect Destination:\n"
              << "1. Moon\n"
              << "2. Mars\n"
              << "3. ISS\n"
              << "4. Europa\n";
    
    Destination dest;
    int destChoice = 0;
    while (true) {
        destChoice = getIntInput("Choice: ");
        if (destChoice == 1) { dest = Destination("Moon", 384400.0, 1000.0, 2); break; }
        else if (destChoice == 2) { dest = Destination("Mars", 225000000.0, 4000.0, 8); break; }
        else if (destChoice == 3) { dest = Destination("ISS", 400.0, 500.0, 1); break; }
        else if (destChoice == 4) { dest = Destination("Europa", 628300000.0, 8000.0, 10); break; }
        else { std::cout << "Invalid destination choice.\n"; }
    }

    std::cout << "\n--- Configure Spacecraft ---\n";
    std::string sName = getStringInput("Spacecraft name:\n");
    double fuel = getDoubleInput("Initial Fuel: ");
    double oxy = getDoubleInput("Initial Oxygen: ");
    double hull = getDoubleInput("Initial Hull Integrity (0-100): ");
    if (hull > 100.0) hull = 100.0;

    Spacecraft ship(sName, fuel, oxy, hull);
    currentMission = std::make_unique<Mission>(mName, dest, ship);

    std::cout << "\nMission '" << mName << "' created successfully.\n";
}

void MissionControl::viewMissionDetails() const {
    if (!currentMission) {
        std::cout << "No mission available.\n";
        return;
    }
    std::cout << "\n==================================================\n"
              << "                 MISSION DETAILS\n"
              << "==================================================\n\n";
    std::cout << "Mission Name    : " << currentMission->getMissionName() << "\n"
              << "Destination     : " << currentMission->getDestination().getName() << "\n"
              << "State           : " << currentMission->getStateString() << "\n"
              << "Stage           : " << currentMission->getCurrentStage() << " / " << currentMission->getTotalStages() << "\n\n"
              << "Spacecraft      : " << currentMission->getSpacecraft().getName() << "\n\n"
              << "Crew:\n";
    
    if (currentMission->getCrew().empty()) {
        std::cout << "- (No crew assigned)\n";
    } else {
        for (const auto& c : currentMission->getCrew()) {
            std::cout << "- " << c->getRoleName() << " " << c->getName() << "\n";
        }
    }
}

void MissionControl::manageCrew() {
    if (!currentMission) {
        std::cout << "No mission available.\n";
        return;
    }
    if (currentMission->getState() != MissionState::PREPARING) {
        std::cout << "Crew can only be managed during the PREPARING state.\n";
        return;
    }
    
    while (true) {
        std::cout << "\n==================================================\n"
                  << "                 CREW MANAGEMENT\n"
                  << "==================================================\n\n"
                  << "Current Crew Size: " << currentMission->getCrew().size() << " / 4\n\n"
                  << "1. Add Commander\n"
                  << "2. Add Pilot\n"
                  << "3. Add Scientist\n"
                  << "4. Add Engineer\n"
                  << "5. View Crew\n"
                  << "0. Back\n\n";
        
        int choice = getIntInput("Enter choice: ");
        if (choice == 0) break;
        if (choice == 5) {
            std::cout << "\n--- Current Crew ---\n";
            if (currentMission->getCrew().empty()) std::cout << "(Empty)\n";
            else currentMission->displayCrew();
            continue;
        }
        
        if (choice < 1 || choice > 4) {
            std::cout << "Invalid choice.\n";
            continue;
        }

        if (currentMission->getCrew().size() >= 4) {
            std::cout << "Maximum crew size of 4 reached.\n";
            continue;
        }

        std::string role;
        if (choice == 1) role = "Commander";
        else if (choice == 2) role = "Pilot";
        else if (choice == 3) role = "Scientist";
        else if (choice == 4) role = "Engineer";
        
        // Prevent duplicate essential roles to enforce balance (as requested: 1 of each ideally)
        bool exists = false;
        for (const auto& c : currentMission->getCrew()) {
            if (c->getRoleName() == role) {
                exists = true;
                break;
            }
        }
        if (exists) {
            std::cout << "A " << role << " is already assigned to this mission.\n";
            continue;
        }

        std::string name = getStringInput("Enter " + role + " name:\n");
        if (choice == 1) currentMission->addAstronaut(std::make_unique<Commander>(name, 100, 95));
        else if (choice == 2) currentMission->addAstronaut(std::make_unique<Pilot>(name, 100, 90));
        else if (choice == 3) currentMission->addAstronaut(std::make_unique<Scientist>(name, 100, 88));
        else if (choice == 4) currentMission->addAstronaut(std::make_unique<Engineer>(name, 100, 92));
        
        std::cout << role << " " << name << " added to crew.\n";
    }
}

void MissionControl::viewSpacecraftStatus() const {
    if (!currentMission) {
        std::cout << "No mission available.\n";
        return;
    }
    std::cout << "\n==================================================\n"
              << "              SPACECRAFT STATUS\n"
              << "==================================================\n\n";
    const auto& ship = currentMission->getSpacecraft();
    std::cout << "Fuel              : " << ship.getFuel() << "\n"
              << "Oxygen            : " << ship.getOxygen() << "\n"
              << "Hull Integrity    : " << ship.getHullIntegrity() << "%\n"
              << "Engine Health     : 100%\n"
              << "Navigation        : 100%\n"
              << "Communication     : 100%\n";
}

void MissionControl::launchOrContinueMission() {
    if (!currentMission) {
        std::cout << "No mission available.\n";
        return;
    }
    
    MissionState state = currentMission->getState();
    
    if (state == MissionState::COMPLETED) {
        std::cout << "Mission has already been completed.\n";
        return;
    }
    if (state == MissionState::FAILED) {
        std::cout << "Mission has failed and cannot continue.\n";
        return;
    }
    if (state == MissionState::ABORTED) {
        std::cout << "Mission has been aborted.\n";
        return;
    }
    
    if (state == MissionState::PREPARING) {
        // Crew validation
        bool hasCmdr = false, hasPilot = false, hasEng = false;
        for (const auto& c : currentMission->getCrew()) {
            if (c->getRoleName() == "Commander") hasCmdr = true;
            if (c->getRoleName() == "Pilot") hasPilot = true;
            if (c->getRoleName() == "Engineer") hasEng = true;
        }
        
        if (!hasCmdr || !hasPilot || !hasEng) {
            std::cout << "\nCrew configuration: INVALID\nMissing: ";
            if (!hasCmdr) std::cout << "Commander ";
            if (!hasPilot) std::cout << "Pilot ";
            if (!hasEng) std::cout << "Engineer ";
            std::cout << "\nCannot launch without essential crew.\n";
            return;
        }
        std::cout << "\nCrew configuration: VALID\n";
        
        currentMission->runMission(); // will do pre-launch, launch, and travel
    } else if (state == MissionState::READY) {
        currentMission->runMission();
    } else if (state == MissionState::LAUNCHED || state == MissionState::IN_SPACE) {
        std::cout << "Continuing travel...\n";
        currentMission->runMission();
    }
}

void MissionControl::viewMissionReport() const {
    if (!currentMission) {
        std::cout << "No mission available.\n";
        return;
    }
    
    while (true) {
        std::cout << "\n1. Basic Report\n2. Detailed Report\n0. Back\n";
        int choice = getIntInput("Choice: ");
        if (choice == 0) break;
        
        MissionReport report(*currentMission);
        if (choice == 1) {
            report.generate();
            break;
        } else if (choice == 2) {
            report.generate(true);
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

void MissionControl::saveCurrentMission() {
    if (!currentMission) {
        std::cout << "No mission to save.\n";
        return;
    }
    std::cout << "Saving mission...\n";
    if (fileManager.saveMission(*currentMission, "data/mission_save.txt")) {
        std::cout << "Mission saved successfully.\n";
    } else {
        std::cout << "Unable to save mission.\n";
    }
}

void MissionControl::loadMission() {
    std::cout << "Loading mission...\n";
    Mission tempMission;
    if (fileManager.loadMission(tempMission, "data/mission_save.txt")) {
        currentMission = std::make_unique<Mission>(std::move(tempMission));
        std::cout << "Mission loaded successfully.\n";
    } else {
        std::cout << "Unable to load mission.\n";
    }
}

void MissionControl::abortCurrentMission() {
    if (!currentMission) {
        std::cout << "No mission available.\n";
        return;
    }
    MissionState state = currentMission->getState();
    if (state == MissionState::COMPLETED || state == MissionState::FAILED || state == MissionState::ABORTED) {
        std::cout << "Cannot abort a mission that is already completed, failed, or aborted.\n";
        return;
    }
    
    std::cout << "Are you sure you want to abort this mission?\n"
              << "1. Yes\n"
              << "2. No\n";
    int choice = getIntInput("Choice: ");
    if (choice == 1) {
        currentMission->abortMission();
    } else {
        std::cout << "Abort cancelled.\n";
    }
}
