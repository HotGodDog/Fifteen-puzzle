#include "History.h"
#include <iostream>

int main() {
    History h;

    cout << "=== Step 4: History test ===" << endl;

    h.add(15, 3, 2, 3, 3, '→', false);
    h.add(11, 2, 2, 3, 2, '↓', false);
    h.add(7, 1, 2, 2, 2, '↓', true);
    h.add(3, 0, 1, 0, 2, '→', false);
    h.add(4, 0, 2, 0, 3, '→', true);  

    cout << "Total: " << h.size() << endl;
    cout << "User: " << h.countUser() << ", Auto: " << h.countAuto() << endl;
    cout << "Pages (per 4): " << h.totalPages(4) << endl << endl;

    cout << "Last 4 moves (newest first):" << endl;
    auto last = h.lastN(4);
    for (const auto& r : last) {
        cout << r.number << ". cell " << r.tile
            << " from [" << r.fromR << "," << r.fromC << "] " << r.arrow
            << " [" << r.toR << "," << r.toC << "]"
            << (r.isAuto ? " [author]" : " [user]") << endl;
    }

    cout << "\nPage 2 (per 2):" << endl;
    auto page2 = h.getPage(2, 2);
    for (const auto& r : page2) {
        cout << r.number << ". cell " << r.tile << endl;
    }

    h.clear();
    cout << "\nAfter clear: " << h.size() << endl;

    return 0;
}