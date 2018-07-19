#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QPoint>
#include <QDebug>
#include <QSet>
#include <QMouseEvent>
#include <QMessageBox>
#include <QTimer>
#include <QElapsedTimer>
#include <QComboBox>
#include <QSpinBox>
#include <QDialog>
#include <QHeaderView>

#include "player.h"
#include "leaderboard.h"
#include "data_structures.h"

class Game : public QObject
{
    Q_OBJECT
public:
    Game();
    ~Game();

    // vector of available game difficulties
    QVector<Difficulty> difficulties;

    // timers
    QTimer timer; // for updating time in GUI
    QElapsedTimer elap_timer; // for measuring overall time

    // function to place mines in the invisible game grid
    void placeMines(int count);

    // function to reveal an empty cell region, returning number of cells revealed
    QVector<QPoint> revealEmptyArea(int row, int col);

    // function to compute a number of nearby mines around the given cell
    int countNearbyMines(int row, int col);

    // function to create invisible game grid with the given dimensions
    // and set it to the user-defined value. Previous values are removed.
    void createInvisibleGrid(int rows, int cols, Cell cell);

    // function to notify about the outcome of user click
    ClickResult userLeftClick(int row, int col);
    void userRightClick(int row, int col);

    // getters and setters
    int getCurrent_difficulty() const;
    void setCurrent_difficulty(int value);

    Player getPlayer() const;
    void setPlayer(const Player &value);

    QVector<QVector<Cell> > getInvisible_grid() const;

    QTimer getTimer() const;
    void setTimer(const QTimer &value);

    QElapsedTimer getElap_timer() const;
    void setElap_timer(const QElapsedTimer &value);

public slots:

private:

    // invisible game grid
    QVector<QVector<Cell>> invisible_grid;

    // object for a player
    Player player;

    // object for a leaderboard
    LeaderBoard lb;

    // index of currently selected game difficulty from the available difficulties
    int current_difficulty;

    // function to place mine numbers in the invisible game grid
    void placeMineNumbers();
};

#endif // GAME_H
