//#ifndef LEADERBOARD_H
//#define LEADERBOARD_H

//#include <QMainWindow>
//#include <QDebug>
//#include <QFile>
//#include <QTextStream>
//#include <QMessageBox>
//#include <QTableWidget>
//#include <QMultiMap>
//#include <QThread>
//#include <QLabel>
//#include <QLineEdit>
//#include <QCloseEvent>
//#include <QStatusBar>
//#include <QPushButton>
//#include <QComboBox>
//#include <QGroupBox>

//#include "data_structures.h"

//namespace Ui {
//class LeaderBoard;
//}

//class LeaderBoard : public QMainWindow
//{
//    Q_OBJECT

//public:
//    LeaderBoard(QWidget *parent = 0);
//    ~LeaderBoard();

//    void setResultboxVisible(bool);
//    void setLeader_board_types(QVector<Difficulty>);
//    bool loadFromFile(const QString&);
//    void redraw();
//    void setTimeTaken(quint64 time_taken);
//    void setSubmitBtnEnabled(bool);

//    QMultiMap<quint64, UserResult> getLeader_board() const;
//    void setLeader_board(const QMultiMap<quint64, UserResult> &value);

//    QString getLeader_board_file() const;
//    void setLeader_board_file(const QString &value);

//private slots:
//    void on_submit_result_button_clicked();

//private:
//    Ui::LeaderBoard *ui;
//    QMultiMap<quint64,UserResult> leader_board;
//    void closeEvent (QCloseEvent *event);
//    QString leader_board_file;

//signals:
//    void leaderboardClosedSignal();
//};

//#endif // LEADERBOARD_H
