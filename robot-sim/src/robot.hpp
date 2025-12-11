#pragma once
#include <vector>
#include <string>

struct Robot {
    int x;
    int y;
    int dir; // 0 = up, 1 = right, 2 = down, 3 = left
};

using Maze = std::vector<std::string>;

Robot find_robot_start(const Maze& maze);
bool  at_goal(const Robot& r, const Maze& maze);
void draw_maze(const Maze& maze, const Robot& r);

bool is_wall(const Maze& maze, int x, int y);
bool wall_in_front(const Robot& r, const Maze& maze);
void move_forward(Robot& r, const Maze& maze);
void turn_left(Robot& r);

bool visited_in_front(const Robot& r,
                      const std::vector<std::vector<bool>>& visited,
                      const Maze& maze);