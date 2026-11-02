# Space Mission Simulator

An interactive Space Mission Simulator implemented in C++ demonstrating core Object-Oriented Programming (OOP) design patterns and concepts.

## Overview

The Space Mission Simulator is a modular, console-based simulation that models space missions from pre-launch preparation to interplanetary transit, space hazard encounters, and orbital arrival.

### Key Features
- **Spacecraft Physical Systems:** Models fuel, life-support oxygen, and structural hull integrity.
- **Polymorphic Crew Roles:** Specialized astronaut roles (`Commander`, `Pilot`, `Scientist`, `Engineer`) offering unique tactical perks during transit and crisis mitigation.
- **Dynamic Space Hazards:** Random event handling including Asteroid Fields, Solar Storms, Fuel Leaks, and Oxygen Leaks.
- **State Machine Architecture:** Enforces pre-launch validation checks, stage-by-stage transit, and post-flight mission debriefing.
- **Persistence & Reporting:** File I/O manager to save and load mission states, alongside comprehensive mission performance report generation.

---

## Project Structure

```text
SpaceMissionSimulator/
├── include/               # Header declarations (.h)
│   ├── Astronaut.h
│   ├── Destination.h
│   ├── FileManager.h
│   ├── Mission.h
│   ├── MissionControl.h
│   ├── MissionReport.h
│   ├── Spacecraft.h
│   └── SpaceEvent.h
├── src/                   # Implementation files (.cpp)
│   ├── AsteroidEvent.cpp
│   ├── Astronaut.cpp
│   ├── Destination.cpp
│   ├── FileManager.cpp
│   ├── FuelLeakEvent.cpp
│   ├── Mission.cpp
│   ├── MissionControl.cpp
│   ├── MissionReport.cpp
│   ├── OxygenLeakEvent.cpp
│   ├── SolarStormEvent.cpp
│   ├── Spacecraft.cpp
│   └── SpaceEvent.cpp
├── data/                  # Mission state persistence & test files
├── SpaceMissionSimulator_Report/ # Academic report, documentation & screenshots
├── main.cpp               # Program entry point
├── Makefile               # Build script
└── README.md
```

---

## Build and Run

### Prerequisites
- C++17 compatible compiler (`g++` or `clang++`)
- `make`

### Building the Project
```bash
make
```

### Running the Simulator
```bash
./SpaceMissionSimulator
```

### Cleaning Build Artifacts
```bash
make clean
```

