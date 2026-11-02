#pragma once
#include "SpaceEvent.h"

class FuelLeakEvent : public SpaceEvent {
public:
    FuelLeakEvent(int severity);
    void trigger(Spacecraft& ship) override;
    void displayDescription() const override;
};
