#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidget>
#include <QMultiMap>
#include <QThread>

#define DATA_FILE_PATH "leaderboard.txt"

namespace Ui {
class LeaderBoard;
}

class LeaderBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit LeaderBoard(quint64 time_taken, QWidget *parent = 0);
    ~LeaderBoard();
    bool loadLeaderBoard(const QString&);
    bool error;

private slots:
    void on_submit_result_button_clicked();

private:
    Ui::LeaderBoard *ui;
    QMultiMap<quint64,QString> leader_board;
};

#endif // LEADERBOARD_H
