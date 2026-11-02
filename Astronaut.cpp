#include "../include/Astronaut.h"
#include <iostream>

Astronaut::Astronaut(const std::string& name, int health, const std::string& roleName)
    : name(name), health(health), roleName(roleName) {
    if (this->health < 0) this->health = 0;
}

std::string Astronaut::getName() const { return name; }
int Astronaut::getHealth() const { return health; }
std::string Astronaut::getRoleName() const { return roleName; }

void Astronaut::takeDamage(int amount) {
    if (amount > 0) {
        health -= amount;
        if (health < 0) health = 0;
    }
}

// Commander
Commander::Commander(const std::string& name, int health, int leadershipSkill)
    : Astronaut(name, health, "Commander"), leadershipSkill(leadershipSkill) {}

void Commander::performDuty() {
    std::cout << "Commander " << name << " is leading the mission and making crucial decisions.\n";
}

// Pilot
Pilot::Pilot(const std::string& name, int health, int navigationSkill)
    : Astronaut(name, health, "Pilot"), navigationSkill(navigationSkill) {}

void Pilot::performDuty() {
    std::cout << "Pilot " << name << " is checking navigation and adjusting the flight path.\n";
}

// Scientist
Scientist::Scientist(const std::string& name, int health, int researchSkill)
    : Astronaut(name, health, "Scientist"), researchSkill(researchSkill) {}

void Scientist::performDuty() {
    std::cout << "Scientist " << name << " is analyzing scientific data and anomalies.\n";
}

// Engineer
Engineer::Engineer(const std::string& name, int health, int repairSkill)
    : Astronaut(name, health, "Engineer"), repairSkill(repairSkill) {}

void Engineer::performDuty() {
    std::cout << "Engineer " << name << " is inspecting spacecraft systems and performing maintenance.\n";
}
