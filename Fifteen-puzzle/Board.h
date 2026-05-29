#pragma once

#include <iostream>
#include <array>
#include <algorithm>
#include <random>

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

    int getTile(int row, int col) const;    // get the cell value
    pair<int, int> getBlank() const;        // get the position of an empty cell

    void shuffle();         // random start position

private:
    array<array<int, SIZE>, SIZE> tiles;
    int blankR, blankC;             // coordinates of an empty cell
    bool isSolvable() const;        // checking the possibility of a solution
};