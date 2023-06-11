#include "heuristic.hpp"


#define UPOFFSET -8
#define DOWNOFFSET 8
#define LEFTOFFSET -1
#define RIGHTOFFSET 1
#define UPLEFTOFFSET -9
#define UPRIGHTOFFSET -7
#define LOWLEFTOFFSET 7
#define LOWRIGHTOFFSET 9


void othelloHeuristic::downRight(int corner, bool &down, bool &right){
    if (corner == 0)
    {
        down = true;
        right = true;
    }
    else if (corner == 7)
    {
        down = true;
        right = false;
    }
    else if (corner == 56)
    {
        down = false;
        right = true;
    }
    else
    {
        down = false;
        right = false;
    }
}

int othelloHeuristic::calc(othelloboardlogic &board, int color) {
    int util = std::accumulate(board.positions.begin(), board.positions.end(), 0);
    int blackCount = std::count(board.positions.begin(), board.positions.end(), 1);
    int whiteCount = std::count(board.positions.begin(), board.positions.end(), -1);
    int diskDif;
    if (color == 1) {
        diskDif = 100 * (blackCount - whiteCount) / (blackCount + whiteCount);
    }
    else {
        diskDif = 100 * (whiteCount - blackCount) / (blackCount + whiteCount);
    }
    if (board.terminalState()) {
    	if (color == 1) {
    		return 100000*util;
    	}
    	else {
    		return -100000*util;
    	}
    	}
    int mob;
    board.findLegalMoves(1, &pMoves);
    int blackMoves = pMoves.size();
    pMoves.clear();

    board.findLegalMoves(-1, &pMoves);
    int whiteMoves = pMoves.size();
    pMoves.clear();

    if (color == 1) {
        mob = 100 * (blackMoves - whiteMoves) / (blackMoves + whiteMoves + 1);
    }
    else {
        mob = 100 * (whiteMoves - blackMoves) / (blackMoves + whiteMoves + 1);
    }

    int myPotMob = calcPotMob(board, color);
    int oppPotMob = calcPotMob(board, -color);
    int potMob =  100 * (myPotMob - oppPotMob) / (myPotMob + oppPotMob + 1);

    stableDiscs.clear();
    cornerStables(board, 0, color);
    cornerStables(board, 7, color);
    cornerStables(board, 56, color);
    cornerStables(board, 63, color);
    int myStables = stableDiscs.size();
    cornerStables(board, 0, -color);
    cornerStables(board, 7, -color);
    cornerStables(board, 56, -color);
    cornerStables(board, 63, -color);
    int opponentStables = stableDiscs.size();
    int stable = myStables - opponentStables;

    int parity;
    if ((64 - board.discsOnboardlogic) % 2 == 0) {
        parity = -1;
    }
    else {
        parity = 1;
    }

// Game is in Initial state
    if (board.discsOnboardlogic <= 20) {
        return 5*mob
            + 5*potMob
            + 20*weights(board, color)
            + 10000*corners(board, color)
            + 10000*stable;
    }
// Game is in Middle State
    else if (board.discsOnboardlogic <= 58) {
        return 10*diskDif
            + 2*mob
            + 2*potMob
            + 10*weights(board, color)
            + 100*parity
            + 10000*corners(board, color)
            + 10000*stable;
    }
// Game is in End state
    else {

        return 500*diskDif
            + 500*parity
            + 10000*corners(board, color)
            + 10000*stable;
    }
}



int othelloHeuristic::calcPotMob(othelloboardlogic &board, int color) {
    std::vector<int> boardInt = {18, 19, 20, 21,
                                      26, 27, 28, 29,
                                      34, 35, 36, 37,
                                      42, 43, 44, 45};

    int current, up, down, left, right, upperLeft, upperRight, lowerLeft, lowerRight;
    int potMob = 0;

    for (int square : boardInt) {
        current = board.positions[square];
        up = board.positions[square+UPOFFSET];
        down = board.positions[square+DOWNOFFSET];
        left = board.positions[square+LEFTOFFSET];
        right = board.positions[square+RIGHTOFFSET];
        upperLeft = board.positions[square+UPLEFTOFFSET];
        upperRight = board.positions[square+UPRIGHTOFFSET];
        lowerLeft = board.positions[square+LOWLEFTOFFSET];
        lowerRight = board.positions[square+LOWRIGHTOFFSET];

        if (current == -color && up == 0)
            potMob++;
        if (current == -color && down == 0)
        	potMob++;
        if (current == -color && right == 0)
        	potMob++;
        if (current == -color && right == 0)
        	potMob++;
        if (current == -color && upperLeft == 0)
        	potMob++;
        if (current == -color && upperRight == 0)
        	potMob++;
        if (current == -color && lowerLeft == 0)
        	potMob++;
        if (current == -color && lowerRight == 0)
        	potMob++;
    }

    std::vector<int> topRow = {10, 11, 12, 13};
    for (int square : topRow) {
        current = board.positions[square];
        left = board.positions[square+LEFTOFFSET];
        right = board.positions[square+RIGHTOFFSET];
        if (current == -color && left == 0)
        	potMob++;
        if (current == -color && right == 0)
        	potMob++;
    }

    std::vector<int> bottomRow = {50, 51, 52, 53};
    for (int square : bottomRow) {
        current = board.positions[square];
        left = board.positions[square+LEFTOFFSET];
        right = board.positions[square+RIGHTOFFSET];
        if (current == -color && left == 0)
        	potMob++;
        if (current == -color && right == 0)
        	potMob++;
    }

    std::vector<int> leftColumn = {17, 25, 33, 41};
    for (int square : leftColumn) {
        current = board.positions[square];
        up = board.positions[square+UPOFFSET];
        down = board.positions[square+DOWNOFFSET];
        if (current == -color && up == 0)
        	potMob++;
        if (current == -color && down == 0)
        	potMob++;
    }

    std::vector<int> rightColumn = {22, 30, 38, 46};
    for (int square : leftColumn) {
        current = board.positions[square];
        up = board.positions[square+UPOFFSET];
        down = board.positions[square+DOWNOFFSET];
        if (current == -color && up == 0)
            potMob++;
        if (current == -color && down == 0)
            potMob++;
    }

    return potMob;
}

void othelloHeuristic::cornerStables(othelloboardlogic &board, int corner, int color) {
    bool down, right;
    downRight(corner, down, right);

    int hrzIncr = 1, hrzStop = 7, vrtIncr = 8, vrtStop = 56;
    if (!right) {
        hrzIncr *= -1;
        hrzStop *= -1;
    }
    if (!down) {
        vrtIncr *= -1;
        vrtStop *= -1;
    }

    for (int i = corner; i != corner + hrzIncr + hrzStop; i += hrzIncr) {
        if (board.positions[i] == color) {
            for (int j = i; j != i + vrtStop; j+= vrtIncr) {
                if (board.positions[j] == color
                    && stableDiscs.find(j) == stableDiscs.end()) {
                    stableDiscs.insert(j);
                }
                else {
                    break;
                }
            }
        }
        else {
            break;
        }
    }
}




int othelloHeuristic::weights(othelloboardlogic &board, int &color) {
    std::vector<int> weight = {
         200,-100,100,50,50,100,-100,200,
        -100,-200,-50,-50,-50,-50,-200,-100,
         100,-50,100,0,0,100,-50,100,
          50,-50,0,0,0,0,-50,50,
          50,-50,0,0,0,0,-50,50,
         100,-50,100,0,0,100,-50100,
        -100,-200,-50,-50,-50,-50,-200,-100,
         200,-100,100,50,50,100,-100,200,
    };
//check corners
    if (board.positions[0] != 0) {
        weight[1]  = 0;
        weight[2]  = 0;
        weight[3]  = 0;
        weight[8]  = 0;
        weight[9]  = 0;
        weight[10] = 0;
        weight[11] = 0;
        weight[16] = 0;
        weight[17] = 0;
        weight[18] = 0;
        weight[24] = 0;
        weight[25] = 0;
    }

    if (board.positions[7] != 0) {
        weight[4]  = 0;
        weight[5]  = 0;
        weight[6]  = 0;
        weight[12] = 0;
        weight[13] = 0;
        weight[14] = 0;
        weight[15] = 0;
        weight[21] = 0;
        weight[22] = 0;
        weight[23] = 0;
        weight[30] = 0;
        weight[31] = 0;
    }

    if (board.positions[56] != 0) {
        weight[32] = 0;
        weight[33] = 0;
        weight[40] = 0;
        weight[41] = 0;
        weight[42] = 0;
        weight[48] = 0;
        weight[49] = 0;
        weight[50] = 0;
        weight[51] = 0;
        weight[57] = 0;
        weight[58] = 0;
        weight[59] = 0;
    }

    if (board.positions[63] != 0) {
        weight[38] = 0;
        weight[39] = 0;
        weight[45] = 0;
        weight[46] = 0;
        weight[47] = 0;
        weight[52] = 0;
        weight[53] = 0;
        weight[54] = 0;
        weight[55] = 0;
        weight[60] = 0;
        weight[61] = 0;
        weight[62] = 0;
    }

    if (color == 1) {
        return std::inner_product(board.positions.begin(),
                board.positions.end(), weight.begin(), 0);
    }
    else {
        return -1*std::inner_product(board.positions.begin(),
                board.positions.end(), weight.begin(), 0);
    }
}

int othelloHeuristic::corners(othelloboardlogic &board, int &color) {
    std::vector<int> corners = {0, 7, 56, 63};
    int blackCount = 0;
    int whiteCount = 0;

    for (int corner : corners) {
        if (board.positions[corner] == 1) {
            blackCount++;
        }
        else if (board.positions[corner] == -1) {
            whiteCount++;
        }
    }

    if (color == 1) {
        return 100 * (blackCount - whiteCount) / (blackCount + whiteCount + 1);
    }
    else {
        return 100 * (whiteCount - blackCount) / (blackCount + whiteCount + 1);
    }
}
