#include "game.h"

// helper function for QMultiMap
inline uint qHash (const QPoint & key)
{
    return qHash (QPair<int,int>(key.x(), key.y()) );
}

// constructor
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
                Cell()
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

// destructor
Game::~Game(){

}

// function to place random mines on the invisible game grid along with mine numbers
void Game::placeMines(int count)
{
    if(!this->invisible_grid.isEmpty()){
        // clear the invisible game grid
        for(int i=0; i<this->invisible_grid.length();i++){
            this->invisible_grid[i].fill(Cell());
        }

        // qrand init
        qsrand(time(0));

        int r_row, r_col;
        // place mines
        while(count>0){
            r_row = qrand()%this->difficulties[this->current_difficulty].grid_height;
            r_col = qrand()%this->difficulties[this->current_difficulty].grid_width;
            this->invisible_grid[r_row][r_col]=Cell(MINE,UNVISITED);
            count--;
        }
        // place mine numbers
        this->placeMineNumbers();
    }
    else{
        qDebug() << "Placing mines: Invisible game grid does not exist.";
    }
}

// function to place mine numbers on the invisible game grid
void Game::placeMineNumbers()
{
    // compute mine numbers in non-mine cells
    for(int i=0; i< this->difficulties[this->current_difficulty].grid_height;i++){
        for(int j=0; j<this->difficulties[this->current_difficulty].grid_width;j++){
            if(this->invisible_grid[i][j].value != MINE){
                this->invisible_grid[i][j].value = this->countNearbyMines(i,j);
                this->invisible_grid[i][j].status = UNVISITED;
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

    if(this->invisible_grid[row][col].value == MINE){
        qDebug() << "Counting nearby mines: Mine.";
        return -999;
    }
    int mineCount = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(this->invisible_grid.value(row-1+i).value(col-1+j).value == MINE){
                mineCount++;
            }
        }
    }
    return mineCount;
}

// function to handle user left-clicks
ClickResult Game::userLeftClick(int row, int col)
{
    ClickResult cr;
    if(this->invisible_grid[row][col].status == UNVISITED){
        if(this->invisible_grid[row][col].value == MINE){
            this->invisible_grid[row][col].status = VISITED;
            cr.is_mine = true;
        }
        else if(this->invisible_grid[row][col].value == 0){
            cr.cellsRevealed = this->revealEmptyArea(row,col);
            cr.is_mine = false;
        }
        else{
            this->invisible_grid[row][col].status = VISITED;
            cr.cellsRevealed.push_back(QPoint(col,row));
            cr.is_mine = false;
        }
    }
    return cr;
}

// function to handle user right-clicks
void Game::userRightClick(int row, int col)
{

}

// function to reveal empty cell region when some empty cell is clicked
QVector<QPoint> Game::revealEmptyArea(int row, int col)
{
    QVector<QPoint> cellsRevealed;
    if(this->invisible_grid[row][col].value == 0){
        QList<QPoint> unvisitedEmptyCells;
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
                    if(
                            (new_row>=0 && new_row<this->difficulties[this->current_difficulty].grid_height)
                            &&
                            (new_col>=0 && new_col<this->difficulties[this->current_difficulty].grid_width)
                      ){
                        // check if the cell was not visited
                        if(this->invisible_grid[new_row][new_col].status == UNVISITED){
                            // check if another empty cell is found
                            if(this->invisible_grid[new_row][new_col].value == 0){
                                unvisitedEmptyCells.push_back(QPoint(new_col,new_row));
                            }
                            this->invisible_grid[new_row][new_col].status = VISITED;
                            cellsRevealed.push_back(QPoint(new_col,new_row));
                            qApp->processEvents();
                            itemsRevealed++;
                        }
                    }
                }
            }
            // remove the current empty cell from the list of unvisited empty cells
            unvisitedEmptyCells.removeFirst();
        }
    }
    qDebug() << "Revealing empty cells: Cell is not empty.";
    return cellsRevealed;
}

// function to create new invisible game grid and set it to user-defined value,
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

QVector<QVector<Cell> > Game::getInvisible_grid() const
{
    return invisible_grid;
}
