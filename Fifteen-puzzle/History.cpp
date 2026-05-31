#include "History.h"
#include <algorithm>

void History::add(int tile, int fromR, int fromC, int toR, int toC, char arrow, bool isAuto) {
    MoveRecord rec;
    rec.number = ++counter;
    rec.tile = tile;
    rec.fromR = fromR;
    rec.fromC = fromC;
    rec.toR = toR;
    rec.toC = toC;
    rec.arrow = arrow;
    rec.isAuto = isAuto;
    records.push_back(rec);
}

int History::size() const {
    return (int)records.size();
}

int History::countUser() const {
    int cnt = 0;
    for (const auto& r : records) {
        if (!r.isAuto) ++cnt;
    }
    return cnt;
}

int History::countAuto() const {
    int cnt = 0;
    for (const auto& r : records) {
        if (r.isAuto) ++cnt;
    }
    return cnt;
}

vector<MoveRecord> History::getPage(int page, int perPage) const {
    vector<MoveRecord> result;
    if (page < 1 || perPage < 1) return result;

    int start = (int)records.size() - 1 - (page - 1) * perPage;
    if (start < 0) return result;

    int end = max(start - perPage + 1, 0);
    for (int i = start; i >= end; --i) {
        result.push_back(records[i]);
    }
    return result;
}

vector<MoveRecord> History::lastN(int n) const {
    return getPage(1, n);
}

void History::clear() {
    records.clear();
    counter = 0;
}

int History::totalPages(int perPage) const {
    if (perPage < 1) return 0;
    return ((int)records.size() + perPage - 1) / perPage;
}