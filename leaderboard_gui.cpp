#include "leaderboard_gui.h"
#include "ui_leaderboard_gui.h"

LeaderBoardGUI::LeaderBoardGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LeaderBoardGUI)
{
    ui->setupUi(this);

    this->setWindowTitle("Leaderboard");
    this->setWindowIcon(QIcon(QDir::currentPath() + QDir::separator() + LEADERBOARD_ICON_FILE));

    // reset GUI
    this->resetGui();

    // create leaderboard
    this->lb = LeaderBoard(QDir::currentPath() + QDir::separator() + LEADERBOARD_FILE);
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
    ui->leader_table->horizontalHeader()->setStyleSheet("font-weight:bold;");
    ui->leader_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->leader_table->horizontalHeader()->setStretchLastSection(true);
    ui->leader_table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->leader_table->verticalHeader()->setStretchLastSection(false);

    // reset user result box
    ui->leaderboard_result_box->setVisible(false);

    // reset status bar
    ui->statusbar->clearMessage();
}

void LeaderBoardGUI::setLeaderboardTypes(QVector<Difficulty> difficulties)
{
    ui->leaderboard_selection_combobox->clear();
    foreach (Difficulty d, difficulties) {
        if(d.name == "Custom"){
            ui->leaderboard_selection_combobox->addItem(d.name);
        }
        else{
            ui->leaderboard_selection_combobox->addItem(d.name + ", " + QString::number(d.grid_height) + "x" + QString::number(d.grid_width) + ", " + QString::number(d.number_of_mines) + " mines");
        }
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

void LeaderBoardGUI::redrawLeaderboard(int row_index)
{
    this->resetGui();

    // hint for newly added time
    QString hint_new = "-highlight";
    // hint for ready-to-insert time
    QString hint_ready = "-ready";

    QMultiMap<quint64,UserResult>::iterator iter = this->lb.getLeader_board().begin();
    while (iter != this->lb.getLeader_board().end()) {
        if(iter.value().difficulty != ui->leaderboard_selection_combobox->currentText().split(",").at(0)){
            ++iter;
            continue;
        }
        if(iter.value().name.endsWith(hint_ready)){
            ui->leader_table->insertRow(ui->leader_table->rowCount());
            ui->leader_table->setItem(ui->leader_table->rowCount()-1, 0, new QTableWidgetItem("Your result"));
            ui->leader_table->setItem(ui->leader_table->rowCount()-1, 1, new QTableWidgetItem(QString::number(iter.key())));
            ui->leader_table->setItem(ui->leader_table->rowCount()-1, 2, new QTableWidgetItem(iter.value().difficulty));
            ui->leader_table->setItem(ui->leader_table->rowCount()-1, 3, new QTableWidgetItem(iter.value().date));
            ui->leader_table->item(ui->leader_table->rowCount()-1,0)->setWhatsThis("to-remove");
            ui->leader_table->item(ui->leader_table->rowCount()-1,0)->setBackgroundColor(QColor(255, 180, 180));
            ui->leader_table->item(ui->leader_table->rowCount()-1,1)->setBackgroundColor(QColor(255, 180, 180));
            ui->leader_table->item(ui->leader_table->rowCount()-1,2)->setBackgroundColor(QColor(255, 180, 180));
            ui->leader_table->item(ui->leader_table->rowCount()-1,3)->setBackgroundColor(QColor(255, 180, 180));
            ++iter;
            continue;
        }

        ui->leader_table->insertRow(ui->leader_table->rowCount());
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 0, new QTableWidgetItem(iter.value().name));
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 1, new QTableWidgetItem(QString::number(iter.key())));
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 2, new QTableWidgetItem(iter.value().difficulty));
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 3, new QTableWidgetItem(iter.value().date));
        if(iter.value().name.endsWith(hint_new)){
            iter.value().name = iter.value().name.chopped(hint_new.length()); // remove the hint
            ui->leader_table->item(ui->leader_table->rowCount()-1,0)->setText(iter.value().name);
            ui->leader_table->item(ui->leader_table->rowCount()-1,0)->setBackgroundColor(QColor(0, 204, 102));
            ui->leader_table->item(ui->leader_table->rowCount()-1,1)->setBackgroundColor(QColor(0, 204, 102));
            ui->leader_table->item(ui->leader_table->rowCount()-1,2)->setBackgroundColor(QColor(0, 204, 102));
            ui->leader_table->item(ui->leader_table->rowCount()-1,3)->setBackgroundColor(QColor(0, 204, 102));
        }
        ++iter;
    }

    // scroll to currently added item
    if(row_index == -1){
        ui->leader_table->scrollToTop();
    }else{
        ui->leader_table->scrollToItem(ui->leader_table->item(row_index,0),QAbstractItemView::PositionAtCenter);
    }

    qApp->processEvents();
}

void LeaderBoardGUI::setCurrentDifficulty(int index)
{
    ui->leaderboard_selection_combobox->setCurrentIndex(index);
}

void LeaderBoardGUI::highlightRow(int index, QColor background_color, QColor text_color)
{
    // TODO
}

QMultiMap<quint64, UserResult>::iterator LeaderBoardGUI::addToLeaderboard(quint64 key, UserResult value)
{
    // insert new result to the leaderboard map
    return this->lb.getLeader_board().insert(key, value);
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

    for(int i=0; i < ui->leader_table->rowCount();i++){
        for(int j=0; j < ui->leader_table->columnCount(); j++ ){
            if(ui->leader_table->item(i,j)->whatsThis() == "to-remove"){
                ui->leader_table->item(i,j)->setWhatsThis("");
                QMultiMap<quint64,UserResult>::iterator iter = this->lb.getLeader_board().begin();
                while (iter != this->lb.getLeader_board().end()) {
                    if(iter.value().name == "_?_result-ready"){
                        iter.value().name = ui->username->text() + "-highlight";
                        break;
                    }
                    ++iter;
                }
                this->redrawLeaderboard(ui->leader_table->item(i,j)->row());
            }
        }
    }

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
    QMultiMap<quint64,UserResult>::iterator iter = this->lb.getLeader_board().begin();
    while (iter != this->lb.getLeader_board().end()) {
        if(iter.value().name == "_?_result-ready"){
            this->lb.getLeader_board().erase(iter);
            break;
        }
        ++iter;
    }
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
    this->redrawLeaderboard();
    ui->leaderboard_result_box->setVisible(true);
}

LeaderBoard &LeaderBoardGUI::getLb()
{
    return lb;
}

void LeaderBoardGUI::setLb(const LeaderBoard &value)
{
    lb = value;
}
