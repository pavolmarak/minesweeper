#ifndef LEADERBOARDGUI_H
#define LEADERBOARDGUI_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QMultiMap>
#include <QThread>
#include <QLabel>
#include <QLineEdit>
#include <QCloseEvent>
#include <QStatusBar>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QDateTime>
#include <QDir>

#include "data_structures.h"
#include "leaderboard.h"

namespace Ui {
class LeaderBoardGUI;
}

class LeaderBoardGUI : public QMainWindow
{
    Q_OBJECT

public:
    LeaderBoardGUI(QWidget *parent = 0);
    ~LeaderBoardGUI();
    void resetGui();
    void setLeaderboardTypes(QVector<Difficulty> difficulties);
    void showUserResultBox(bool on_off, quint64 time);
    void redrawLeaderboard();
    void setCurrentDifficulty(int index);

    quint64 getLast_time() const;
    void setLast_time(const quint64 &value);

private slots:
    void on_submit_result_button_clicked();
    void on_leaderboard_selection_combobox_activated(int index);

private:
    Ui::LeaderBoardGUI *ui;
    LeaderBoard lb;
    void closeEvent (QCloseEvent *event);
    quint64 last_time;

signals:
    void leaderboardClosedSignal();
};

#endif // LEADERBOARDGUI_H
