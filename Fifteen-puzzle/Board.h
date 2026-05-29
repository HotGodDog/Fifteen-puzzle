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

private:
    array<array<int, SIZE>, SIZE> tiles;
    int blankR, blankC;         // coordinates of an empty cell
};