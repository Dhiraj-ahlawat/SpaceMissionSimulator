#include "../include/Spacecraft.h"
#include <iostream>

Spacecraft::Spacecraft() 
    : name("Unknown Ship"), fuel(0.0), oxygen(0.0), hullIntegrity(0.0), 
      engineHealth(100.0), navigationHealth(100.0), communicationHealth(100.0) {}

Spacecraft::Spacecraft(const std::string& name, double initialFuel, double initialOxygen, double initialHull)
    : name(name), fuel(initialFuel), oxygen(initialOxygen), hullIntegrity(initialHull),
      engineHealth(100.0), navigationHealth(100.0), communicationHealth(100.0) {
    if (fuel < 0) fuel = 0;
    if (oxygen < 0) oxygen = 0;
    if (hullIntegrity < 0) hullIntegrity = 0;
}

Spacecraft::~Spacecraft() {}

double Spacecraft::getFuel() const { return fuel; }
double Spacecraft::getOxygen() const { return oxygen; }
double Spacecraft::getHullIntegrity() const { return hullIntegrity; }
std::string Spacecraft::getName() const { return name; }

bool Spacecraft::consumeFuel(double amount) {
    if (amount < 0) return false;
    if (fuel >= amount) {
        fuel -= amount;
        return true;
    }
    return false;
}

bool Spacecraft::consumeOxygen(double amount) {
    if (amount < 0) return false;
    if (oxygen >= amount) {
        oxygen -= amount;
        return true;
    }
    return false;
}

void Spacecraft::addFuel(double amount) {
    if (amount > 0) fuel += amount;
}

void Spacecraft::addOxygen(double amount) {
    if (amount > 0) oxygen += amount;
}

void Spacecraft::takeDamage(double amount) {
    if (amount > 0) {
        hullIntegrity -= amount;
        if (hullIntegrity < 0) hullIntegrity = 0;
    }
}

void Spacecraft::repairHull(double amount) {
    if (amount > 0) {
        hullIntegrity += amount;
        if (hullIntegrity > 100.0) hullIntegrity = 100.0;
    }
}

void Spacecraft::restoreState(double fuel, double oxygen, double hullIntegrity) {
    if (fuel < 0) this->fuel = 0; else this->fuel = fuel;
    if (oxygen < 0) this->oxygen = 0; else this->oxygen = oxygen;
    if (hullIntegrity < 0) this->hullIntegrity = 0;
    else if (hullIntegrity > 100) this->hullIntegrity = 100;
    else this->hullIntegrity = hullIntegrity;
}

void Spacecraft::displayStatus() const {
    std::cout << "Spacecraft [" << name << "] Status:\n"
              << "  Fuel: " << fuel << "\n"
              << "  Oxygen: " << oxygen << "\n"
              << "  Hull Integrity: " << hullIntegrity << "%\n"
              << "  Engine Health: " << engineHealth << "%\n"
              << "  Navigation: " << navigationHealth << "%\n"
              << "  Communication: " << communicationHealth << "%\n";
}

bool Spacecraft::operator>(const Spacecraft& other) const {
    // Condition is based on the sum of fuel, oxygen and hull integrity.
    // Higher total value means the spacecraft is in a better overall condition.
    double conditionThis = fuel + oxygen + hullIntegrity;
    double conditionOther = other.fuel + other.oxygen + other.hullIntegrity;
    return conditionThis > conditionOther;
}
