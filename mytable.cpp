#include "mytable.h"

MyTable::MyTable(QWidget *)
{
    this->mineCounter=0;
    this->noMineCounter=GRID_HEIGHT*GRID_WIDTH;
    this->congratsShown=false;
}

MyTable::~MyTable()
{

}

void MyTable::leaderboardDialog()
{
    QMessageBox::about(this,"Congratulations" ,"You won.");
}

void MyTable::mousePressEvent(QMouseEvent *event)
{
    QTableWidgetItem * itClicked = this->itemAt(event->pos());
    itClicked->setSelected(false);
    if(event->button()==Qt::LeftButton){
        if(itClicked->whatsThis() == "noflag-nomine-novisit"){
            emit itemClicked(itClicked);
        }
        else if(itClicked->whatsThis() == "noflag-mine-novisit"){
            this->timer.stop();
            itClicked->setWhatsThis("noflag-mine-visit");
            emit itemClicked(itClicked);
        }

    }
    else if(event->button()==Qt::RightButton){
        if(itClicked->whatsThis() == "flag-nomine-novisit"){
            this->removeCellWidget(itClicked->row(),itClicked->column());
            itClicked->setWhatsThis("noflag-nomine-novisit");
            emit flagCounterDecreased();
        }
        else if(itClicked->whatsThis() == "flag-mine-novisit"){
            this->removeCellWidget(itClicked->row(),itClicked->column());
            itClicked->setWhatsThis("noflag-mine-novisit");
            this->mineCounter--;
            emit flagCounterDecreased();
        }
        else if(itClicked->whatsThis() == "noflag-nomine-novisit"){
            QLabel* wi;
            wi = new QLabel();
            wi->setPixmap(QPixmap(qApp->applicationDirPath() + "/flag.png"));
            wi->setScaledContents(true);
            this->setCellWidget(itClicked->row(),itClicked->column(),wi);
            itClicked->setWhatsThis("flag-nomine-novisit");
            emit flagCounterIncreased();
        }
        // user detected a mine in the field
        else if(itClicked->whatsThis() == "noflag-mine-novisit"){
            QLabel* wi;
            wi = new QLabel();
            wi->setPixmap(QPixmap(qApp->applicationDirPath() + "/flag.png"));
            wi->setScaledContents(true);
            this->setCellWidget(itClicked->row(),itClicked->column(),wi);
            itClicked->setWhatsThis("flag-mine-novisit");
            this->mineCounter++;
            emit flagCounterIncreased();
        }
    }
    if(this->mineCounter == this->noMineCounter && this->congratsShown==false){
        this->timer.stop();
        qDebug() << "Congratulations, you made it.";
        this->congratsShown = true;
        this->setEnabled(false);
        this->leaderboardDialog();
    }
}

void MyTable::mouseMoveEvent(QMouseEvent *event)
{
    QTableWidgetItem * itClicked = this->itemAt(event->pos());
    itClicked->setSelected(false);
}

void MyTable::mouseReleaseEvent(QMouseEvent *event)
{
    QTableWidgetItem * itClicked = this->itemAt(event->pos());
    itClicked->setSelected(false);
}

void MyTable::cellsRevealedAutomaticallySlot(int number)
{
    this->noMineCounter-=number;
    if(this->mineCounter == this->noMineCounter && this->congratsShown==false){
        this->timer.stop();
        qDebug() << "Congratulations, you made it.";
        this->congratsShown = true;
        this->setEnabled(false);
        this->leaderboardDialog();
    }
}
