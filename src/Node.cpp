#include "Node.h"

Node::Node(vector<vector<int>> s, int g_cost, int h_cost, Node* p, pair<int, int> bp)
    : state(s), g(g_cost), h(h_cost), f(g_cost + h_cost), parent(p), blank_pos(bp) {}

bool Node::operator>(const Node& other) const {
    return f > other.f;
}
