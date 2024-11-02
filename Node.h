#pragma once

#include <vector>
#include <utility>
#include <string>
using namespace std;

// Node class represents a single state in the puzzle search space.
class Node {
public:
    // Constructor to initialize the node with its state, cost, depth, parent, blank position, and action.
    Node(const vector<vector<int>>& game_state, int cost_path, int depth, Node* p, const pair<int, int>& bp, const string& action_chosen);

    // i moved this to another file
    // bool operator>(const Node& other) const;

    // Checks if the current state matches the goal state.
    bool is_goal(const vector<vector<int>>& goal) const;

    // Getter for the path cost of reaching this node.
    int get_path_cost() const;

    // Getter for the heuristic cost.
    int get_heuristic() const;

    // Getter for the total cost (path cost + heuristic) of reaching this node.
    int get_total_cost() const;

    // Getter for the state of the node.
    const vector<vector<int>>& get_state() const;

    // Method to generate child nodes (possible moves).
    vector<Node*> add_child(const vector<string>& actions);

// private:
    vector<vector<int>> state;       // Represents the current puzzle state as a 2D vector.
    int path_cost;                    // Cost to reach this node from the start (g cost).
    int heuristic;                   // Heuristic cost (estimated cost to goal, h cost).
    int depth;                       // Depth of this node in the search tree.
    string action;                   // Action taken to reach this state from the parent.
    Node* parent;                    // Pointer to the parent node (used for reconstructing the path).
    pair<int, int> blank_pos;         // Position of the blank (zero) tile.

    // Helper function to find the position of the blank (zero) tile.
    // pair<int, int> find_blank() const;
};