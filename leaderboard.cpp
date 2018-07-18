#include "leaderboard.h"
#include "ui_leaderboard.h"

LeaderBoard::LeaderBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LeaderBoard)
{
    ui->setupUi(this);
}

void LeaderBoard::setup(const QString &path_to_file, const QVector<DIFFICULTY> difficulties)
{
    // general setup
    this->leader_board.clear();
    this->leader_board_file = "";

    // set leaderboard difficulties
    ui->leaderboard_selection_combobox->clear();
    foreach (DIFFICULTY d, difficulties) {
        ui->leaderboard_selection_combobox->addItem(d.name);
    }

    // set path to a text file containing leaderboard data
    this->leader_board_file = path_to_file;

    // set leaderboard
    ui->leader_table->clearContents();
    ui->leader_table->setColumnCount(COLUMN_COUNT);
    ui->leader_table->setHorizontalHeaderLabels(QStringList() << "Username" << "Time [ms]" << "Difficulty" << "Date");
    ui->leader_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->leader_table->horizontalHeader()->setStretchLastSection(true);
    ui->leader_table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->leader_table->verticalHeader()->setStretchLastSection(false);
    int factor_ratio = ui->leader_table->width()/40;
    ui->leader_table->setColumnWidth(0, factor_ratio*12);
    ui->leader_table->setColumnWidth(1, factor_ratio*8);
    ui->leader_table->setColumnWidth(2, factor_ratio*7);
    ui->leader_table->setColumnWidth(3, factor_ratio*9);

    // populate leaderboard from file
    if(!this->loadFromFile(this->leader_board_file)){
        exit(EXIT_FAILURE);
    }

    ui->leaderboard_result_box->setVisible(false);
}

LeaderBoard::~LeaderBoard()
{
    delete ui;
}

// function to load leaderboard data from file and display it
bool LeaderBoard::loadFromFile(const QString &path_to_file)
{
    this->leader_board.clear();
    ui->leader_table->clearContents();
    QFile data_file(path_to_file);
    data_file.open(QFile::ReadOnly);
    if(!data_file.isOpen()){
        qDebug() << "There was an error opening file with leaderboard data.";
        QMessageBox::about(this,"Error", "There was an error opening file with leaderboard data.");
        return false;
    }
    QTextStream txt(&data_file);
    txt.readLine(); // consume the first line in the text file
    UserResult usr_result;
    quint64 msec;

    // reading from file
    while(!txt.atEnd()){
        txt >> usr_result.name >> msec >> usr_result.diff >> usr_result.date;
        this->leader_board.insert(msec,usr_result);
    }
    this->leader_board.remove(0,{"","",""});
    data_file.close();

    QMultiMap<quint64,UserResult>::const_iterator iter = this->leader_board.constBegin();
    while (iter != this->leader_board.constEnd()) {
        ui->leader_table->insertRow(ui->leader_table->rowCount());
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 0, new QTableWidgetItem(iter.value().name));
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 1, new QTableWidgetItem(QString::number(iter.key())));
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 2, new QTableWidgetItem(iter.value().diff));
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 3, new QTableWidgetItem(iter.value().date));
        ++iter;
    }
    return true;
}

// function to redraw the leaderboard and highlight the last added row
void LeaderBoard::redraw()
{
    // clear the previous contents
    ui->leader_table->clearContents();

    // hint
    QString hint = "-highlight";

    QMultiMap<quint64,UserResult>::iterator iter = this->leader_board.begin();
    while (iter != this->leader_board.end()) {
        ui->leader_table->insertRow(ui->leader_table->rowCount());
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 0, new QTableWidgetItem(iter.value().name));
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 1, new QTableWidgetItem(QString::number(iter.key())));
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 2, new QTableWidgetItem(iter.value().diff));
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
}

void LeaderBoard::setTimeTaken(quint64 time_taken)
{
    ui->your_time->setText(QString::number(time_taken) + " ms");
}



void LeaderBoard::setSubmitBtnEnabled(bool value)
{
    ui->submit_result_button->setEnabled(value);
}

void LeaderBoard::setLeaderboardTypes(QVector<QString> ltypes)
{
    foreach (QString s, ltypes) {
        ui->leaderboard_selection_combobox->addItem(s);
    }
}

void LeaderBoard::setResultboxVisible(bool value)
{
    ui->leaderboard_result_box->setVisible(value);
}


void LeaderBoard::on_submit_result_button_clicked()
{
    if(ui->username->text().isEmpty()){
        ui->statusbar->showMessage("Please enter your name.",5000);
        return;
    }
    if(ui->username->text().contains(" ")){
        ui->statusbar->showMessage("White characters are not allowed.",5000);
        return;
    }
    this->leader_board.insert(ui->your_time->text().chopped(3).toULongLong(),{ui->username->text()+"-highlight","Easy","1.1.1999"});
    this->redraw();

    QFile data_file(this->leader_board_file);
    data_file.open(QFile::WriteOnly);
    if(!data_file.isOpen()){
        qDebug() << "There was an error opening file with leaderboard data.";
        QMessageBox::about(this,"Bad news", "There was an error opening file with leaderboard data.");
        return;
    }
    QTextStream txt(&data_file);
    txt << "# DO NOT MODIFY THIS FILE !!!\n\n";
    QMultiMap<quint64,UserResult>::const_iterator iterat = this->leader_board.constBegin();
    while (iterat != this->leader_board.constEnd()) {
        txt << iterat.value().name << " " << iterat.key() << " " << iterat.value().diff << " " << iterat.value().date << "\n";
        ++iterat;
    }
    data_file.close();
    ui->submit_result_button->setEnabled(false);
    ui->statusbar->showMessage("Your result has been recorded.");

}

void LeaderBoard::closeEvent(QCloseEvent *event)
{
    event->accept();
    this->redraw();
    ui->username->setText("");
    ui->statusbar->showMessage("");
    emit leaderboardClosedSignal();
}


