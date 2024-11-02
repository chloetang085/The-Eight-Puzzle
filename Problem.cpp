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
double Problem::misplaced_tile_heuristic(const vector<vector<int>>& state) const {
    double misplaced = 0;
    for (unsigned i = 0; i < state.size(); ++i) {
        for (unsigned j = 0; j < state[i].size(); ++j) {
            if (state[i][j] != 0 && state[i][j] != goal_state[i][j]) {
                ++misplaced;
            }
        }
    }
    return misplaced;
}


double Problem::euclidean_distance_heuristic(const std::vector<std::vector<int>>& state) const {
    double total_distance = 0.0;

    for (int i = 0; i < state.size(); ++i) {
        for (int j = 0; j < state[i].size(); ++j) {
            int tile = state[i][j];

            if (tile != 0) {  // Ignore the blank tile
                int target_x = (tile - 1) / 3;
                int target_y = (tile - 1) % 3;

                // Calculate Euclidean distance
                double distance = sqrt(pow(i - target_x, 2) + pow(j - target_y, 2));
                total_distance += distance;
            }
        }
    }

    return total_distance;
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

Node* Problem::a_star_search(double (Problem::*heuristic)(const vector<vector<int>>& state) const) {
    priority_queue<Node*, vector<Node*>, NodeComparator> frontier;
    unordered_set<string> explored;
    unordered_map<string, int> frontier_map;  // Tracks nodes in frontier with cost

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

    // Initialize the root node
    int initial_heuristic = heuristic ? (this->*heuristic)(initial_state) : 0;
    Node* initial_node = new Node(initial_state, 0, initial_heuristic, nullptr, blank_pos, "");
    frontier.push(initial_node);
    frontier_map[state_to_string(initial_state)] = initial_node->get_total_cost();

    cout << "Initial heuristic: " << initial_heuristic << endl;

    int max_queue_size = 0;
    int nodes_expanded = 0;

    while (!frontier.empty()) {
        Node* current = frontier.top();
        frontier.pop();
        frontier_map.erase(state_to_string(current->get_state()));

        nodes_expanded++;
        max_queue_size = max(max_queue_size, static_cast<int>(frontier.size()));

        cout << "Expanding state:\n";
        display_puzzle(current->get_state());
        cout << "g(n) = " << current->get_path_cost() << ", h(n) = " << current->get_heuristic() 
             << ", f(n) = " << current->get_total_cost() << endl;

        if (current->is_goal(goal_state)) {
            cout << "Goal!!!" << endl;
            cout << "Total nodes expanded: " << nodes_expanded << endl;
            cout << "Maximum queue size at any one time: " << max_queue_size << endl;
            cout << "Depth of the goal node was: " << current->get_path_cost() << endl;
            return current;
        }

        explored.insert(state_to_string(current->get_state()));

        vector<Node*> children = current->add_child({"UP", "DOWN", "LEFT", "RIGHT"});
        for (Node* child : children) {
            string child_state_str = state_to_string(child->get_state());

            if (explored.find(child_state_str) == explored.end() &&
                (frontier_map.find(child_state_str) == frontier_map.end() || 
                frontier_map[child_state_str] > child->get_total_cost())) {
                
                child->heuristic = heuristic ? (this->*heuristic)(child->get_state()) : 0;
                frontier.push(child);
                frontier_map[child_state_str] = child->get_total_cost();
            } else {
                delete child;
            }
        }
    }

    cout << "No solution found." << endl;
    return nullptr;
}

// Uniform Cost Search (UCS): calls A* without any heuristic (h = 0).
Node* Problem::uniform_cost_search() {
    return a_star_search(nullptr); // No heuristic means h(n) = 0 for UCS
}

// A* search with the Misplaced Tile heuristic.
Node* Problem::misplaced_tile_A() {
    return a_star_search(&Problem::misplaced_tile_heuristic);
}

// A* search with the Euclidean Distance heuristic.
Node* Problem::euclidean_distance_A() {
    return a_star_search(&Problem::euclidean_distance_heuristic);
}

// Display function to print the puzzle state, showing 0 as '*'.
void Problem::display_puzzle(const vector<vector<int>>& state) const {
    for (const auto& row : state) {
        for (int num : row) {
            if (num == 0) {
                cout << "* ";
            } else {
                cout << num << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}
