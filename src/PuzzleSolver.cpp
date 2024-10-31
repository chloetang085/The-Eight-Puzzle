#include "PuzzleSolver.h"

PuzzleSolver::PuzzleSolver(const Problem& prob) : problem(prob) {} //constructor, initializes with a problem instance

void PuzzleSolver::solve(int algorithmChoice) { //solving function
    switch (algorithmChoice) {
        case 1:
            uniformCostSearch();
            break;
        case 2:
            aStarSearch("misplaced");
            break;
        case 3:
            aStarSearch("euclidean");
            break;
        default:
            cout << "Invalid choice." << endl;
    }
}
//counts the number of tiles that are misplace compared to the goal state
int PuzzleSolver::misplacedTiles(const vector<vector<int>>& state) { //heuristic function
    int misplaced = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (state[i][j] != 0 && state[i][j] != problem.goal_state[i][j]) {
                ++misplaced; //increment if the tile is not in its goal position
            }
        }
    }
    return misplaced;
}
//calculates the euclidean distance for each tile to its goal pos
int PuzzleSolver::euclideanDistance(const vector<vector<int>>& state) {
    int distance = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (state[i][j] != 0) { //skip blank tile
                int target_x = (state[i][j] - 1) / 3;
                int target_y = (state[i][j] - 1) % 3;
                distance += sqrt(pow(i - target_x, 2) + pow(j - target_y, 2)); //formula
            }
        }
    }
    return distance;
}
//check if curr state = goal state
bool PuzzleSolver::isGoal(const vector<vector<int>>& state) {
    return state == problem.goal_state;
}
//recursively prints solution path by following parent nodes
void PuzzleSolver::printSolution(Node* node) {
    if (node == nullptr) return;
    printSolution(node->parent);
    for (const auto& row : node->state) {
        for (int num : row) cout << num << " ";
        cout << endl;
    }
    cout << "----" << endl;
}

void PuzzleSolver::uniformCostSearch() {
    priority_queue<Node, vector<Node>, greater<Node>> frontier;
    unordered_set<string> explored;
    pair<int, int> blank = findBlank(problem.initial_state);

    frontier.push(Node(problem.initial_state, 0, 0, nullptr, blank)); //initialize the frontier with the intitial state node

    while (!frontier.empty()) {
        Node current = frontier.top();
        frontier.pop();
        
        if (isGoal(current.state)) { //checks if goal state is reached
            cout << "Goal found with Uniform Cost Search!" << endl;
            printSolution(&current);
            return;
        }

        explored.insert(hashState(current.state)); //mark as explored

        for (const auto& dir : directions) {
            auto next_state = moveBlank(current.state, current.blank_pos, dir);
            if (next_state.empty()) continue;

            string hashed = hashState(next_state);
            if (explored.find(hashed) == explored.end()) {
                frontier.push(Node(next_state, current.g + 1, 0, new Node(current), findBlank(next_state)));
            }
        }
    }
    cout << "No solution found with Uniform Cost Search." << endl;
}

void PuzzleSolver::aStarSearch(const string& heuristic) {
    priority_queue<Node, vector<Node>, greater<Node>> frontier;
    unordered_set<string> explored;
    pair<int, int> blank = findBlank(problem.initial_state);

    int initial_h = (heuristic == "misplaced") ? misplacedTiles(problem.initial_state) : euclideanDistance(problem.initial_state);
    frontier.push(Node(problem.initial_state, 0, initial_h, nullptr, blank));

    while (!frontier.empty()) {
        Node current = frontier.top();
        frontier.pop();

        if (isGoal(current.state)) {
            cout << "Goal found with A* Search (" << heuristic << " heuristic)!" << endl;
            printSolution(&current);
            return;
        }

        explored.insert(hashState(current.state));

        for (const auto& dir : directions) {
            auto next_state = moveBlank(current.state, current.blank_pos, dir);
            if (next_state.empty()) continue;

            string hashed = hashState(next_state);
            if (explored.find(hashed) == explored.end()) {
                int next_g = current.g + 1;
                int next_h = (heuristic == "misplaced") ? misplacedTiles(next_state) : euclideanDistance(next_state);
                frontier.push(Node(next_state, next_g, next_h, new Node(current), findBlank(next_state)));
            }
        }
    }
    cout << "No solution found with A* Search." << endl;
}

string PuzzleSolver::hashState(const vector<vector<int>>& state) {
    string hash = "";
    for (const auto& row : state) {
        for (int num : row) hash += to_string(num) + ",";
    }
    return hash;
}

pair<int, int> PuzzleSolver::findBlank(const vector<vector<int>>& state) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (state[i][j] == 0) return {i, j};
        }
    }
    return {-1, -1}; // Should never reach here
}

vector<vector<int>> PuzzleSolver::moveBlank(const vector<vector<int>>& state, pair<int, int> blank_pos, pair<int, int> dir) {
    int x = blank_pos.first + dir.first;
    int y = blank_pos.second + dir.second;
    if (x < 0 || x >= 3 || y < 0 || y >= 3) return {}; // Out of bounds

    vector<vector<int>> new_state = state;
    swap(new_state[blank_pos.first][blank_pos.second], new_state[x][y]);
    return new_state;
}
