#include "game_gui.h"
#include "ui_game_gui.h"

// constructor
GameGUI::GameGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameGUI)
{
    ui->setupUi(this);

    // reset gui
    this->resetGui();

    // start game button setup
    ui->start_game_button->setEnabled(true);

    // *********** SIGNALS/SLOTS ***********
    QObject::connect(&(this->game.timer), SIGNAL(timeout()), this, SLOT(timeoutSlot()));
    QObject::connect(ui->visibleGrid, SIGNAL(rightClickSignal(QTableWidgetItem*)), this, SLOT(rightClickSlot(QTableWidgetItem*)));
    QObject::connect(ui->visibleGrid, SIGNAL(leftClickSignal(QTableWidgetItem*)), this, SLOT(leftClickSlot(QTableWidgetItem*)));
    QObject::connect(&(this->game.getLb()), SIGNAL(leaderboardClosedSignal()), this, SLOT(leaderboardClosedSlot()));
    qApp->processEvents();
}

// destructor
GameGUI::~GameGUI()
{
    delete ui;
}

void GameGUI::resetGui()
{
    // reset leaderboard button
    ui->show_leaderboard_button->setEnabled(true);

    // reset visible grid
    ui->visibleGrid->clearContents();
    ui->visibleGrid->setEnabled(false);
    ui->visibleGrid->setVisible(true);
    ui->visibleGrid->setFocusPolicy(Qt::NoFocus);

    ui->visibleGrid->setRowCount(this->game.difficulties[this->game.getCurrent_difficulty()].grid_height);
    ui->visibleGrid->setColumnCount(this->game.difficulties[this->game.getCurrent_difficulty()].grid_width);
    //    this->setGeometry(0,0, this->game.difficulties[this->game.getCurrent_difficulty()].grid_width,this->game.difficulties[this->game.getCurrent_difficulty()].grid_height);
    //    this->setm
    for(int i=0; i< ui->visibleGrid->rowCount();i++){
        ui->visibleGrid->setRowHeight(i,TILE_SIZE);
    }
    for(int i=0; i<ui->visibleGrid->columnCount();i++){
        ui->visibleGrid->setColumnWidth(i, TILE_SIZE);
    }
    ui->visibleGrid->horizontalHeader()->setDefaultSectionSize(TILE_SIZE);
    ui->visibleGrid->verticalHeader()->setDefaultSectionSize(TILE_SIZE);
    ui->visibleGrid->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->visibleGrid->horizontalHeader()->setStretchLastSection(false);
    ui->visibleGrid->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->visibleGrid->verticalHeader()->setStretchLastSection(false);

    for(int i=0; i< ui->visibleGrid->rowCount();i++){
        for(int j=0; j<ui->visibleGrid->columnCount();j++){
            ui->visibleGrid->setItem(i,j,new QTableWidgetItem(""));
            ui->visibleGrid->item(i,j)->setBackgroundColor(QColor(150,150,150));
            ui->visibleGrid->item(i,j)->setSizeHint(QSize(TILE_SIZE,TILE_SIZE));
        }
    }

    // reset game info box
    ui->flag_counter->setText("0/" + QString::number(this->game.difficulties[this->game.getCurrent_difficulty()].number_of_mines));
    ui->pause_time_button->setEnabled(false);
    ui->pause_time_button->setChecked(false);
    ui->time->setText("0 ms");
    ui->time->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    // reset game configuration box
    ui->gridsize_selector->setEnabled(true);
    ui->gridsize_selector->clear();
    foreach (Difficulty d, this->game.difficulties) {
        ui->gridsize_selector->addItem(d.name + ", " + QString::number(d.grid_height) + "x" + QString::number(d.grid_width) + ", " + QString::number(d.number_of_mines) + " mines");
    }
    ui->gridsize_selector->setCurrentIndex(this->game.getCurrent_difficulty());

    // set the number of mines for the given game difficulty
    ui->noMinesSpinBox->setValue(this->game.difficulties[this->game.getCurrent_difficulty()].number_of_mines);
    if(this->game.difficulties[this->game.getCurrent_difficulty()].name != "Custom"){
        ui->noMinesSpinBox->setEnabled(false);
    }

    // initial start button focus
    ui->start_game_button->setFocus();
}



// function to start the game
void GameGUI::on_start_game_button_clicked()
{
    // apply the currently selected difficulty
    this->game.setCurrent_difficulty(ui->gridsize_selector->currentIndex());

    // reset invisible grid
    this->game.createInvisibleGrid(
                this->game.difficulties[this->game.getCurrent_difficulty()].grid_height,
                this->game.difficulties[this->game.getCurrent_difficulty()].grid_width,
                Cell()
            );

    // set number of unvisited cells in the grid
    this->game.setUnvisited_cells(this->game.difficulties[this->game.getCurrent_difficulty()].grid_height *this->game.difficulties[this->game.getCurrent_difficulty()].grid_width);

    // populate invisible grid
    this->game.placeMines(this->game.difficulties[this->game.getCurrent_difficulty()].number_of_mines);

    // reset gui
    this->resetGui();
    ui->visibleGrid->setEnabled(true);
    ui->pause_time_button->setEnabled(true);

    // reset player
    this->game.setPlayer(Player());

    ui->statusBar->showMessage("New game started.",3000);

    // reset timers
    this->game.timer.start(TIMER_INTERVAL);
    this->game.elap_timer.restart();

    qApp->processEvents();
}


void GameGUI::on_pause_time_button_clicked(bool checked)
{
    Player p = this->game.getPlayer();
    if(checked){
        p.setTime(p.getTime() + this->game.elap_timer.elapsed());
        this->game.timer.stop();
        ui->visibleGrid->setVisible(false);
    }
    else{
        ui->visibleGrid->setVisible(true);
        this->game.timer.start(TIMER_INTERVAL);
        this->game.elap_timer.restart();
    }
    this->game.setPlayer(p);
}


void GameGUI::on_show_leaderboard_button_clicked()
{
    ui->show_leaderboard_button->setEnabled(false);
    this->game.showLeaderboard(false,ui->gridsize_selector->currentIndex());
}

void GameGUI::on_noMinesSpinBox_valueChanged(int arg1)
{

}

void GameGUI::timeoutSlot()
{
    ui->time->setText(QString::number(this->game.getPlayer().getTime()+ this->game.elap_timer.elapsed()) + " ms");
}


void GameGUI::leftClickSlot(QTableWidgetItem* item)
{
    LeftClickResult result = this->game.userLeftClick(item->row(),item->column());
    // if user left-clicked on a mine
    if(result.is_mine == true){
        ui->pause_time_button->setEnabled(false);

        this->game.timer.stop();
        qDebug() << "*** MINE ***";
        for(int i=0; i<this->game.getInvisible_grid().length();i++) {
            for(int j=0; j<this->game.getInvisible_grid().at(i).length();j++) {
                if(this->game.getInvisible_grid().at(i).at(j).value == MINE){
                    QLabel* wi = new QLabel();
                    wi->setPixmap(QPixmap(qApp->applicationDirPath() + "/mine_icon.png"));
                    wi->setScaledContents(true);
                    ui->visibleGrid->item(i,j)->setBackgroundColor(QColor(220,220,220));
                    ui->visibleGrid->setCellWidget(i,j,wi);
                }
            }
        }
        ui->visibleGrid->setEnabled(false);
        qApp->processEvents();
        // on Linux and Windows this is modal window blocking all background activity
        // on MacOS it is modeless
        QMessageBox::about(this, "Mine", "Game Over");
    }
    else{
        // reveal one or more cells
        foreach (QPoint p, result.cellsRevealed) {
            ui->visibleGrid->item(p.y(), p.x())->setBackgroundColor(QColor(220,220,220));
            if(this->game.getInvisible_grid()[p.y()][p.x()].value > 0){
                ui->visibleGrid->item(p.y(), p.x())->setFont(QFont("Tahoma",12));
                ui->visibleGrid->item(p.y(), p.x())->setTextAlignment(Qt::AlignCenter);
                ui->visibleGrid->item(p.y(), p.x())->setText(QString::number(this->game.getInvisible_grid()[p.y()][p.x()].value));
            }
            ui->visibleGrid->item(p.y(), p.x())->setSelected(false);
            this->game.unvisited_cellsDown();
        }
    }
    if(this->game.accomplished(ui->gridsize_selector->currentIndex())==true){
        ui->show_leaderboard_button->setEnabled(false);
        ui->pause_time_button->setEnabled(false);
        ui->start_game_button->setEnabled(false);
        ui->visibleGrid->setEnabled(false);
        ui->time->setText(QString::number(this->game.getPlayer().getTime()) + " ms");
        qDebug() << "Game accomplished.";
    }
}

void GameGUI::leaderboardClosedSlot()
{
    ui->show_leaderboard_button->setEnabled(true);
    ui->start_game_button->setEnabled(true);
}

void GameGUI::rightClickSlot(QTableWidgetItem* item)
{
    if(this->game.userRightClick(item->row(),item->column()) == true){
        QLabel* wi = new QLabel();
        wi->setPixmap(QPixmap(qApp->applicationDirPath() + "/flag.png"));
        wi->setScaledContents(true);
        ui->visibleGrid->setCellWidget(item->row(),item->column(),wi);
        if(this->game.getPlayer().getFlag_counter() > this->game.difficulties[this->game.getCurrent_difficulty()].number_of_mines){
            ui->flag_counter->setStyleSheet("color:red;font-weight:bold;");
        }
        ui->flag_counter->setText(QString::number(this->game.getPlayer().getFlag_counter()) + "/" + QString::number(this->game.difficulties[this->game.getCurrent_difficulty()].number_of_mines));
        qApp->processEvents();
    }
    else{
        ui->visibleGrid->removeCellWidget(item->row(),item->column());
        if(this->game.getPlayer().getFlag_counter() <= this->game.difficulties[this->game.getCurrent_difficulty()].number_of_mines){
            ui->flag_counter->setStyleSheet("color:auto;font-weight:auto;");
        }
        ui->flag_counter->setText(QString::number(this->game.getPlayer().getFlag_counter()) + "/" + QString::number(this->game.difficulties[this->game.getCurrent_difficulty()].number_of_mines));
    }
    if(this->game.accomplished(ui->gridsize_selector->currentIndex())==true){
        ui->show_leaderboard_button->setEnabled(false);
        ui->pause_time_button->setEnabled(false);
        ui->start_game_button->setEnabled(false);
        ui->visibleGrid->setEnabled(false);
        ui->time->setText(QString::number(this->game.getPlayer().getTime()) + " ms");
        qDebug() << "Game accomplished.";
    }
}
