#include "Board.h"

Board::Board() {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            tiles[row][col] = row * BOARD_SIZE + col + 1;
        }
    }
    tiles[BOARD_SIZE - 1][BOARD_SIZE - 1] = 0;
    blankR = BOARD_SIZE - 1;
    blankC = BOARD_SIZE - 1;
}

bool Board::isSolved() const {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            int expected = row * BOARD_SIZE + col + 1;
            if (row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1) {
                expected = 0;
            }
            if (tiles[row][col] != expected) {
                return false;
            }
        }
    }
    return true;
}

bool Board::isValidMove(int dr, int dc) const {
    int newR = blankR + dr;
    int newC = blankC + dc;
    return (newR >= 0 && newR < BOARD_SIZE && newC >= 0 && newC < BOARD_SIZE);
}

bool Board::moveByDelta(int dr, int dc) {
    if (!isValidMove(dr, dc)) {
        return false;
    }
    int newR = blankR + dr;
    int newC = blankC + dc;
    swap(tiles[blankR][blankC], tiles[newR][newC]);
    blankR = newR;
    blankC = newC;
    return true;
}

bool Board::move(int key) {
    int dr = 0, dc = 0;
    switch (key) {
        case 75: dc = -1; break;    // left
        case 77: dc =  1; break;    // right
        case 72: dr = -1; break;    // up
        case 80: dr =  1; break;    // down
        default: return false;
    }
    return moveByDelta(dr, dc);
}

int Board::getTile(int row, int col) const {
    return tiles[row][col];
}

pair<int, int> Board::getBlank() const {
    return {blankR, blankC};
}

bool Board::isSolvable() const {
    // counting inversions N (0 is skipped)
    int inversions = 0;
    vector<int> flat;
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (tiles[row][col] != 0) {
                flat.push_back(tiles[row][col]);
            }
        }
    }
    for (size_t i = 0; i < flat.size(); ++i) {
        for (size_t j = i + 1; j < flat.size(); ++j) {
            if (flat[i] > flat[j]) {
                ++inversions;
            }
        }
    }

    // row number of an empty cell counting from the buttom: R in (1, 2, 3, 4)
    int R = BOARD_SIZE - blankR;

    // a position is solvable if (N + R) % 2 == 1
    return (inversions + R) % 2 == 1;
}

void Board::shuffle() {
    // create an array [0, 1, 2, ..., 15]
    vector<int> nums(BOARD_SIZE * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i) {
        nums[i] = i;
    }

    // shuffling
    random_device rd;
    mt19937 gen(rd());
    std::shuffle(nums.begin(), nums.end(), gen);

    // write in tiles, find an empty cell
    int idx = 0;
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            tiles[row][col] = nums[idx++];
            if (tiles[row][col] == 0) {
                blankR = row;
                blankC = col;
            }
        }
    }

    // if it is not solvable, we change 2 non-zero cells
    if (!isSolvable()) {
        // search for the first 2 non-zero cells
        int r1 = -1, c1 = -1, r2 = -1, c2 = -1;
        for (int row = 0; row < BOARD_SIZE && r2 == -1; ++row) {
            for (int col = 0; col < BOARD_SIZE && r2 == -1; ++col) {
                if (tiles[row][col] != 0) {
                    if (r1 == -1) {
                        r1 = row; c1 = col;
                    }
                    else {
                        r2 = row; c2 = col;
                    }
                }
            }
        }
        swap(tiles[r1][c1], tiles[r2][c2]);
    }
}