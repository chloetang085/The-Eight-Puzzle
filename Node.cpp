#include "Node.h"
#include <cmath>
#include <iostream>

// Constructor: Initializes the node with the given state, cost, depth, parent, blank position, and action.
Node::Node(const vector<vector<int>>& game_state, int cost_path, int heuristicCost, Node* p, const pair<int, int>& bp, const string& action_chosen)
    : state(game_state), path_cost(cost_path), heuristic(heuristicCost), parent(p), blank_pos(bp), action(action_chosen) {}

// Checks if the node's state matches the goal state.
bool Node::is_goal(const vector<vector<int>>& goal) const {
    if (state == goal) {
        return true;
    }
    return false;
}

// Getter for the state of the node.
const vector<vector<int>>& Node::get_state() const {
    return state;
}

int Node::get_path_cost() const {
    return path_cost;
}

// Getter for the heuristic cost.
int Node::get_heuristic() const {
    return heuristic;
}

int Node::get_total_cost() const {
    return path_cost + heuristic;
}

// Method to expand the current node by generating child nodes based on possible moves.
vector<Node*> Node::add_child(const vector<string>& actions) {
    vector<Node*> children;
    int x = blank_pos.first;
    int y = blank_pos.second;

    for (const string& action : actions) {
        int new_x = x, new_y = y;

        // Determine the new position based on the action string
        if (action == "UP" && x > 0) {
            new_x = x - 1;
        } else if (action == "DOWN" && x < state.size() - 1) {
            new_x = x + 1;
        } else if (action == "LEFT" && y > 0) {
            new_y = y - 1;
        } else if (action == "RIGHT" && y < state.at(0).size() - 1) {
            new_y = y + 1;
        } else {
            continue;       // Skip if the move is invalid
        }

        // Create a new state by moving the blank tile
        vector<vector<int>> new_state = state;
        new_state[x][y] = new_state[new_x][new_y];
        new_state[new_x][new_y] = 0; // Move the blank tile to the new position

        // Create the child node with the new state and update the blank position
        Node* child = new Node(new_state, path_cost + 1, 0, this, {new_x, new_y}, action);
        children.push_back(child);
    }
    return children;
}
