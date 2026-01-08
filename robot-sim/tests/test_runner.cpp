// robot-sim/tests/test_runner.cpp
#include "../src/robot.hpp"
#include <iostream>
#include <vector>

struct TestCase {
    const char* name;
    Maze maze;
    int max_steps;
};

static bool run_until_goal(Maze maze, int max_steps, int& out_steps) {
    Robot robot = find_robot_start(maze);
    maze[robot.y][robot.x] = '.'; // replace 'O' with path

    for (int steps = 0; steps < max_steps; ++steps) {

        // Right-hand rule:
        // 1) If right is open -> turn right + move
        // 2) Else if front is open -> move
        // 3) Else -> turn left
        if (!wall_on_right(robot, maze)) {
            turn_right(robot);
            move_forward(robot, maze);
        } else if (!wall_in_front(robot, maze)) {
            move_forward(robot, maze);
        } else {
            turn_left(robot);
        }

        if (at_goal(robot, maze)) {
            out_steps = steps + 1;
            return true;
        }
    }

    out_steps = max_steps;
    return false;
}

int main() {
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

    for (const auto& tc : cases) {
        int steps_taken = 0;
        bool ok = run_until_goal(tc.maze, tc.max_steps, steps_taken);

        if (ok) {
            std::cout << "PASS: " << tc.name << " (steps=" << steps_taken << ")\n";
        } else {
            std::cout << "FAIL: " << tc.name << " (hit max_steps=" << tc.max_steps << ")\n";
            failed++;
        }
    }

    if (failed > 0) {
        std::cerr << failed << " test(s) failed.\n";
        return 1;
    }

    std::cout << "All tests passed.\n";
    return 0;
}
