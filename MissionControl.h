#pragma once

#include <memory>
#include <string>
#include "Mission.h"
#include "FileManager.h"

class MissionControl {
private:
    std::unique_ptr<Mission> currentMission;
    FileManager fileManager;

    void displayMenu() const;
    void createNewMission();
    void viewMissionDetails() const;
    void manageCrew();
    void viewSpacecraftStatus() const;
    void launchOrContinueMission();
    void viewMissionReport() const;
    void saveCurrentMission();
    void loadMission();
    void abortCurrentMission();

    int getIntInput(const std::string& prompt) const;
    double getDoubleInput(const std::string& prompt) const;
    std::string getStringInput(const std::string& prompt) const;

public:
    MissionControl();
    void run();
};
