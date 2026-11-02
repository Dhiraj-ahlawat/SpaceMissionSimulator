#include "../include/SolarStormEvent.h"
#include <iostream>

SolarStormEvent::SolarStormEvent(int severity)
    : SpaceEvent("Solar Storm", severity) {}

void SolarStormEvent::displayDescription() const {
    std::cout << "⚠ SOLAR STORM DETECTED!\n"
              << "Radiation levels increasing! Spacecraft systems affected.\n";
}

void SolarStormEvent::trigger(Spacecraft& ship) {
    displayDescription();
    double damage = severity * 5.0;
    
    ship.takeDamage(damage);
    std::cout << "Hull integrity reduced by " << damage << " points due to radiation bursts.\n";
}
