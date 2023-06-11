#ifndef boardlogic_HPP
#define boardlogic_HPP

#include <unordered_map>
#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>

class othelloboardlogic {
    public:

        std::vector<int> positions;

        int discsOnboardlogic = 4;
        float MaxTime = 0.0;


        bool passes[2] = {false, false};
        std::unordered_map<int, std::list<int>> moves;

        othelloboardlogic();
        void findLegalMoves(int color,
                std::unordered_map<int, std::list<int>> *pMoves);

        void findLegalMoveInDirection(int &disc, int &color, int direction,
                std::unordered_map<int, std::list<int>> *pMoves);


        void updateboardlogic(int color, std::pair<int, std::list<int>> move);

        bool terminalState();

        void index2coord(int index, int &colNum, int &rowNum);
};

#endif
