#include "Solver.h"
#include <algorithm>

int Solver::manhattan(const State& state) {
    int dist = 0;
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            int tile = state[r][c];
            if (tile == 0) continue;
            int targetR = (tile - 1) / BOARD_SIZE;
            int targetC = (tile - 1) % BOARD_SIZE;
            dist += abs(r - targetR) + abs(c - targetC);
        }
    }
    return dist;
}

int Solver::linearConflict(const State& state) {
    int conflict = 0;

    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c1 = 0; c1 < BOARD_SIZE; ++c1) {
            int tile1 = state[r][c1];
            if (tile1 == 0) continue;
            if ((tile1 - 1) / BOARD_SIZE != r) continue;

            for (int c2 = c1 + 1; c2 < BOARD_SIZE; ++c2) {
                int tile2 = state[r][c2];
                if (tile2 == 0) continue;
                if ((tile2 - 1) / BOARD_SIZE != r) continue;

                int targetC1 = (tile1 - 1) % BOARD_SIZE;
                int targetC2 = (tile2 - 1) % BOARD_SIZE;
                if (targetC1 > targetC2) conflict += 2;
            }
        }
    }

    for (int c = 0; c < BOARD_SIZE; ++c) {
        for (int r1 = 0; r1 < BOARD_SIZE; ++r1) {
            int tile1 = state[r1][c];
            if (tile1 == 0) continue;
            if ((tile1 - 1) % BOARD_SIZE != c) continue;

            for (int r2 = r1 + 1; r2 < BOARD_SIZE; ++r2) {
                int tile2 = state[r2][c];
                if (tile2 == 0) continue;
                if ((tile2 - 1) % BOARD_SIZE != c) continue;

                int targetR1 = (tile1 - 1) / BOARD_SIZE;
                int targetR2 = (tile2 - 1) / BOARD_SIZE;
                if (targetR1 > targetR2) conflict += 2;
            }
        }
    }

    return conflict;
}

int Solver::heuristic(const State& state) {
    return manhattan(state) + linearConflict(state);
}

bool Solver::isSolved(const State& state) const {
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            int expected = r * BOARD_SIZE + c + 1;
            if (r == BOARD_SIZE - 1 && c == BOARD_SIZE - 1) expected = 0;
            if (state[r][c] != expected) return false;
        }
    }
    return true;
}

bool Solver::search(State& state, int g, int bound, int blankR, int blankC,
    int& newBound, vector<pair<int, int>>& path,
    pair<int, int> lastMove) {

    int f = g + heuristic(state);
    if (f > bound) {
        newBound = min(newBound, f);
        return false;
    }
    if (isSolved(state)) return true;

    const int drs[4] = { -1, 1, 0, 0 };
    const int dcs[4] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; ++i) {
        int newR = blankR + drs[i];
        int newC = blankC + dcs[i];

        if (newR < 0 || newR >= BOARD_SIZE || newC < 0 || newC >= BOARD_SIZE) continue;

        // Don't undo last move
        if (lastMove.first == -drs[i] && lastMove.second == -dcs[i]) continue;

        swap(state[blankR][blankC], state[newR][newC]);
        path.push_back({ drs[i], dcs[i] });

        if (search(state, g + 1, bound, newR, newC, newBound, path, { drs[i], dcs[i] })) {
            return true;
        }

        path.pop_back();
        swap(state[blankR][blankC], state[newR][newC]);
    }

    return false;
}

vector<pair<int, int>> Solver::solve(const Board& start) {
    if (start.isSolved()) return {};

    State state;
    int blankR = 0, blankC = 0;

    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            state[r][c] = start.getTile(r, c);
            if (state[r][c] == 0) {
                blankR = r;
                blankC = c;
            }
        }
    }

    int bound = heuristic(state);
    vector<pair<int, int>> path;

    while (true) {
        int newBound = INT_MAX;
        if (search(state, 0, bound, blankR, blankC, newBound, path, { 0, 0 })) {
            return path;
        }
        if (newBound == INT_MAX) return {}; // no solution
        bound = newBound;
    }
}