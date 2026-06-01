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
                bool correct = (tile == r * BOARD_SIZE + c + 1);    // correct position flag
                if (correct) {
                    setColor(10);
                }
                if (tile < 10) cout << " ";
                cout << " " << tile << " ";
                if (correct) {
                    resetColor();
                }
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

void Renderer::drawFooter() {
    cout << "\n[h] - auto-solve  [arrows] - move  [n] - new game" << endl;
}

void Renderer::draw(const Board& board, bool winShown) {
    clearScreen();
    drawBoard(board);

    if (winShown) {
        setColor(14);
        cout << "\n     *** YOU WIN ***" << endl;
        resetColor();
    }

    drawFooter();
}