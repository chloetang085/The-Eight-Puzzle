#pragma once

#include <vector>
#include <utility>
#include <string>
#include "Node.h"
using namespace std;

// Represents the eight-puzzle problem, including initial and goal states, available moves, and search methods.
class Problem {
public:
    // Constructor to initialize the problem with a specified initial and goal state.
    Problem(const vector<vector<int>>& initial, const vector<vector<int>>& goal);

    // Getters for the initial and goal states.
    const vector<vector<int>>& get_initial_state() const;
    const vector<vector<int>>& get_goal_state() const;

    // Heuristic function that returns the number of misplaced tiles compared to the goal state.
    int misplaced_tile_heuristic(const vector<vector<int>>& state) const;

    // Heuristic function that calculates the Euclidean distance heuristic for the given state.
    int euclidean_distance_heuristic(const vector<vector<int>>& state) const;

    // Solves the problem using Uniform Cost Search (UCS).
    Node* uniform_cost_search();

    // Solves the problem using A* search with the Misplaced Tile heuristic.
    Node* misplaced_tile_A();

    // Solves the problem using A* search with the Euclidean Distance heuristic.
    Node* euclidean_distance_A();

    void display_puzzle(const vector<vector<int>>& state) const;

private:
    vector<vector<int>> initial_state;  // 2D vector representing the starting state of the puzzle.
    vector<vector<int>> goal_state;     // 2D vector representing the goal state of the puzzle.
    
    // Generic A* search function that accepts a heuristic function pointer.
    Node* a_star_search(int (Problem::*heuristic)(const vector<vector<int>>& state) const);

    // Helper function to convert a puzzle state to a unique string for hashing.
    string state_to_string(const vector<vector<int>>& state) const;

    // Helper function to find the position of the blank (zero) tile.
    pair<int, int> find_blank() const;
};
