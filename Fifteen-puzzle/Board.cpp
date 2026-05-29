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