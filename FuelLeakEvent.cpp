#include "../include/FuelLeakEvent.h"
#include <iostream>

FuelLeakEvent::FuelLeakEvent(int severity)
    : SpaceEvent("Fuel Leak", severity) {}

void FuelLeakEvent::displayDescription() const {
    std::cout << "⚠ FUEL LEAK DETECTED!\n"
              << "Fuel line rupture detected in main propulsion.\n";
}

void FuelLeakEvent::trigger(Spacecraft& ship) {
    displayDescription();
    double fuelLoss = severity * 25.0;
    
    ship.consumeFuel(fuelLoss);
    std::cout << "Fuel reduced by " << fuelLoss << " units.\n";
}
