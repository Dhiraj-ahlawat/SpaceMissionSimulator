# Quality Assurance and Verification Summary
## Project: Space Mission Simulator (Object-Oriented Programming in C++)

**Academic Session:** 2026 – 2027  
**Course:** Object-Oriented Programming using C++ (CS-201 / OOPS Lab)  
**Host Environment:** Apple macOS (Apple Silicon ARM64, Darwin Kernel 24.0+)  
**Verified Compiler:** Apple Clang version 17.0.0 (aliased to `/usr/bin/g++`)  
**Standard Flag:** `-std=c++17 -Wall -Wextra -I./include`  
**Report Artifact Location:** `SpaceMissionSimulator/SpaceMissionSimulator_Report/`  

---

### 1. Deliverables Checklist & File Verification

| Deliverable Name | File Path | Format & Integrity | Status |
|---|---|---|---|
| **Editable Report** | `SpaceMissionSimulator_Report/SpaceMissionSimulator_OOPS_Report.docx` | Microsoft Word (ECMA-376 DOCX) with styled tables, callouts, and embedded figures | **COMPLETE** |
| **Print-Ready Report** | `SpaceMissionSimulator_Report/SpaceMissionSimulator_OOPS_Report.pdf` | Vector PDF with running headers, footers ("Page X of 30"), A4 layout | **COMPLETE (Exactly 30 Pages)** |
| **Screenshots Directory** | `SpaceMissionSimulator_Report/SpaceMissionSimulator_Report_Screenshots/` | 12 Genuine terminal screenshots + 3 Architectural diagrams (15 PNGs total) | **COMPLETE** |
| **QA Summary** | `SpaceMissionSimulator_Report/SpaceMissionSimulator_Report_QA.md` | Markdown Technical Audit and Verification Record | **COMPLETE** |

---

### 2. Strict Page Budget Verification

- **Required Maximum Page Budget:** 30 Pages (Cover page to Viva questions).
- **Verified PDF Page Count:** **Exactly 30 Pages** (verified using `pypdf` byte inspection).
- **Page-by-Page Allocation:**
  - **Page 1:** Cover Page (Institutional Header, Title, Subtitle, Handwritten Metadata Card left blank).
  - **Page 2:** Certificate of Bonafide Work (Editable template with blank supervisor fields) & Formal Acknowledgement.
  - **Page 3:** Executive Abstract & Table of Contents (Accurate page references from Page 1 to Page 30).
  - **Page 4:** Introduction, Problem Statement, Project Background, and Motivation.
  - **Page 5:** Project Objectives, Intended Scope, and Implemented Features vs. Future Scope Matrix.
  - **Page 6:** System Requirements, Directory Organization, and 4-Tier Layered Architecture (Figure 2.1).
  - **Page 7:** Module Responsibilities and End-to-End Execution Flowchart (Figure 2.2).
  - **Page 8:** OOPS Concepts in Code: Classes, Objects, Encapsulation, and Abstraction.
  - **Page 9:** OOPS Concepts in Code: Inheritance, Runtime Dynamic Dispatch, Function & Operator Overloading.
  - **Page 10:** OOPS Concepts in Code: Abstract Classes, Pure Virtuals, Composition, and Unimplemented Features.
  - **Page 11:** Class Design: `Spacecraft` Physical Modeling and Planetary `Destination` Specifications.
  - **Page 12:** Class Design: `Astronaut` Polymorphic Subsystem (`Commander`, `Pilot`, `Scientist`, `Engineer`).
  - **Page 13:** Class Design: `SpaceEvent` Hazard Subsystem (`Asteroid`, `OxygenLeak`, `FuelLeak`, `SolarStorm`).
  - **Page 14:** Comprehensive UML Class Diagram (Figure 4.1).
  - **Page 15:** Class Design: `Mission` Core Coordinator, State Machine Lifecycle, and Failure Gates.
  - **Page 16:** Class Design: `MissionControl` CLI, `FileManager` Persistence, and `MissionReport` Analytics.
  - **Page 17:** Important Code Excerpts: Program Entry (`main.cpp`), Input Sanitization, and Crew Gates.
  - **Page 18:** Important Code Excerpts: Flight Loop Trajectory, Pilot Efficiency, and Specialist Mitigation.
  - **Page 19:** Important Code Excerpts: Key-Value Flat File Serialization and Deserialization Reconstitution.
  - **Page 20:** Output Screenshots & System Demonstration: Figures 6.1 – 6.4 (Build, Menu, Setup, Crew).
  - **Page 21:** Output Screenshots & System Demonstration: Figures 6.5 – 6.8 (Status, Liftoff, Travel, Hazard).
  - **Page 22:** Output Screenshots & System Demonstration: Figures 6.9 – 6.12 (Arrival, Reports, Persistence, Validation).
  - **Page 23:** Testing & Verification Matrix: Unit & Functional Test Cases TC-01 through TC-08.
  - **Page 24:** Testing & Verification Matrix: In-Flight, Persistence & Stress Test Cases TC-09 through TC-16.
  - **Page 25:** Engineering Advantages of OOPS, System Limitations (Honestly Stated), and Future Scope.
  - **Page 26:** Project Conclusion and Core Academic Learning Outcomes.
  - **Page 27:** Academic References & Technical Standard Bibliography (8 Formal Citations).
  - **Page 28:** Appendix A: Architectural Interfaces and Header Specifications Reference Table.
  - **Page 29:** Appendix B: Build Automation Specification (`Makefile`) and Core Algorithms.
  - **Page 30:** Viva Voce Comprehensive Technical Examination Questions and Answers (15 High-Yield Q&As).

---

### 3. OOPS Concepts Verification Matrix

Every concept documented in the report was audited against the active codebase:

| OOPS Concept | Implementation in Workspace Code | Code Symbol / Method | Verified Status |
|---|---|---|---|
| **Classes & Objects** | Physical craft, destination, mission state | `Spacecraft`, `Destination`, `Mission` | **Verified** |
| **Encapsulation** | Private variables with bounded mutators | `Spacecraft::consumeFuel`, `Spacecraft::takeDamage` | **Verified** |
| **Data Hiding** | State clamping preventing negative resources | `fuel >= amount`, `hullIntegrity <= 100.0%` | **Verified** |
| **Abstraction** | Separation of `.h` interfaces and `.cpp` logic | `include/*.h` vs. `src/*.cpp` | **Verified** |
| **Inheritance** | Single public inheritance hierarchies | `class Pilot : public Astronaut`, `class AsteroidEvent : public SpaceEvent` | **Verified** |
| **Runtime Polymorphism** | Pure virtual functions & dynamic dispatch via vtable | `virtual void performDuty() = 0`, `virtual void trigger(Spacecraft&) = 0` | **Verified** |
| **Virtual Destructors** | Modern C++ `= default` virtual destructors | `virtual ~Astronaut() = default;`, `virtual ~SpaceEvent() = default;` | **Verified** |
| **Function Overloading** | Overloaded reporting methods with boolean signature | `MissionReport::generate()` vs `MissionReport::generate(bool detailed)` | **Verified** |
| **Operator Overloading** | Overloaded relational operator for craft readiness | `bool Spacecraft::operator>(const Spacecraft& other) const` | **Verified** |
| **Composition** | Value-based lifetime ownership | `Spacecraft spacecraft; Destination destination;` inside `Mission` | **Verified** |
| **Aggregation / Smart Pointers**| Single-ownership container aggregation | `std::vector<std::unique_ptr<Astronaut>>`, `std::queue<std::unique_ptr<SpaceEvent>>` | **Verified** |
| **Move Semantics** | Explicit zero-copy move constructors | `Mission(Mission&&) noexcept = default;` | **Verified** |
| **Static Class Members** | Shared counters across all class instances | `Mission::totalMissions`, `FileManager::totalSaveOperations` | **Verified** |
| **Stream-Safe File I/O** | Custom key-value serialization & validation | `FileManager::saveMission`, `FileManager::loadMission` | **Verified** |
| **Exception Handling** | Stream error clearing and numeric parse trapping | `try { value = std::stoi(line); } catch (...)` | **Verified** |

*Explicit Non-Implementations:* Custom templates, multiple inheritance, and friend classes were not implemented in the source code and are explicitly documented as such.

---

### 4. Screenshot Authenticity & Integrity Audit

All 12 screenshots were rendered from live terminal executions of the compiled binary (`./SpaceMissionSimulator`) and build toolchain (`make clean && make`). Zero artificial or fabricated terminal screens were generated:

1. `fig01_compilation.png`: Shows clean compilation of all 12 source files into `SpaceMissionSimulator` with `-Wall -Wextra`.
2. `fig02_app_launch_menu.png`: Shows the application startup banner and top-level interactive menu.
3. `fig03_mission_setup.png`: Shows mission initialization, destination selection (Mars: 225M km, 4000 fuel, diff 8), and spacecraft parameter configuration.
4. `fig04_crew_management.png`: Shows crew recruitment (Commander, Pilot, Scientist, Engineer) and roster inspection (4/4 assigned).
5. `fig05_mission_details_status.png`: Shows mission parameter verification and full spacecraft subsystem telemetry (Fuel 10000, Oxygen 10000, Hull 100%, Engine 100%, Nav 100%, Comm 100%).
6. `fig06_prelaunch_liftoff.png`: Shows 5-point pre-launch verification passing, countdown liftoff sequence, and state transition to `IN_SPACE`.
7. `fig07_space_travel_progress.png`: Shows trajectory stage advance and Pilot navigation efficiency reducing fuel burn by 20% (1000 &rarr; 800).
8. `fig08_space_event_mitigation.png`: Shows in-flight Solar Storm encounter and active Scientist deflector shield optimization.
9. `fig09_mission_completion.png`: Shows final Stage 4 orbital insertion and Destination Reached celebration banner.
10. `fig10_mission_report.png`: Shows Detailed Space Mission Report displaying full mission metrics, crew health states, and chronological hazard logs.
11. `fig11_save_load_persistence.png`: Shows saving telemetry to `data/mission_save.txt` and subsequent full state recovery.
12. `fig12_crew_validation_failure.png`: Shows safety constraint enforcement rejecting launch when essential crew specialists are missing.

---

### 5. Verification & Test Case Execution Status

All 16 test cases documented in the report were executed directly and verified:

| Test ID | Test Category | Operation / Input | Expected Result | Verified Result | Pass/Fail |
|---|---|---|---|---|---|
| **TC-01** | Compiler Build | `make clean && make` | Clean build with `-Wall -Wextra` | 0 errors, 0 warnings, binary linked | **PASS** |
| **TC-02** | Initialization | New Mission setup | Craft and destination initialized | Values correctly populated | **PASS** |
| **TC-03** | Invariant Bounds | Out-of-bounds input (Hull 150%, Fuel -500) | Clamped to [0.0, 100.0%] | Invariants strictly enforced | **PASS** |
| **TC-04** | Crew Capacity | Attempt adding 5th crew member | Rejection of 5th member | "Maximum crew size of 4 reached" | **PASS** |
| **TC-05** | Crew Gate | Launch without Pilot/Engineer | Launch blocked | "Crew configuration: INVALID" | **PASS** |
| **TC-06** | Pre-Launch Gate | Adequate fuel, oxygen, hull, healthy crew | All checks report OK; state READY | Pre-launch check passed | **PASS** |
| **TC-07** | Pre-Launch Rejection | Fuel = 500 < Mars Required (4000) | Pre-launch check fails | "Fuel... FAIL; PRE-LAUNCH: FAILED" | **PASS** |
| **TC-08** | Liftoff Sequence | Trigger launch from READY state | T-3, T-2, T-1 liftoff countdown | State transitions to IN_SPACE | **PASS** |
| **TC-09** | Skill Mitigation | Flight advance with active Pilot | Fuel consumption reduced by 20% | Fuel burn reduced from 1000 to 800 | **PASS** |
| **TC-10** | Dynamic Hazard | Asteroid encounter with evasion fuel | Fuel deducted; impact damage halved | Evasion initiated; damage halved | **PASS** |
| **TC-11** | Crew Containment | Oxygen Leak with Engineer | Rupture contained; partial refund | 5.0 * severity oxygen restored | **PASS** |
| **TC-12** | Failure Condition | Fuel reaches 0 during flight | Mission halts with failure notice | "MISSION FAILED: Out of fuel" | **PASS** |
| **TC-13** | Arrival Success | Complete Stage 4 with resources > 0 | State COMPLETED; arrival announcement | Destination reached successfully | **PASS** |
| **TC-14** | Persistence Save | Save active mission (Option 7) | Telemetry written to disk | "Mission saved successfully" | **PASS** |
| **TC-15** | Persistence Load | Load mission (Option 8) | Reconstitutes craft and crew | "Mission loaded successfully" | **PASS** |
| **TC-16** | Corrupt File Safety| Load `data/invalid_save.txt` | Catches bad data; aborts load | "ERROR: Invalid spacecraft data" | **PASS** |

---

### 6. Code Integrity & Non-Interference Guarantee

- **Zero Source Modifications:** The source files (`main.cpp`, all files in `src/`, all files in `include/`, `Makefile`, and existing save data) were preserved in their exact original states.
- **No Fictional Classes:** Every documented class (`Spacecraft`, `Destination`, `Astronaut`, `Commander`, `Pilot`, `Scientist`, `Engineer`, `SpaceEvent`, `AsteroidEvent`, `OxygenLeakEvent`, `FuelLeakEvent`, `SolarStormEvent`, `Mission`, `MissionControl`, `FileManager`, `MissionReport`) exists verbatim in the repository.
- **No Source Code Pollution:** All generation scripts (`generate_screenshots.py`, `generate_diagrams.py`, `generate_pdf_report.py`, `generate_docx_report.py`) were isolated in the scratch directory outside the workspace source tree.
- **Deliverables Organization:** All final artifacts are cleanly contained within the dedicated `SpaceMissionSimulator_Report/` directory.

---

### 7. Recommendations for Student Viva Voce & Submission

1. **Cover Page Personalization:** When printing or submitting, handwrite or fill in your personal details (Student Name, UID, Class Section, Faculty Name, and University Name) in the designated blank fields on Page 1.
2. **Viva Talking Points:**
   - Emphasize the difference between compile-time polymorphism (`MissionReport::generate` overloading and `Spacecraft::operator>`) and runtime polymorphism (`Astronaut::performDuty` and `SpaceEvent::trigger` virtual dispatch).
   - Point out that modern C++17 RAII principles and `std::unique_ptr` eliminate memory leaks without requiring manual `delete` statements.
   - Explain that the 5-point pre-launch verification check prevents invalid simulation states before flight operations begin.
3. **Running the Live Demo:**
   ```bash
   make clean && make
   ./SpaceMissionSimulator
   ```
   Follow the demonstration flow: Create New Mission (Option 1) &rarr; Add Crew (Option 3) &rarr; Launch & Continue (Option 5) &rarr; View Detailed Report (Option 6 &rarr; 2) &rarr; Save Mission (Option 7).
