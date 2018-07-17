#include "leaderboard.h"
#include "ui_leaderboard.h"

LeaderBoard::LeaderBoard(const QString &path_to_file, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LeaderBoard)
{
    ui->setupUi(this);
    this->leader_board_file = path_to_file;
    this->error = false;
    this->difficulty = "10x10, 10 mines";

    int columnCnt = 3;
    ui->leader_table->setColumnCount(columnCnt);
    if(!this->loadLeaderBoard(this->leader_board_file)){
        this->error = true;
    }

    ui->leader_table->setHorizontalHeaderLabels(QStringList() << "Username" << "Time [ms]" << "Difficulty");
    //columns width
    int factor_ratio = ui->leader_table->width()/10;
    ui->leader_table->setColumnWidth(0, factor_ratio*4);
    ui->leader_table->setColumnWidth(1, factor_ratio*2);
    ui->leader_table->setColumnWidth(2, factor_ratio*2);
}

LeaderBoard::~LeaderBoard()
{
    delete ui;
}

bool LeaderBoard::loadLeaderBoard(const QString &path_to_file)
{
    this->leader_board.clear();
    QFile data_file(path_to_file);
    data_file.open(QFile::ReadOnly);
    if(!data_file.isOpen()){
        qDebug() << "You won, but ... there was an error opening file with leaderboard data.";
        QMessageBox::about(this,"Good news, bad news", "You won, but ... there was an error opening file with leaderboard data.");
        return false;
    }
    QTextStream txt(&data_file);
    QString username;
    quint64 msec;
    txt.readLine();
    User usr;
    while(!txt.atEnd()){
        txt >> usr.name >> msec >> usr.difficulty;
        username.chop(1);
        this->leader_board.insert(msec,usr);
    }
    this->leader_board.remove(0,{"",""});
    data_file.close();

    QMultiMap<quint64,User>::const_iterator iterat = this->leader_board.constBegin();
    while (iterat != this->leader_board.constEnd()) {
        //qDebug() << iterat.key() << iterat.value();
        ui->leader_table->insertRow(ui->leader_table->rowCount());
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 0, new QTableWidgetItem(iterat.value().name));
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 1, new QTableWidgetItem(QString::number(iterat.key())));
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 2, new QTableWidgetItem(iterat.value().difficulty));
        ++iterat;
    }
    return true;
}

void LeaderBoard::redraw()
{
    while(ui->leader_table->rowCount()>0){
       ui->leader_table->removeRow(0);
    }

    QMultiMap<quint64,User>::iterator iterat = this->leader_board.begin();
    while (iterat != this->leader_board.end()) {
        ui->leader_table->insertRow(ui->leader_table->rowCount());
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 0, new QTableWidgetItem(iterat.value().name));
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 1, new QTableWidgetItem(QString::number(iterat.key())));
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 2, new QTableWidgetItem(iterat.value().difficulty));
        if(iterat.value().name.endsWith("-highlight")){
            iterat.value().name = iterat.value().name.chopped(10);
            ui->leader_table->item(ui->leader_table->rowCount()-1,0)->setText(iterat.value().name);
            ui->leader_table->item(ui->leader_table->rowCount()-1,0)->setBackgroundColor(QColor(0, 204, 102));
            ui->leader_table->item(ui->leader_table->rowCount()-1,1)->setBackgroundColor(QColor(0, 204, 102));
            ui->leader_table->item(ui->leader_table->rowCount()-1,2)->setBackgroundColor(QColor(0, 204, 102));

        }

        ++iterat;
    }
}

void LeaderBoard::setTimeTaken(quint64 time_taken)
{
    ui->your_time->setText(QString::number(time_taken) + " ms");
}

void LeaderBoard::setDifficulty(const QString &difficulty)
{
    this->difficulty = difficulty;
}

void LeaderBoard::setSubmitBtnEnabled()
{
    ui->submit_result_button->setEnabled(true);
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
    this->leader_board.insert(ui->your_time->text().chopped(3).toULongLong(),{ui->username->text()+"-highlight",this->difficulty});
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
    QMultiMap<quint64,User>::const_iterator iterat = this->leader_board.constBegin();
    while (iterat != this->leader_board.constEnd()) {
        txt << iterat.value().name << " " << iterat.key() << " " << iterat.value().difficulty << "\n";
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
}


