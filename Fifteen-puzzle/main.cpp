#include "Board.h"

int main() {
    Board board;

    cout << "=== Step 2: Move test ===" << endl;
    cout << "Initial:" << endl;
    board.print();
    cout << "isSolved: " << (board.isSolved() ? "YES" : "NO") << endl << endl;

    cout << "Move LEFT (key 75):" << endl;
    bool ok = board.move(75);
    cout << "Result: " << (ok ? "OK" : "FAIL") << endl;
    board.print();
    cout << "isSolved: " << (board.isSolved() ? "YES" : "NO") << endl << endl;

    cout << "Move DOWN (key 80) from bottom — should fail:" << endl;
    ok = board.move(80);
    cout << "Result: " << (ok ? "OK" : "FAIL") << endl;
    board.print();

    return 0;
}