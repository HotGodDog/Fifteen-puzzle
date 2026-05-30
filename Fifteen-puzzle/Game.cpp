#include "Game.h"
#include <conio.h>
#include <windows.h>

Game::Game() : demoMode(false), historyPage(1), demoPathIndex(0), winShown(false) {
    newGame();
}

void Game::newGame() {
    board.shuffle();
    history.clear();
    historyPage = 1;
    demoMode = false;
    demoPath.clear();       // reset path
    demoPathIndex = 0;      // reset index
    winShown = false;       // reset win window
}

char Game::deltaToArrow(int dr, int dc) const {
    if (dr == -1 && dc == 0) return '\x18';  // ↑
    if (dr == 1 && dc == 0) return '\x19';   // ↓
    if (dr == 0 && dc == -1) return '\x1B';  // ←
    if (dr == 0 && dc == 1) return '\x1A';   // →
    return '?';
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
            if (!demoMode && board.move(key)) {
                auto blankPos = board.getBlank();
                int newR = blankPos.first;
                int newC = blankPos.second;
                int dr = 0, dc = 0;
                if (key == 72) dr = -1;
                else if (key == 80) dr = 1;
                else if (key == 75) dc = -1;
                else if (key == 77) dc = 1;

                int oldR = newR - dr;
                int oldC = newC - dc;
                int tile = board.getTile(oldR, oldC);
                char arrow = deltaToArrow(dr, dc);

                history.add(tile, oldR, oldC, newR, newC, arrow, false);
                historyPage = 1;
            }
            break;
        case 73: // PgUp
            if (historyPage < history.totalPages(4)) historyPage++;
            break;
        case 81: // PgDn
            if (historyPage > 1) historyPage--;
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
    if (demoPath.empty()) {
        renderer.clearScreen();
        cout << "Solving puzzle, please wait..." << endl;

        demoPath = solver.solve(board);
        demoPathIndex = 0;

        if (demoPath.empty()) {
            cout << "Already solved or no solution!" << endl;
            Sleep(1000);
            demoMode = false;
            return false;
        }

        cout << "Solution found: " << demoPath.size() << " moves" << endl;
        Sleep(500);
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

    int oldBlankR = board.getBlank().first;
    int oldBlankC = board.getBlank().second;

    board.moveByDelta(dr, dc);

    auto newBlank = board.getBlank();
    int newBlankR = newBlank.first;
    int newBlankC = newBlank.second;
    int tile = board.getTile(oldBlankR, oldBlankC);
    char arrow = deltaToArrow(dr, dc);

    history.add(tile, oldBlankR, oldBlankC, newBlankR, newBlankC, arrow, true);

    return true;
}

void Game::run() {
    while (true) {
        if (board.isSolved() && !winShown && history.size() > 0) {
            winShown = true;
        }

        renderer.draw(board, history, historyPage, winShown);

        if (demoMode) {
            if (!demoStep()) {}
            Sleep(200);
        }
        else {
            processInput();
        }
    }
}