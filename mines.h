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

#define TILE_SIZE 50
#define MINE 999
#define LEADERBOARD_FILE "leaderboard.txt"

#include "player.h"
#include "leaderboard.h"
#include "data_structures.h"


namespace Ui {
class Mines;
}

class Mines : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mines(QWidget *parent = 0);
    ~Mines();
    // vector of available game difficulties
    QVector<DIFFICULTY> difficulties;
signals:
    void cellsRevealedAutomatically(int number);

private slots:
    void on_start_game_button_clicked();    
    void on_pause_time_button_clicked(bool checked);
    void on_show_leaderboard_button_clicked();
    void on_visibleGrid_itemClicked(QTableWidgetItem *item);

public slots:
    void flagCounterIncreasedSlot();
    void flagCounterDecreasedSlot();
    void updateTime();
    void timerStopSlot();
    void leaderboardClosedSlot();

private:
    Ui::Mines *ui;
    // mines are represented as set of QPoints
    QSet<QPoint> mines;
    int **grid; // extra borders for problem-free indexing
    int current_difficulty;
    Player player;
    LeaderBoard lb;

    void placeMines(int count);
    void placeMineNumbers();
    int countNearbyMines(int row, int col);
    void clearVisibleGrid();
    int revealEmptyArea(int row, int col);
    void showMineNumber(int row, int col);
    void clearEverything();

};

#endif // MINES_H
