#ifndef GAME_H
#define GAME_H

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
#include <QElapsedTimer>
#include <QTimer>
#include <QComboBox>
#include <QSpinBox>
#include <QDialog>
#include <QHeaderView>

#include "player.h"
#include "leaderboard_gui.h"
#include "data_structures.h"

class Game
{
public:
    Game();
    ~Game();

    // vector of available game difficulties
    QVector<Difficulty> difficulties;

    // function to place mines in the invisible game grid
    void placeMines(int count);

    // function to place mine numbers in the invisible game grid
    void placeMineNumbers();

    // function to reveal an empty cell region, returning number of cells revealed
    int revealEmptyArea(int row, int col);

    // function to reset visible game grid in order to prepare it for the new game
    void clearVisibleGrid();

    // function to reset data and GUI in order to prepare it for the new game
    void clearEverything();

    // getters and setters
    QSet<QPoint> getMines() const;
    void setMines(const QSet<QPoint> &value);

    int getCurrent_difficulty() const;
    void setCurrent_difficulty(int value);

    Player getPlayer() const;
    void setPlayer(const Player &value);

    QVector<QVector<Cell> > getInvisible_grid() const;
    void setInvisible_grid(const QVector<QVector<Cell> > &value);

public slots:
    void flagCounterIncreasedSlot();
    void flagCounterDecreasedSlot();
    void updateTime();
    void timerStopSlot();
    void leaderboardClosedSlot();

private:
    // mines are represented as set of QPoints
    QSet<QPoint> mines;

    // invisible game grid
    QVector<QVector<Cell>> invisible_grid;

    // object for a player
    Player player;

    // object for a leaderboard
    LeaderBoard lb;

    // index of currently selected game difficulty from the available difficulties
    int current_difficulty;

    // function to compute a number of nearby mines around the given cell
    int countNearbyMines(int row, int col);

    // function to reveal a number of nearby mines at the given coordinate
    void showMineNumber(int row, int col);

    // function to create invisible game grid with the given dimensions
    // and set it to the default value. Previous values are removed.
    void createInvisibleGrid(int rows, int cols, Cell cell);

};

#endif // GAME_H
