#ifndef MINES_H
#define MINES_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <QPoint>
#include <QDebug>
#include <QSet>
#include <QMouseEvent>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QTimer>
#include <QComboBox>
#include <QSpinBox>
#include <QDialog>
#include <QHeaderView>

#include "game.h"

namespace Ui {
class GameGUI;
}

class GameGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameGUI(QWidget *parent = 0);
    ~GameGUI();

signals:
    void cellsRevealedAutomatically(int number);

private slots:
    void on_start_game_button_clicked();
    void on_pause_time_button_clicked(bool checked);
    void on_show_leaderboard_button_clicked();
    void on_visibleGrid_itemClicked(QTableWidgetItem *item);

public slots:
        void leaderboardClosedSlot();
        void updateTime();
        void flagCounterIncreasedSlot();
        void flagCounterDecreasedSlot();
private:
    Ui::GameGUI *ui;
    Game game;
};

#endif // MINES_H
