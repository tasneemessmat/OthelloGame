#include "board.h"
#include "ui_board.h"
#include "MainGame.hpp"
#include "iostream"
#include <QTime>
#include <qthread.h>
#include <synchapi.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>
#include <unistd.h>
using namespace std;
vector<int> v{1,-1,0,1,-1,0,1,-1,1,-1,0,1,-1,0,1,-1,1,-1,0,1,-1,0,1,-1,1,-1,0,1,-1,0,1,-1,1,-1,0,1,-1,0,1,-1,1,-1,0,1,-1,0,1,-1,1,-1,0,1,-1,0,1,-1,1,-1,0,1,-1,0,1,-1};
QVector <int> ValidMoves;
int flag;




Board::Board(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Board)
{
    flag=0;

    game.Black.turn=1;
    game.White.turn=0;
    ui->setupUi(this);

    ui->PNextStep->setVisible(false);
    game.GameLogic.findLegalMoves(1, &game.GameLogic.moves);
    //game.GameLogic();

    ValidMoves.resize(64,0);
    INIT_PUSH();


    LOGIC_SetCircles(game.GameLogic.positions);

    ValidInterface();

    //SetValidMoves(ValidMoves);
    //ValidInterface();

    if(game.Black.isComputer&&!game.White.isComputer)
    {
        //Ai
        game.move(1,0);
        LOGIC_SetCircles(game.GameLogic.positions);
        game.GameLogic.findLegalMoves(-1, &game.GameLogic.moves);
        ValidInterface();
    }
    if(game.Black.isComputer&&game.White.isComputer)
    {
        ui->PNextStep->setVisible(true);
    }




}

Board::~Board()
{
    delete ui;
}




void Board::LOGIC_SetCircles( vector<int> v)
{
    QVector<int> QV;
    for(int i=0;i<v.size();i++)
    {
        QV.push_back(v.at(i));
    }
    SetCircles(QV);
}
void Board::LOGIC_SetValidMoves(vector<int> v)
{
    QVector<int> QV;
    for(int i=0;i<v.size();i++)
    {
        QV.push_back(v.at(i));
    }
    SetValidMoves(QV);
}


void Board::SetCircles(QVector<int> v)
{
    ui->P0_0->setIcon(GetImage(v.at(0+0)));
    ui->P0_1->setIcon(GetImage(v.at(0+1)));
    ui->P0_2->setIcon(GetImage(v.at(0+2)));
    ui->P0_3->setIcon(GetImage(v.at(0+3)));
    ui->P0_4->setIcon(GetImage(v.at(0+4)));
    ui->P0_5->setIcon(GetImage(v.at(0+5)));
    ui->P0_6->setIcon(GetImage(v.at(0+6)));
    ui->P0_7->setIcon(GetImage(v.at(0+7)));

    ui->P1_0->setIcon(GetImage(v.at(8+0)));
    ui->P1_1->setIcon(GetImage(v.at(8+1)));
    ui->P1_2->setIcon(GetImage(v.at(8+2)));
    ui->P1_3->setIcon(GetImage(v.at(8+3)));
    ui->P1_4->setIcon(GetImage(v.at(8+4)));
    ui->P1_5->setIcon(GetImage(v.at(8+5)));
    ui->P1_6->setIcon(GetImage(v.at(8+6)));
    ui->P1_7->setIcon(GetImage(v.at(8+7)));

    ui->P2_0->setIcon(GetImage(v.at(16+0)));
    ui->P2_1->setIcon(GetImage(v.at(16+1)));
    ui->P2_2->setIcon(GetImage(v.at(16+2)));
    ui->P2_3->setIcon(GetImage(v.at(16+3)));
    ui->P2_4->setIcon(GetImage(v.at(16+4)));
    ui->P2_5->setIcon(GetImage(v.at(16+5)));
    ui->P2_6->setIcon(GetImage(v.at(16+6)));
    ui->P2_7->setIcon(GetImage(v.at(16+7)));

    ui->P3_0->setIcon(GetImage(v.at(24+0)));
    ui->P3_1->setIcon(GetImage(v.at(24+1)));
    ui->P3_2->setIcon(GetImage(v.at(24+2)));
    ui->P3_3->setIcon(GetImage(v.at(24+3)));
    ui->P3_4->setIcon(GetImage(v.at(24+4)));
    ui->P3_5->setIcon(GetImage(v.at(24+5)));
    ui->P3_6->setIcon(GetImage(v.at(24+6)));
    ui->P3_7->setIcon(GetImage(v.at(24+7)));

    ui->P4_0->setIcon(GetImage(v.at(32+0)));
    ui->P4_1->setIcon(GetImage(v.at(32+1)));
    ui->P4_2->setIcon(GetImage(v.at(32+2)));
    ui->P4_3->setIcon(GetImage(v.at(32+3)));
    ui->P4_4->setIcon(GetImage(v.at(32+4)));
    ui->P4_5->setIcon(GetImage(v.at(32+5)));
    ui->P4_6->setIcon(GetImage(v.at(32+6)));
    ui->P4_7->setIcon(GetImage(v.at(32+7)));

    ui->P5_0->setIcon(GetImage(v.at(40+0)));
    ui->P5_1->setIcon(GetImage(v.at(40+1)));
    ui->P5_2->setIcon(GetImage(v.at(40+2)));
    ui->P5_3->setIcon(GetImage(v.at(40+3)));
    ui->P5_4->setIcon(GetImage(v.at(40+4)));
    ui->P5_5->setIcon(GetImage(v.at(40+5)));
    ui->P5_6->setIcon(GetImage(v.at(40+6)));
    ui->P5_7->setIcon(GetImage(v.at(40+7)));

    ui->P6_0->setIcon(GetImage(v.at(48+0)));
    ui->P6_1->setIcon(GetImage(v.at(48+1)));
    ui->P6_2->setIcon(GetImage(v.at(48+2)));
    ui->P6_3->setIcon(GetImage(v.at(48+3)));
    ui->P6_4->setIcon(GetImage(v.at(48+4)));
    ui->P6_5->setIcon(GetImage(v.at(48+5)));
    ui->P6_6->setIcon(GetImage(v.at(48+6)));
    ui->P6_7->setIcon(GetImage(v.at(48+7)));

    ui->P7_0->setIcon(GetImage(v.at(56+0)));
    ui->P7_1->setIcon(GetImage(v.at(56+1)));
    ui->P7_2->setIcon(GetImage(v.at(56+2)));
    ui->P7_3->setIcon(GetImage(v.at(56+3)));
    ui->P7_4->setIcon(GetImage(v.at(56+4)));
    ui->P7_5->setIcon(GetImage(v.at(56+5)));
    ui->P7_6->setIcon(GetImage(v.at(56+6)));
    ui->P7_7->setIcon(GetImage(v.at(56+7)));


    ui->P0_0->setIconSize(GetSize(v.at(0+0)));
    ui->P0_1->setIconSize(GetSize(v.at(0+1)));
    ui->P0_2->setIconSize(GetSize(v.at(0+2)));
    ui->P0_3->setIconSize(GetSize(v.at(0+3)));
    ui->P0_4->setIconSize(GetSize(v.at(0+4)));
    ui->P0_5->setIconSize(GetSize(v.at(0+5)));
    ui->P0_6->setIconSize(GetSize(v.at(0+6)));
    ui->P0_7->setIconSize(GetSize(v.at(0+7)));

    ui->P1_0->setIconSize(GetSize(v.at(8+0)));
    ui->P1_1->setIconSize(GetSize(v.at(8+1)));
    ui->P1_2->setIconSize(GetSize(v.at(8+2)));
    ui->P1_3->setIconSize(GetSize(v.at(8+3)));
    ui->P1_4->setIconSize(GetSize(v.at(8+4)));
    ui->P1_5->setIconSize(GetSize(v.at(8+5)));
    ui->P1_6->setIconSize(GetSize(v.at(8+6)));
    ui->P1_7->setIconSize(GetSize(v.at(8+7)));

    ui->P2_0->setIconSize(GetSize(v.at(16+0)));
    ui->P2_1->setIconSize(GetSize(v.at(16+1)));
    ui->P2_2->setIconSize(GetSize(v.at(16+2)));
    ui->P2_3->setIconSize(GetSize(v.at(16+3)));
    ui->P2_4->setIconSize(GetSize(v.at(16+4)));
    ui->P2_5->setIconSize(GetSize(v.at(16+5)));
    ui->P2_6->setIconSize(GetSize(v.at(16+6)));
    ui->P2_7->setIconSize(GetSize(v.at(16+7)));

    ui->P3_0->setIconSize(GetSize(v.at(24+0)));
    ui->P3_1->setIconSize(GetSize(v.at(24+1)));
    ui->P3_2->setIconSize(GetSize(v.at(24+2)));
    ui->P3_3->setIconSize(GetSize(v.at(24+3)));
    ui->P3_4->setIconSize(GetSize(v.at(24+4)));
    ui->P3_5->setIconSize(GetSize(v.at(24+5)));
    ui->P3_6->setIconSize(GetSize(v.at(24+6)));
    ui->P3_7->setIconSize(GetSize(v.at(24+7)));

    ui->P4_0->setIconSize(GetSize(v.at(32+0)));
    ui->P4_1->setIconSize(GetSize(v.at(32+1)));
    ui->P4_2->setIconSize(GetSize(v.at(32+2)));
    ui->P4_3->setIconSize(GetSize(v.at(32+3)));
    ui->P4_4->setIconSize(GetSize(v.at(32+4)));
    ui->P4_5->setIconSize(GetSize(v.at(32+5)));
    ui->P4_6->setIconSize(GetSize(v.at(32+6)));
    ui->P4_7->setIconSize(GetSize(v.at(32+7)));

    ui->P5_0->setIconSize(GetSize(v.at(40+0)));
    ui->P5_1->setIconSize(GetSize(v.at(40+1)));
    ui->P5_2->setIconSize(GetSize(v.at(40+2)));
    ui->P5_3->setIconSize(GetSize(v.at(40+3)));
    ui->P5_4->setIconSize(GetSize(v.at(40+4)));
    ui->P5_5->setIconSize(GetSize(v.at(40+5)));
    ui->P5_6->setIconSize(GetSize(v.at(40+6)));
    ui->P5_7->setIconSize(GetSize(v.at(40+7)));

    ui->P6_0->setIconSize(GetSize(v.at(48+0)));
    ui->P6_1->setIconSize(GetSize(v.at(48+1)));
    ui->P6_2->setIconSize(GetSize(v.at(48+2)));
    ui->P6_3->setIconSize(GetSize(v.at(48+3)));
    ui->P6_4->setIconSize(GetSize(v.at(48+4)));
    ui->P6_5->setIconSize(GetSize(v.at(48+5)));
    ui->P6_6->setIconSize(GetSize(v.at(48+6)));
    ui->P6_7->setIconSize(GetSize(v.at(48+7)));

    ui->P7_0->setIconSize(GetSize(v.at(56+0)));
    ui->P7_1->setIconSize(GetSize(v.at(56+1)));
    ui->P7_2->setIconSize(GetSize(v.at(56+2)));
    ui->P7_3->setIconSize(GetSize(v.at(56+3)));
    ui->P7_4->setIconSize(GetSize(v.at(56+4)));
    ui->P7_5->setIconSize(GetSize(v.at(56+5)));
    ui->P7_6->setIconSize(GetSize(v.at(56+6)));
    ui->P7_7->setIconSize(GetSize(v.at(56+7)));
    flag=1;

}
QIcon Board::GetImage(int image)
{
    QPixmap black("C:/Users/user/OneDrive/Documents/OthelloGame/images/black_disk.png");
    QPixmap white("C:/Users/user/OneDrive/Documents/OthelloGame/images/white_disk.png");
    QPixmap blank("C:/Users/user/OneDrive/Documents/OthelloGame/images/blank.png");
    if(image==1)
    {
        QIcon BLACK(black);
        return BLACK;
    }
    else if(image==-1)
    {
        QIcon WHITE(white);
        return WHITE;
    }
    else
    {
        QIcon BLANK(blank);
        return BLANK;
    }
}
void Board::SetValidMoves(QVector<int> v)
{

    ui->P0_0->setStyleSheet(SetBorder(v.at(0+0)));
    ui->P0_1->setStyleSheet(SetBorder(v.at(0+1)));
    ui->P0_2->setStyleSheet(SetBorder(v.at(0+2)));
    ui->P0_3->setStyleSheet(SetBorder(v.at(0+3)));
    ui->P0_4->setStyleSheet(SetBorder(v.at(0+4)));
    ui->P0_5->setStyleSheet(SetBorder(v.at(0+5)));
    ui->P0_6->setStyleSheet(SetBorder(v.at(0+6)));
    ui->P0_7->setStyleSheet(SetBorder(v.at(0+7)));

    ui->P1_0->setStyleSheet(SetBorder(v.at(8+0)));
    ui->P1_1->setStyleSheet(SetBorder(v.at(8+1)));
    ui->P1_2->setStyleSheet(SetBorder(v.at(8+2)));
    ui->P1_3->setStyleSheet(SetBorder(v.at(8+3)));
    ui->P1_4->setStyleSheet(SetBorder(v.at(8+4)));
    ui->P1_5->setStyleSheet(SetBorder(v.at(8+5)));
    ui->P1_6->setStyleSheet(SetBorder(v.at(8+6)));
    ui->P1_7->setStyleSheet(SetBorder(v.at(8+7)));

    ui->P2_0->setStyleSheet(SetBorder(v.at(16+0)));
    ui->P2_1->setStyleSheet(SetBorder(v.at(16+1)));
    ui->P2_2->setStyleSheet(SetBorder(v.at(16+2)));
    ui->P2_3->setStyleSheet(SetBorder(v.at(16+3)));
    ui->P2_4->setStyleSheet(SetBorder(v.at(16+4)));
    ui->P2_5->setStyleSheet(SetBorder(v.at(16+5)));
    ui->P2_6->setStyleSheet(SetBorder(v.at(16+6)));
    ui->P2_7->setStyleSheet(SetBorder(v.at(16+7)));

    ui->P3_0->setStyleSheet(SetBorder(v.at(24+0)));
    ui->P3_1->setStyleSheet(SetBorder(v.at(24+1)));
    ui->P3_2->setStyleSheet(SetBorder(v.at(24+2)));
    ui->P3_3->setStyleSheet(SetBorder(v.at(24+3)));
    ui->P3_4->setStyleSheet(SetBorder(v.at(24+4)));
    ui->P3_5->setStyleSheet(SetBorder(v.at(24+5)));
    ui->P3_6->setStyleSheet(SetBorder(v.at(24+6)));
    ui->P3_7->setStyleSheet(SetBorder(v.at(24+7)));

    ui->P4_0->setStyleSheet(SetBorder(v.at(32+0)));
    ui->P4_1->setStyleSheet(SetBorder(v.at(32+1)));
    ui->P4_2->setStyleSheet(SetBorder(v.at(32+2)));
    ui->P4_3->setStyleSheet(SetBorder(v.at(32+3)));
    ui->P4_4->setStyleSheet(SetBorder(v.at(32+4)));
    ui->P4_5->setStyleSheet(SetBorder(v.at(32+5)));
    ui->P4_6->setStyleSheet(SetBorder(v.at(32+6)));
    ui->P4_7->setStyleSheet(SetBorder(v.at(32+7)));

    ui->P5_0->setStyleSheet(SetBorder(v.at(40+0)));
    ui->P5_1->setStyleSheet(SetBorder(v.at(40+1)));
    ui->P5_2->setStyleSheet(SetBorder(v.at(40+2)));
    ui->P5_3->setStyleSheet(SetBorder(v.at(40+3)));
    ui->P5_4->setStyleSheet(SetBorder(v.at(40+4)));
    ui->P5_5->setStyleSheet(SetBorder(v.at(40+5)));
    ui->P5_6->setStyleSheet(SetBorder(v.at(40+6)));
    ui->P5_7->setStyleSheet(SetBorder(v.at(40+7)));

    ui->P6_0->setStyleSheet(SetBorder(v.at(48+0)));
    ui->P6_1->setStyleSheet(SetBorder(v.at(48+1)));
    ui->P6_2->setStyleSheet(SetBorder(v.at(48+2)));
    ui->P6_3->setStyleSheet(SetBorder(v.at(48+3)));
    ui->P6_4->setStyleSheet(SetBorder(v.at(48+4)));
    ui->P6_5->setStyleSheet(SetBorder(v.at(48+5)));
    ui->P6_6->setStyleSheet(SetBorder(v.at(48+6)));
    ui->P6_7->setStyleSheet(SetBorder(v.at(48+7)));

    ui->P7_0->setStyleSheet(SetBorder(v.at(56+0)));
    ui->P7_1->setStyleSheet(SetBorder(v.at(56+1)));
    ui->P7_2->setStyleSheet(SetBorder(v.at(56+2)));
    ui->P7_3->setStyleSheet(SetBorder(v.at(56+3)));
    ui->P7_4->setStyleSheet(SetBorder(v.at(56+4)));
    ui->P7_5->setStyleSheet(SetBorder(v.at(56+5)));
    ui->P7_6->setStyleSheet(SetBorder(v.at(56+6)));
    ui->P7_7->setStyleSheet(SetBorder(v.at(56+7)));



}

QString Board::SetBorder(int border)
{
    if(border)
    {
        return "border: 4px solid rgb(195, 227, 201);background-color: rgb(85, 170, 0);";
    }
    else
    {
        return "background-color: rgb(85, 170, 0);";
    }

}

void Board::on_C0_0_linkActivated(const QString &link)
{

}


const QSize Board::GetSize(int image)
{
    QPixmap black("C:/Users/user/OneDrive/Documents/OthelloGame/images/black_disk.png");
    QPixmap white("C:/Users/user/OneDrive/Documents/OthelloGame/images/white_disk.png");
    QPixmap blank("C:/Users/user/OneDrive/Documents/OthelloGame/images/blank.png");
    if(image==1)
    {
        return (black.rect().size());
    }
    else if(image==-1)
    {
        return (white.rect().size());
    }
    else
    {
        return (blank.rect().size());
    }
}


void Board::INIT_PUSH()
{
    ui->P0_0->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P0_1->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P0_2->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P0_3->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P0_4->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P0_5->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P0_6->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P0_7->setStyleSheet("background-color: rgb(85, 170, 0);");

    ui->P1_0->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P1_1->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P1_2->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P1_3->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P1_4->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P1_5->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P1_6->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P1_7->setStyleSheet("background-color: rgb(85, 170, 0);");

    ui->P2_0->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P2_1->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P2_2->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P2_3->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P2_4->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P2_5->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P2_6->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P2_7->setStyleSheet("background-color: rgb(85, 170, 0);");

    ui->P3_0->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P3_1->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P3_2->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P3_3->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P3_4->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P3_5->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P3_6->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P3_7->setStyleSheet("background-color: rgb(85, 170, 0);");

    ui->P4_0->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P4_1->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P4_2->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P4_3->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P4_4->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P4_5->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P4_6->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P4_7->setStyleSheet("background-color: rgb(85, 170, 0);");

    ui->P5_0->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P5_1->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P5_2->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P5_3->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P5_4->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P5_5->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P5_6->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P5_7->setStyleSheet("background-color: rgb(85, 170, 0);");

    ui->P6_0->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P6_1->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P6_2->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P6_3->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P6_4->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P6_5->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P6_6->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P6_7->setStyleSheet("background-color: rgb(85, 170, 0);");

    ui->P7_0->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P7_1->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P7_2->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P7_3->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P7_4->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P7_5->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P7_6->setStyleSheet("background-color: rgb(85, 170, 0);");
    ui->P7_7->setStyleSheet("background-color: rgb(85, 170, 0);");
}

void Board::ValidInterface()
{

    cout<<"OUT FOR LOOP"<<"\n";
//    for (auto keyval : game.boardlogic.moves)
//    {
//        cout<<"IN FOR LOOP"<<"\n";
//        ValidMoves.insert(keyval.first,1);
//        cout<<keyval.first<<"\n";
//    }

    for(int i=0;i<64;i++)
    {
        ValidMoves[i]=0;

    }
    for(auto x: game.GameLogic.moves){

             std::cout<<x.first<<std::endl;
                ValidMoves[x.first]=1;


           }

    SetValidMoves(ValidMoves);
}


void Board::updateScode()
{
    int blackCount=0;
    int whiteCount=0;

    for(int i=0;i<64;i++)
    {
        if(game.GameLogic.positions.at(i)==1)
        {
            blackCount++;
        }
        else if(game.GameLogic.positions.at(i)==-1)
        {
            whiteCount++;
        }

    }

    ui->LBlack->setText(QString::number(blackCount));
    ui->LWhite->setText(QString::number(whiteCount));
    if(whiteCount>blackCount)
    {
        ui->LWinner->setText("White is Winning");
    }
    else if(whiteCount<blackCount)
    {
        ui->LWinner->setText("Black Winning");
    }

    if(game.checkGameOver())
    {
        ui->LWinner->setText("Test reach");
    }
}

void Board::Select_turn(int index)
{
    //human vs human
    if((!game.Black.isComputer)&&(!game.White.isComputer))
    {
     if(game.Black.turn)
        {

            game.move(1,index);
            updateScode();
            LOGIC_SetCircles(game.GameLogic.positions);

            game.GameLogic.findLegalMoves(-1, &game.GameLogic.moves);
            ValidInterface();
            game.Black.turn=0;
            game.White.turn=1;



        }
        else
        {

            game.move(-1,index);
            updateScode();
            LOGIC_SetCircles(game.GameLogic.positions);

            game.GameLogic.findLegalMoves(1, &game.GameLogic.moves);
            ValidInterface();
            game.Black.turn=1;
            game.White.turn=0;
        }
    }

    //Human vs Ai
    if(!game.Black.isComputer && game.White.isComputer)
    {


            //Human
            if(!game.checkGameOver())
            {
            game.move(1,index);
            game.checkGameOver();
            updateScode();
            LOGIC_SetCircles(game.GameLogic.positions);

            game.GameLogic.findLegalMoves(-1, &game.GameLogic.moves);
            ValidInterface();
            LOGIC_SetCircles(game.GameLogic.positions);
            }
            if(!game.checkGameOver())
            {
            //Ai
            game.move(-1,index);
            game.checkGameOver();
            updateScode();
            LOGIC_SetCircles(game.GameLogic.positions);
            game.GameLogic.findLegalMoves(1, &game.GameLogic.moves);
            ValidInterface();
            }



    }
    if(game.Black.isComputer && !game.White.isComputer)
    {





            //Human

            game.move(-1,index);
            updateScode();
            LOGIC_SetCircles(game.GameLogic.positions);
            game.GameLogic.findLegalMoves(1, &game.GameLogic.moves);
            ValidInterface();
            LOGIC_SetCircles(game.GameLogic.positions);

            //Ai
            game.move(1,index);
            updateScode();
            LOGIC_SetCircles(game.GameLogic.positions);
            game.GameLogic.findLegalMoves(-1, &game.GameLogic.moves);
            ValidInterface();





    }

    if(game.Black.isComputer && game.White.isComputer)
    {
        if(game.Black.turn)
           {

               game.move(1,index);
               updateScode();
               LOGIC_SetCircles(game.GameLogic.positions);

               game.GameLogic.findLegalMoves(-1, &game.GameLogic.moves);
               ValidInterface();
               game.Black.turn=0;
               game.White.turn=1;



           }
           else
           {
               game.move(-1,index);
               updateScode();
               LOGIC_SetCircles(game.GameLogic.positions);

               game.GameLogic.findLegalMoves(1, &game.GameLogic.moves);
               ValidInterface();
               game.Black.turn=1;
               game.White.turn=0;
           }
    }



}


void Board::on_P0_0_clicked()

{
    if(ValidMoves.at(0+0))
    {
       game.ChoosenIndex=0;
       Select_turn( game.ChoosenIndex);
    }

    //ui->P0_0->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P0_1_clicked()
{
    if(ValidMoves.at(0+1))
    {
        game.ChoosenIndex=1;
       Select_turn( game.ChoosenIndex);
    }
    //ui->P0_1->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P0_2_clicked()
{
    if(ValidMoves.at(0+2))
    {
        game.ChoosenIndex=2;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P0_2->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P0_3_clicked()
{
    if(ValidMoves.at(0+3))
    {
        game.ChoosenIndex=3;
        Select_turn( game.ChoosenIndex);
    }

}

void Board::on_P0_4_clicked()
{
    if(ValidMoves.at(0+4))
    {
        game.ChoosenIndex=4;
        Select_turn( game.ChoosenIndex);
    }

}


void Board::on_P0_5_clicked()
{
    if(ValidMoves.at(0+5))
    {
        game.ChoosenIndex=5;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P0_5->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P0_6_clicked()
{
    if(ValidMoves.at(0+6))
    {
        game.ChoosenIndex=6;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P0_6->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P0_7_clicked()
{
    if(ValidMoves.at(0+7))
    {
        game.ChoosenIndex=7;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P0_7->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P1_0_clicked()
{
    if(ValidMoves.at(8+0))
    {
        game.ChoosenIndex=8;
        Select_turn( game.ChoosenIndex);
    }
     //ui->P1_0->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P1_1_clicked()
{
    if(ValidMoves.at(8+1))
    {
        game.ChoosenIndex=9;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P1_1->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P1_2_clicked()
{
    if(ValidMoves.at(8+2))
    {
        game.ChoosenIndex=10;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P1_2->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P1_3_clicked()
{
    if(ValidMoves.at(8+3))
    {
        game.ChoosenIndex=11;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P1_3->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P1_4_clicked()
{
    if(ValidMoves.at(8+4))
    {
        game.ChoosenIndex=12;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P1_4->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P1_5_clicked()
{
    if(ValidMoves.at(8+5))
    {
        game.ChoosenIndex=13;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P1_5->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P1_6_clicked()
{
    if(ValidMoves.at(8+6))
    {
        game.ChoosenIndex=14;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P1_6->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P1_7_clicked()
{
    if(ValidMoves.at(8+7))
    {
        game.ChoosenIndex=15;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P1_7->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P2_0_clicked()
{
    if(ValidMoves.at(16+0))
    {
        game.ChoosenIndex=16;
        Select_turn( game.ChoosenIndex);
    }
    // ui->P2_0->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P2_1_clicked()
{
    if(ValidMoves.at(16+1))
    {
        game.ChoosenIndex=17;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P2_1->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P2_2_clicked()
{
    if(ValidMoves.at(16+2))
    {
        game.ChoosenIndex=18;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P2_2->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P2_3_clicked()
{
    if(ValidMoves.at(16+3))
    {
        game.ChoosenIndex=19;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P2_3->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P2_4_clicked()
{
    if(ValidMoves.at(16+4))
    {
        game.ChoosenIndex=20;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P2_4->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P2_5_clicked()
{
    if(ValidMoves.at(16+5))
    {
        game.ChoosenIndex=21;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P2_5->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P2_6_clicked()
{
    if(ValidMoves.at(16+6))
    {
        game.ChoosenIndex=22;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P2_6->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P2_7_clicked()
{
    if(ValidMoves.at(16+7))
    {
        game.ChoosenIndex=23;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P2_7->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P3_0_clicked()
{
    if(ValidMoves.at(24+0))
    {
        game.ChoosenIndex=24;
        Select_turn( game.ChoosenIndex);
    }
     //ui->P3_0->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P3_1_clicked()
{
    if(ValidMoves.at(24+1))
    {
        game.ChoosenIndex=25;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P3_1->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P3_2_clicked()
{
    if(ValidMoves.at(24+2))
    {
        game.ChoosenIndex=26;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P3_2->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P3_3_clicked()
{
    if(ValidMoves.at(24+3))
    {
        game.ChoosenIndex=27;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P3_3->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P3_4_clicked()
{
    if(ValidMoves.at(24+4))
    {
        game.ChoosenIndex=28;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P3_4->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P3_5_clicked()
{
    if(ValidMoves.at(24+5))
    {
        game.ChoosenIndex=29;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P3_5->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P3_6_clicked()
{
    if(ValidMoves.at(24+6))
    {
        game.ChoosenIndex=30;
        Select_turn( game.ChoosenIndex);
    }
   // ui->P3_6->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P3_7_clicked()
{
    if(ValidMoves.at(24+7))
    {
        game.ChoosenIndex=31;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P3_7->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P4_0_clicked()
{
    if(ValidMoves.at(32+0))
    {
        game.ChoosenIndex=32;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P4_0->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P4_1_clicked()
{
    if(ValidMoves.at(32+1))
    {
        game.ChoosenIndex=33;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P4_1->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P4_2_clicked()
{
    if(ValidMoves.at(32+2))
    {
        game.ChoosenIndex=34;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P4_2->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P4_3_clicked()
{
    if(ValidMoves.at(32+3))
    {
        game.ChoosenIndex=35;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P4_3->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P4_4_clicked()
{
    if(ValidMoves.at(32+4))
    {
        game.ChoosenIndex=36;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P4_4->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P4_5_clicked()
{
    if(ValidMoves.at(32+5))
    {
        game.ChoosenIndex=37;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P4_5->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P4_6_clicked()
{
    if(ValidMoves.at(32+6))
    {
        game.ChoosenIndex=38;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P4_6->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P4_7_clicked()
{
    if(ValidMoves.at(32+7))
    {
        game.ChoosenIndex=39;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P4_7->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P5_0_clicked()
{
    if(ValidMoves.at(40+0))
    {
        game.ChoosenIndex=40;
        Select_turn( game.ChoosenIndex);
    }
     //ui->P5_0->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P5_1_clicked()
{
    if(ValidMoves.at(40+1))
    {
        game.ChoosenIndex=41;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P5_1->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P5_2_clicked()
{
    if(ValidMoves.at(40+2))
    {
        game.ChoosenIndex=42;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P5_2->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P5_3_clicked()
{
    if(ValidMoves.at(40+3))
    {
        game.ChoosenIndex=43;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P5_3->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P5_4_clicked()
{
    if(ValidMoves.at(40+4))
    {
        game.ChoosenIndex=44;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P5_4->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P5_5_clicked()
{
    if(ValidMoves.at(40+5))
    {
        game.ChoosenIndex=45;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P5_5->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P5_6_clicked()
{
    if(ValidMoves.at(40+6))
    {
        game.ChoosenIndex=46;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P5_6->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P5_7_clicked()
{
    if(ValidMoves.at(40+7))
    {
        game.ChoosenIndex=47;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P5_7->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P6_0_clicked()
{
    if(ValidMoves.at(48+0))
    {
        game.ChoosenIndex=48;
        Select_turn( game.ChoosenIndex);
    }
     //ui->P6_0->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P6_1_clicked()
{
    if(ValidMoves.at(48+1))
    {
        game.ChoosenIndex=49;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P6_1->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P6_2_clicked()
{
    if(ValidMoves.at(48+2))
    {
        game.ChoosenIndex=50;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P6_2->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P6_3_clicked()
{
    if(ValidMoves.at(48+3))
    {
        game.ChoosenIndex=51;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P6_3->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P6_4_clicked()
{
    if(ValidMoves.at(48+4))
    {
        game.ChoosenIndex=52;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P6_4->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P6_5_clicked()
{
    if(ValidMoves.at(48+5))
    {
        game.ChoosenIndex=53;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P6_5->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P6_6_clicked()
{
    if(ValidMoves.at(48+6))
    {
        game.ChoosenIndex=54;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P6_6->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P6_7_clicked()
{
    if(ValidMoves.at(48+7))
    {
        game.ChoosenIndex=55;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P6_7->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P7_0_clicked()
{
    if(ValidMoves.at(56+0))
    {
        game.ChoosenIndex=56;
        Select_turn( game.ChoosenIndex);
    }
     //ui->P7_0->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P7_1_clicked()
{
    if(ValidMoves.at(56+1))
    {
        game.ChoosenIndex=57;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P7_1->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P7_2_clicked()
{
    if(ValidMoves.at(56+2))
    {
        game.ChoosenIndex=58;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P7_2->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P7_3_clicked()
{
    if(ValidMoves.at(56+3))
    {
        game.ChoosenIndex=59;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P7_3->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P7_4_clicked()
{
    if(ValidMoves.at(56+4))
    {
        game.ChoosenIndex=60;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P7_4->setStyleSheet("background-color: rgb(255, 255, 255);");
}


void Board::on_P7_5_clicked()
{
    if(ValidMoves.at(56+5))
    {
        game.ChoosenIndex=61;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P7_5->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P7_6_clicked()
{
    if(ValidMoves.at(56+6))
    {
        game.ChoosenIndex=62;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P7_6->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_P7_7_clicked()
{
    if(ValidMoves.at(56+7))
    {
        game.ChoosenIndex=63;
        Select_turn( game.ChoosenIndex);
    }
    //ui->P7_7->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void Board::on_PNextStep_clicked()
{
    Select_turn(0);
}
