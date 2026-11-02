#pragma once

#include <string>

class Destination {
private:
    std::string name;
    double distance;
    double requiredFuel;
    int difficulty;

public:
    Destination();
    Destination(const std::string& name, double distance, double requiredFuel, int difficulty);
    ~Destination();

    std::string getName() const;
    double getDistance() const;
    double getRequiredFuel() const;
    int getDifficulty() const;
    
    void display() const;
};
