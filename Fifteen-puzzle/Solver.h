#pragma once

#include "Board.h"
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

using State = array<array<int, BOARD_SIZE>, BOARD_SIZE>;

struct Node {
    State state;
    int g;
    int h;
    int blankR, blankC;

    int f() const { return g + h; }

    bool operator>(const Node& o) const { return f() > o.f(); }
};

class Solver {
public:
    vector<pair<int, int>> solve(const Board& start);

private:
    int manhattan(const State& state);
    int linearConflict(const State& state);
    int heuristic(const State& state);      // Manhattan + Linear Conflict
    string stateToString(const State& state);
    vector<pair<int, int>> reconstructPath(
        const unordered_map<string, pair<string, pair<int, int>>>& cameFrom,
        const string& startStr,
        const string& goalStr
    );
};