#include "mines.h"
#include "ui_mines.h"

inline uint qHash (const QPoint & key)
{
    return qHash (QPair<int,int>(key.x(), key.y()) );
}

Mines::Mines(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mines)
{
    ui->setupUi(this);

    // general setup
    this->current_difficulty = 0;
    difficulties.push_back(DIFFICULTY(10,10,10,"Easy"));
    difficulties.push_back(DIFFICULTY(15,15,25,"Medium"));
    difficulties.push_back(DIFFICULTY(20,20,50,"Hard"));
    this->grid = new int*[difficulties[this->current_difficulty].grid_height+2];
    for(int i=0;i<difficulties[this->current_difficulty].grid_height+2;i++){
        this->grid[i] = new int[difficulties[this->current_difficulty].grid_width+2];
        for(int j=0;j<difficulties[this->current_difficulty].grid_width+2;j++){
            this->grid[i][j] = -1;
        }
    }


    // leaderboard button setup
    ui->show_leaderboard_button->setEnabled(true);


    // game grid setup
    ui->visibleGrid->setEnabled(false);
    ui->visibleGrid->setRowCount(difficulties[this->current_difficulty].grid_height);
    ui->visibleGrid->setColumnCount(difficulties[this->current_difficulty].grid_width);
    for(int i=0; i< ui->visibleGrid->rowCount();i++){
        ui->visibleGrid->setRowHeight(i,TILE_SIZE);
    }
    for(int i=0; i<ui->visibleGrid->columnCount();i++){
        ui->visibleGrid->setColumnWidth(i, TILE_SIZE);
    }
    ui->visibleGrid->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->visibleGrid->horizontalHeader()->setStretchLastSection(true);
    ui->visibleGrid->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->visibleGrid->verticalHeader()->setStretchLastSection(false);
    for(int i=0; i< ui->visibleGrid->rowCount();i++){
        for(int j=0; j<ui->visibleGrid->columnCount();j++){
            ui->visibleGrid->setItem(i,j,new QTableWidgetItem(""));
            ui->visibleGrid->item(i,j)->setBackgroundColor(QColor(150,150,150));
            ui->visibleGrid->item(i,j)->setWhatsThis("noflag-nomine-novisit");
        }
    }


    // game info setup
    ui->flag_counter->setText(QString::number(this->player.getFlag_counter()) + "/" + QString::number(difficulties[this->current_difficulty].number_of_mines));
    ui->pause_time_button->setEnabled(false);
    ui->time->setText("0 ms");
    ui->time->setAlignment(Qt::AlignVCenter|Qt::AlignRight);


    // game configuration setup
    foreach (DIFFICULTY d, difficulties) {
        ui->gridsize_selector->addItem(d.name);
    }
    ui->noMinesSpinBox->setValue(difficulties[this->current_difficulty].number_of_mines);
    ui->noMinesSpinBox->setEnabled(false);
    ui->start_game_button->setEnabled(true);


    // leaderboard setup
    this->lb.setup(qApp->applicationDirPath() + "/" + LEADERBOARD_FILE,difficulties);
    this->lb.setWindowTitle("Leaderboard");
    this->lb.setWindowIcon(QIcon(qApp->applicationDirPath() + "/leaderboard_icon.png"));


    // SIGNAL/SLOT connections
    QObject::connect(this,
                     SIGNAL(cellsRevealedAutomatically(int)),
                     ui->visibleGrid,
                     SLOT(cellsRevealedAutomaticallySlot(int)));
    QObject::connect(ui->visibleGrid, SIGNAL(flagCounterIncreased()), this, SLOT(flagCounterIncreasedSlot()));
    QObject::connect(ui->visibleGrid, SIGNAL(flagCounterDecreased()), this, SLOT(flagCounterDecreasedSlot()));
    QObject::connect(&(ui->visibleGrid->timer), SIGNAL(timeout()), this, SLOT(updateTime()));
    QObject::connect(ui->visibleGrid, SIGNAL(timerStop()), this, SLOT(timerStopSlot()));
    QObject::connect(ui->visibleGrid->getLb(),SIGNAL(leaderboardClosedSignal()),this, SLOT(leaderboardClosedSlot()));


    qApp->processEvents();
}

Mines::~Mines()
{
    // free the game grid
    for(int i=0;i<difficulties[this->current_difficulty].grid_height+2;i++){
       delete [] this->grid[i];
    }
    delete [] this->grid;
    delete ui;
}

// function to place random mines on the game grid
void Mines::placeMines(int count)
{
    // qrand init
    qsrand(time(0));

    // clear the previous set of mines
    this->mines.clear();

    // place mines
    while(this->mines.count()<count){
        QPoint point(qrand()%difficulties[this->current_difficulty].grid_width, qrand()%difficulties[this->current_difficulty].grid_height);
        this->mines.insert(point);
        this->grid[point.y()+1][point.x()+1]=MINE; // +1 offset beacuse the grid has extra stripe of cells on each side
        ui->visibleGrid->item(point.y(),point.x())->setWhatsThis("noflag-mine-novisit");
    }
}

// function to place mine numbers on the game grid
void Mines::placeMineNumbers()
{
    // compute mine numbers in non-mine cells
    for(int i=0; i< difficulties[this->current_difficulty].grid_height;i++){
        for(int j=0; j<difficulties[this->current_difficulty].grid_width;j++){
            if(this->grid[i+1][j+1]!=MINE){
                this->grid[i+1][j+1] = this->countNearbyMines(i,j);
                ui->visibleGrid->item(i,j)->setWhatsThis("noflag-nomine-novisit");
            }
        }
    }
}

// function to compute how many nearby mines are present around the cell
int Mines::countNearbyMines(int row, int col)
{
    if(row<0 || row>=difficulties[this->current_difficulty].grid_height){
        qDebug() << "Out of range.";
        return -1;
    }
    if(col<0 || col>=difficulties[this->current_difficulty].grid_width){
        qDebug() << "Out of range.";
        return -2;
    }

    if(this->grid[row+1][col+1]==MINE){
        return -999;
    }
    int mineCount = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(this->grid[row+i][col+j]==MINE){
                mineCount++;
            }
        }
    }
    return mineCount;
}

// function to clear the visible game grid
void Mines::clearVisibleGrid()
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

// function to reveal all empty cells when some empty cell is clicked
int Mines::revealEmptyArea(int row, int col)
{
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
                        if(this->grid[new_row+1][new_col+1]==0 && visitedEmptyCells.indexOf(unvisitedEmptyCells.first(),0)==-1){
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

// function to show mine number on the game grid
void Mines::showMineNumber(int row, int col)
{
    if(ui->visibleGrid->item(row, col)->whatsThis() == "noflag-nomine-novisit"){
        ui->visibleGrid->item(row, col)->setWhatsThis("noflag-nomine-visit");

        // prevents from displaying 0
        if(this->grid[row+1][col+1]>0){
            ui->visibleGrid->item(row, col)->setText(QString::number(this->grid[row+1][col+1]));
        }
        ui->visibleGrid->item(row, col)->setFont(QFont("Tahoma",12,60));
        ui->visibleGrid->item(row, col)->setTextAlignment(Qt::AlignCenter);
        ui->visibleGrid->item(row, col)->setBackgroundColor(QColor(210,210,210));
    }

}

// function to clear necessary data before game starts
void Mines::clearEverything()
{
    this->mines.clear();
    for(int i=0; i < difficulties[this->current_difficulty].grid_height+2; i++){
        for(int j=0; j < difficulties[this->current_difficulty].grid_width+2; j++){
            this->grid[i+1][j+1]=-1;
        }
    }
    this->clearVisibleGrid();
    ui->time->setText("0 ms");
    ui->time->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    ui->flag_counter->setText("0/" + QString::number(difficulties[this->current_difficulty].number_of_mines));
}

// function to handle user clicks
void Mines::on_visibleGrid_itemClicked(QTableWidgetItem *item)
{
    // if a user clicks on a mine, game ends
    if(this->grid[item->row()+1][item->column()+1]==MINE){
        //when a mine is found, all buttons are disabled
//        ui->pause_time_button->setEnabled(false);
//        ui->show_leaderboard_button->setEnabled(false);
//        ui->start_game_button->setEnabled(false);
//        ui->gridsize_selector->setEnabled(false);
        qDebug() << "MINE";
        QLabel* wi = new QLabel();
        wi->setPixmap(QPixmap(qApp->applicationDirPath() + "/icon.png"));
        wi->setScaledContents(true);
        ui->visibleGrid->setCellWidget(item->row(),item->column(),wi);
        qApp->processEvents();
        QMessageBox::about(this, "Mine", "Game Over");
        ui->visibleGrid->setEnabled(false);
    }
    // if a user clicks on empty cell, a whole empty area gets revealed
    else if(this->grid[item->row()+1][item->column()+1]==0){
        emit cellsRevealedAutomatically(this->revealEmptyArea(item->row(),item->column()));
    }
    // if a user clicks on a cell with mine number, the cell is revealed
    else{
        this->showMineNumber(item->row(), item->column());
        ui->visibleGrid->noMineCounter--;
    }
}

// function to start the game
void Mines::on_start_game_button_clicked()
{
    this->clearEverything();

    // free old game grid
    for(int i=0;i<difficulties[this->current_difficulty].grid_height+2;i++){
       delete [] this->grid[i];
    }
    delete [] this->grid;

    this->current_difficulty = ui->gridsize_selector->currentIndex();

    // allocate new game grid
    this->grid = new int*[difficulties[this->current_difficulty].grid_height+2];
    for(int i=0;i<difficulties[this->current_difficulty].grid_height+2;i++){
        this->grid[i] = new int[difficulties[this->current_difficulty].grid_width+2];
        for(int j=0;j<difficulties[this->current_difficulty].grid_width+2;j++){
            this->grid[i][j] = -1;
        }
    }

    // re-create visible grid
    ui->visibleGrid->setEnabled(true);
    ui->visibleGrid->setVisible(true);
    ui->visibleGrid->clearContents();
    ui->visibleGrid->setRowCount(difficulties[this->current_difficulty].grid_height);
    ui->visibleGrid->setColumnCount(difficulties[this->current_difficulty].grid_width);
    for(int i=0; i< ui->visibleGrid->rowCount();i++){
        ui->visibleGrid->setRowHeight(i,TILE_SIZE);
    }
    for(int i=0; i<ui->visibleGrid->columnCount();i++){
        ui->visibleGrid->setColumnWidth(i, TILE_SIZE);
    }
    ui->visibleGrid->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->visibleGrid->horizontalHeader()->setStretchLastSection(true);
    ui->visibleGrid->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->visibleGrid->verticalHeader()->setStretchLastSection(false);
    for(int i=0; i< ui->visibleGrid->rowCount();i++){
        for(int j=0; j<ui->visibleGrid->columnCount();j++){
            ui->visibleGrid->setItem(i,j,new QTableWidgetItem(""));
            ui->visibleGrid->item(i,j)->setBackgroundColor(QColor(150,150,150));
            ui->visibleGrid->item(i,j)->setWhatsThis("noflag-nomine-novisit");
        }
    }

    ui->show_leaderboard_button->setEnabled(true);
    ui->pause_time_button->setEnabled(true);
    ui->pause_time_button->setChecked(false);
    ui->start_game_button->setEnabled(true);
    ui->gridsize_selector->setEnabled(true);
    ui->noMinesSpinBox->setValue(difficulties[this->current_difficulty].number_of_mines);

    this->placeMines(difficulties[this->current_difficulty].number_of_mines);
    this->placeMineNumbers();
    this->player.setTime(0);
    this->player.setFlag_counter(0);


    ui->visibleGrid->mineCounter=0;
    ui->visibleGrid->noMineCounter=difficulties[this->current_difficulty].grid_height*difficulties[this->current_difficulty].grid_width;
    ui->visibleGrid->congratsShown=false;
    ui->visibleGrid->timer.start(1);
    ui->visibleGrid->elap_timer.restart();

    ui->statusBar->showMessage("New game started.",3000);
    qApp->processEvents();
}

void Mines::flagCounterIncreasedSlot()
{
    this->player.setFlag_counter(this->player.getFlag_counter()+1);
    ui->flag_counter->setText(QString::number(this->player.getFlag_counter()) + "/" + QString::number(difficulties[this->current_difficulty].number_of_mines));
    if(this->player.getFlag_counter() > difficulties[this->current_difficulty].number_of_mines){
        ui->flag_counter->setStyleSheet("color:red;font-weight: bold;");
    }
}

void Mines::flagCounterDecreasedSlot()
{
    this->player.setFlag_counter(this->player.getFlag_counter()-1);
    ui->flag_counter->setText(QString::number(this->player.getFlag_counter()) + "/" + QString::number(difficulties[this->current_difficulty].number_of_mines));
    if(this->player.getFlag_counter() <= difficulties[this->current_difficulty].number_of_mines){
        ui->flag_counter->setStyleSheet("color:auto;font-weight: auto;");
    }
}

void Mines::updateTime()
{
    ui->time->setText(QString::number(this->player.getTime()+ui->visibleGrid->elap_timer.elapsed()) + " ms");
    qApp->processEvents();
}

// when a user wins
void Mines::timerStopSlot()
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

void Mines::leaderboardClosedSlot()
{
    ui->show_leaderboard_button->setEnabled(true);
    ui->start_game_button->setEnabled(true);
    ui->gridsize_selector->setEnabled(true);
}

void Mines::on_pause_time_button_clicked(bool checked)
{
    if(checked){
        this->player.setTime(this->player.getTime() + ui->visibleGrid->elap_timer.elapsed());
        ui->visibleGrid->timer.stop();
        ui->pause_time_button->setChecked(true);
        ui->visibleGrid->setVisible(false);
    }
    else{
        ui->visibleGrid->setVisible(true);
        ui->visibleGrid->timer.start(1);
        ui->visibleGrid->elap_timer.restart();
        ui->pause_time_button->setChecked(false);
    }
}


void Mines::on_show_leaderboard_button_clicked()
{
    this->lb.setResultboxVisible(false); // displays also a resultbox
    this->lb.setTimeTaken(0);
    this->lb.setSubmitBtnEnabled(false);
    this->lb.show();
}
