#include "Solver.h"

int Solver::manhattan(const State& state) {
    int dist = 0;
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            int tile = state[row][col];
            if (tile == 0) continue;
            int targetR = (tile - 1) / BOARD_SIZE;
            int targetC = (tile - 1) % BOARD_SIZE;
            dist += abs(row - targetR) + abs(col - targetC);
        }
    }
    return dist;
}

int Solver::linearConflict(const State& state) {
    int conflict = 0;

    // Row conflicts
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c1 = 0; c1 < BOARD_SIZE; ++c1) {
            int tile1 = state[r][c1];
            if (tile1 == 0) continue;
            int targetR1 = (tile1 - 1) / BOARD_SIZE;
            if (targetR1 != r) continue;

            for (int c2 = c1 + 1; c2 < BOARD_SIZE; ++c2) {
                int tile2 = state[r][c2];
                if (tile2 == 0) continue;
                int targetR2 = (tile2 - 1) / BOARD_SIZE;
                if (targetR2 != r) continue;

                int targetC1 = (tile1 - 1) % BOARD_SIZE;
                int targetC2 = (tile2 - 1) % BOARD_SIZE;

                if (targetC1 > targetC2) {
                    conflict += 2;
                }
            }
        }
    }

    // Column conflicts
    for (int c = 0; c < BOARD_SIZE; ++c) {
        for (int r1 = 0; r1 < BOARD_SIZE; ++r1) {
            int tile1 = state[r1][c];
            if (tile1 == 0) continue;
            int targetC1 = (tile1 - 1) % BOARD_SIZE;
            if (targetC1 != c) continue;

            for (int r2 = r1 + 1; r2 < BOARD_SIZE; ++r2) {
                int tile2 = state[r2][c];
                if (tile2 == 0) continue;
                int targetC2 = (tile2 - 1) % BOARD_SIZE;
                if (targetC2 != c) continue;

                int targetR1 = (tile1 - 1) / BOARD_SIZE;
                int targetR2 = (tile2 - 1) / BOARD_SIZE;

                if (targetR1 > targetR2) {
                    conflict += 2;
                }
            }
        }
    }

    return conflict;
}

int Solver::heuristic(const State& state) {
    return manhattan(state) + linearConflict(state);
}

string Solver::stateToString(const State& state) {
    string s;
    s.reserve(BOARD_SIZE * BOARD_SIZE);
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            s += char(state[row][col]);
        }
    }
    return s;
}

vector<pair<int, int>> Solver::reconstructPath(
    const unordered_map<string, pair<string, pair<int, int>>>& cameFrom,
    const string& startStr,
    const string& goalStr) {

    vector<pair<int, int>> path;
    string current = goalStr;

    while (current != startStr) {
        auto it = cameFrom.find(current);
        if (it == cameFrom.end()) break;
        path.push_back(it->second.second);
        current = it->second.first;
    }

    reverse(path.begin(), path.end());
    return path;
}

vector<pair<int, int>> Solver::solve(const Board& start) {
    if (start.isSolved()) return {};

    State startState;
    int startBlankR = 0, startBlankC = 0;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            startState[row][col] = start.getTile(row, col);
            if (startState[row][col] == 0) {
                startBlankR = row;
                startBlankC = col;
            }
        }
    }

    string startStr = stateToString(startState);

    priority_queue<Node, vector<Node>, greater<Node>> open;
    unordered_set<string> visited;
    unordered_map<string, pair<string, pair<int, int>>> cameFrom;

    Node startNode;
    startNode.state = startState;
    startNode.g = 0;
    startNode.h = heuristic(startState);
    startNode.blankR = startBlankR;
    startNode.blankC = startBlankC;

    open.push(startNode);
    visited.insert(startStr);

    const int drs[4] = { -1, 1, 0, 0 };
    const int dcs[4] = { 0, 0, -1, 1 };

    while (!open.empty()) {
        Node current = open.top();
        open.pop();

        // Check solved
        bool solved = true;
        for (int row = 0; row < BOARD_SIZE && solved; ++row) {
            for (int col = 0; col < BOARD_SIZE && solved; ++col) {
                int expected = row * BOARD_SIZE + col + 1;
                if (row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1) expected = 0;
                if (current.state[row][col] != expected) solved = false;
            }
        }

        if (solved) {
            return reconstructPath(cameFrom, startStr, stateToString(current.state));
        }

        for (int i = 0; i < 4; ++i) {
            int newR = current.blankR + drs[i];
            int newC = current.blankC + dcs[i];

            if (newR < 0 || newR >= BOARD_SIZE || newC < 0 || newC >= BOARD_SIZE) continue;

            // Don't return to previous state
            if (newR == current.blankR && newC == current.blankC) continue;

            State nextState = current.state;
            swap(nextState[current.blankR][current.blankC], nextState[newR][newC]);

            string nextStr = stateToString(nextState);
            if (visited.count(nextStr)) continue;

            Node next;
            next.state = nextState;
            next.g = current.g + 1;
            next.h = heuristic(nextState);
            next.blankR = newR;
            next.blankC = newC;

            open.push(next);
            visited.insert(nextStr);
            cameFrom[nextStr] = { stateToString(current.state), {drs[i], dcs[i]} };
        }
    }

    return {};
}