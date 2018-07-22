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
    void redrawLeaderboard(int row_index = -1);
    void setCurrentDifficulty(int index);
    void highlightRow(int index, QColor background_color, QColor text_color);
    QMultiMap<quint64, UserResult>::iterator addToLeaderboard(quint64 key, UserResult value);

    quint64 getLast_time() const;
    void setLast_time(const quint64 &value);

    LeaderBoard& getLb();
    void setLb(const LeaderBoard &value);

private slots:
    void on_submit_result_button_clicked();
    void on_leaderboard_selection_combobox_activated(int index);

private:
    Ui::LeaderBoardGUI *ui;
    LeaderBoard lb;
    quint64 last_time;
    void closeEvent (QCloseEvent *event);

signals:
    void leaderboardClosedSignal();
};

#endif // LEADERBOARDGUI_H
