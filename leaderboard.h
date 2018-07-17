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
#include <QLabel>
#include <QLineEdit>
#include <QCloseEvent>
#include <QStatusBar>
#include <QPushButton>

namespace Ui {
class LeaderBoard;
}

class LeaderBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit LeaderBoard(const QString &path_to_file, QWidget *parent = 0);
    ~LeaderBoard();
    bool loadLeaderBoard(const QString&);
    void redraw(); // redraws a leaderboard table and highlights the specified row
    void setTimeTaken(quint64 time_taken);
    void setSubmitBtnEnabled();
    bool error;

private slots:
    void on_submit_result_button_clicked();

private:
    Ui::LeaderBoard *ui;
    QMultiMap<quint64,QString> leader_board;
    QString leader_board_file;
    void closeEvent (QCloseEvent *event);
};

#endif // LEADERBOARD_H
