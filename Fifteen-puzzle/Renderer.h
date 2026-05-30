#pragma once

#include "Board.h"
#include "History.h"
#include <windows.h>

using namespace std;

class Renderer {
public:
    void draw(const Board& board, const History& history, int historyPage);
    void showWin(int userMoves, int autoMoves, int totalMoves);
    void clearScreen();

private:
    void setColor(int color);
    void resetColor();
    void drawBoard(const Board& board);
    void drawHistory(const History& history, int page);
    void drawFooter();
    static const int HISTORY_PER_PAGE = 4;
};