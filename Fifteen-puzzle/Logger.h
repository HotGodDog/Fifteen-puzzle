#pragma once

#include <fstream>
#include <string>
#include "Board.h"

using namespace std;

class Logger {
public:
    Logger();
    ~Logger();

    void write(const string& msg);
    void logBoard(const Board& b);
    void logMove(const string& who, int tile, int fr, int fc, int tr, int tc, const string& dir);

private:
    ofstream log;
};