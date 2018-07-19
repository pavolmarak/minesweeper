#include "game_gui.h"
#include "ui_mines.h"

// constructor
GameGUI::GameGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mines)
{
    ui->setupUi(this);

    // ************************************************
    // ***********                          ***********
    // *********** LEADERBOARD BUTTON SETUP ***********
    // ***********                          ***********
    // ************************************************

    // enable leaderboard button
    ui->show_leaderboard_button->setEnabled(true);


    // ******************************************
    // ***********                    ***********
    // *********** VISIBLE GRID SETUP ***********
    // ***********                    ***********
    // ******************************************

    // visible game grid is represented as QTableWidget

    // visible grid is disabled by default
    ui->visibleGrid->setEnabled(false);

    // set dimensions of the visible game grid
    ui->visibleGrid->setRowCount(this->game.difficulties[this->game.getCurrent_difficulty()].grid_height);
    ui->visibleGrid->setColumnCount(this->game.difficulties[this->game.getCurrent_difficulty()].grid_width);
    for(int i=0; i< ui->visibleGrid->rowCount();i++){
        ui->visibleGrid->setRowHeight(i,TILE_SIZE);
    }
    for(int i=0; i<ui->visibleGrid->columnCount();i++){
        ui->visibleGrid->setColumnWidth(i, TILE_SIZE);
    }

    // set headers
    ui->visibleGrid->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->visibleGrid->horizontalHeader()->setStretchLastSection(true);
    ui->visibleGrid->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->visibleGrid->verticalHeader()->setStretchLastSection(false);

    // create items in visible game grid, set their default color and hints
    for(int i=0; i< ui->visibleGrid->rowCount();i++){
        for(int j=0; j<ui->visibleGrid->columnCount();j++){
            ui->visibleGrid->setItem(i,j,new QTableWidgetItem(""));
            ui->visibleGrid->item(i,j)->setBackgroundColor(QColor(150,150,150));
            ui->visibleGrid->item(i,j)->setWhatsThis("noflag-nomine-novisit");
        }
    }


    // ***************************************
    // ***********                 ***********
    // *********** GAME INFO SETUP ***********
    // ***********                 ***********
    // ***************************************

    // flag counter setup
    ui->flag_counter->setText("0/" + QString::number(this->game.difficulties[this->game.getCurrent_difficulty()].number_of_mines));

    // pause button setup
    ui->pause_time_button->setEnabled(false);

    // game time setup
    ui->time->setText("0 ms");
    ui->time->setAlignment(Qt::AlignVCenter|Qt::AlignRight);


    // *****************************************
    // ***********                   ***********
    // *********** GAME CONFIG SETUP ***********
    // ***********                   ***********
    // *****************************************

    // populate the list of available difficulties in the combobox
    foreach (Difficulty d, this->game.difficulties) {
        ui->gridsize_selector->addItem(d.name);
    }

    // set the number of mines for the given game difficulty
    ui->noMinesSpinBox->setValue(this->game.difficulties[this->game.getCurrent_difficulty()].number_of_mines);
    ui->noMinesSpinBox->setEnabled(false); // user cannot change number of mines in the preset game difficulty

    // start game button setup
    ui->start_game_button->setEnabled(true);


    // *************************************
    // ***********               ***********
    // *********** SIGNALS/SLOTS ***********
    // ***********               ***********
    // *************************************

    // signal when empty cell region is revealed automatically
    QObject::connect(this,
                     SIGNAL(cellsRevealedAutomatically(int)),
                     ui->visibleGrid,
                     SLOT(cellsRevealedAutomaticallySlot(int)));
    // signal when user places a flag on the visible game grid
    QObject::connect(ui->visibleGrid, SIGNAL(flagCounterIncreased()), &(this->game), SLOT(flagCounterIncreasedSlot()));
    // signal when user removes a flag from the visible game grid
    QObject::connect(ui->visibleGrid, SIGNAL(flagCounterDecreased()), &(this-game), SLOT(flagCounterDecreasedSlot()));
    // signal emitted every 1 ms to update time of gameplay
    QObject::connect(&(ui->visibleGrid->timer), SIGNAL(timeout()), this, SLOT(updateTime()));
    // signal when leaderboard window is closed
    QObject::connect(&(this->game.lb),SIGNAL(leaderboardClosedSignal()),this, SLOT(leaderboardClosedSlot()));

    qApp->processEvents();
}

//destructor
GameGUI::~GameGUI()
{
    delete ui;
}

// function to handle user clicks
void GameGUI::on_visibleGrid_itemClicked(QTableWidgetItem *item)
{
    int** invisible_grid = this->game.getInvisible_grid();
    // if invisible game grid exists
    if(invisible_grid){
        // if a user clicks on a mine, game ends
        if(invisible_grid[item->row()+1][item->column()+1]==MINE){
            //when a mine is found, some elements are disabled
            ui->pause_time_button->setEnabled(false);
            ui->visibleGrid->setEnabled(false);

            qDebug() << "*** MINE ***";
            QLabel* wi = new QLabel();
            wi->setPixmap(QPixmap(qApp->applicationDirPath() + "/mine_icon.png"));
            wi->setScaledContents(true);
            ui->visibleGrid->setCellWidget(item->row(),item->column(),wi);
            qApp->processEvents();
            // on Linux and Windows this is modal window blocking all background activity
            // on MacOS it is modeless
            QMessageBox::about(this, "Mine", "Game Over");
        }
        // if a user clicks on empty cell, a whole empty area gets revealed
        else if(invisible_grid[item->row()+1][item->column()+1]==0){
            emit cellsRevealedAutomatically(this->game.revealEmptyArea(item->row(),item->column()));
        }
        // if a user clicks on a cell with mine number, the cell is revealed
        else{
            this->showMineNumber(item->row(), item->column());
            ui->visibleGrid->noMineCounter--;
        }
    }
    else{
        qDebug() << "User click: Invisible game grid does not exist.";
    }
}



// function to start the game
void GameGUI::on_start_game_button_clicked()
{
    this->clearEverything();

    // free old game grid
    this->freeInvisibleGrid(difficulties[this->current_difficulty].grid_height+2);

    this->current_difficulty = ui->gridsize_selector->currentIndex();

    // allocate new game grid
    this->createInvisibleGrid(
        this->difficulties[this->current_difficulty].grid_height+2,
        this->difficulties[this->current_difficulty].grid_width+2
    );

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


void GameGUI::on_pause_time_button_clicked(bool checked)
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


void GameGUI::on_show_leaderboard_button_clicked()
{
    this->lb.setResultboxVisible(false); // displays also a resultbox
    this->lb.setTimeTaken(0);
    this->lb.setSubmitBtnEnabled(false);
    this->lb.show();
}

void GameGUI::leaderboardClosedSlot()
{
    ui->show_leaderboard_button->setEnabled(true);
    ui->start_game_button->setEnabled(true);
    ui->gridsize_selector->setEnabled(true);
}

void GameGUI::updateTime()
{
    ui->time->setText(QString::number(this->player.getTime()+ui->visibleGrid->elap_timer.elapsed()) + " ms");
    qApp->processEvents();
}

void GameGUI::flagCounterIncreasedSlot()
{
    this->player.setFlag_counter(this->player.getFlag_counter()+1);
    ui->flag_counter->setText(QString::number(this->player.getFlag_counter()) + "/" + QString::number(difficulties[this->current_difficulty].number_of_mines));
    if(this->player.getFlag_counter() > difficulties[this->current_difficulty].number_of_mines){
        ui->flag_counter->setStyleSheet("color:red;font-weight: bold;");
    }
}

void GameGUI::flagCounterDecreasedSlot()
{
    this->player.setFlag_counter(this->player.getFlag_counter()-1);
    ui->flag_counter->setText(QString::number(this->player.getFlag_counter()) + "/" + QString::number(difficulties[this->current_difficulty].number_of_mines));
    if(this->player.getFlag_counter() <= difficulties[this->current_difficulty].number_of_mines){
        ui->flag_counter->setStyleSheet("color:auto;font-weight: auto;");
    }
}

