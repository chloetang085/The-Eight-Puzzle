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
        for (unsigned j = 0; j < state[i].size(); ++j) {
            if (state[i][j] != 0 && state[i][j] != goal_state[i][j]) {
                ++misplaced;
            }
        }
    }
    return misplaced;
}

// Euclidean distance heuristic: Calculates the total Euclidean distance of tiles to their goal positions.
int Problem::euclidean_distance_heuristic(const vector<vector<int>>& state) const {
    int distance = 0;
    for (unsigned i = 0; i < state.size(); ++i) {
        for (unsigned j = 0; j < state[i].size(); ++j) {
            if (state[i][j] != 0) {
                int target_x = (state[i][j] - 1) / 3;
                int target_y = (state[i][j] - 1) % 3;
                distance += sqrt(pow(i - target_x, 2) + pow(j - target_y, 2));
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
    // Call a_star_search with nullptr to indicate UCS (h(n) = 0)
    return a_star_search(nullptr);
}

// Solves the problem using A* with the Misplaced Tile heuristic.
Node* Problem::misplaced_tile_A() {
    return a_star_search(&Problem::misplaced_tile_heuristic);
}

// Solves the problem using A* with the Euclidean Distance heuristic.
Node* Problem::euclidean_distance_A() {
    return a_star_search(&Problem::euclidean_distance_heuristic);
}

// Display function to print the puzzle state, showing 0 as *
void Problem::display_puzzle(const vector<vector<int>>& state) const {
    for (const auto& row : state) {
        for (int num : row) {
            if (num == 0) {
                cout << "* "; // Display blank as *
            } else {
                cout << num << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

// Generic A* search function that uses the specified heuristic function.
Node* Problem::a_star_search(int (Problem::*heuristic)(const vector<vector<int>>& state) const) {
    priority_queue<Node*, vector<Node*>, NodeComparator> frontier;
    unordered_set<string> explored;

    // Find the blank position in the initial state
    pair<int, int> blank_pos = {-1, -1};
    for (int i = 0; i < initial_state.size(); ++i) {
        for (int j = 0; j < initial_state[i].size(); ++j) {
            if (initial_state[i][j] == 0) {
                blank_pos = {i, j};
                break;
            }
        }
        if (blank_pos.first != -1) break;
    }

    // Initialize the root node with path cost = 0 and heuristic cost (or 0 if heuristic is nullptr)
    int initial_heuristic = heuristic ? (this->*heuristic)(initial_state) : 0;
    Node* initial_node = new Node(initial_state, 0, initial_heuristic, nullptr, blank_pos, "");
    frontier.push(initial_node);

    cout << "Initial heuristic: " << initial_heuristic << endl;

    // Main A* search loop
    int nodes_expanded = 0; // Debug: count nodes expanded
    while (!frontier.empty()) {
        Node* current = frontier.top();
        frontier.pop();

        nodes_expanded++; // Increment nodes expanded

        if (current->is_goal(goal_state)) {
            cout << "Goal state reached!" << endl;
            cout << "Total nodes expanded: " << nodes_expanded << endl; // Debug output
            return current;
        }

        explored.insert(state_to_string(current->get_state()));

        // Expand the current node
        vector<Node*> children = current->add_child({"UP", "DOWN", "LEFT", "RIGHT"});
        for (Node* child : children) {
            string child_state_str = state_to_string(child->get_state());

            if (explored.find(child_state_str) == explored.end()) {
                child->heuristic = heuristic ? (this->*heuristic)(child->get_state()) : 0;
                frontier.push(child);
            } else {
                delete child;
            }
        }
    }

    cout << "No solution found." << endl;
    return nullptr;
}
