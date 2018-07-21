#ifndef STATUSBARSWITCH_H
#define STATUSBARSWITCH_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDir>
#include <QDebug>
#include <QMouseEvent>

class StatusBarSwitch : public QLabel
{
public:
    StatusBarSwitch();

private slots:
    void mousePressEvent(QMouseEvent* event);

private:
    bool status;
};

#endif // STATUSBARSWITCH_H
