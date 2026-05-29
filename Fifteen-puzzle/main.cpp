#include "Board.h"

int main() {
    Board board;

    cout << "=== 15-Puzzle (Step 1) ===" << endl;
    cout << "Initial board:" << endl;
    board.print();

    cout << endl << "isSolved: " << (board.isSolved() ? "YES" : "NO") << endl;

    return 0;
}