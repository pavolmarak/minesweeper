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
    ui->visibleGrid->setEnabled(true);
    ui->visibleGrid->setVisible(true);

    ui->visibleGrid->setRowCount(this->game.difficulties[this->game.getCurrent_difficulty()].grid_height);
    ui->visibleGrid->setColumnCount(this->game.difficulties[this->game.getCurrent_difficulty()].grid_width);
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
    foreach (Difficulty d, this->game.difficulties) {
        ui->gridsize_selector->addItem(d.name);
    }
    ui->gridsize_selector->setCurrentIndex(this->game.getCurrent_difficulty());

    // set the number of mines for the given game difficulty
    ui->noMinesSpinBox->setValue(this->game.difficulties[this->game.getCurrent_difficulty()].number_of_mines);
    if(this->game.difficulties[this->game.getCurrent_difficulty()].name != "Custom"){
        ui->noMinesSpinBox->setEnabled(false);
    }
}

// function to handle user left-clicks
void GameGUI::on_visibleGrid_itemClicked(QTableWidgetItem *item)
{
    ClickResult result = this->game.userLeftClick(item->row(),item->column());
    // if user left-clicked on a mine
    if(result.is_mine == true){
        ui->pause_time_button->setEnabled(false);
        ui->visibleGrid->setEnabled(false);
        qDebug() << "*** MINE ***";
        QLabel* wi = new QLabel();
        wi->setPixmap(QPixmap(qApp->applicationDirPath() + "/mine_icon.png"));
        wi->setScaledContents(true);
        ui->visibleGrid->item(item->row(),item->column())->setBackgroundColor(QColor(220,220,220));
        ui->visibleGrid->setCellWidget(item->row(),item->column(),wi);
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
                ui->visibleGrid->item(p.y(), p.x())->setText(QString::number(this->game.getInvisible_grid()[p.y()][p.x()].value));
            }
            ui->visibleGrid->item(p.y(), p.x())->setSelected(false);
        }
    }
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

    // populate invisible grid
    this->game.placeMines(this->game.difficulties[this->game.getCurrent_difficulty()].number_of_mines);

    // reset gui
    this->resetGui();

    // reset player
    Player p = this->game.getPlayer();
    p.setFlag_counter(0);
    p.setTime(0);
    this->game.setPlayer(p);

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

}


void GameGUI::on_noMinesSpinBox_valueChanged(int arg1)
{

}

