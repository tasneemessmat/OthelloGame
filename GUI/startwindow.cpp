#include "startwindow.h"
#include "difficulty.h"
#include "ui_startwindow.h"
#include "MainGame.hpp"
#include "Board.h"
StartWindow::StartWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_pushButton_clicked()
{
    blackComputer=0;
    whiteComputer=0;
    initializeGame(1, game, blackComputer, whiteComputer, timeLimit);
    Board *b=new Board();
    b->show();
    this->close();
}


void StartWindow::on_pushButton_2_clicked()
{
    blackComputer=1;
    whiteComputer=0;
    Difficulty *d=new Difficulty();
    d->show();
    this->close();
    //this->close();
}


void StartWindow::on_pushButton_3_clicked()
{

     // here you can send your own message to signal the start of wait,
     // start a thread, for example.

    blackComputer=0;
    whiteComputer=1;
    Difficulty *d=new Difficulty();
    d->show();
    this->close();
    //this->close();
}


void StartWindow::on_pushButton_4_clicked()
{

    blackComputer=1;
    whiteComputer=1;
    timeLimit=1;
    initializeGame(1, game, blackComputer, whiteComputer, timeLimit);
    Board *b=new Board();
    b->show();
    this->close();
    //this->close();
}

