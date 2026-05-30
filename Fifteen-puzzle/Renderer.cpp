#include "Renderer.h"
#include <iostream>

void Renderer::setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Renderer::resetColor() {
    setColor(7);    // default white
}

void Renderer::clearScreen() {
    system("cls");
}

void Renderer::drawBoard(const Board& board) {
    cout << "  ===== 15-Puzzle =====" << endl;
    cout << "  +----+----+----+----+" << endl;
    for (int r = 0; r < BOARD_SIZE; ++r) {
        cout << "  |";
        for (int c = 0; c < BOARD_SIZE; ++c) {
            int tile = board.getTile(r, c);
            if (tile == 0) {
                setColor(8);        // gray for blank
                cout << "    ";
                resetColor();
                cout << "|";
            }
            else {
                if (tile == r * BOARD_SIZE + c + 1) {
                    setColor(10);   // green if in correct position
                }
                if (tile < 10) cout << " ";
                cout << " " << tile << " ";
                resetColor();
                cout << "|";
            }
        }
        cout << endl;
        if (r < BOARD_SIZE - 1) {
            cout << "  +----+----+----+----+" << endl;
        }
    }
    cout << "  +----+----+----+----+" << endl;
}

void Renderer::drawHistory(const History& history, int page) {
    int totalPages = history.totalPages(HISTORY_PER_PAGE);
    if (totalPages < 1) totalPages = 1;

    cout << "\nHistory (page " << page << "/" << totalPages << ", PgUp/PgDn):" << endl;

    auto moves = history.getPage(page, HISTORY_PER_PAGE);
    if (moves.empty()) {
        cout << "  (no moves yet)" << endl;
        return;
    }

    for (const auto& rec : moves) {
        if (rec.isAuto) {
            setColor(8);    // gray for auto moves
        }
        cout << " " << rec.number << ". Tile " << rec.tile;
        if (rec.tile < 10) cout << " ";
        cout << " from [" << rec.fromR << "," << rec.fromC << "] to"
            << " [" << rec.toR << "," << rec.toC << "]";
        if (rec.isAuto) {
            cout << " [auto]";
        }
        resetColor();
        cout << endl;
    }
}

void Renderer::drawFooter() {
    cout << "\n[h] - auto-solve  [arrows] - move  [n] - new game  [PgUp/PgDn] - history" << endl;
}

void Renderer::draw(const Board& board, const History& history, int historyPage) {
    clearScreen();
    drawBoard(board);
    drawHistory(history, historyPage);
    drawFooter();
}

void Renderer::showWin(int userMoves, int autoMoves, int totalMoves) {
    setColor(14);   // yellow
    cout << "\n*** YOU WIN! ***" << endl;
    resetColor();
    cout << "User moves: " << userMoves << endl;
    cout << "Auto moves: " << autoMoves << endl;
    cout << "Total moves: " << totalMoves << endl;
    cout << "Press any key to continue..." << endl;
}