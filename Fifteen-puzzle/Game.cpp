#include "Game.h"
#include <conio.h>
#include <windows.h>

Game::Game() : demoMode(false), historyPage(1) {
    newGame();
}

void Game::newGame() {
    board.shuffle();
    history.clear();
    historyPage = 1;
    demoMode = false;
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
        demoMode = !demoMode;
        break;
    case 'n':
    case 'N':
        newGame();
        break;
    }
}

bool Game::demoStep() {
    // Placeholder - solver not yet implemented
    // Will be filled in Step 6
    return false;
}

void Game::run() {
    while (true) {
        if (board.isSolved()) {
            renderer.draw(board, history, historyPage);
            renderer.showWin(history.countUser(), history.countAuto(), history.size());
            _getch();
            newGame();
            continue;
        }

        renderer.draw(board, history, historyPage);

        if (demoMode) {
            if (!demoStep()) {
                demoMode = false;
            }
            Sleep(200);
        }
        else {
            processInput();
        }
    }
}