#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "../src/robot.hpp"


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

    int steps = 0;

    auto start_time = std::chrono::steady_clock::now();

    while (true) {
        

        bool blocked = wall_in_front(robot, maze);
        bool was_visited = visited_in_front(robot, visited, maze);

        if (blocked || was_visited) {
            turn_left(robot);
        } else {
            move_forward(robot, maze);
        }

        visited[robot.y][robot.x] = true;
        steps++;

        if (at_goal(robot, maze)) {
            auto end_time = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                end_time - start_time
            ).count();

            draw_maze(maze, robot);
            std::cout << "\nGoal reached!\n";
            std::cout << "Steps: " << steps << "\n";
            std::cout << "Elapsed time: " << elapsed_ms << " ms (~"<< elapsed_ms / 1000.0 << " s)\n";
            break;
        }


        draw_maze(maze, robot);

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}