#include "Game.h"
#include <conio.h>
#include <windows.h>

Game::Game() : demoMode(false), demoPathIndex(0), winShown(false) {
    newGame();
}

void Game::newGame() {
    board.shuffle();
    demoMode = false;
    demoPath.clear();       // reset path
    demoPathIndex = 0;      // reset index
    winShown = false;       // reset win window
}

void Game::processInput() {
    int key = _getch();

    // Arrow keys: first byte 224 (or 0), second is direction
    if (key == 224 || key == 0) {
        key = _getch();
        switch (key) {
        case 72:    // up
        case 80:    // down
        case 75:    // left
        case 77:    // right
            if (!demoMode) {
                board.move(key);
            }
            break;
        }
        return;
    }

    // Single-byte keys
    switch (key) {
    case 'h':
    case 'H':
        if (!demoMode) {
            demoMode = true;
        }
        break;
    case 'n':
    case 'N':
        newGame();
        break;
    }
}

bool Game::demoStep() {
    if (board.isSolved()) {     // protection against repeated calls
        demoPath.clear();
        demoPathIndex = 0;
        demoMode = false;
        return false;
    }

    if (demoPath.empty()) {
        cout << "\nSolving puzzle, please wait..." << endl;

        demoPath = solver.solve(board);
        demoPathIndex = 0;

        if (demoPath.empty()) {
            cout << "Already solved or no solution!" << endl;
            Sleep(1000);
            demoMode = false;
            return false;
        }

        cout << "Solution found: " << demoPath.size() << " moves" << endl;
        cout << "Press any key to start";
        _getch();
    }

    if (demoPathIndex >= demoPath.size()) {
        demoPath.clear();
        demoPathIndex = 0;
        demoMode = false;
        return false;
    }

    int dr = demoPath[demoPathIndex].first;
    int dc = demoPath[demoPathIndex].second;
    demoPathIndex++;

    board.moveByDelta(dr, dc);

    return true;
}

void Game::run() {
    while (true) {
        if (board.isSolved()) {
            if (demoMode) {
                demoMode = false;
                demoPath.clear();
                demoPathIndex = 0;
            }
            if (!winShown) {
                winShown = true;
            }
        }

        renderer.draw(board, winShown);

        if (demoMode) {
            if (demoStep()) {
                Sleep(300);
            }
        }
        else {
            processInput();
        }
    }
}