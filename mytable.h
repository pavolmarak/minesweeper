#ifndef MYTABLE_H
#define MYTABLE_H

#include <QTableWidget>
#include <QObject>
#include <QMouseEvent>
#include <QDebug>
#include <QLabel>

class MyTable : public QTableWidget
{
public:
    MyTable(QWidget*);
private slots:
    void mousePressEvent(QMouseEvent* e);
private:

};

#endif // MYTABLE_H
