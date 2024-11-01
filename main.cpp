#include "Problem.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to get puzzle input from the user
void get_user_puzzle(vector<vector<int>>& initial_state) {
    cout << "Enter your puzzle, use a '*' to represent the blank" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << "Enter row " << i + 1 << " (use space or tabs between numbers): ";
        for (int j = 0; j < 3; ++j) {
            string input;
            cin >> input;

            if (input == "*") {
                initial_state[i][j] = 0; // Internally represent '*' as 0
            } else {
                initial_state[i][j] = stoi(input);
            }
        }
    }
}

// Function to display solution actions, accessing `parent` and `action` directly
void display_solution(Node* goal_node) {
    if (!goal_node) {
        cout << "No solution found." << endl;
        return;
    }

    vector<string> actions;
    Node* current = goal_node;
    while (current->parent) {  // Traverse using parent pointer directly
        actions.push_back(current->action);  // Access action directly
        current = current->parent;  // Move to parent
    }

    cout << "Solution found in " << actions.size() << " steps:" << endl;
    for (auto it = actions.rbegin(); it != actions.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    // Print welcome message and get puzzle choice
    cout << "Welcome to the puzzle solver" << endl;
    cout << "Type 1 to use a default puzzle, or 2 to enter your own puzzle" << endl;
    int choice;
    cin >> choice;

    vector<vector<int>> initial_state(3, vector<int>(3));
    vector<vector<int>> goal_state = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    // Select puzzle state based on user choice
    if (choice == 1) {
        initial_state = {
            {1, 2, 3},
            {4, 8, 0},
            {7, 6, 5}
        };
    } else if (choice == 2) {
        get_user_puzzle(initial_state);
    } else {
        cout << "Invalid choice. Exiting." << endl;
        return 1;
    }

    cout << "\nInitial Puzzle State:" << endl;
    // Create a Problem instance
    Problem problem(initial_state, goal_state);
    problem.display_puzzle(initial_state); // Display the puzzle with * for the blank


    // Prompt user for search algorithm
    cout << "\nChoose search algorithm:" << endl;
    cout << "1. Uniform Cost Search" << endl;
    cout << "2. A* with Misplaced Tile heuristic" << endl;
    cout << "3. A* with Euclidean Distance heuristic" << endl;
    int algorithm_choice;
    cin >> algorithm_choice;

    Node* solution = nullptr;

    // Execute the chosen search algorithm
    switch (algorithm_choice) {
        case 1:
            cout << "Running Uniform Cost Search..." << endl;
            solution = problem.uniform_cost_search();
            break;
        case 2:
            cout << "Running A* with Misplaced Tile heuristic..." << endl;
            solution = problem.misplaced_tile_A();
            break;
        case 3:
            cout << "Running A* with Euclidean Distance heuristic..." << endl;
            solution = problem.euclidean_distance_A();
            break;
        default:
            cout << "Invalid choice. Exiting." << endl;
            return 0;
    }

    // Display the solution path
    display_solution(solution);

    return 0;
}
