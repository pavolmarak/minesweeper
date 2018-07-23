#include "game_gui.h"
#include "ui_game_gui.h"

// constructor
GameGUI::GameGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameGUI)
{
    this->resized = false;

    ui->setupUi(this);

    // create box for defining a custom game grid
    this->addCustomizeGridControls(10,10,10);

    // reset gui
    this->resetGui();

    // set game switch
    this->switch_on_off = new MySwitch();
    this->switch_on_off->setObjectName("switch-off");
    //ui->horizontalLayout_9->insertWidget(2,this->switch_on_off);

    // set custom status bar message widget
    this->statusbar_message = new QLabel();
    this->statusbar_message->setObjectName("statusbar_message");
    ui->statusBar->addPermanentWidget(this->statusbar_message);

    // start game button setup
    ui->start_game_button->setEnabled(true);

    // *********** SIGNALS/SLOTS ***********
    QObject::connect(&(this->game.timer), SIGNAL(timeout()), this, SLOT(timeoutSlot()));
    QObject::connect(ui->visibleGrid, SIGNAL(rightClickSignal(QTableWidgetItem*)), this, SLOT(rightClickSlot(QTableWidgetItem*)));
    QObject::connect(ui->visibleGrid, SIGNAL(leftClickSignal(QTableWidgetItem*)), this, SLOT(leftClickSlot(QTableWidgetItem*)));
    QObject::connect(&(this->game.getLb()), SIGNAL(leaderboardClosedSignal()), this, SLOT(leaderboardClosedSlot()));
    QObject::connect(this->custom_grid_width_spinbox, SIGNAL(valueChanged(int)), this, SLOT(onCustomGridWidthSpinboxChanged(int)));
    QObject::connect(this->custom_grid_height_spinbox, SIGNAL(valueChanged(int)), this, SLOT(onCustomGridHeightSpinboxChanged(int)));

    qApp->processEvents();
}

// destructor
GameGUI::~GameGUI()
{
    delete ui;
}

void GameGUI::resetGui()
{
    ui->visibleGrid->setMinimumSize(QSize(this->game.difficulties[this->game.getCurrent_difficulty()].grid_width*TILE_SIZE,this->game.difficulties[this->game.getCurrent_difficulty()].grid_height*TILE_SIZE));
    ui->visibleGrid->resize(QSize(this->game.difficulties[this->game.getCurrent_difficulty()].grid_width*TILE_SIZE,this->game.difficulties[this->game.getCurrent_difficulty()].grid_height*TILE_SIZE));

    // reset leaderboard button
    ui->show_leaderboard_button->setEnabled(true);

    // reset visible grid
    ui->visibleGrid->clearContents();
    ui->visibleGrid->setEnabled(false);
    ui->visibleGrid->setVisible(true);
    ui->visibleGrid->setFocusPolicy(Qt::NoFocus);

    ui->visibleGrid->setRowCount(this->game.difficulties[this->game.getCurrent_difficulty()].grid_height);
    ui->visibleGrid->setColumnCount(this->game.difficulties[this->game.getCurrent_difficulty()].grid_width);

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
        }
    }
    ui->visibleGrid->setSelectionMode(QAbstractItemView::SingleSelection);

    // reset game info box
    ui->flag_counter->setText("0/" + QString::number(this->game.difficulties[this->game.getCurrent_difficulty()].number_of_mines));
    ui->pause_time_button->setEnabled(false);
    ui->pause_time_button->setChecked(false);
    ui->time->setText("0 ms");
    ui->time->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    ui->time->setStyleSheet("color:auto;");

    // reset game configuration box
    ui->gridsize_selector->setEnabled(true);
    ui->gridsize_selector->clear();
    foreach (Difficulty d, this->game.difficulties) {
        if(d.name == "Custom"){
            ui->gridsize_selector->addItem(d.name);
        }
        else{
            ui->gridsize_selector->addItem(d.name + ", " + QString::number(d.grid_height) + "x" + QString::number(d.grid_width) + ", " + QString::number(d.number_of_mines) + " mines");
        }
    }
    ui->gridsize_selector->setCurrentIndex(this->game.getCurrent_difficulty());

    // reset cell status
    ui->visibleGrid->setItClicked(nullptr);
    ui->visibleGrid->setItHover(nullptr);

    // initial start button focus
    ui->start_game_button->setFocus();
}

void GameGUI::addCustomizeGridControls(int width, int height, int mine_count)
{
    this->customizeGridBox = new QGroupBox("Make your own grid");
    QHBoxLayout* hl = new QHBoxLayout();
    hl->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hl->addWidget(new QLabel("Width:"));
    this->custom_grid_width_spinbox = new QSpinBox();
    custom_grid_width_spinbox->setMinimum(1);
    custom_grid_width_spinbox->setValue(width);
    hl->addWidget(custom_grid_width_spinbox);
    hl->addWidget(new QLabel("Height:"));
    this->custom_grid_height_spinbox = new QSpinBox();
    custom_grid_height_spinbox->setMinimum(1);
    custom_grid_height_spinbox->setValue(height);
    hl->addWidget(custom_grid_height_spinbox);
    hl->addWidget(new QLabel("Number of mines:"));
    this->custom_mine_count_spinbox = new QSpinBox();
    custom_mine_count_spinbox->setMinimum(0);
    custom_mine_count_spinbox->setMaximum(width*height);
    custom_mine_count_spinbox->setValue(mine_count);
    hl->addWidget(custom_mine_count_spinbox);
    hl->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    this->customizeGridBox->setLayout(hl);
    this->customizeGridBox->setVisible(false);
    ui->config_groupbox->layout()->addWidget(this->customizeGridBox);
}

void GameGUI::startGame()
{
    this->switch_on_off->setPixmap(QPixmap(QDir::currentPath() + QDir::separator() + "switch-on.png"));

    // apply the currently selected difficulty
    this->game.setCurrent_difficulty(ui->gridsize_selector->currentIndex());

    if(ui->gridsize_selector->currentText() == "Custom"){
        this->game.difficulties[this->game.getCurrent_difficulty()].grid_width = this->custom_grid_width_spinbox->value();
        this->game.difficulties[this->game.getCurrent_difficulty()].grid_height = this->custom_grid_height_spinbox->value();
        this->game.difficulties[this->game.getCurrent_difficulty()].number_of_mines = this->custom_mine_count_spinbox->value();
    }

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

void GameGUI::onCustomGridWidthSpinboxChanged(int v)
{
    this->custom_mine_count_spinbox->setMaximum(v*this->custom_grid_height_spinbox->value());
}

void GameGUI::onCustomGridHeightSpinboxChanged(int v)
{
    this->custom_mine_count_spinbox->setMaximum(v*this->custom_grid_width_spinbox->value());
}



// function to start the game
void GameGUI::on_start_game_button_clicked()
{
    this->startGame();
}


void GameGUI::on_pause_time_button_clicked(bool checked)
{
    Player p = this->game.getPlayer();
    if(checked){
        p.setTime(p.getTime() + this->game.elap_timer.elapsed());
        this->game.timer.stop();
        ui->visibleGrid->setVisible(false);
        ui->time->setStyleSheet("color:red;");
        ui->statusBar->showMessage("Game paused.");
    }
    else{
        ui->visibleGrid->setVisible(true);
        this->game.timer.start(TIMER_INTERVAL);
        this->game.elap_timer.restart();
        ui->time->setStyleSheet("color:auto;");
        ui->statusBar->showMessage("Game resumed.", 3000);
    }
    this->game.setPlayer(p);
}


void GameGUI::on_show_leaderboard_button_clicked()
{
    ui->show_leaderboard_button->setEnabled(false);
    this->game.showLeaderboard(false,ui->gridsize_selector->currentIndex());
}

void GameGUI::resizeEvent(QResizeEvent *event)
{
    QRect geometry =  ui->visibleGrid->geometry();
    if(geometry.width() != geometry.height()){
        geometry.setHeight(geometry.width());
    }
    ui->visibleGrid->setGeometry(geometry.x(), geometry.y(), geometry.width(), geometry.height());
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
        this->switch_on_off->setPixmap(QPixmap(QDir::currentPath() + QDir::separator() + "switch-off.png"));
        ui->pause_time_button->setEnabled(false);

        this->game.timer.stop();
        qDebug() << "*** MINE ***";
        for(int i=0; i<this->game.getInvisible_grid().length();i++) {
            for(int j=0; j<this->game.getInvisible_grid().at(i).length();j++) {
                if(this->game.getInvisible_grid().at(i).at(j).value == MINE){
                    QLabel* wi = new QLabel();
                    wi->setPixmap(QPixmap(QDir::currentPath() + QDir::separator() + "mine_icon.png"));
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
                switch(this->game.getInvisible_grid()[p.y()][p.x()].value){
                case 1:
                    ui->visibleGrid->item(p.y(), p.x())->setTextColor(QColor(0,0,180));
                    break;
                case 2:
                    ui->visibleGrid->item(p.y(), p.x())->setTextColor(QColor(0,100,0));
                    break;
                case 3:
                    ui->visibleGrid->item(p.y(), p.x())->setTextColor(QColor(148,20,96));
                    break;
                case 4:
                    ui->visibleGrid->item(p.y(), p.x())->setTextColor(QColor(200,60,180));
                    break;
                case 5:
                    ui->visibleGrid->item(p.y(), p.x())->setTextColor(QColor(174,85,100));
                    break;
                case 6:
                    ui->visibleGrid->item(p.y(), p.x())->setTextColor(QColor(201,157,14));
                    break;
                case 7:
                    ui->visibleGrid->item(p.y(), p.x())->setTextColor(QColor(150,100,50));
                    break;
                case 8:
                    ui->visibleGrid->item(p.y(), p.x())->setTextColor(QColor(50,100,150));
                    break;

                }
            }
            ui->visibleGrid->item(p.y(), p.x())->setSelected(false);
            this->game.unvisited_cellsDown();
        }
    }
    if(this->game.accomplished(ui->gridsize_selector->currentIndex())==true){
        this->switch_on_off->setPixmap(QPixmap(QDir::currentPath() + QDir::separator() + "switch-off.png"));
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
        wi->setPixmap(QPixmap(QDir::currentPath() + QDir::separator() + "flag.png"));
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
        this->switch_on_off->setPixmap(QPixmap(QDir::currentPath() + QDir::separator() + "switch-off.png"));
        ui->show_leaderboard_button->setEnabled(false);
        ui->pause_time_button->setEnabled(false);
        ui->start_game_button->setEnabled(false);
        ui->visibleGrid->setEnabled(false);
        ui->time->setText(QString::number(this->game.getPlayer().getTime()) + " ms");
        qDebug() << "Game accomplished.";
    }
}

void GameGUI::on_gridsize_selector_activated(int index)
{
    if(this->game.difficulties[index].name == "Custom"){
        this->customizeGridBox->setVisible(true);
    }
    else{
        this->customizeGridBox->setVisible(false);
    }
}

void GameGUI::on_stop_game_button_clicked()
{
    ui->statusBar->showMessage("This button is missing functionality at the moment.", 3000);
}
