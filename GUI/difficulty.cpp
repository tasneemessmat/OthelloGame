#include "difficulty.h"
#include "ui_difficulty.h"
#include "MainGame.hpp"
#include "Board.h"
Difficulty::Difficulty(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Difficulty)
{
    ui->setupUi(this);
}

Difficulty::~Difficulty()
{
    delete ui;
}

void Difficulty::on_PEasy_clicked()
{
    timeLimit=0.1;
    initializeGame(1, game, blackComputer, whiteComputer, timeLimit);
    Board *b=new Board();
    b->show();
    this->close();
}


void Difficulty::on_PMedium_clicked()
{
    timeLimit=0.5;
    initializeGame(1, game, blackComputer, whiteComputer, timeLimit);
    Board *b=new Board();
    b->show();
    this->close();
}


void Difficulty::on_PHard_clicked()
{
    timeLimit=2;
    initializeGame(1, game, blackComputer, whiteComputer, timeLimit);
    Board *b=new Board();
    b->show();
    this->close();
}

