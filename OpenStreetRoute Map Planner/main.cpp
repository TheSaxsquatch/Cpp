#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
using std::ifstream;
using std::istringstream;
using std::sort;
using std::string;
using std::vector;
using std::abs;

enum class State { kStart, kEmpty, kObstacle, kClosed, kPath, kFinish };

// Directional Delta's
const int delta[4][2]{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

vector<State> ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    vector<State> row;
    while (sline >> n >> c && c == ',') {
        if (n == 0) {
            row.push_back(State::kEmpty);
        }
        else {
            row.push_back(State::kObstacle);
        }
    }
    return row;
}


vector<vector<State>> ReadBoardFile(string path) {
    ifstream myfile(path);
    vector<vector<State>> board{};
    if (myfile) {
        string line;
        while (getline(myfile, line)) {
            vector<State> row = ParseLine(line);
            board.push_back(row);
        }
    }
    return board;
}

// Compare the f-value of two nodes
bool Compare(const vector<int> a, const vector<int> b) {
    int f1 = a[2] + a[3];
    int f2 = b[2] + b[3];
    
    return f1 > f2;
}

// Sorth the two-dimensional vector inf ints in descending order.
void CellSort(vector<vector<int>>* v) {
    sort(v->begin(), v->end(), Compare);
}

// Calculate the Manhattan Distance
int Heuristic(int x1, int y1, int x2, int y2) {
    int manhattanDist = abs(x2 - x1) + abs(y2 - y1);

    return manhattanDist;
}

// Check for Valid Neighbor Cells
bool CheckValidCell(int x, int y, vector<vector<State>> &grid) {
    bool gridCheckX = (x >= 0 && x < grid.size());
    bool gridCheckY = (y >= 0 && y < grid[0].size());

    if (gridCheckX && gridCheckY) 
        return grid[x][y] == State::kEmpty;
    return false;
}

// Add a node to the open list and mark it as open.
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &openlist, vector<vector<State>> &grid) {
    // Add node to open vector, and mark grid cell as closed.
    openlist.push_back(vector<int> {x, y, g, h});
    grid[x][y] = State::kClosed;
}

// Expand current nodes neighbors and add them to the open list
void ExpandNeighbors(const vector<int>& current, int goal[2], vector<vector<int>>& openlist, vector<vector<State>>& grid) {
    int x = current[0];
    int y = current[1];
    int g = current[2];

    for (int i = 0; i < 4; i++) {
        int x2 = x + delta[i][0];
        int y2 = x + delta[i][1];

        if (CheckValidCell(x2, y2, grid)) {
            int g2 = g + 1;
            int h2 = Heuristic(x2, y2, goal[0], goal[1]);
            AddToOpen(x2, y2, g2, h2, openlist, grid);
        }
    }
}

// Implementation of A* search algorithm.
vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2]) {
    // Create the vector of open nodes.
    vector<vector<int>> open{};

    // Initialize the starting node.
    int x = init[0];
    int y = init[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0], goal[1]);
    AddToOpen(x, y, g, h, open, grid);

    while (open.size() > 0) {
        CellSort(&open);
        auto current = open.back();
        open.pop_back();
        int x = current[0];
        int y = current[1];

        grid[x][y] = State::kPath;

        // Check for completion
        if (x == goal[0] && y == goal[1]) {
            grid[init[0]][init[1]] = State::kStart;
            grid[goal[0]][goal[1]] = State::kFinish;

            return grid;
        }
        // If we're not done, expand search to current node's neighbors. This step will be completed in a later quiz.
        ExpandNeighbors(current, goal, open, grid);
    }

    // Run out of new nodes to explore and have not found a path.
    cout << "No path found!" << endl;
    return vector<vector<State>> {};
}

string CellString(State cell) {
    switch (cell) {
    case State::kObstacle: return "⛰️   ";
    case State::kPath: return "🚗   ";
    case State::kStart: return "🚦 ";
    case State::kFinish: return "🏁 ";
    default: return "0   ";
    }
}


void PrintBoard(const vector<vector<State>> board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            cout << CellString(board[i][j]);
        }
        cout << "\n";
    }
}


int main() {
    // TODO: Declare "init" and "goal" arrays with values {0, 0} and {4, 5} respectively.
    int init[2] { 0,0 };
    int goal[2] { 4,5 };
    auto board = ReadBoardFile("1.board");
    auto solution = Search(board, init, goal);
    PrintBoard(solution);

    /* Tests
    TestHeuristic();
    TestAddToOpen();
    TestCompare();
    */
}
