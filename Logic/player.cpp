#include "heuristic.hpp"
#include "player.hpp"
#include "MainGame.hpp"
#include <synchapi.h>
#include "boardlogic.hpp"
/**
 * Makes a move for the player in the Othello game based on the provided index.
 *
 * @param boardLogic       An instance of the Othello board logic representing the current state of the game.
 * @param legalMoves       A map of legal moves available to the player.
 * @param passedLastTurn   A boolean flag indicating if the last turn was passed.
 * @param moveHistory      A string representing the move history.
 * @param index            The index of the desired move (for human player).
 * @return                 A pair containing the chosen move.
 */
std::pair<int, std::list<int>> OthelloPlayer::makeMove(othelloboardlogic& boardLogic,
    std::unordered_map<int, std::list<int>>& legalMoves,
    bool &passedLastTurn, std::string &moveHistory, int index) {
    std::pair<int, std::list<int>> moveChoice;

    // If the player is a computer, make a computer move
    if (this->isComputer) {
        moveChoice = this->getComputerMove(boardLogic, legalMoves, passedLastTurn, moveHistory);
    }
    // If the player is a human, make a human move
    else {
        moveChoice = this->getHumanMove(legalMoves, passedLastTurn, index);
    }

    // Append the chosen move to the move history
    moveHistory.append(std::to_string(moveChoice.first) + ",");

    return moveChoice;
}

/**
 * Gets the human player's move in the Othello game based on the provided index.
 *
 * @param legalMoves       A map of legal moves available to the human player.
 * @param passedLastTurn   A boolean flag indicating if the last turn was passed.
 * @param index            The index of the desired move.
 * @return                 A pair containing the selected move.
 */
std::pair<int, std::list<int>> OthelloPlayer::getHumanMove(
    std::unordered_map<int, std::list<int>>& legalMoves, bool& passedLastTurn, int index)
{
    std::pair<int, std::list<int>> selectedMove;
    int requestedMoveIndex = 0;
    int desiredMoveIndex = -1;

    // Check if there are no legal moves available
    if (legalMoves.empty()) {
        passedLastTurn = true;
        return selectedMove;
    }

    // Check if the index is valid and the corresponding move exists in legalMoves
    desiredMoveIndex = index;
    if (desiredMoveIndex != -1 && legalMoves.find(desiredMoveIndex) != legalMoves.end()) {
        return *legalMoves.find(desiredMoveIndex);
    }

    int currentMoveIndex = 0;
    // Iterate over the legalMoves map to find the move at the specified moveNum
    for (std::pair<int, std::list<int>> moveEntry : legalMoves) {
        selectedMove = moveEntry;
        currentMoveIndex++;
        if (currentMoveIndex == requestedMoveIndex) {
            break;
        }
    }

    return selectedMove;
}

/**
 * Gets the computer's move in the Othello game by performing an AI search algorithm.
 * It selects the best move based on the current state of the board and the specified time constraints.
 *
 * @param boardlogic      An instance of the Othello board logic representing the current state of the game.
 * @param legalMoves      A map of legal moves available to the computer player.
 * @param passedLastTurn  A boolean flag indicating if the last turn was passed.
 * @param moveHistory     A string representing the move history.
 * @return                A pair containing the best move selected by the computer player.
 */
std::pair<int, std::list<int>> OthelloPlayer::getComputerMove(
    othelloboardlogic &boardlogic, std::unordered_map<int, std::list<int>> &legalMoves,
    bool &passedLastTurn, std::string &moveHistory)
{
    // Start the timer
    std::chrono::time_point<std::chrono::system_clock> startTime = this->startTimer();

    std::pair<int, std::list<int>> selectedMove;
    std::pair<int, std::list<int>> bestMove;

    // If there are no legal moves, pass the turn
    if (legalMoves.empty()) {
        passedLastTurn = true;
        return bestMove;
    }
    // If there is only one legal move, choose it as the best move
    else if (legalMoves.size() == 1) {
        bestMove = *legalMoves.begin();
    }
    // If the time limit is less than 0.5 seconds, choose the first legal move
    else if (timeLimit < 0.5) {
        bestMove = *legalMoves.begin();
    }
    else {
        int maxDepth = 64 - boardlogic.discsOnboardlogic;

        // If the remaining depth is less than 10, perform depth-limited alpha-beta search
        if (maxDepth < 10) {
            bestMove = this->depthLimitedAlphaBeta(boardlogic, maxDepth, startTime, boardlogic.MaxTime);
        }
        else {
            // Perform iterative deepening with increasing depth limits
            for (int depthLimit = 1; depthLimit <= maxDepth; depthLimit++) {
                selectedMove = this->depthLimitedAlphaBeta(boardlogic, depthLimit, startTime, boardlogic.MaxTime);

                // If no valid move is found, break the loop
                if (selectedMove.first == -1) {
                    break;
                }
                else {
                    bestMove = selectedMove;
                }

                // If the elapsed time exceeds half of the maximum allowed time, break the loop
                if (this->stopTimer(startTime) > 0.5 * boardlogic.MaxTime) {
                    break;
                }
            }
        }
    }

    // Convert the best move index to row and column numbers
    int rowNumber = 0, columnNumber = 0;
    boardlogic.index2coord(bestMove.first, columnNumber, rowNumber);

    return bestMove;
}



/**
 * Start the timer and get the current time.
 * @return The start time of the timer.
 */
std::chrono::time_point<std::chrono::system_clock> OthelloPlayer::startTimer() {
    // Get the current time
    std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();

    // Return the start time of the timer
    return startTime;
}



/**
 * Stop the timer and calculate the elapsed time in seconds.
 * @param startTime The start time of the timer.
 * @return The elapsed time in seconds.
 */
float OthelloPlayer::stopTimer(std::chrono::time_point<std::chrono::system_clock> startTime) {
    // Get the current time
    std::chrono::time_point<std::chrono::system_clock> endTime = std::chrono::system_clock::now();

    // Calculate the elapsed time in seconds
    std::chrono::duration<float> elapsedSeconds = endTime - startTime;

    // Return the elapsed time in seconds
    return elapsedSeconds.count();
}


/**
 * Performs a depth-limited alpha-beta search on the given Othello board using iterative deepening.
 * It evaluates the positions up to the specified depth limit and uses alpha-beta pruning to improve efficiency.
 * The function returns the best move found along with its score.
 *
 * @param boardlogic   An instance of the Othello board logic representing the current state of the game.
 * @param depthLimit   The maximum depth to search.
 * @param startTime    The start time of the search.
 * @param timeLimit    The maximum time allowed for the search.
 * @return             A pair containing the best move found and its score.
 */

std::pair<int, std::list<int>> OthelloPlayer::depthLimitedAlphaBeta(
        othelloboardlogic &boardLogic, int depthLimit,
        std::chrono::time_point<std::chrono::system_clock> startTime,
        float timeLimit) {

    // Initialize the root node of the search tree
    this->nodeStack[0].isMaxNode = true;
    this->nodeStack[0].alpha = INT_MIN;
    this->nodeStack[0].beta = INT_MAX;
    this->nodeStack[0].score = INT_MIN;
    this->nodeStack[0].boardLogic = boardLogic;
    this->nodeStack[0].currMoveIt = this->nodeStack[0].boardLogic.moves.begin();
    this->nodeStack[0].prevMoveIt = this->nodeStack[0].currMoveIt;
    this->nodeStack[0].lastMoveIt = this->nodeStack[0].boardLogic.moves.end();

    int currentDepth = 0;
    int leafScore = 0;
    std::unordered_map<int, std::list<int>>::iterator bestMove = this->nodeStack[0].boardLogic.moves.begin();

    while (true) {
        // If all moves at this depth have been traversed
        if (this->nodeStack[currentDepth].currMoveIt == this->nodeStack[currentDepth].lastMoveIt) {
            // If we have reached the root node, update the best move and alpha value
            if (currentDepth-- == 0) {
                // Update the best move if the current score is higher or equal (with a 50% chance) to the previous best score
                if (this->nodeStack[1].score > this->nodeStack[0].score
                        || (this->nodeStack[1].score == this->nodeStack[0].score && rand() % 2 == 0)) {
                    this->nodeStack[0].score = this->nodeStack[1].score;
                    bestMove = this->nodeStack[0].prevMoveIt;
                }

                // Update the alpha value if the current score is higher
                if (this->nodeStack[0].score > this->nodeStack[0].alpha) {
                    this->nodeStack[0].alpha = this->nodeStack[0].score;
                }

                break;
            }

            // Update the score and alpha/beta values based on whether it is a max node or min node
            if (this->nodeStack[currentDepth].isMaxNode) {
                // Update the score and best move if the current score is higher or equal (with a 50% chance) to the previous best score
                if (this->nodeStack[currentDepth+1].score > this->nodeStack[currentDepth].score
                        || (this->nodeStack[currentDepth+1].score == this->nodeStack[currentDepth].score && rand() % 2 == 0)) {
                    this->nodeStack[currentDepth].score = this->nodeStack[currentDepth+1].score;
                    if (currentDepth == 0) {
                        bestMove = this->nodeStack[0].prevMoveIt;
                    }
                }

                // Update the alpha value if the current score is higher
                if (this->nodeStack[currentDepth].score > this->nodeStack[currentDepth].alpha) {
                    this->nodeStack[currentDepth].alpha = this->nodeStack[currentDepth].score;
                }
            }
            else {
                // Update the score if the current score is lower
                if (this->nodeStack[currentDepth+1].score < this->nodeStack[currentDepth].score) {
                    this->nodeStack[currentDepth].score = this->nodeStack[currentDepth+1].score;
                }

                // Update the beta value if the current score is lower
                if (this->nodeStack[currentDepth].score < this->nodeStack[currentDepth].beta) {
                    this->nodeStack[currentDepth].beta = this->nodeStack[currentDepth].score;
                }
            }
        }
        // If we can prune the subtree
        else if (this->nodeStack[currentDepth].beta <= this->nodeStack[currentDepth].alpha) {
            // If we have reached the root node, update the best move and alpha value
            if (currentDepth-- == 0) {
                // Update the best move if the current score is higher or equal (with a 50% chance) to the previous best score
                if (this->nodeStack[1].score > this->nodeStack[0].score
                    || (this->nodeStack[1].score == this->nodeStack[0].score && rand() % 2 == 0)) {
                    this->nodeStack[0].score = this->nodeStack[1].score;
                    bestMove = this->nodeStack[0].prevMoveIt;
                }

                // Update the alpha value if the current score is higher
                if (this->nodeStack[0].score > this->nodeStack[0].alpha) {
                    this->nodeStack[0].alpha = this->nodeStack[0].score;
                }

                break;
            }

            // Update the score and alpha/beta values based on whether it is a max node or min node
            if (this->nodeStack[currentDepth].isMaxNode) {
                // Update the score and best move if the current score is higher or equal (with a 50% chance) to the previous best score
                if (this->nodeStack[currentDepth+1].score > this->nodeStack[currentDepth].score
                    || (this->nodeStack[currentDepth+1].score == this->nodeStack[currentDepth].score && rand() % 2 == 0)) {
                    this->nodeStack[currentDepth].score = this->nodeStack[currentDepth+1].score - 1;
                    if (currentDepth == 0) {
                        bestMove = this->nodeStack[0].prevMoveIt;
                    }
                }

                // Update the alpha value if the current score is higher
                if (this->nodeStack[currentDepth].score > this->nodeStack[currentDepth].alpha) {
                    this->nodeStack[currentDepth].alpha = this->nodeStack[currentDepth].score;
                }
            }
            else {
                // Update the score if the current score is lower
                if (this->nodeStack[currentDepth+1].score < this->nodeStack[currentDepth].score) {
                    this->nodeStack[currentDepth].score = this->nodeStack[currentDepth+1].score + 1;
                }

                // Update the beta value if the current score is lower
                if (this->nodeStack[currentDepth].score < this->nodeStack[currentDepth].beta) {
                    this->nodeStack[currentDepth].beta = this->nodeStack[currentDepth].score;
                }
            }
        }
        else {
            // Expand the next child node by making the corresponding move
            this->nodeStack[currentDepth+1].boardLogic = this->nodeStack[currentDepth].boardLogic;
            this->nodeStack[currentDepth+1].boardLogic.updateboardlogic(
                    (this->nodeStack[currentDepth].isMaxNode ? this->pieceColor : -this->pieceColor),
                    *this->nodeStack[currentDepth].currMoveIt);
            this->nodeStack[currentDepth].prevMoveIt = this->nodeStack[currentDepth].currMoveIt;
            this->nodeStack[currentDepth].currMoveIt++;

            // If we have not reached the depth limit, go deeper into the tree
            if (currentDepth + 1 < depthLimit) {
                currentDepth++;
                this->nodeStack[currentDepth].isMaxNode = !this->nodeStack[currentDepth-1].isMaxNode;
                this->nodeStack[currentDepth].score =
                    (this->nodeStack[currentDepth].isMaxNode ? INT_MIN : INT_MAX);
                this->nodeStack[currentDepth].alpha = this->nodeStack[currentDepth-1].alpha;
                this->nodeStack[currentDepth].beta = this->nodeStack[currentDepth-1].beta;
                this->nodeStack[currentDepth].boardLogic.findLegalMoves(
                        (this->nodeStack[currentDepth].isMaxNode ? this->pieceColor : -this->pieceColor),
                        &this->nodeStack[currentDepth].boardLogic.moves);
                this->nodeStack[currentDepth].currMoveIt =
                    this->nodeStack[currentDepth].boardLogic.moves.begin();
                this->nodeStack[currentDepth].prevMoveIt =
                    this->nodeStack[currentDepth].currMoveIt;
                this->nodeStack[currentDepth].lastMoveIt = this->nodeStack[currentDepth].boardLogic.moves.end();
            }
            else {
                // Evaluate the leaf node using the heuristic function
                leafScore = this->heuristic.calc(
                        this->nodeStack[currentDepth+1].boardLogic, this->pieceColor);

                // Update the score and best move based on whether it is a max node or min node
                if (this->nodeStack[currentDepth].isMaxNode) {
                    // Update the score and best move if the current score is higher
                    if (leafScore > this->nodeStack[currentDepth].score) {
                        this->nodeStack[currentDepth].score = leafScore;
                        if (currentDepth == 0) {
                            bestMove = this->nodeStack[0].prevMoveIt;
                        }
                    }

                    // Update the alpha value if the current score is higher
                    if (this->nodeStack[currentDepth].score > this->nodeStack[currentDepth].alpha) {
                        this->nodeStack[currentDepth].alpha = this->nodeStack[currentDepth].score;
                    }
                }
                else {
                    // Update the score if the current score is lower
                    if (leafScore < this->nodeStack[currentDepth].score) {
                        this->nodeStack[currentDepth].score = leafScore;
                    }

                    // Update the beta value if the current score is lower
                    if (this->nodeStack[currentDepth].score < this->nodeStack[currentDepth].beta) {
                        this->nodeStack[currentDepth].beta = this->nodeStack[currentDepth].score;
                    }
                }
            }
        }

        // Check if the time limit has been reached
        if (this->stopTimer(startTime) > 0.998 * timeLimit) {
            std::pair<int, std::list<int>> move;
            move.first = -1;
            return move;
        }
    }

    return *bestMove;
}

