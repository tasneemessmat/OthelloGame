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
        // positions specifies all pieces on the boardlogic. Squares on the
        // boardlogic are indexed from 0 to 63, left to right, top to bottom.
        // positions[i] is 1 for a black disc, -1 for a white disc
        std::vector<int> positions;

        int discsOnboardlogic = 4;
        float timeLimit = 0.0;

        // passes[0] and passes[1] are true if the most recent/second most
        // recent ply was a pass, resp.
        bool passes[2] = {false, false};

        // moves is a hash table specifying all possible moves from the
        // current boardlogic position. Possible moves are keys, and a list of
        // all pieces to be flipped are values.
        std::unordered_map<int, std::list<int>> moves;

        // Constructor
        othelloboardlogic();

        // Display boardlogic
        void displayboardlogic(int color);

        // Display legal moves for player
        void displayLegalMoves();

        // Finds all legal moves, writing to a reference to a hash table with
        // legal moves as keys, and a list of all discs to be flipped as values.
        void findLegalMoves(int color,
                std::unordered_map<int, std::list<int>> *pMoves);

        // Helper function to find a legal move given a disc, its color and a direction.
        // Writes the legal move and a list of all discs to be flipped as a pair to the
        // reference to a hash table.
        void findLegalMoveInDirection(int &disc, int &color, int direction,
                std::unordered_map<int, std::list<int>> *pMoves);

        // Update boardlogic after a move
        void updateboardlogic(int color, std::pair<int, std::list<int>> move);

        bool terminalState();

        // Helper function to convert boardlogic square index to coordinate
        // strings
        void index2coord(int index, int &colNum, int &rowNum);
};

#endif // boardlogic_HPP
