#include <QString>

#ifndef HELPER_H
#define HELPER_H

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
    difficulty(){
        this->grid_width = 10;
        this->grid_height = 10;
        this->number_of_mines = 10;
        this->name = "Easy";
    }
}DIFFICULTY;

typedef struct _user_result{
    QString name;
    QString diff;
    QString date;

    bool operator ==(const _user_result &lhs)
    {
        if(lhs.name == this->name && lhs.diff == this->diff && lhs.date == this->date){
            return true;
        }
        return false;
    }
}UserResult;

#endif // HELPER_H
