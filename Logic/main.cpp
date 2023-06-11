#include "Board.h"
#include "MainGame.hpp"
#include <QApplication>
#include "startwindow.h"

int promptNewGame();

bool promptAIPlayer(int player);
float promptAITimeLimit();

int main(int argc, char *argv[])
{


    // Initialize game, prompting user appropriately
    int newGame = 1;
    blackComputer=false;
    whiteComputer=false;
    timeLimit=0.0;
    QApplication a(argc, argv);

    StartWindow s;
    s.show();
    //initializeGame(newGame, game, blackComputer, whiteComputer, timeLimit);
    //Board w;
    //w.show();
    // Play game





    return a.exec();
}

// Initialize game appropriately
void initializeGame(int choice, Game &game,
        bool &blackComputer, bool &whiteComputer, float &timeLimit) {
    if (choice == 1) {




        game.newGame(blackComputer, whiteComputer, timeLimit);
    }

}

// Prompts user if black/white is the computer
bool promptAIPlayer(int player) {
    bool isAI = false;
    std::string str;
    char ch;
    bool validInput = false;

    do {
        std::cout << "Is " << ((player == 1) ? "black" : "white") << " the computer?" << std::endl;
        std::cout << "\ty -> Yes" << std::endl;
        std::cout << "\tn -> No" << std::endl;
        std::cout << "\tSelection: ";
        std::cin >> str;
        while (std::cin.get() != '\n');          // clear buffer
        std::istringstream iss(str);
        iss >> ch;

        if (ch == 'y') {
            isAI = true;
            validInput = true;
        }
        else if (ch == 'n') {
            isAI = false;
            validInput = true;
        }
        else {
            std::cout << "\tInvalid input. Please try again.\n" << std::endl;
        }
    }
    while (!validInput);
    std::cout << std::endl;

    return isAI;
}

// Prompts user for a time limit for a computer/AI player
float promptAITimeLimit() {
    float limit = 0;
    std::string str;
    bool validInput = false;

    do {
        std::cout << "Enter time limit for computer (seconds per move): ";
        std::cin >> str;
        while (std::cin.get() != '\n');          // clear buffer
        std::istringstream iss(str);
        iss >> limit;

        if (!iss.eof() || limit <= 0) {
            std::cout << "Invalid input. Please try again.\n" << std::endl;
        }
        else {
            validInput = true;
        }
    }
    while (!validInput);
    std::cout << std::endl;

    return limit;
}
