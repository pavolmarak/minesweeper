#include "game.h"

// helper function for QMultiMap
inline uint qHash (const QPoint & key)
{
    return qHash (QPair<int,int>(key.x(), key.y()) );
}

Game::Game()
{
    // *************************************
    // ***********               ***********
    // *********** GENERAL SETUP ***********
    // ***********               ***********
    // *************************************

    // set game difficulties
    this->difficulties.push_back(Difficulty(10,10,10,"Easy"));
    this->difficulties.push_back(Difficulty(15,15,25,"Medium"));
    this->difficulties.push_back(Difficulty(20,20,50,"Hard"));

    // set current game difficulty
    this->current_difficulty = 0;


    // ********************************************
    // ***********                      ***********
    // *********** INVISIBLE GRID SETUP ***********
    // ***********                      ***********
    // ********************************************

    // create invisible game grid with dimensions corresponding
    // to the current game difficulty and set it to defaults
    this->createInvisibleGrid(
                this->difficulties[this->current_difficulty].grid_height,
                this->difficulties[this->current_difficulty].grid_width,
                Cell(-1,UNVISITED)
            );

    // *****************************************
    // ***********                   ***********
    // *********** LEADERBOARD SETUP ***********
    // ***********                   ***********
    // *****************************************

    this->lb.setWindowTitle("Leaderboard");
    this->lb.setWindowIcon(QIcon(qApp->applicationDirPath() + "/leaderboard_icon.png"));
    this->lb.setLeader_board_types(this->difficulties);
    if(!this->lb.loadFromFile(qApp->applicationDirPath() + "/" + LEADERBOARD_FILE)){
        exit(EXIT_FAILURE);
    }
}

Game::~Game(){

}

// function to place random mines on the invisible game grid along with mine numbers
void Game::placeMines(int count)
{
    if(!this->invisible_grid.isEmpty()){
        this->clearEverything();

        // qrand init
        qsrand(time(0));

        // place mines
        while(this->mines.count()<count){
            QPoint point(qrand()%difficulties[this->current_difficulty].grid_width, qrand()%difficulties[this->current_difficulty].grid_height);
            this->mines.insert(point);
            this->invisible_grid[point.y()+1][point.x()+1]=MINE; // +1 offset beacuse the grid has extra stripe of cells on each side
            ui->visibleGrid->item(point.y(),point.x())->setWhatsThis("noflag-mine-novisit");
        }
        // place mine numbers
        this->placeMineNumbers();
    }
    else{
        qDebug() << "Placing mines: Invisible game grid does not exist.";
    }
}

// function to place mine numbers on the game grid
void Game::placeMineNumbers()
{
    // compute mine numbers in non-mine cells
    for(int i=0; i< difficulties[this->current_difficulty].grid_height;i++){
        for(int j=0; j<difficulties[this->current_difficulty].grid_width;j++){
            if(this->invisible_grid[i+1][j+1]!=MINE){
                this->invisible_grid[i+1][j+1] = this->countNearbyMines(i,j);
                ui->visibleGrid->item(i,j)->setWhatsThis("noflag-nomine-novisit");
            }
        }
    }
}

// function to compute how many nearby mines are present around the cell
int Game::countNearbyMines(int row, int col)
{
    if(row<0 || row>=difficulties[this->current_difficulty].grid_height){
        qDebug() << "Counting nearby mines: Out of range.";
        return -1;
    }
    if(col<0 || col>=difficulties[this->current_difficulty].grid_width){
        qDebug() << "Counting nearby mines: Out of range.";
        return -2;
    }

    if(this->invisible_grid[row+1][col+1]==MINE){
        qDebug() << "Counting nearby mines: Mine.";
        return -999;
    }
    int mineCount = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(this->invisible_grid[row+i][col+j]==MINE){
                mineCount++;
            }
        }
    }
    return mineCount;
}

// function to reveal all empty cells when some empty cell is clicked
int Game::revealEmptyArea(int row, int col)
{
    if(this->invisible_grid[row+1][col+1]==0){
        QList<QPoint> unvisitedEmptyCells;
        QList<QPoint> visitedEmptyCells;
        unvisitedEmptyCells.push_back(QPoint(col,row));
        int new_row, new_col;
        int itemsRevealed = 0;
        while(!unvisitedEmptyCells.isEmpty()){
            // exploring 8-connected neighborhood of the selected empty cell
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    new_row = unvisitedEmptyCells.first().y()-1+i;
                    new_col = unvisitedEmptyCells.first().x()-1+j;
                    // check if not out of bounds
                    if(ui->visibleGrid->item(new_row, new_col)){
                        // check if the cell was not visited
                        if(ui->visibleGrid->item(new_row, new_col)->whatsThis() == "noflag-nomine-novisit"){
                            ui->visibleGrid->removeCellWidget(new_row, new_col); // to remove possible flags
                            // check if another empty cell is found
                            if(this->invisible_grid[new_row+1][new_col+1]==0 && visitedEmptyCells.indexOf(unvisitedEmptyCells.first(),0)==-1){
                                unvisitedEmptyCells.push_back(QPoint(new_col,new_row));
                            }
                            this->showMineNumber(new_row, new_col);
                            qApp->processEvents();
                            itemsRevealed++;
                        }
                    }
                }
            }
            // put the current empty cell to the list of visited empty cells
            visitedEmptyCells.push_back(unvisitedEmptyCells.first());
            // remove the current empty cell from the list of unvisited empty cells
            unvisitedEmptyCells.removeFirst();
        }
        return itemsRevealed;
    }
    return 0;
}

// function to show mine number on the game grid
void Game::showMineNumber(int row, int col)
{
    if(ui->visibleGrid->item(row, col)){
        // showing mine number only if the cell has not yet been visited
        if(ui->visibleGrid->item(row, col)->whatsThis() == "noflag-nomine-novisit"){
            ui->visibleGrid->item(row, col)->setWhatsThis("noflag-nomine-visit");

            // prevents from displaying 0
            if(this->invisible_grid[row+1][col+1]>0){
                ui->visibleGrid->item(row, col)->setText(QString::number(this->invisible_grid[row+1][col+1]));
            }
            ui->visibleGrid->item(row, col)->setFont(QFont("Tahoma",12,60));
            ui->visibleGrid->item(row, col)->setTextAlignment(Qt::AlignCenter);
            ui->visibleGrid->item(row, col)->setBackgroundColor(QColor(210,210,210));
        }
    }
    else{
        qDebug() << "Show mine number: Cell at given coordinate does not exist.";
    }

}

// function to clear necessary data and GUI before game starts
void Game::clearEverything()
{
    // clear all neccessary data structures
    this->mines.clear();

    else{
        qDebug() << "Clearing: Invisible grid does not exist.";
    }

    // clear all neccessary GUI elements
    this->clearVisibleGrid();
    ui->time->setText("0 ms");
    ui->time->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    ui->flag_counter->setText("0/" + QString::number(difficulties[this->current_difficulty].number_of_mines));
}

// function to clear the visible game grid
void Game::clearVisibleGrid()
{
    for(int i=0; i< ui->visibleGrid->rowCount();i++){
        for(int j=0; j<ui->visibleGrid->columnCount();j++){
            ui->visibleGrid->item(i,j)->setWhatsThis("noflag-nomine-novisit");
            if(ui->visibleGrid->cellWidget(i,j)){
                ui->visibleGrid->removeCellWidget(i,j);
            }
            else if(ui->visibleGrid->item(i,j)){
                ui->visibleGrid->item(i,j)->setText("");
                ui->visibleGrid->item(i,j)->setBackgroundColor(QColor(150,150,150));
            }
        }
    }
}

// function to create new invisible game grid and set it to defaults,
// previous data is removed
void Game::createInvisibleGrid(int rows, int cols, Cell cell)
{
    this->invisible_grid.clear();
    this->invisible_grid.resize(rows);
    for(int i=0; i < this->invisible_grid.length(); i++) {
        this->invisible_grid[i].resize(cols);
        this->invisible_grid[i].fill(cell);
    }
}


void Game::leaderboardClosedSlot()
{
    ui->show_leaderboard_button->setEnabled(true);
    ui->start_game_button->setEnabled(true);
    ui->gridsize_selector->setEnabled(true);
}

// when a user wins
void Game::timerStopSlot()
{
    ui->pause_time_button->setEnabled(false);
    ui->start_game_button->setEnabled(false);
    ui->show_leaderboard_button->setEnabled(false);
    ui->gridsize_selector->setEnabled(false);
    ui->visibleGrid->timer.stop();
    this->player.setTime(this->player.getTime() + ui->visibleGrid->elap_timer.elapsed());
    ui->time->setText(QString::number(this->player.getTime()) + " ms");

    this->lb.setResultboxVisible(true); // displays also a resultbox
    this->lb.setTimeTaken(this->player.getTime());
    this->lb.setSubmitBtnEnabled(true);
    this->lb.show();
}

void Game::flagCounterIncreasedSlot()
{
    this->player.setFlag_counter(this->player.getFlag_counter()+1);
    ui->flag_counter->setText(QString::number(this->player.getFlag_counter()) + "/" + QString::number(difficulties[this->current_difficulty].number_of_mines));
    if(this->player.getFlag_counter() > difficulties[this->current_difficulty].number_of_mines){
        ui->flag_counter->setStyleSheet("color:red;font-weight: bold;");
    }
}

void Game::flagCounterDecreasedSlot()
{
    this->player.setFlag_counter(this->player.getFlag_counter()-1);
    ui->flag_counter->setText(QString::number(this->player.getFlag_counter()) + "/" + QString::number(difficulties[this->current_difficulty].number_of_mines));
    if(this->player.getFlag_counter() <= difficulties[this->current_difficulty].number_of_mines){
        ui->flag_counter->setStyleSheet("color:auto;font-weight: auto;");
    }
}

void Game::updateTime()
{
    ui->time->setText(QString::number(this->player.getTime()+ui->visibleGrid->elap_timer.elapsed()) + " ms");
    qApp->processEvents();
}

Player Game::getPlayer() const
{
    return player;
}

void Game::setPlayer(const Player &value)
{
    player = value;
}

int Game::getCurrent_difficulty() const
{
    return current_difficulty;
}

void Game::setCurrent_difficulty(int value)
{
    current_difficulty = value;
}


QSet<QPoint> Game::getMines() const
{
    return mines;
}

void Game::setMines(const QSet<QPoint> &value)
{
    mines = value;
}

QVector<QVector<Cell> > Game::getInvisible_grid() const
{
    return invisible_grid;
}

void Game::setInvisible_grid(const QVector<QVector<Cell> > &value)
{
    invisible_grid = value;
}
