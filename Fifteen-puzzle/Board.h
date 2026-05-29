#pragma once

#include <iostream>
#include <array>

using namespace std;

const int SIZE = 4;

class Board {
public:
    Board();
    void print() const;
    bool isSolved() const;

    bool move(int key);
    bool moveByDelta(int dr, int dc);
    bool isValidMove(int dr, int dc) const;

    int getTile(int row, int col) const;
    pair<int, int> getBlank() const;

private:
    array<array<int, SIZE>, SIZE> tiles;
    int blankR, blankC;         // coordinates of an empty cell
};