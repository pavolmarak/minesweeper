#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QMultiMap>
#include <QDebug>

#include "data_structures.h"

class LeaderBoard
{
public:
    LeaderBoard();
    LeaderBoard(const QString &leaderboard_file);

    bool loadFromFile(const QString&);

    QMultiMap<quint64, UserResult>& getLeader_board();
    void setLeader_board(const QMultiMap<quint64, UserResult> &value);

    QString getLeader_board_file() const;
    void setLeader_board_file(const QString &value);

private:
    QMultiMap<quint64,UserResult> leader_board;
    QString leader_board_file;
};

#endif // LEADERBOARD_H
