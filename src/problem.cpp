#include "Problem.h"
#include <queue>
#include <unordered_set>
#include <cmath>
#include <iostream>

// Comparator for the priority queue based on f = g + h.
struct NodeComparator {
    bool operator()(Node* a, Node* b) {
        return a->get_total_cost() > b->get_total_cost();
    }
};

// Constructor: Initializes the problem with initial and goal states.
Problem::Problem(const vector<vector<int>>& initial, const vector<vector<int>>& goal)
    : initial_state(initial), goal_state(goal) {}

// Getters for initial and goal states.
const vector<vector<int>>& Problem::get_initial_state() const {
    return initial_state;
}

const vector<vector<int>>& Problem::get_goal_state() const {
    return goal_state;
}

// Misplaced tile heuristic: Counts tiles in the wrong position.
int Problem::misplaced_tile_heuristic(const vector<vector<int>>& state) const {
    int misplaced = 0;
    for (unsigned i = 0; i < state.size(); ++i) {
        for (unsigned j = 0; j < state.at(i).size(); ++j) {
            if (state[i][j] != 0 && state[i][j] != goal_state[i][j]) {
                ++misplaced; //increment if the tile is not in its goal position
            }
        }
    }
    return misplaced;
}

// Euclidean distance heuristic: Calculates the total Euclidean distance of tiles to their goal positions.
int Problem::euclidean_distance_heuristic(const vector<vector<int>>& state) const {
    int distance = 0;
    for (unsigned i = 0; i < state.size(); ++i) {
        for (unsigned j = 0; j < state.at(i).size(); ++j) {
            if (state[i][j] != 0) { //skip blank tile
                int target_x = (state[i][j] - 1) / 3;
                int target_y = (state[i][j] - 1) % 3;
                distance += sqrt(pow(i - target_x, 2) + pow(j - target_y, 2)); //formula
            }
        }
    }
    return distance;
}

// Helper function to convert a puzzle state to a unique string for the explored set.
string Problem::state_to_string(const vector<vector<int>>& state) const {
    string hash;
    for (const auto& row : state) {
        for (int tile : row) {
            hash += to_string(tile) + ",";
        }
    }
    return hash;
}

// Solves the problem using Uniform Cost Search (UCS).
Node* Problem::uniform_cost_search() {
    return a_star_search(&Problem::misplaced_tile_heuristic);  // Use a heuristic that always returns 0 for UCS
}

// Solves the problem using A* with the Misplaced Tile heuristic.
Node* Problem::misplaced_tile_A() {
    return a_star_search(&Problem::misplaced_tile_heuristic);
}

// Solves the problem using A* with the Euclidean Distance heuristic.
Node* Problem::euclidean_distance_A() {
    return a_star_search(&Problem::euclidean_distance_heuristic);
}

// Generic A* search function that uses the specified heuristic function.
Node* Problem::a_star_search(int (Problem::*heuristic)(const vector<vector<int>>& state) const) {
    priority_queue<Node*, vector<Node*>, NodeComparator> unexplored;
    unordered_set<string> explored;

    // Initialize the root node with path cost = 0 and heuristic cost calculated from the chosen heuristic
    Node* initial_node = new Node(initial_state, 0, (this->*heuristic)(initial_state), nullptr, find_blank(), "");
    unexplored.push(initial_node);

    while (!unexplored.empty()) {
        Node* current = unexplored.top();
        unexplored.pop();

        // Check if the current node is the goal
        if (current->is_goal(goal_state)) {
            return current;
        }

        // Add the current state to the explored set
        explored.insert(state_to_string(current->get_state()));

        // Expand the current node
        vector<Node*> children = current->add_child({"UP", "DOWN", "LEFT", "RIGHT"});
        for (Node* child : children) {
            string child_state_str = state_to_string(child->get_state());

            // Only add child if it hasn’t been explored
            if (explored.find(child_state_str) == explored.end()) {
                child->heuristic = (this->*heuristic)(child->get_state());
                unexplored.push(child);
            }
        }
    }

    return nullptr; // No solution found
}
