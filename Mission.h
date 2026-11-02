#pragma once

#include <string>
#include <vector>
#include <queue>
#include <memory>
#include "Spacecraft.h"
#include "Destination.h"
#include "Astronaut.h"
#include "SpaceEvent.h"

enum class MissionState {
    PREPARING,
    READY,
    LAUNCHED,
    IN_SPACE,
    COMPLETED,
    FAILED,
    ABORTED
};

class Mission {
private:
    std::string missionName;
    Spacecraft spacecraft;
    Destination destination;
    std::vector<std::unique_ptr<Astronaut>> crew;
    std::queue<std::unique_ptr<SpaceEvent>> events;

    MissionState state;
    int currentStage;
    int totalStages;
    std::vector<std::string> eventHistory; // Phase 5 history

    static int totalMissions; // Static member

    void checkFailureConditions();

public:
    Mission();
    Mission(const std::string& missionName, const Destination& destination, const Spacecraft& spacecraft);
    ~Mission();

    // Enable move semantics (required for FileManager)
    Mission(Mission&&) noexcept = default;
    Mission& operator=(Mission&&) noexcept = default;

    // Getters
    const std::string& getMissionName() const;
    const Destination& getDestination() const;
    const Spacecraft& getSpacecraft() const;
    int getCurrentStage() const;
    int getTotalStages() const;
    const std::vector<std::unique_ptr<Astronaut>>& getCrew() const;
    const std::vector<std::string>& getEventHistory() const;
    MissionState getState() const;

    // Setters / Restorers for Phase 5
    void restoreMissionState(MissionState state, int currentStage, int totalStages);
    void clearCrew();
    void addEventToHistory(const std::string& evt);
    
    void addAstronaut(std::unique_ptr<Astronaut> astronaut);
    void displayMissionDetails() const;
    void displayCrew() const;
    
    void addEvent(std::unique_ptr<SpaceEvent> event);
    void triggerNextEvent();
    void displayEvents() const;
    void generateRandomEvent();

    // Phase 4 methods
    bool performPreLaunchChecks();
    bool launch();
    bool advanceTravel();
    void runMission();
    void abortMission();
    std::string getStateString() const;

    static int getTotalMissions(); // Static getter
};
