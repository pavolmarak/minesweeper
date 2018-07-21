#include "leaderboard_gui.h"
#include "ui_leaderboard_gui.h"

LeaderBoardGUI::LeaderBoardGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LeaderBoardGUI)
{
    ui->setupUi(this);

    this->setWindowTitle("Leaderboard");
    this->setWindowIcon(QIcon(qApp->applicationDirPath() + "/" + LEADERBOARD_ICON_FILE));

    // reset GUI
    this->resetGui();

    // create leaderboard
    this->lb = LeaderBoard(qApp->applicationDirPath() + "/" + LEADERBOARD_FILE);
}


LeaderBoardGUI::~LeaderBoardGUI()
{
    delete ui;
}

void LeaderBoardGUI::resetGui()
{
    // reset difficulty selection combobox
    ui->leaderboard_selection_combobox->setEnabled(true);

    // reset leaderboard table
    ui->leader_table->clearContents();
    ui->leader_table->setEnabled(true);
    ui->leader_table->setVisible(true);
    ui->leader_table->setFocusPolicy(Qt::NoFocus);

    ui->leader_table->setRowCount(0);
    ui->leader_table->setColumnCount(LEADERBOARD_COLUMN_COUNT);
    ui->leader_table->setHorizontalHeaderLabels(QStringList() << "Username" << "Time [ms]" << "Difficulty" << "Date");
    ui->leader_table->verticalHeader()->show();
    ui->leader_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->leader_table->horizontalHeader()->setStretchLastSection(true);
    ui->leader_table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->leader_table->verticalHeader()->setStretchLastSection(false);

    int factor_ratio = ui->leader_table->width()/40;
    int factors[] = {factor_ratio*12, factor_ratio*8, factor_ratio*7, factor_ratio*9};
    for(int i=0; i< ui->leader_table->columnCount();i++){
        ui->leader_table->setColumnWidth(i, factors[i]);
    }

    // reset user result box
    ui->leaderboard_result_box->setVisible(false);

    // reset status bar
    ui->statusbar->clearMessage();
}

void LeaderBoardGUI::setLeaderboardTypes(QVector<Difficulty> difficulties)
{
    ui->leaderboard_selection_combobox->clear();
    foreach (Difficulty d, difficulties) {
        ui->leaderboard_selection_combobox->addItem(d.name + ", " + QString::number(d.grid_height) + "x" + QString::number(d.grid_width) + ", " + QString::number(d.number_of_mines) + " mines");
    }
}

void LeaderBoardGUI::showUserResultBox(bool on_off, quint64 time)
{
    this->last_time = time;
    ui->leaderboard_result_box->setVisible(on_off);
    ui->submit_result_button->setEnabled(on_off);
    ui->username->clear();
    ui->your_time->setText(QString::number(this->last_time) + " ms");
}

void LeaderBoardGUI::redrawLeaderboard()
{
    this->resetGui();

    // hint
    QString hint = "-highlight";
    QMultiMap<quint64,UserResult>::iterator iter = this->lb.getLeader_board().begin();
    while (iter != this->lb.getLeader_board().end()) {
        if(iter.value().difficulty != ui->leaderboard_selection_combobox->currentText().split(",").at(0)){
            ++iter;
            continue;
        }
        ui->leader_table->insertRow(ui->leader_table->rowCount());
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 0, new QTableWidgetItem(iter.value().name));
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 1, new QTableWidgetItem(QString::number(iter.key())));
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 2, new QTableWidgetItem(iter.value().difficulty));
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 3, new QTableWidgetItem(iter.value().date));
        if(iter.value().name.endsWith(hint)){
            iter.value().name = iter.value().name.chopped(hint.length()); // remove the hint
            ui->leader_table->item(ui->leader_table->rowCount()-1,0)->setText(iter.value().name);
            ui->leader_table->item(ui->leader_table->rowCount()-1,0)->setBackgroundColor(QColor(0, 204, 102));
            ui->leader_table->item(ui->leader_table->rowCount()-1,1)->setBackgroundColor(QColor(0, 204, 102));
            ui->leader_table->item(ui->leader_table->rowCount()-1,2)->setBackgroundColor(QColor(0, 204, 102));
            ui->leader_table->item(ui->leader_table->rowCount()-1,3)->setBackgroundColor(QColor(0, 204, 102));
        }
        ++iter;
    }
    ui->leader_table->scrollToTop();
    qApp->processEvents();
}

void LeaderBoardGUI::setCurrentDifficulty(int index)
{
    ui->leaderboard_selection_combobox->setCurrentIndex(index);
}

void LeaderBoardGUI::on_submit_result_button_clicked()
{
    // check if user provided non-empty username
    if(ui->username->text().isEmpty()){
        ui->statusbar->showMessage("Please enter your name.",5000);
        return;
    }
    // check if username contains white characters
    if(ui->username->text().contains(" ")){
        ui->statusbar->showMessage("White characters are not allowed.",5000);
        return;
    }

    // insert new result to the leaderboard map
    QMultiMap<quint64, UserResult>::iterator iter = this->lb.getLeader_board().insert(
                this->last_time,
                {
                    ui->username->text()+"-highlight",
                    ui->leaderboard_selection_combobox->currentText().split(",").at(0),
                    QDateTime::currentDateTime().toString("d.M.yyyy")
                });
    this->redrawLeaderboard();

    // scroll to currently added item
    //    qDebug() << "Scroll to: " << std::distance(this->lb.getLeader_board().begin(),iter);
    //    qDebug() << ui->leader_table->item(std::distance(this->lb.getLeader_board().begin(),iter),0)->text();
    ui->leader_table->scrollToItem(ui->leader_table->item(std::distance(this->lb.getLeader_board().begin(),iter),0),QAbstractItemView::PositionAtCenter);

    ui->leaderboard_result_box->setVisible(true);

    // write main leaderboard data
    QFile data_file(this->lb.getLeader_board_file());
    data_file.open(QFile::WriteOnly);
    if(!data_file.isOpen()){
        qDebug() << "There was an error opening file with leaderboard data.";
        QMessageBox::about(nullptr,"Error", "There was an error opening file with leaderboard data.");
        return;
    }
    QTextStream txt(&data_file);
    txt << "# DO NOT MODIFY THIS FILE !!!\n\n";
    QMultiMap<quint64,UserResult>::const_iterator iterat = this->lb.getLeader_board().constBegin();
    while (iterat != this->lb.getLeader_board().constEnd()) {
        txt << iterat.value().name << " " << iterat.key() << " " << iterat.value().difficulty << " " << iterat.value().date << "\n";
        ++iterat;
    }
    data_file.close();

    // write backup leaderboard data
    QFile data_file_backup(this->lb.getLeader_board_file().chopped(4)+"_backup.txt");
    data_file_backup.open(QIODevice::ReadWrite|QIODevice::Text);
    if(!data_file_backup.isOpen()){
        qDebug() << "There was an error opening file with leaderboard data.";
        QMessageBox::about(nullptr,"Error", "There was an error opening file with leaderboard data.");
        return;
    }
    QTextStream txt_backup(&data_file_backup);
    txt_backup << "# DO NOT MODIFY THIS FILE !!!\n\n";
    iterat = this->lb.getLeader_board().constBegin();
    while (iterat != this->lb.getLeader_board().constEnd()) {
        txt_backup << iterat.value().name << " " << iterat.key() << " " << iterat.value().difficulty << " " << iterat.value().date << "\n";
        ++iterat;
    }
    data_file_backup.close();

    ui->submit_result_button->setEnabled(false);
    ui->statusbar->showMessage("Your result has been recorded.");

}

void LeaderBoardGUI::closeEvent(QCloseEvent *event)
{
    event->accept();
    //    this->redraw();
    emit leaderboardClosedSignal();
}

quint64 LeaderBoardGUI::getLast_time() const
{
    return last_time;
}

void LeaderBoardGUI::setLast_time(const quint64 &value)
{
    last_time = value;
}

void LeaderBoardGUI::on_leaderboard_selection_combobox_activated(int index)
{

}
