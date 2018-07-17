#include "leaderboard.h"
#include "ui_leaderboard.h"

LeaderBoard::LeaderBoard(quint64 time_taken, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LeaderBoard)
{
    ui->setupUi(this);
    this->error = false;

    int columnCnt = 2;
    ui->leader_table->setColumnCount(columnCnt);
    if(!this->loadLeaderBoard(qApp->applicationDirPath() + "/" + DATA_FILE_PATH)){
        this->error = true;
    }

    ui->leader_table->setHorizontalHeaderLabels(QStringList() << "Username" << "Time");
    //columns width
    int factor_ratio = ui->leader_table->width()/10;
    ui->leader_table->setColumnWidth(0, factor_ratio*6);
    ui->leader_table->setColumnWidth(1, factor_ratio*2);
    ui->your_time->setText(QString::number(time_taken) + " ms");
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
    while(!txt.atEnd()){
        txt >> username >> msec;
        username.chop(1);
        this->leader_board.insert(msec,username);
    }
    qDebug() << "Removed: " << this->leader_board.remove(0,"");
    data_file.close();

    QMultiMap<quint64,QString>::const_iterator iterat = this->leader_board.constBegin();
    while (iterat != this->leader_board.constEnd()) {
        qDebug() << iterat.key() << iterat.value();
        ui->leader_table->insertRow(ui->leader_table->rowCount());
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 0, new QTableWidgetItem(iterat.value()));
        ui->leader_table->setItem(ui->leader_table->rowCount()-1, 1, new QTableWidgetItem(QString::number(iterat.key())));
        ++iterat;
    }
    return true;
}

void LeaderBoard::on_submit_result_button_clicked()
{

}
