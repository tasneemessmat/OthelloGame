#ifndef MAINGAME_H
#define MAINGAME_H

#include <string>
#include "player.hpp"
#include "boardlogic.hpp"

class Game {
    public:
        othelloboardlogic GameLogic;
        OthelloPlayer Black;
        OthelloPlayer White;
        std::string History = "";
        int ChoosenIndex;

        int toMove = 1;
        bool gameOver = false;
        Game();
        void newGame(bool blackComputer, bool whiteComputer, float timeLimit);
        void move(int color,int index);
        bool checkGameOver();
};

void initializeGame(int choice, Game &game,
        bool &blackComputer, bool &whiteComputer, float &timeLimit);


extern Game game;
extern bool blackComputer ;
extern bool whiteComputer ;
extern float timeLimit ;

#endif // MAINGAME_H
