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
    ui->tableWidget->setEnabled(false);
    QObject::connect(this,
                     SIGNAL(cellsRevealedAutomatically(int)),
                     ui->tableWidget,
                     SLOT(cellsRevealedAutomaticallySlot(int)));
    QObject::connect(ui->tableWidget, SIGNAL(flagCounterIncreased()), this, SLOT(flagCounterIncreasedSlot()));
    QObject::connect(ui->tableWidget, SIGNAL(flagCounterDecreased()), this, SLOT(flagCounterDecreasedSlot()));

    this->ready = false;
    this->flagCnt=0;
    for(int j=0; j< ui->tableWidget->rowCount();j++){
        ui->tableWidget->setRowHeight(j,50);
    }
    for(int i=0; i<ui->tableWidget->columnCount();i++){
        ui->tableWidget->setColumnWidth(i, 50);
    }

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int j=0; j< ui->tableWidget->rowCount();j++){
        for(int i=0; i<ui->tableWidget->columnCount();i++){
            ui->tableWidget->setItem(j,i,new QTableWidgetItem(""));
            ui->tableWidget->item(j,i)->setBackgroundColor(QColor(150,150,150));
            ui->tableWidget->item(j,i)->setWhatsThis("noflag-nomine-novisit");
        }
    }
    qApp->processEvents();
}

Mines::~Mines()
{
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
        QPoint point(qrand()%ui->tableWidget->columnCount(), qrand()%ui->tableWidget->rowCount());
        this->mines.insert(point);
        this->grid[point.y()+1][point.x()+1]=MINE;
        ui->tableWidget->item(point.y(),point.x())->setWhatsThis("noflag-mine-novisit");
    }
}

// function to place mine numbers on the game grid
void Mines::placeMineNumbers()
{
    // compute mine numbers in non-mine cells
    for(int i=0; i< ui->tableWidget->rowCount();i++){
        for(int j=0; j<ui->tableWidget->columnCount();j++){
            if(this->grid[i+1][j+1]!=MINE){
                this->grid[i+1][j+1] = this->countNearbyMines(i,j);
            }
        }
    }
}

// function to compute how many nearby mines are present in the cell
int Mines::countNearbyMines(int row, int col)
{
    if(row<0 || row>=ui->tableWidget->rowCount()){
        qDebug() << "Out of range.";
        return -1;
    }
    if(col<0 || col>=ui->tableWidget->columnCount()){
        qDebug() << "Out of range.";
        return -2;
    }

    if(this->grid[row+1][col+1]==MINE){
        qDebug() << "MINE";
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
    for(int i=0; i< ui->tableWidget->rowCount();i++){
        for(int j=0; j<ui->tableWidget->columnCount();j++){
            ui->tableWidget->item(i,j)->setWhatsThis("noflag-nomine-novisit");
            if(ui->tableWidget->cellWidget(i,j)){
                ui->tableWidget->removeCellWidget(i,j);
            }
            else if(ui->tableWidget->item(i,j)){
                ui->tableWidget->item(i,j)->setText("");
                ui->tableWidget->item(i,j)->setBackgroundColor(QColor(150,150,150));
            }
        }
    }
}

// function reveal all empty cells when som empty cell is clicked
void Mines::revealEmptyArea(int row, int col)
{
    QList<QPoint> unvisitedEmptyCells;
    QList<QPoint> visitedEmptyCells;
    unvisitedEmptyCells.push_back(QPoint(col,row));
    int new_row, new_col;
    int complexity = 0;
    while(!unvisitedEmptyCells.isEmpty()){
        // exploring 8-connected neighborhood of the selected empty cell
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                new_row = unvisitedEmptyCells.first().y()-1+i;
                new_col = unvisitedEmptyCells.first().x()-1+j;
                // check if not out of bounds
                if(ui->tableWidget->item(new_row, new_col)){
                    // check if the cell was not visited
                    if(ui->tableWidget->item(new_row, new_col)->whatsThis() == "noflag-nomine-novisit"){
                        ui->tableWidget->removeCellWidget(new_row, new_col); // to remove possible flags
                        // check if another empty cell is found
                        if(this->grid[new_row+1][new_col+1]==0 && visitedEmptyCells.indexOf(unvisitedEmptyCells.first(),0)==-1){
                            unvisitedEmptyCells.push_back(QPoint(new_col,new_row));
                        }
                        this->makeItemVisible(new_row, new_col);
                        qApp->processEvents();
                        complexity++;
                    }
                }
            }
        }
        // put the current empty cell to the list of visited empty cells
        visitedEmptyCells.push_back(unvisitedEmptyCells.first());
        // remove the current empty cell from the list of unvisited empty cells
        unvisitedEmptyCells.removeFirst();
    }
    emit cellsRevealedAutomatically(complexity);
}

// function to make the selected cell visible
void Mines::makeItemVisible(int row, int col)
{
    ui->tableWidget->item(row, col)->setWhatsThis("noflag-nomine-visit");
    if(this->grid[row+1][col+1]>0){
        ui->tableWidget->item(row, col)->setText(QString::number(this->grid[row+1][col+1]));
    }
    ui->tableWidget->item(row, col)->setFont(QFont("Tahoma",12,60));
    ui->tableWidget->item(row, col)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->item(row, col)->setBackgroundColor(QColor(210,210,210));
}

// function to clear necessary data before game starts
void Mines::clearEverything()
{
    for(int i=0; i < GRID_HEIGHT; i++){
        for(int j=0; j < GRID_WIDTH; j++){
            this->grid[i+1][j+1]=-1;
        }
    }
    this->clearVisibleGrid();
}

// function to handle user clicks
void Mines::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    if(this->ready==true){
        // if a user clicks on a mine game ends
        if(this->grid[item->row()+1][item->column()+1]==MINE){
            qDebug() << "MINE";
            QLabel* wi = new QLabel();
            wi->setPixmap(QPixmap(qApp->applicationDirPath() + "/icon.png"));
            wi->setScaledContents(true);
            ui->tableWidget->setCellWidget(item->row(),item->column(),wi);
            qApp->processEvents();
            QMessageBox::about(this, "Mines", "Game Over");
            ui->tableWidget->setEnabled(false);
        }
        // if a user clicks on empty cell, a whole empty area gets revealed
        else if(this->grid[item->row()+1][item->column()+1]==0){
            this->revealEmptyArea(item->row(),item->column());
        }
        // if a user clicks on a cell with mine number, the cell is revealed
        else{
            this->makeItemVisible(item->row(), item->column());
            ui->tableWidget->noMineCounter--;
        }
        item->setWhatsThis("noflag-nomine-visit");
    }
}

// function to start the game
void Mines::on_start_game_button_clicked()
{
    ui->tableWidget->mineCounter=0;
    ui->tableWidget->noMineCounter=GRID_HEIGHT*GRID_WIDTH;
    ui->tableWidget->congratsShown=false;
    this->clearEverything();
    this->placeMines(ui->noMinesSpinBox->value());
    this->placeMineNumbers();
    ui->tableWidget->setEnabled(true);
    this->ready = true;
    this->flagCnt=0;
    ui->flag_counter->setText(QString::number(this->flagCnt) + "/" + QString::number(ui->noMinesSpinBox->value()));
    ui->statusBar->showMessage("New game started.",3000);
}

void Mines::flagCounterIncreasedSlot()
{
    this->flagCnt++;
    ui->flag_counter->setText(QString::number(this->flagCnt) + "/" + QString::number(ui->noMinesSpinBox->value()));
    if(this->flagCnt > ui->noMinesSpinBox->value()){
        ui->flag_counter->setStyleSheet("color:red;font-weight: bold;");
    }
}

void Mines::flagCounterDecreasedSlot()
{
    this->flagCnt--;
    ui->flag_counter->setText(QString::number(this->flagCnt) + "/" + QString::number(ui->noMinesSpinBox->value()));
    if(this->flagCnt <= ui->noMinesSpinBox->value()){
        ui->flag_counter->setStyleSheet("color:auto;font-weight: auto;");
    }
}
