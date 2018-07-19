#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class Player
{
public:
    Player();
    quint64 getTime() const;
    void setTime(const quint64 &value);

    QString getName() const;
    void setName(const QString &value);

    int getFlag_counter() const;
    void setFlag_counter(int value);

    void flagUp();
    void flagDown();

private:
    quint64 time;
    QString name;
    int flag_counter;
};

#endif // PLAYER_H
