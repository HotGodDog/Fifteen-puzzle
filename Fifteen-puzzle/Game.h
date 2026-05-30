#pragma once

#include "Board.h"
#include "History.h"
#include "Renderer.h"
#include "Solver.h"

class Game {
public:
    Game();
    void run();

private:
    Board board;
    History history;
    Renderer renderer;
    Solver solver;
    bool demoMode;
    int historyPage;

    void newGame();
    void processInput();
    bool demoStep();
    char deltaToArrow(int dr, int dc) const;
};