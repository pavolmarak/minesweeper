#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QMainWindow>
#include <QDebug>

namespace Ui {
class LeaderBoard;
}

class LeaderBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit LeaderBoard(quint64 time_taken, QWidget *parent = 0);
    ~LeaderBoard();

private slots:
    void on_submit_result_button_clicked();

private:
    Ui::LeaderBoard *ui;
};

#endif // LEADERBOARD_H
