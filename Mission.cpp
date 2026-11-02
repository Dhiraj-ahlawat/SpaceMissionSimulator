#include "../include/Mission.h"
#include "../include/AsteroidEvent.h"
#include "../include/OxygenLeakEvent.h"
#include "../include/FuelLeakEvent.h"
#include "../include/SolarStormEvent.h"
#include <iostream>
#include <random>

// Initialize static member
int Mission::totalMissions = 0;

Mission::Mission() : missionName("Unknown Mission"), state(MissionState::PREPARING), currentStage(0), totalStages(4) {
    totalMissions++;
}

Mission::Mission(const std::string& missionName, const Destination& destination, const Spacecraft& spacecraft)
    : missionName(missionName), spacecraft(spacecraft), destination(destination), state(MissionState::PREPARING), currentStage(0), totalStages(4) {
    totalMissions++;
}

Mission::~Mission() {
    // Vector of unique_ptr cleans up automatically.
}

void Mission::addAstronaut(std::unique_ptr<Astronaut> astronaut) {
    if (astronaut) {
        crew.push_back(std::move(astronaut));
    }
}

void Mission::displayMissionDetails() const {
    std::cout << "Mission: " << missionName << "\n";
    destination.display();
    spacecraft.displayStatus();
}

void Mission::displayCrew() const {
    std::cout << "Crew Roster:\n";
    for (const auto& member : crew) {
        std::cout << " - " << member->getRoleName() << " " << member->getName() 
                  << " (Health: " << member->getHealth() << ")\n";
    }
}

int Mission::getTotalMissions() {
    return totalMissions;
}

void Mission::addEvent(std::unique_ptr<SpaceEvent> event) {
    if (event) {
        events.push(std::move(event));
    }
}

void Mission::triggerNextEvent() {
    if (events.empty()) return;
    
    auto& nextEvent = events.front();
    std::string evtName = nextEvent->getEventName();
    int severity = nextEvent->getSeverity();
    
    // Add to Phase 5 history
    eventHistory.push_back(evtName + " - Severity " + std::to_string(severity));

    nextEvent->trigger(spacecraft);
    
    // Crew Response Phase 4 logic
    bool handled = false;
    for (auto& member : crew) {
        if (member->getHealth() <= 0) continue;
        
        if (evtName == "Oxygen Leak" && member->getRepairSkill() > 0) {
            std::cout << "Engineer " << member->getName() << " responding to oxygen leak...\n";
            std::cout << "Emergency system repaired by Engineer.\n";
            spacecraft.addOxygen(5.0 * nextEvent->getSeverity()); // partial refund
            handled = true; break;
        }
        else if (evtName == "Fuel Leak" && member->getRepairSkill() > 0) {
            std::cout << "Engineer " << member->getName() << " repairing fuel system...\n";
            std::cout << "Fuel leak partially contained.\n";
            spacecraft.addFuel(10.0 * nextEvent->getSeverity());
            handled = true; break;
        }
        else if (evtName == "Asteroid Field" && member->getNavigationSkill() > 0) {
            std::cout << "Pilot " << member->getName() << " correcting navigation...\n";
            std::cout << "Course stabilized, minimizing further risk.\n";
            handled = true; break;
        }
        else if (evtName == "Solar Storm" && member->getResearchSkill() > 0) {
            std::cout << "Scientist " << member->getName() << " analyzing anomaly...\n";
            std::cout << "Data collected successfully, shielding optimized.\n";
            spacecraft.repairHull(2.0 * nextEvent->getSeverity());
            handled = true; break;
        }
    }
    
    if (!handled) {
        // Default to Commander if no specialist handles it
        for (auto& member : crew) {
            if (member->getHealth() > 0 && member->getLeadershipSkill() > 0) {
                std::cout << "Commander " << member->getName() << " evaluating emergency response...\n";
                std::cout << "Crew ordered to continue mission safely.\n";
                handled = true; break;
            }
        }
    }
    
    // Chance of random crew injury on severe events
    if (nextEvent->getSeverity() >= 2 && !crew.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dmgDist(0, 100);
        if (dmgDist(gen) < 30) { // 30% chance someone gets hurt
            std::uniform_int_distribution<> crewDist(0, crew.size() - 1);
            int victim = crewDist(gen);
            if (crew[victim]->getHealth() > 0) {
                crew[victim]->takeDamage(20 * nextEvent->getSeverity());
                std::cout << "Crew member " << crew[victim]->getName() << " was injured during the event!\n";
            }
        }
    }
    
    events.pop();
}

void Mission::displayEvents() const {
    std::cout << "Upcoming Events Queue Size: " << events.size() << "\n";
}

void Mission::generateRandomEvent() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> eventTypeDist(1, 4);
    std::uniform_int_distribution<> severityDist(1, 3); // 1 = Minor, 2 = Moderate, 3 = Severe

    int type = eventTypeDist(gen);
    int severity = severityDist(gen);

    switch (type) {
        case 1:
            addEvent(std::make_unique<AsteroidEvent>(severity));
            break;
        case 2:
            addEvent(std::make_unique<OxygenLeakEvent>(severity));
            break;
        case 3:
            addEvent(std::make_unique<FuelLeakEvent>(severity));
            break;
        case 4:
            addEvent(std::make_unique<SolarStormEvent>(severity));
            break;
    }
}

// Phase 4 additions

MissionState Mission::getState() const {
    return state;
}

std::string Mission::getStateString() const {
    switch(state) {
        case MissionState::PREPARING: return "PREPARING";
        case MissionState::READY: return "READY";
        case MissionState::LAUNCHED: return "LAUNCHED";
        case MissionState::IN_SPACE: return "IN SPACE";
        case MissionState::COMPLETED: return "COMPLETED";
        case MissionState::FAILED: return "FAILED";
        case MissionState::ABORTED: return "ABORTED";
        default: return "UNKNOWN";
    }
}

// Phase 5 getters and helpers
const std::string& Mission::getMissionName() const { return missionName; }
const Destination& Mission::getDestination() const { return destination; }
const Spacecraft& Mission::getSpacecraft() const { return spacecraft; }
int Mission::getCurrentStage() const { return currentStage; }
int Mission::getTotalStages() const { return totalStages; }
const std::vector<std::unique_ptr<Astronaut>>& Mission::getCrew() const { return crew; }
const std::vector<std::string>& Mission::getEventHistory() const { return eventHistory; }

void Mission::restoreMissionState(MissionState state, int currentStage, int totalStages) {
    this->state = state;
    this->currentStage = currentStage;
    this->totalStages = totalStages;
}

void Mission::clearCrew() {
    crew.clear();
}

void Mission::addEventToHistory(const std::string& evt) {
    eventHistory.push_back(evt);
}

void Mission::checkFailureConditions() {
    if (state == MissionState::FAILED || state == MissionState::ABORTED || state == MissionState::COMPLETED) return;

    if (spacecraft.getFuel() <= 0) {
        state = MissionState::FAILED;
        std::cout << "\n========================================\n"
                  << "          MISSION FAILED\n"
                  << "========================================\n\n"
                  << "Reason:\nSpacecraft has run out of fuel.\n\nThe spacecraft can no longer continue the mission.\n";
        return;
    }
    if (spacecraft.getOxygen() <= 0) {
        state = MissionState::FAILED;
        std::cout << "\n========================================\n"
                  << "          MISSION FAILED\n"
                  << "========================================\n\n"
                  << "Reason:\nSpacecraft has run out of oxygen.\n\nThe spacecraft can no longer continue the mission.\n";
        return;
    }
    if (spacecraft.getHullIntegrity() <= 0) {
        state = MissionState::FAILED;
        std::cout << "\n========================================\n"
                  << "          MISSION FAILED\n"
                  << "========================================\n\n"
                  << "Reason:\nSpacecraft hull integrity reached 0%.\n\nThe spacecraft can no longer continue the mission.\n";
        return;
    }

    bool allIncapacitated = true;
    for (const auto& member : crew) {
        if (member->getHealth() > 0) {
            allIncapacitated = false;
            break;
        }
    }
    if (allIncapacitated && !crew.empty()) {
        state = MissionState::FAILED;
        std::cout << "\n========================================\n"
                  << "          MISSION FAILED\n"
                  << "========================================\n\n"
                  << "Reason:\nAll crew members are incapacitated.\n\nThe spacecraft can no longer continue the mission.\n";
        return;
    }
}

bool Mission::performPreLaunchChecks() {
    std::cout << "Performing pre-launch checks...\n\n";
    bool passed = true;
    
    std::cout << "Fuel.................... ";
    if (spacecraft.getFuel() >= destination.getRequiredFuel()) { std::cout << "OK\n"; }
    else { std::cout << "FAIL\n"; passed = false; }
    
    std::cout << "Oxygen.................. ";
    if (spacecraft.getOxygen() > 0) { std::cout << "OK\n"; }
    else { std::cout << "FAIL\n"; passed = false; }

    std::cout << "Hull.................... ";
    if (spacecraft.getHullIntegrity() > 0) { std::cout << "OK\n"; }
    else { std::cout << "FAIL\n"; passed = false; }

    std::cout << "Crew.................... ";
    bool hasHealthyCrew = false;
    for (const auto& mem : crew) {
        if (mem->getHealth() > 0) hasHealthyCrew = true;
    }
    if (hasHealthyCrew) { std::cout << "OK\n"; }
    else { std::cout << "FAIL\n"; passed = false; }

    std::cout << "Destination............. ";
    if (destination.getDistance() > 0) { std::cout << "OK\n"; }
    else { std::cout << "FAIL\n"; passed = false; }

    std::cout << "\n";
    if (passed) {
        std::cout << "PRE-LAUNCH CHECK: PASSED\n";
        state = MissionState::READY;
        return true;
    } else {
        std::cout << "PRE-LAUNCH CHECK: FAILED\n";
        return false;
    }
}

bool Mission::launch() {
    if (state != MissionState::READY) {
        std::cout << "Cannot launch: Pre-launch checks not completed or failed.\n";
        return false;
    }

    std::cout << "\n========================================\n"
              << "         MISSION LAUNCH\n"
              << "========================================\n\n"
              << "ALL SYSTEMS GO!\n\n"
              << "T-3\n"
              << "T-2\n"
              << "T-1\n\n"
              << "LIFTOFF!\n\n"
              << "Mission launched successfully.\n";
              
    state = MissionState::LAUNCHED;
    // Immediately transition
    state = MissionState::IN_SPACE;
    return true;
}

bool Mission::advanceTravel() {
    if (state != MissionState::IN_SPACE) return false;
    
    currentStage++;
    
    std::cout << "\n========================================\n"
              << "        SPACE TRAVEL\n"
              << "========================================\n\n";
              
    std::cout << "Stage " << currentStage << " / " << totalStages << "\n";
    if (currentStage == 1) std::cout << "Leaving Earth orbit...\n\n";
    else if (currentStage == totalStages) std::cout << "Destination Approach...\n\n";
    else std::cout << "Entering deep space...\n\n";

    // Navigation skill reduces fuel
    int navSkill = 0;
    for (auto& c : crew) {
        if (c->getHealth() > 0) {
            navSkill = std::max(navSkill, c->getNavigationSkill());
        }
    }
    
    double baseFuelCost = destination.getRequiredFuel() / totalStages;
    double baseOxyCost = 1000.0; // Arbitrary base
    
    // Applying Pilot skill reduction
    if (navSkill > 0) {
        baseFuelCost *= 0.8; // 20% reduction
        std::cout << "Pilot navigation efficiency reduced fuel consumption.\n";
    }

    spacecraft.consumeFuel(baseFuelCost);
    spacecraft.consumeOxygen(baseOxyCost);
    
    std::cout << "Fuel consumed: " << baseFuelCost << "\n";
    std::cout << "Oxygen consumed: " << baseOxyCost << "\n\n";
    
    checkFailureConditions();
    if (state == MissionState::FAILED) return false;

    // Random Event
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> probDist(1, 100);
    
    if (probDist(gen) <= 40 || !events.empty()) { 
        std::cout << "A space event has occurred...\n\n";
        if (events.empty()) {
            generateRandomEvent();
        }
        triggerNextEvent();
        checkFailureConditions();
    } else {
        std::cout << "Travel continued normally.\n";
    }
    
    if (state == MissionState::IN_SPACE && currentStage >= totalStages) {
        state = MissionState::COMPLETED;
        std::cout << "\n========================================\n"
                  << "       DESTINATION REACHED\n"
                  << "========================================\n\n"
                  << "Mission: " << missionName << "\n"
                  << "Destination: " << destination.getName() << "\n\n"
                  << "The spacecraft has successfully reached\n"
                  << "its destination.\n\n"
                  << "MISSION COMPLETED!\n";
    }

    return true;
}

void Mission::abortMission() {
    if (state == MissionState::COMPLETED || state == MissionState::FAILED || state == MissionState::ABORTED) {
        std::cout << "Cannot abort mission from current state.\n";
        return;
    }
    state = MissionState::ABORTED;
    std::cout << "\nMission aborted by crew command.\n\n"
              << "State: ABORTED\n";
}

void Mission::runMission() {
    if (state == MissionState::PREPARING) {
        if (!performPreLaunchChecks()) return;
        if (!launch()) return;
    }
    
    while (state == MissionState::IN_SPACE && currentStage < totalStages) {
        advanceTravel();
    }
}
