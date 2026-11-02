#pragma once

#include <string>
#include "Spacecraft.h"

class SpaceEvent {
protected:
    std::string eventName;
    int severity;

public:
    SpaceEvent(const std::string& name, int severity);
    virtual ~SpaceEvent() = default;

    std::string getEventName() const;
    int getSeverity() const;

    virtual void trigger(Spacecraft& ship) = 0;
    virtual void displayDescription() const = 0;
};
