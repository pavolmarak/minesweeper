#include "player.h"

Player::Player()
{
    this->time = 0;
    this->name = "";
    this->flag_counter = 0;
}

quint64 Player::getTime() const
{
    return time;
}

void Player::setTime(const quint64 &value)
{
    time = value;
}

QString Player::getName() const
{
    return name;
}

void Player::setName(const QString &value)
{
    name = value;
}

int Player::getFlag_counter() const
{
    return flag_counter;
}

void Player::setFlag_counter(int value)
{
    flag_counter = value;
}

void Player::flagUp()
{
    this->flag_counter++;
}

void Player::flagDown()
{
    this->flag_counter--;
}
