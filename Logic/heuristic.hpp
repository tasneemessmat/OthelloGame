#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP

#include <numeric>
#include <unordered_set>
#include "boardlogic.hpp"

class othelloHeuristic {
    public:
        int calc(othelloboardlogic &board, int color);
    private:
        std::unordered_set<int> stableDiscs;
        std::unordered_map<int, std::list<int>> pMoves;
        int calcPotMob(othelloboardlogic &board, int color);
        void cornerStables(othelloboardlogic &board, int corner, int color);
        int weights(othelloboardlogic &board, int &color);
        int corners(othelloboardlogic &board, int &color);
        void downRight(int corner, bool &down, bool &right);
};

#endif // HEURISTIC_HPP
