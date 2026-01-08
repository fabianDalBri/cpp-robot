# C++ Robot Simulator

A simple grid-based robot simulator written in C++.  
The robot navigates a maze using deterministic navigation rules and locates a goal marked with **X**.

`O` marks the robot's starting position, `#` represents walls, and `.` represents free path tiles.

---

## Features

### Automatic Start Detection  
The robot automatically spawns at the tile marked **O** and begins facing right.

### Basic Navigation  
The robot navigates the maze using the **right-hand wall-following rule**:
- Prefers turning right when possible  
- Moves forward when the path ahead is clear  
- Turns left when blocked  

This allows the robot to solve mazes with dead ends and loops without getting stuck.

### Goal Detection  
The simulation ends immediately when the robot reaches the tile **X**.

### Estimated Time Tracking  
Tracks:
- Number of steps taken  
- Execution time (ms)  

### Visit Tracking  
The robot avoids trivial oscillation and infinite loops through deterministic movement rules rather than banning revisits outright.

---

## Testing Support

Includes a reusable test runner that verifies robot navigation logic:
- Runs multiple predefined mazes in a single executable  
- Executes navigation for a fixed maximum number of steps  
- Fails if the robot does not reach the goal  

Tests run automatically in GitHub Actions and locally via the terminal.

---

## GitHub CI Integration

A build-and-test pipeline that:
- Compiles the robot logic and test runner on push / pull requests  
- Executes all maze test cases  
- Fails PRs if any test case fails  

This ensures stable and reliable behavior across changes.

---

## Technologies Used

- **C++20**
- **std::vector**, **std::chrono**, **std::thread**
- **GitHub Actions** for CI  
- Standalone C++ test runner (no external test framework)

---

## Run Instructions

### Run automated tests (recommended)

```bash
g++ -std=c++20 -O2 robot-sim/tests/test_runner.cpp robot-sim/src/robot.cpp -o robot-sim/build/test_runner
./robot-sim/build/test_runner
