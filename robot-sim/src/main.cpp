#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

// 0=up, 1=right, 2=down, 3=left
struct Robot {
    int x;
    int y;
    int dir; 
};

// Simple maze: # = wall, . = empty
using Maze = std::vector<std::string>;

void draw_maze(const Maze& maze, const Robot& r) {
    
    std::cout << "\x1B[2J\x1B[H"; // Clear screen (not perfect)

    for (int y = 0; y < (int)maze.size(); ++y) {
        for (int x = 0; x < (int)maze[y].size(); ++x) {
            if (x == r.x && y == r.y) {
                std::cout << 'R';
            } else {
                std::cout << maze[y][x];
            }
        }
        std::cout << '\n';
    }
}

bool is_wall(const Maze& maze, int x, int y) {
    if (y < 0 || y >= (int)maze.size()) return true;
    if (x < 0 || x >= (int)maze[y].size()) return true;
    return maze[y][x] == '#';
}

bool wall_in_front(const Robot& r, const Maze& maze) {
    int nx = r.x;
    int ny = r.y;

    if (r.dir == 0) ny -= 1;      // up
    else if (r.dir == 1) nx += 1; // right
    else if (r.dir == 2) ny += 1; // down
    else if (r.dir == 3) nx -= 1; // left

    return is_wall(maze, nx, ny);
}

Robot find_robot_start(const Maze& maze) {
    for (int y = 0; y < (int)maze.size(); ++y) {
        for (int x = 0; x < (int)maze[y].size(); ++x) {
            if (maze[y][x] == 'O') {
                
                return Robot{x, y, 1}; //facing direction: right (1)
            }
        }
    }

    // If no O found, crash on purpose:
    std::cerr << "Error: No 'O' start position found in world.\n";
    exit(1);
}


void move_forward(Robot& r, const Maze& maze) {
    if (wall_in_front(r, maze)) return;

    if (r.dir == 0) r.y -= 1;
    else if (r.dir == 1) r.x += 1;
    else if (r.dir == 2) r.y += 1;
    else if (r.dir == 3) r.x -= 1;
}

void turn_left(Robot& r) {
    r.dir = (r.dir + 1) % 4;
}

bool visited_in_front(const Robot& r, const std::vector<std::vector<bool>>& visited, const Maze& maze)
{
    int nx = r.x;
    int ny = r.y;

    if (r.dir == 0) ny -= 1;
    else if (r.dir == 1) nx += 1;
    else if (r.dir == 2) ny += 1;
    else if (r.dir == 3) nx -= 1;

    // Treat out-of-bounds as visited (same idea as walls)
    if (ny < 0 || ny >= (int)visited.size()) return true;
    if (nx < 0 || nx >= (int)visited[0].size()) return true;

    return visited[ny][nx];
}

bool at_goal(const Robot& r, const Maze& maze) {
    return maze[r.y][r.x] == 'X'; //end program on "X"
}

int main() {
    Maze maze = {
        "####################",
        "#....#...#...#....#",
        "#.O#.#.#.#.#.#.#X.#",
        "#..#.#.#.#.#.#.#..#",
        "#..#.#.#.#.#.#.#..#",
        "#..#...#...#...#..#",
        "####################"
    };

    // Track visited cells
    std::vector<std::vector<bool>> visited(maze.size(), std::vector<bool>(maze[0].size(), false));

    Robot robot = find_robot_start(maze);

    while (true) {
        visited[robot.y][robot.x] = true;

        bool blocked = wall_in_front(robot, maze);
        bool was_visited = visited_in_front(robot, visited, maze);

        if (blocked || was_visited) {
            turn_left(robot);
        } else {
            move_forward(robot, maze);
        }

        if (at_goal(robot, maze)) {
        draw_maze(maze, robot);
        std::cout << "\nGoal reached, exiting...\n";
        break;
        }

        draw_maze(maze, robot);

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}