#ifndef NODE_H
#define NODE_H

#include <vector>
#include <utility>
using namespace std;

class Node {
public:
    vector<vector<int>> state;  // represents current states as vectors
    int g;                      // cost to reach this node
    int h;                      // heuristic value
    int f;                      // total cost (g + h)
    Node* parent;               // points to previous node, traces through parent pointers to reconstruct a solution path
    pair<int, int> blank_pos;   // stores current position

    Node(vector<vector<int>> s, int g_cost, int h_cost, Node* p, pair<int, int> bp);

    // define ordering for priority queue (min-heap based on f value)
    bool operator>(const Node& other) const;
};

#endif 
