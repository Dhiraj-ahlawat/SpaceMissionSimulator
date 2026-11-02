#pragma once
#include "SpaceEvent.h"

class AsteroidEvent : public SpaceEvent {
public:
    AsteroidEvent(int severity);
    void trigger(Spacecraft& ship) override;
    void displayDescription() const override;
};
