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

    // getters and setters
    int getCurrent_difficulty() const;
    void setCurrent_difficulty(int value);

    Player getPlayer() const;
    void setPlayer(const Player &value);

    QVector<QVector<Cell> > getInvisible_grid() const;
    void setInvisible_grid(const QVector<QVector<Cell> > &value);

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

    // function to compute a number of nearby mines around the given cell
    int countNearbyMines(int row, int col);

    // function to create invisible game grid with the given dimensions
    // and set it to the user-defined value. Previous values are removed.
    void createInvisibleGrid(int rows, int cols, Cell cell);

};

#endif // GAME_H
