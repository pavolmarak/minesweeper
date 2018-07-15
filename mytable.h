#ifndef MYTABLE_H
#define MYTABLE_H

#include <QApplication>
#include <QTableWidget>
#include <QObject>
#include <QMouseEvent>
#include <QDebug>
#include <QLabel>
#include <QDir>
#include <QMessageBox>
#include <QAbstractItemView>
#include <QElapsedTimer>
#include <QTimer>

#define GRID_WIDTH 10
#define GRID_HEIGHT 10

class MyTable : public QTableWidget
{
    Q_OBJECT
public:
    MyTable(QWidget*);
    virtual ~MyTable();
    int mineCounter;
    int noMineCounter;
    bool congratsShown;
    QTimer timer;
    QElapsedTimer elap_timer;
private slots:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public slots:
    void cellsRevealedAutomaticallySlot(int);
signals:
    void flagCounterIncreased();
    void flagCounterDecreased();
};

#endif // MYTABLE_H
