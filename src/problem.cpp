using namespace std;
#include<vector>
#include <utility>

//represents the eight puzzle problem and all the initial/goal states and moves
class Problem {
public:
    vector<vector<int>> initial_state; //vector to hold teh starting states 
    vector<vector<int>> goal_state;    //vector to stre the goal state
    // objective is to transition initial state to goal state
    vector<pair<int, int>> operators; // list of moves for the blank tile

    Problem(vector<vector<int>> initial, vector<vector<int>> goal)
        : initial_state(initial), goal_state(goal) { //initializes initial_state and goal_state with provided arguments
        // define the possible moves (up, down, left, right)
        //{0,1} move right
        //{1,0} move down
        //{0,-1} move left
        //{-1,0} move up
        operators = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    }
};
