#include <QString>

#ifndef HELPER_H
#define HELPER_H

// struct for representing game difficulty
typedef struct difficulty{
    int grid_width;
    int grid_height;
    int number_of_mines;
    QString name;
    difficulty(int _grid_width, int _grid_height, int _number_of_mines, QString _name){
        this->grid_width = _grid_width;
        this->grid_height = _grid_height;
        this->number_of_mines = _number_of_mines;
        this->name = _name;
    }
    difficulty() :
        grid_width(10),
        grid_height(10),
        number_of_mines(10),
        name("Easy")
    {}
}DIFFICULTY;

// struct for representing user result that is stored in the leaderboard
typedef struct _user_result{
    QString name;
    QString difficulty;
    QString date;
    bool operator ==(const _user_result &other)
    {
        if(other.name == this->name && other.difficulty == this->difficulty && other.date == this->date){
            return true;
        }
        return false;
    }
}UserResult;

#endif // HELPER_H
