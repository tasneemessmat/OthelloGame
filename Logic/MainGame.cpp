#include "MainGame.hpp"
Game game;
bool blackComputer ;
bool whiteComputer ;
float timeLimit ;
int dead;

// Constructor
Game::Game() {
    this->GameLogic.positions.resize(64, 0);
}

// Initialize new game
void Game::newGame(bool BlackIsAi, bool WhiteIsAi,
        float MaxTime) {
    // Initialize boardlogic
    std::vector<int> MatrixInit(64, 0);
    dead=0;
    MatrixInit[27] = -1;
    MatrixInit[28] = 1;
    MatrixInit[35] = 1;
    MatrixInit[36] = -1;
    this->GameLogic.positions.swap(MatrixInit);

    // Initialize players
    this->Black.pieceColor = 1;
    this->Black.isComputer = BlackIsAi;
    this->White.pieceColor = -1;
    this->White.isComputer = WhiteIsAi;

    // Initialize player to move
    this->toMove = 1;

    // Initialize time limit
    this->GameLogic.MaxTime = MaxTime;
}

// Load game from file

// Make a move
void Game::move(int color,int index) {
    std::pair<int, std::list<int>> move;

    if (color == 1) {

        move = this->Black.makeMove(this->GameLogic, this->GameLogic.moves,
                this->GameLogic.passes[0], this->History,index);
    } 
    else if (color == -1) {

        move = this->White.makeMove(this->GameLogic, this->GameLogic.moves,
                this->GameLogic.passes[0], this->History,index);
    }

    if (!this->GameLogic.passes[0]) {
        this->GameLogic.updateboardlogic(color, move);
    }


}

// Update status of the game
bool Game::checkGameOver() {
    if (this->GameLogic.passes[0] && this->GameLogic.passes[1]) {

        this->gameOver = true;
        return true;
    }
    else {
        if (!this->GameLogic.passes[0]) {
            this->GameLogic.discsOnboardlogic++;
        }

        this->GameLogic.passes[1] = this->GameLogic.passes[0];
        this->GameLogic.passes[0] = false;
        return false;
    }
}



