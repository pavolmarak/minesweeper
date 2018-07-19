#include <QString>

#ifndef HELPER_H
#define HELPER_H

#define TILE_SIZE 50
#define MINE 999
#define LEADERBOARD_FILE "leaderboard.txt"
#define LEADERBOARD_COLUMN_COUNT 4

// enum representing a cell status
typedef enum _cell_status{
    UNVISITED,
    VISITED,
    FLAG
}CellStatus;

// struct representing one cell in the invisible game grid
typedef struct _cell{
    int value;
    CellStatus status;
    _cell(int _value, CellStatus _status){
        this->value = _value;
        this->status = _status;
    }
    _cell() :
        value(-1),
        status(UNVISITED)
    {}
}Cell;

// struct for representing game difficulty
typedef struct _difficulty{
    int grid_width;
    int grid_height;
    int number_of_mines;
    QString name;
    _difficulty(int _grid_width, int _grid_height, int _number_of_mines, QString _name){
        this->grid_width = _grid_width;
        this->grid_height = _grid_height;
        this->number_of_mines = _number_of_mines;
        this->name = _name;
    }
    _difficulty() :
        grid_width(10),
        grid_height(10),
        number_of_mines(10),
        name("Easy")
    {}
}Difficulty;

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
