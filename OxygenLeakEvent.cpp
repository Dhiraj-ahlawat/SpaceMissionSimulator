#include "../include/OxygenLeakEvent.h"
#include <iostream>

OxygenLeakEvent::OxygenLeakEvent(int severity)
    : SpaceEvent("Oxygen Leak", severity) {}

void OxygenLeakEvent::displayDescription() const {
    std::cout << "⚠ OXYGEN LEAK DETECTED!\n"
              << "Emergency oxygen systems activated.\n";
}

void OxygenLeakEvent::trigger(Spacecraft& ship) {
    displayDescription();
    double oxygenLoss = severity * 15.0; // 15 units per severity
    
    ship.consumeOxygen(oxygenLoss); // consumeOxygen returns bool but we ignore failure here
    std::cout << "Oxygen reduced by " << oxygenLoss << " units.\n";
}
