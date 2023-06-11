#ifndef BOARDGUI_H
#define BOARDGUI_H

#include <QWidget>
#include <qvector.h>
#include <vector>
#include <list>
#include <unordered_map>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class Board; }
QT_END_NAMESPACE

class Board : public QWidget
{
    Q_OBJECT

public:
    Board(QWidget *parent = nullptr);
    ~Board();
    void LOGIC_SetCircles(vector<int> v);
    void LOGIC_SetValidMoves(vector<int> v);
    void ValidInterface();

private slots:
    void on_C0_0_linkActivated(const QString &link);

    void on_P0_0_clicked();

    void on_P0_1_clicked();

    void on_P0_2_clicked();

    void on_P0_3_clicked();

    void on_P0_4_clicked();

    void on_P0_5_clicked();

    void on_P0_6_clicked();

    void on_P0_7_clicked();

    void on_P1_0_clicked();

    void on_P1_1_clicked();

    void on_P1_2_clicked();

    void on_P1_3_clicked();

    void on_P1_4_clicked();

    void on_P1_5_clicked();

    void on_P1_6_clicked();

    void on_P1_7_clicked();

    void on_P2_0_clicked();

    void on_P2_1_clicked();

    void on_P2_2_clicked();

    void on_P2_3_clicked();

    void on_P2_4_clicked();

    void on_P2_5_clicked();

    void on_P2_6_clicked();

    void on_P2_7_clicked();

    void on_P3_0_clicked();

    void on_P3_1_clicked();

    void on_P3_2_clicked();

    void on_P3_3_clicked();

    void on_P3_4_clicked();

    void on_P3_5_clicked();

    void on_P3_6_clicked();

    void on_P3_7_clicked();

    void on_P4_0_clicked();

    void on_P4_1_clicked();

    void on_P4_2_clicked();

    void on_P4_3_clicked();

    void on_P4_4_clicked();

    void on_P4_5_clicked();

    void on_P4_6_clicked();

    void on_P4_7_clicked();

    void on_P5_0_clicked();

    void on_P5_1_clicked();

    void on_P5_2_clicked();

    void on_P5_3_clicked();

    void on_P5_4_clicked();

    void on_P5_5_clicked();

    void on_P5_6_clicked();

    void on_P5_7_clicked();

    void on_P6_0_clicked();

    void on_P6_1_clicked();

    void on_P6_2_clicked();

    void on_P6_3_clicked();

    void on_P6_4_clicked();

    void on_P6_5_clicked();

    void on_P6_6_clicked();

    void on_P6_7_clicked();

    void on_P7_0_clicked();

    void on_P7_1_clicked();

    void on_P7_2_clicked();

    void on_P7_3_clicked();

    void on_P7_4_clicked();

    void on_P7_5_clicked();

    void on_P7_6_clicked();

    void on_P7_7_clicked();

    void on_PNextStep_clicked();



private:
    Ui::Board *ui;
    void updateScode();
    void Ai2Ai();
    void Select_turn(int index);
    QIcon GetImage(int image);
    void SetCircles(QVector<int> v);
    void SetValidMoves(QVector<int> v);
    void INIT_PUSH();
    QString SetBorder(int border);
    const QSize  GetSize(int image);
};
#endif // BOARDGUI_H
