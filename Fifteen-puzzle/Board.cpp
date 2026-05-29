#include "board.h"

Board::Board() {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            tiles[row][col] = row * SIZE + col + 1;
        }
    }
    tiles[SIZE - 1][SIZE - 1] = 0;
    blankR = SIZE - 1;
    blankC = SIZE - 1;
}

void Board::print() const {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (tiles[row][col] == 0) {
                cout << "   _";
            }
            else {
                if (tiles[row][col] < 10) cout << " ";
                cout << " " << tiles[row][col];
            }
        }
        cout << endl;
    }
}

bool Board::isSolved() const {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            int expected = row * SIZE + col + 1;
            if (row == SIZE - 1 && col == SIZE - 1) {
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
    return (newR >= 0 && newR < SIZE && newC >= 0 && newC < SIZE);
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