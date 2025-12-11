# C++ Robot Simulator

A simple grid-based robot simulator written in C++.  
The robot navigates a maze, avoids walls, tracks visited tiles, and locates a goal marked with **X**.

`O` marks the robot's starting position, `#` represents walls, and `.` represents free path tiles.

---

## Features

### Automatic Start Detection  
Robot automatically spawns at the tile marked **O** and begins facing right.

### Basic Navigation  
Robot moves through the maze using simple rules:
- Moves forward when possible  
- Turns left when blocked  
- Avoids revisiting previously visited tiles  

### Goal Detection  
Simulation ends immediately when the robot reaches the tile **X**.

### Estimated Time Tracking  
Tracks:
- Number of steps taken  
- Real execution time (ms)  

### Visit Tracking  
Keeps in mind of visited tiles to avoid loops and backtracking.

---

## GitHub CI Integration

A build-and-test pipeline that:
- Compiles the simulator on push / pull requests  
- Compiles and runs test cases  
- Fails PRs if tests fail  

Ensures stable and reliable behavior across changes.

---

## Technologies Used

- **C++20**
- **std::vector**, **std::chrono**, **std::thread**
- **GitHub Actions** for CI  

---

## Run Instructions

Compile:

g++ -std=c++20 -O2 src/main.cpp -o robot
./robot
