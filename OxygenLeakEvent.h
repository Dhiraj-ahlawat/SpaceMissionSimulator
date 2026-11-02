#pragma once
#include "SpaceEvent.h"

class OxygenLeakEvent : public SpaceEvent {
public:
    OxygenLeakEvent(int severity);
    void trigger(Spacecraft& ship) override;
    void displayDescription() const override;
};
