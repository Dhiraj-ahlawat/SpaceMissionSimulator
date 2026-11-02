#include "../include/MissionReport.h"
#include <iostream>

MissionReport::MissionReport(const Mission& mission)
    : missionName(mission.getMissionName()),
      destinationName(mission.getDestination().getName()),
      finalState(mission.getStateString()),
      currentStage(mission.getCurrentStage()),
      totalStages(mission.getTotalStages()),
      eventsEncountered(mission.getEventHistory()),
      finalFuel(mission.getSpacecraft().getFuel()),
      finalOxygen(mission.getSpacecraft().getOxygen()),
      finalHull(mission.getSpacecraft().getHullIntegrity()) {
          
    for (const auto& member : mission.getCrew()) {
        crewStatus.push_back({member->getName(), member->getRoleName(), member->getHealth()});
    }
}

void MissionReport::generate() const {
    std::cout << "\n==================================================\n"
              << "              SPACE MISSION REPORT\n"
              << "==================================================\n\n"
              << "Mission Name       : " << missionName << "\n"
              << "Destination        : " << destinationName << "\n"
              << "Final State        : " << finalState << "\n\n"
              << "--------------------------------------------------\n"
              << "SPACECRAFT\n"
              << "--------------------------------------------------\n\n"
              << "Fuel Remaining     : " << finalFuel << "\n"
              << "Oxygen Remaining   : " << finalOxygen << "\n"
              << "Hull Integrity     : " << finalHull << "%\n\n"
              << "--------------------------------------------------\n"
              << "CREW\n"
              << "--------------------------------------------------\n\n";

    for (const auto& c : crewStatus) {
        std::cout << c.role << " " << c.name << "    : " 
                  << (c.health > 0 ? "Healthy" : "Incapacitated") << "\n";
    }

    std::cout << "\n--------------------------------------------------\n"
              << "EVENTS ENCOUNTERED\n"
              << "--------------------------------------------------\n\n";
              
    if (eventsEncountered.empty()) {
        std::cout << "No major events encountered.\n";
    } else {
        int i = 1;
        for (const auto& evt : eventsEncountered) {
            std::cout << i++ << ". " << evt << "\n";
        }
    }

    std::cout << "\n--------------------------------------------------\n\n"
              << "Mission Status: " << finalState << "\n\n"
              << "==================================================\n";
}

void MissionReport::generate(bool detailed) const {
    if (!detailed) {
        generate();
        return;
    }

    std::cout << "\n==================================================\n"
              << "          DETAILED SPACE MISSION REPORT\n"
              << "==================================================\n\n"
              << "Mission Name       : " << missionName << "\n"
              << "Destination        : " << destinationName << "\n"
              << "Final State        : " << finalState << "\n"
              << "Stages Completed   : " << currentStage << " / " << totalStages << "\n\n"
              << "--------------------------------------------------\n"
              << "SPACECRAFT DETAILED STATUS\n"
              << "--------------------------------------------------\n\n"
              << "Fuel Remaining     : " << finalFuel << "\n"
              << "Oxygen Remaining   : " << finalOxygen << "\n"
              << "Hull Integrity     : " << finalHull << "%\n\n"
              << "--------------------------------------------------\n"
              << "CREW DETAILED STATUS\n"
              << "--------------------------------------------------\n\n";

    for (const auto& c : crewStatus) {
        std::cout << c.role << " " << c.name << "    : Health " << c.health 
                  << (c.health > 0 ? "" : " (CRITICAL)") << "\n";
    }

    std::cout << "\n--------------------------------------------------\n"
              << "DETAILED EVENT HISTORY\n"
              << "--------------------------------------------------\n\n";
              
    if (eventsEncountered.empty()) {
        std::cout << "No major events encountered.\n";
    } else {
        int i = 1;
        for (const auto& evt : eventsEncountered) {
            std::cout << i++ << ". " << evt << "\n";
        }
    }

    std::cout << "\n--------------------------------------------------\n\n"
              << "Mission Conclusion : " << finalState << "\n\n"
              << "==================================================\n";
}
