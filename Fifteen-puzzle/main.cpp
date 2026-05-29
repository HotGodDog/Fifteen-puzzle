#include "Board.h"

int main() {
    Board board;

    cout << "=== Step 3: Shuffle test ===" << endl;

    for (int i = 0; i < 5; ++i) {
        board.shuffle();
        cout << "\n--- Game " << (i + 1) << " ---" << endl;
        board.print();
    }

    return 0;
}