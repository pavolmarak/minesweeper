#include "leaderboard.h"

LeaderBoard::LeaderBoard()
{

}

LeaderBoard::LeaderBoard(const QString& leaderboard_file)
{
    this->leader_board_file = leaderboard_file;
    this->loadFromFile(this->leader_board_file);
}

// function to load leaderboard data from file and display it
bool LeaderBoard::loadFromFile(const QString &path_to_file)
{
    this->leader_board.clear();

    QFile data_file(path_to_file);
    data_file.open(QFile::ReadOnly);
    if(!data_file.isOpen()){
        qDebug() << "There was an error opening file with leaderboard data.";
        QMessageBox::about(nullptr,"Error", "There was an error opening file with leaderboard data.");
        return false;
    }
    QTextStream txt(&data_file);
    txt.readLine(); // consume the first line in the text file
    UserResult usr_result;
    quint64 msec;

    // reading from file
    while(!txt.atEnd()){
        txt >> usr_result.name >> msec >> usr_result.difficulty >> usr_result.date;
        this->leader_board.insert(msec,usr_result);
    }
    this->leader_board.remove(0,{"","",""});
    data_file.close();
    return true;
}

QMultiMap<quint64, UserResult>& LeaderBoard::getLeader_board()
{
    return leader_board;
}

void LeaderBoard::setLeader_board(const QMultiMap<quint64, UserResult> &value)
{
    leader_board = value;
}

QString LeaderBoard::getLeader_board_file() const
{
    return leader_board_file;
}

void LeaderBoard::setLeader_board_file(const QString &value)
{
    leader_board_file = value;
}
