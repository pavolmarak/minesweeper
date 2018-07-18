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

    // invisible game grid
    int **grid; // extra borders for problem-free indexing

    // index of currently selected game difficulty from the available difficulties
    int current_difficulty;

    // object for a player
    Player player;

    // object for a leaderboard
    LeaderBoard lb;

    // function to place mines in the invisible game grid
    void placeMines(int count);

    // function to place mine numbers in the invisible game grid
    void placeMineNumbers();

    // function to compute a number of nearby mines around the given cell
    int countNearbyMines(int row, int col);

    // function to reveal an empty cell region, returning number of cells revealed
    int revealEmptyArea(int row, int col);

    // function to reveal a number of nearby mines at the given coordinate
    void showMineNumber(int row, int col);

    // function to reset visible game grid in order to prepare it for the new game
    void clearVisibleGrid();

    // function to reset data and GUI in order to prepare it for the new game
    void clearEverything();

    // function to create invisible game grid with the given dimensions
    void createInvisibleGrid(int rows, int cols);

    // function to free invisible game grid and set it to nullptr
    void freeInvisibleGrid(int rows);
};

#endif // MINES_H
