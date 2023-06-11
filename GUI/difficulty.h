#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <QWidget>

namespace Ui {
class Difficulty;
}

class Difficulty : public QWidget
{
    Q_OBJECT

public:
    explicit Difficulty(QWidget *parent = nullptr);
    ~Difficulty();

private slots:
    void on_PEasy_clicked();

    void on_PMedium_clicked();

    void on_PHard_clicked();

private:
    Ui::Difficulty *ui;
};

#endif // DIFFICULTY_H
