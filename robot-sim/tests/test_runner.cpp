// Include the robot logic (NO main() here, just functions + structs)
#include "../src/robot.hpp"

#include <iostream>
#include <vector>


// A single test case definition.
// Each test case has:
struct TestCase {
    const char* name;   // test name printed in output
    Maze maze;          // maze data (O=start, X=goal)
    int max_steps;      // safety limit to avoid infinite loops
};


// Runs the robot simulation until either:
//  - the robot reaches the goal (X) -> returns true
//  - max_steps is exceeded           -> returns false
//
// maze is passed by VALUE on purpose:
// each test gets its own copy so tests don't affect each other.
static bool run_until_goal(Maze maze, int max_steps, int& out_steps) {

    // Track which tiles were already visited
    std::vector<std::vector<bool>> visited(
        maze.size(),
        std::vector<bool>(maze[0].size(), false)
    );

    // Find the robot start position (marked with 'O')
    Robot robot = find_robot_start(maze);

    // Replace the start tile with normal path
    // so the robot can move over it like any other '.'
    maze[robot.y][robot.x] = '.';

    int prev_x = robot.x;
    int prev_y = robot.y;

    for (int steps = 0; steps < max_steps; ++steps) {

        // Compute where we'd go if we moved forward
        auto [nx, ny] = next_cell_in_front(robot);

        bool blocked = is_wall(maze, nx, ny);

        // A) avoid immediate backtracking:
        // if moving forward would go to the tile we were just on, treat it like blocked
        bool immediate_backtrack = (nx == prev_x && ny == prev_y);

        if (blocked || immediate_backtrack) {
            turn_left(robot);
        } else {
            // store current position as "previous" BEFORE moving
            prev_x = robot.x;
            prev_y = robot.y;

            move_forward(robot, maze);
        }

        if (at_goal(robot, maze)) {
            out_steps = steps + 1;
            return true;
        }
    }


        // Failed to reach goal within step limit
        out_steps = max_steps;
        return false;
    }


// Program entry point for ALL tests.
// One executable, many mazes.
int main() {

    // List of all test cases
    std::vector<TestCase> cases = {

        {
            "simple_line",
            {
                "#########",
                "#O.....X#",
                "#########"
            },
            200
        },

        {
            "dead_end",
            {
                "#############",
                "#O....#.....#",
                "###.#.#.###.#",
                "#...#...#X#.#",
                "#.#######.#.#",
                "#.........#.#",
                "#############"
            },
            2000
        },

        {
            "loopy",
            {
                "###############",
                "#O..........#X#",
                "#.#########.#.#",
                "#.#.......#.#.#",
                "#.#.#####.#.#.#",
                "#.#.#...#.#.#.#",
                "#...#...#.....#",
                "###############"
            },
            4000
        }
    };

    int failed = 0;

    // Run all test cases
    for (const auto& tc : cases) {
        int steps_taken = 0;

        bool success = run_until_goal(
            tc.maze,
            tc.max_steps,
            steps_taken
        );

        if (success) {
            std::cout << "PASS: " << tc.name
                      << " (steps=" << steps_taken << ")\n";
        } else {
            std::cout << "FAIL: " << tc.name
                      << " (hit max_steps=" << tc.max_steps << ")\n";
            failed++;
        }
    }

    // If any test failed, return non-zero exit code
    if (failed > 0) {
        std::cerr << failed << " test(s) failed.\n";
        return 1;
    }

    std::cout << "All tests passed.\n";
    return 0;
}
