#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <array>
#include <chrono>
#include <climits>
#include <iterator>
#include <sstream>

#include "heuristic.hpp"

class OthelloPlayer {
public:
    int pieceColor;     // Color of the player's pieces (1 for black, -1 for white)
    bool isComputer;    // Indicates whether the player is controlled by the computer
    bool turn;          // Indicates whether it is currently the player's turn

    // Driver function for making moves, regardless of player type
    std::pair<int, std::list<int>> makeMove(othelloboardlogic &boardLogic,
            std::unordered_map<int, std::list<int>> &legalMoves,
            bool &passedLastTurn, std::string &moveHistory, int index);

private:
    struct Node {
        bool isMaxNode;                                                 // Indicates if it's a max node in the AI algorithm
        int alpha;                                                      // Alpha value for alpha-beta pruning
        int beta;                                                       // Beta value for alpha-beta pruning
        int score;                                                      // Score of the board state
        othelloboardlogic boardLogic;                                   // Board state
        std::unordered_map<int, std::list<int>>::iterator prevMoveIt;   // Iterator for the previous move
        std::unordered_map<int, std::list<int>>::iterator currMoveIt;   // Iterator for the current move
        std::unordered_map<int, std::list<int>>::iterator lastMoveIt;     // Iterator for the last move
    };

    std::array<Node, 64> nodeStack = {};                                 // Stack of nodes used in the AI algorithm
    //std::array<std::array<int, 2>, 64> killerMoves = {};               // Array of killer moves (not used in this code)

    othelloHeuristic heuristic;                                         // Heuristic object for evaluating board states

    // Prompts the human player for the next move
    std::pair<int, std::list<int>> getHumanMove(
            std::unordered_map<int, std::list<int>> &legalMoves, bool &passedLastTurn, int index);

    // Converts the string representation of coordinates to the index on the board
    int coordinatesToIndex(std::string coord);

    // Driver for the computer
    std::pair<int, std::list<int>> getComputerMove(othelloboardlogic &boardLogic,
            std::unordered_map<int, std::list<int>> &legalMoves, bool &passedLastTurn, std::string &moveHistory);

    // Returns the current time point
    std::chrono::time_point<std::chrono::system_clock> startTimer();

    // Returns the time elapsed in seconds
    float stopTimer(std::chrono::time_point<std::chrono::system_clock> startTime);

    // Performs depth-limited minimax search with alpha-beta pruning
    // Implemented using a stack to avoid recursion overhead
    // Returns the move for square -1 if the time runs out
    std::pair<int, std::list<int>> depthLimitedAlphaBeta(
            othelloboardlogic &boardLogic, int depthLimit,
            std::chrono::time_point<std::chrono::system_clock> startTime,
            float timeLimit);
};

#endif //PLAYER_HPP
