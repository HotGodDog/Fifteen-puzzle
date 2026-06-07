#pragma once

#include "Board.h"
#include "Renderer.h"
#include "Solver.h"
#include "Logger.h"

class Game {
public:
    Game();
    void run();

private:
    Board board;
    Renderer renderer;
    Solver solver;
    Logger logger;
    bool demoMode;
    bool winShown;
    vector<pair<int, int>> demoPath;
    size_t demoPathIndex;

    void newGame();
    void processInput();
    bool demoStep();
};