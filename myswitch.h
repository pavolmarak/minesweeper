#ifndef STATUSBARSWITCH_H
#define STATUSBARSWITCH_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDir>
#include <QDebug>
#include <QMouseEvent>

class MySwitch : public QLabel
{

public:
    MySwitch();

private slots:
    void mousePressEvent(QMouseEvent* event);

private:
    bool status;
};

#endif // STATUSBARSWITCH_H
