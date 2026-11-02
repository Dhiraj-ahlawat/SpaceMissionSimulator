#pragma once

#include <string>

class Spacecraft {
private:
    std::string name;
    double fuel;
    double oxygen;
    double hullIntegrity;
    double engineHealth;
    double navigationHealth;
    double communicationHealth;

public:
    Spacecraft();
    Spacecraft(const std::string& name, double initialFuel, double initialOxygen, double initialHull);
    ~Spacecraft();

    double getFuel() const;
    double getOxygen() const;
    double getHullIntegrity() const;
    std::string getName() const;

    bool consumeFuel(double amount);
    bool consumeOxygen(double amount);
    void addFuel(double amount);
    void addOxygen(double amount);
    void takeDamage(double amount);
    void repairHull(double amount);
    
    void restoreState(double fuel, double oxygen, double hullIntegrity);

    void displayStatus() const;

    // Operator overloading: compares overall spacecraft condition
    bool operator>(const Spacecraft& other) const;
};
