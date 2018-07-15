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

#define GRID_WIDTH 10
#define GRID_HEIGHT 10

#define MINE 999

namespace Ui {
class Mines;
}

class Mines : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mines(QWidget *parent = 0);
    ~Mines();
signals:
    void cellsRevealedAutomatically(int number);

private slots:
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void on_start_game_button_clicked();
public slots:
    void flagCounterIncreasedSlot();
    void flagCounterDecreasedSlot();
    void updateTime();

private:
    Ui::Mines *ui;
    void placeMines(int count);
    void placeMineNumbers();
    int countNearbyMines(int row, int col);
    void clearVisibleGrid();
    void revealEmptyArea(int row, int col);
    void makeItemVisible(int row, int col);
    void clearEverything();
    // mines and flags are represented as QPoints
    QSet<QPoint> mines;
    QSet<QPoint> flags;
    int grid[GRID_HEIGHT+2][GRID_WIDTH+2] = {{-1}}; // extra borders for problem-free indexing
    bool ready;
    int flagCnt;
};

#endif // MINES_H
