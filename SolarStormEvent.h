#pragma once
#include "SpaceEvent.h"

class SolarStormEvent : public SpaceEvent {
public:
    SolarStormEvent(int severity);
    void trigger(Spacecraft& ship) override;
    void displayDescription() const override;
};
