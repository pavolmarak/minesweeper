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

typedef struct _user{
    QString name;
    QString difficulty;

    bool operator ==(const _user &lhs)
    {
        if(lhs.name == this->name && lhs.difficulty == this->difficulty){
            return true;
        }
        return false;
    }
}User;




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
    void setDifficulty(const QString& difficulty);
    void setSubmitBtnEnabled();
    bool error;

private slots:
    void on_submit_result_button_clicked();

private:
    Ui::LeaderBoard *ui;
    QMultiMap<quint64,User> leader_board;
    QString leader_board_file;
    void closeEvent (QCloseEvent *event);
    QString difficulty;
};

#endif // LEADERBOARD_H
