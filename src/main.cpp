#include "PuzzleSolver.h"
#include "Problem.h"
#include <iostream>

void getUserPuzzle(vector<vector<int>>& initial_state)  //output to get input from user according to lab manual
{
    cout << "Enter your puzzle, use a zero to represent the blank" << std::endl;
    for (int i = 0; i < 3; ++i) 
    {
        cout << "Enter row " << i + 1 << " (use space or tabs between numbers): ";
        for (int j = 0; j < 3; ++j) 
        {
            std::cin >> initial_state[i][j];
        }
    }
}

int main() {
    cout << "Welcome to 862337526 & HUONG SID 8 puzzle solver" << "\n";
    cout << "type 1 to use a defualt puzzle, or 2 to enter your own puzzle" << "\n";
    int choice;
    cin >> choice; //get user choice (1 or 2 for default or custom puzzle)
    // define the initial and goal states for the puzzle
    vector<vector<int>> initial_state(3, vector<int>(3));
    vector<vector<int>> goal_state =
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    if (choice == 1)
    {   //default state
        initial_state = 
        {
            {1, 2, 3},
            {4, 8, 0},
            {7, 6, 5}
        };
    }
    else if (choice == 2)
    {
        getUserPuzzle(initial_state);   //cal getUserPuzzle function to form the user's puzzle
    }
    else
    {
        cout << "invalid choice" << "\n";
        return 1;
    }
   
   cout << "Initial Puzzle State:" << "\n";
   for (const auto& row : initial_state)
   {
    for (int num : row)
    {
        cout << num << " ";
    }
    cout << endl;
   }
    // create a problem instance
    Problem problem(initial_state, goal_state);

    // prompt user for algorithm choice
    cout << "Select an algorithm:\n";
    cout << "1) Uniform Cost Search\n";
    cout << "2) A* with Misplaced Tile Heuristic\n";
    cout << "3) A* with Euclidean Distance Heuristic\n";
    int algorithm_choice;
    cin >> algorithm_choice;    //get user puzzle

    //solve the puzzle
    PuzzleSolver solver(problem);
    solver.solve(choice);

    return 0;
}
