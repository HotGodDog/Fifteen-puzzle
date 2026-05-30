#include "Game.h"
#include <conio.h>
#include <iostream>

int main() {
    cout << "=== 15-Puzzle (Step 5) ===" << endl;
    cout << "Interactive console game" << endl;
    cout << "Press any key to start..." << endl;
    _getch();

    Game game;
    game.run();

    return 0;
}