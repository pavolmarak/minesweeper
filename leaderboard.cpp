#include "leaderboard.h"
#include "ui_leaderboard.h"

LeaderBoard::LeaderBoard(quint64 time_taken, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LeaderBoard)
{
    ui->setupUi(this);
    int columnCnt = 2;
    ui->leader_table->setColumnCount(columnCnt);
    ui->leader_table->setHorizontalHeaderLabels(QStringList() << "Username" << "Time");
    //columns width
    qDebug() << ui->leader_table->width();
    ui->leader_table->setColumnWidth(0, ui->leader_table->width()/columnCnt);
    ui->leader_table->setColumnWidth(1, ui->leader_table->width()/columnCnt);

    ui->your_time->setText(QString::number(time_taken) + " ms");

}

LeaderBoard::~LeaderBoard()
{
    delete ui;
}

void LeaderBoard::on_submit_result_button_clicked()
{

}
