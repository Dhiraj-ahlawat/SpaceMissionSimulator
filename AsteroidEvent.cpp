#include "../include/AsteroidEvent.h"
#include <iostream>

AsteroidEvent::AsteroidEvent(int severity)
    : SpaceEvent("Asteroid Field", severity) {}

void AsteroidEvent::displayDescription() const {
    std::cout << "⚠ ASTEROID FIELD DETECTED!\n"
              << "The spacecraft has encountered a dangerous asteroid field.\n";
}

void AsteroidEvent::trigger(Spacecraft& ship) {
    displayDescription();
    double damage = severity * 10.0;
    double fuelCost = severity * 20.0;
    
    std::cout << "Evasive maneuvers initiated...\n";
    if (ship.consumeFuel(fuelCost)) {
        std::cout << "Fuel consumed during evasion: " << fuelCost << "\n";
        damage *= 0.5; // Partial damage if successfully evaded
    } else {
        std::cout << "Insufficient fuel for evasion!\n";
    }
    
    ship.takeDamage(damage);
    std::cout << "Hull damaged by " << damage << " points.\n";
}
