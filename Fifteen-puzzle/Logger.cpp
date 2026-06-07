#include "Logger.h"

Logger::Logger() {
    log.open("game_log.txt", ios::app);
}

Logger::~Logger() {
    if (log.is_open()) log.close();
}

void Logger::write(const string& msg) {
    if (log.is_open()) log << msg << endl;
}

void Logger::logBoard(const Board& b) {
    write("Board state:");
    for (int r = 0; r < BOARD_SIZE; ++r) {
        string line;
        for (int c = 0; c < BOARD_SIZE; ++c) {
            int t = b.getTile(r, c);
            if (t == 0) {
                line += " .\t";
            }
            else {
                line += to_string(t) + "\t";
            }
        }
        write(line);
    }
}

void Logger::logMove(const string& who, int tile, int fr, int fc, int tr, int tc, const string& dir) {
    write(who + ": move " + dir + " | tile " + to_string(tile)
        + " from [" + to_string(fr) + "," + to_string(fc) + "]"
        + " to [" + to_string(tr) + "," + to_string(tc) + "]");
}