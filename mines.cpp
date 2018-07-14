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
    ui->tableWidget->setVisible(false);
    this->ready = false;
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
            ui->tableWidget->item(j,i)->setWhatsThis("false");
        }
    }
    qApp->processEvents();
}

Mines::~Mines()
{
    delete ui;
}

void Mines::placeMines(int count)
{
    qsrand(time(0));

    // clear the set of mines
    this->mines.clear();

    qDebug() << " **********";

    // place mines
    int no=0;
    while(this->mines.count()<count){
        QPoint point(qrand()%ui->tableWidget->columnCount(), qrand()%ui->tableWidget->rowCount());
        this->mines.insert(point);
        this->grid[point.y()+1][point.x()+1]=MINE;
        qDebug() << no++ << " : " << point;
    }
}

void Mines::placeMineNumbers()
{
    // compute mine numbers
    for(int i=0; i< ui->tableWidget->rowCount();i++){
        for(int j=0; j<ui->tableWidget->columnCount();j++){
            if(this->grid[i+1][j+1]!=MINE){
                this->grid[i+1][j+1] = this->countNearbyMines(i,j);
            }
        }
    }
}

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
    quint16 mineCount = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(this->grid[row+i][col+j]==MINE){
                mineCount++;
            }
        }
    }
    return mineCount;
}

void Mines::clearVisibleGrid()
{
    for(int i=0; i< ui->tableWidget->rowCount();i++){
        for(int j=0; j<ui->tableWidget->columnCount();j++){
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

void Mines::revealEmptyArea(int row, int col)
{
    QList<QPoint> emptyCells;
    QList<QPoint> visitedCells;
    emptyCells.push_back(QPoint(col,row));
    int new_row, new_col;
    int complexity = 0;
    while(!emptyCells.isEmpty()){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(visitedCells.indexOf(emptyCells.first())==-1){
                    ui->tableWidget->removeCellWidget(new_row, new_col);
                    new_row = emptyCells.first().y()-1+i;
                    new_col = emptyCells.first().x()-1+j;
                    if(ui->tableWidget->item(new_row, new_col)){
                        this->makeItemVisible(new_row, new_col);
                        qApp->processEvents();
                        if(this->grid[new_row+1][new_col+1]==0){
                            emptyCells.push_back(QPoint(new_col,new_row));
                        }
                    }
                }
            }
        }
        complexity++;
        visitedCells.push_back(emptyCells.first());
        emptyCells.removeFirst();
    }
}

void Mines::makeItemVisible(int row, int col)
{
    if(this->grid[row+1][col+1]>0){
        ui->tableWidget->item(row, col)->setText(QString::number(this->grid[row+1][col+1]));
    }
    ui->tableWidget->item(row, col)->setFont(QFont("Tahoma",12,60));
    ui->tableWidget->item(row, col)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->item(row, col)->setBackgroundColor(QColor(210,210,210));
}

void Mines::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    if(this->ready==true){
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
        // if a user clicks on empty cell whole empty area gets revealed
        else if(this->grid[item->row()+1][item->column()+1]==0){
            this->revealEmptyArea(item->row(),item->column());
        }
        else{
            this->makeItemVisible(item->row(), item->column());
        }
    }
}

void Mines::on_start_game_button_clicked()
{
    for(int i=0; i < GRID_HEIGHT; i++){
        for(int j=0; j < GRID_WIDTH; j++){
            this->grid[i+1][j+1]=-1;
        }
    }
    this->clearVisibleGrid();
    this->placeMines(ui->noMinesSpinBox->value());
    this->placeMineNumbers();
    ui->tableWidget->setEnabled(true);
    ui->tableWidget->setVisible(true);
    this->ready = true;
}
