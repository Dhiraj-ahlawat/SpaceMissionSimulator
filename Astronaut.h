#pragma once

#include <string>

class Astronaut {
protected:
    std::string name;
    int health;
    std::string roleName;

public:
    Astronaut(const std::string& name, int health, const std::string& roleName);
    virtual ~Astronaut() = default; // Modern C++ virtual destructor

    virtual void performDuty() = 0; // Pure virtual function

    std::string getName() const;
    int getHealth() const;
    std::string getRoleName() const;

    void takeDamage(int amount);

    virtual int getLeadershipSkill() const { return 0; }
    virtual int getNavigationSkill() const { return 0; }
    virtual int getResearchSkill() const { return 0; }
    virtual int getRepairSkill() const { return 0; }
};

class Commander : public Astronaut {
private:
    int leadershipSkill;
public:
    Commander(const std::string& name, int health, int leadershipSkill);
    void performDuty() override;
    int getLeadershipSkill() const override { return leadershipSkill; }
};

class Pilot : public Astronaut {
private:
    int navigationSkill;
public:
    Pilot(const std::string& name, int health, int navigationSkill);
    void performDuty() override;
    int getNavigationSkill() const override { return navigationSkill; }
};

class Scientist : public Astronaut {
private:
    int researchSkill;
public:
    Scientist(const std::string& name, int health, int researchSkill);
    void performDuty() override;
    int getResearchSkill() const override { return researchSkill; }
};

class Engineer : public Astronaut {
private:
    int repairSkill;
public:
    Engineer(const std::string& name, int health, int repairSkill);
    void performDuty() override;
    int getRepairSkill() const override { return repairSkill; }
};
