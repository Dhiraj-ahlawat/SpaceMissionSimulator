#include "../include/Destination.h"
#include <iostream>

Destination::Destination() : name("Unknown"), distance(0.0), requiredFuel(0.0), difficulty(1) {}

Destination::Destination(const std::string& name, double distance, double requiredFuel, int difficulty)
    : name(name), distance(distance), requiredFuel(requiredFuel), difficulty(difficulty) {}

Destination::~Destination() {}

std::string Destination::getName() const { return name; }
double Destination::getDistance() const { return distance; }
double Destination::getRequiredFuel() const { return requiredFuel; }
int Destination::getDifficulty() const { return difficulty; }

void Destination::display() const {
    std::cout << "Destination: " << name << " | Distance: " << distance 
              << " | Required Fuel: " << requiredFuel << " | Difficulty: " << difficulty << "\n";
}
