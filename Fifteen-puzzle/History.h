#pragma once

#include <vector>

using namespace std;

struct MoveRecord {
    int number;
    int tile;
    int fromR, fromC;
    int toR, toC;
    char arrow;
    bool isAuto;
};

class History {
public:
    void add(int tile, int fromR, int fromC, int toR, int toC, char arrow, bool isAuto);    // recording moves
    int size() const;
    int countUser() const;
    int countAuto() const;
    vector<MoveRecord> getPage(int page, int perPage) const;
    vector<MoveRecord> lastN(int n) const;
    void clear();
    int totalPages(int perPage) const;

private:
    vector<MoveRecord> records;
    int counter = 0;
};