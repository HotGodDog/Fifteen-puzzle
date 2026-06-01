#pragma once

#include "Board.h"
#include <vector>

using namespace std;

using State = array<array<int, BOARD_SIZE>, BOARD_SIZE>;

class Solver {
public:
    vector<pair<int, int>> solve(const Board& start);

private:
    int manhattan(const State& state);
    int linearConflict(const State& state);
    int heuristic(const State& state);

    // IDA* recursive search
    bool search(State& state, int g, int bound, int blankR, int blankC,
        int& newBound, vector<pair<int, int>>& path,
        pair<int, int> lastMove, bool hasLast);

    bool isSolved(const State& state) const;
};