#pragma once

#include "Mission.h"
#include <string>

class FileManager {
private:
    static int totalSaveOperations;

    std::vector<std::string> splitString(const std::string& str, char delimiter) const;
    MissionState parseState(const std::string& str) const;

public:
    static int getTotalSaveOperations();
    
    bool saveMission(const Mission& mission, const std::string& filename);
    bool loadMission(Mission& mission, const std::string& filename);
};
