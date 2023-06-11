#include "boardlogic.hpp"


othelloboardlogic::othelloboardlogic() {
    this->positions.resize(64, 0);
}






void othelloboardlogic::findLegalMoves(int color,
        std::unordered_map<int, std::list<int>> *pMoves) {

    this->moves.clear();

    for (int i = 0; i < 64; i++) {
        if (this->positions[i] == color) {
            // Check rows
            findLegalMoveInDirection(i, color, -1, pMoves);
            findLegalMoveInDirection(i, color, 1, pMoves);

            // Check columns
            findLegalMoveInDirection(i, color, -8, pMoves);
            findLegalMoveInDirection(i, color, 8, pMoves);

            // Check diagonals
            findLegalMoveInDirection(i, color, -9, pMoves);
            findLegalMoveInDirection(i, color, 9, pMoves);
            findLegalMoveInDirection(i, color, -7, pMoves);
            findLegalMoveInDirection(i, color, 7, pMoves);
        }
    }
}


void othelloboardlogic::findLegalMoveInDirection(int &disc, int &color, int direction,
        std::unordered_map<int, std::list<int>> *pMoves) {
    std::pair<int, std::list<int>> legalMove;
    std::list<int> flippedDiscs;
    int currentSquare = 0;
    int row1 = 0, col1 = 0, row2 = 0, col2 = 0;

    for (int i = disc + direction; i < 64 && i > -1; i += direction) {

        index2coord(i-direction, col1, row1);
        index2coord(i, col2, row2);
        if (abs(col1 - col2) > 1 || abs(row1 - row2) > 1) {
            break;
        }


        currentSquare = this->positions[i];
        if (currentSquare == color ||
                (currentSquare == 0 && flippedDiscs.empty())) {
            break;
        }
        else if (currentSquare == -color) {
            flippedDiscs.push_front(i);
            continue;
        }

        else if (currentSquare == 0 && !flippedDiscs.empty()) {
            std::unordered_map<int, std::list<int>>::iterator it = pMoves->find(i);

            if (it != pMoves->end()) {
                it->second.merge(flippedDiscs);
            }
            else {
                legalMove.first = i;
                legalMove.second = flippedDiscs;
                pMoves->insert(legalMove);
            }

            break;
        }
    }
}


void othelloboardlogic::updateboardlogic(int color, std::pair<int, std::list<int>> move) {
    int square = move.first;
    std::list<int> flippedDiscs = move.second;

    this->positions[square] = color;
    for (auto disc : flippedDiscs) {
        this->positions[disc] = color;
    }
}


bool othelloboardlogic::terminalState() {
    if (this->passes[0] && this->passes[1]) {
        return true;
    }
    return false;
}


void othelloboardlogic::index2coord(int index, int &colNum, int &rowNum) {
    colNum = index % 8;
    rowNum = index / 8;
}
