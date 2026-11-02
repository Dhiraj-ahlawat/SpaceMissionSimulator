#pragma once

#include "Mission.h"

class MissionReport {
private:
    std::string missionName;
    std::string destinationName;
    std::string finalState;
    int currentStage;
    int totalStages;
    std::vector<std::string> eventsEncountered;
    double finalFuel;
    double finalOxygen;
    double finalHull;
    
    struct CrewStatus {
        std::string name;
        std::string role;
        int health;
    };
    std::vector<CrewStatus> crewStatus;

public:
    MissionReport(const Mission& mission);
    void generate() const;
    void generate(bool detailed) const; // Overloaded
};
