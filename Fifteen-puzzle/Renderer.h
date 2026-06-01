#pragma once

#include "Board.h"
#include <windows.h>

using namespace std;

class Renderer {
public:
    void draw(const Board& board, bool winShown = false);
    void clearScreen();

private:
    void setColor(int color);
    void resetColor();
    void drawBoard(const Board& board);
    void drawFooter();
};