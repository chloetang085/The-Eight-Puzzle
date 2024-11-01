#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H

#include "Problem.h"
#include "Node.h"
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <algorithm>


class PuzzleSolver {
public:
    // constructor
    PuzzleSolver(const Problem& problem);

    // function that solves the puzzle
    void solve(int algorithmChoice);

private:
    Problem problem;

    pair<int, int> directions[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Directions for blank tile movement

    // helper functions
    int misplacedTiles(const vector<vector<int>>& state);
    int euclideanDistance(const vector<vector<int>>& state);
    bool isGoal(const vector<vector<int>>& state);
    void printSolution(Node* node);
    
    // search algorithms
    void uniformCostSearch();
    void aStarSearch(const string& heuristic);

    // utility functions
    string hashState(const vector<vector<int>>& state);
    pair<int, int> findBlank(const vector<vector<int>>& state);
    vector<vector<int>> moveBlank(const vector<vector<int>>& state, pair<int, int> blank_pos, pair<int, int> dir);
};

#endif