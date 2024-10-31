#include "Problem.h"

Problem::Problem(std::vector<std::vector<int>> initial, std::vector<std::vector<int>> goal)
    : initial_state(initial), goal_state(goal) 
    {
    operators = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; 
    }
    // define the possible moves (up, down, left, right)
        //{0,1} move right
        //{1,0} move down
        //{0,-1} move left
        //{-1,0} move up



