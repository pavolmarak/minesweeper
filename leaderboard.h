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
#include <QComboBox>
#include <QGroupBox>

#define COLUMN_COUNT 4


#include "data_structures.h"




namespace Ui {
class LeaderBoard;
}

class LeaderBoard : public QMainWindow
{
    Q_OBJECT

public:
    LeaderBoard(QWidget *parent = 0);
    ~LeaderBoard();
    bool loadFromFile(const QString&);
    void redraw(); // redraws a leaderboard table and highlights the specified row
    void setTimeTaken(quint64 time_taken);
    void setSubmitBtnEnabled(bool);
    void setLeaderboardTypes(QVector<QString>);
    void setResultboxVisible(bool);
    void setup(const QString &path_to_file, const QVector<DIFFICULTY> diffs);

private slots:
    void on_submit_result_button_clicked();

private:
    Ui::LeaderBoard *ui;
    QMultiMap<quint64,UserResult> leader_board;
    QString leader_board_file;
    void closeEvent (QCloseEvent *event);

signals:
    void leaderboardClosedSignal();
};

#endif // LEADERBOARD_H
