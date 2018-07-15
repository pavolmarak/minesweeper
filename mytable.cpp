#include "mytable.h"

MyTable::MyTable(QWidget *)
{
    this->mineCounter=0;
    this->noMineCounter=GRID_HEIGHT*GRID_WIDTH;
}

MyTable::~MyTable()
{

}

void MyTable::mousePressEvent(QMouseEvent *event)
{
    QTableWidgetItem * itClicked = this->itemAt(event->pos());
    if(event->button()==Qt::LeftButton){
        itClicked->setSelected(false);
        if(itClicked->whatsThis() == "noflag-nomine-novisit"){
           emit itemClicked(itClicked);
        }
        else if(itClicked->whatsThis() == "noflag-mine-novisit"){
            itClicked->setWhatsThis("noflag-mine-visit");
            emit itemClicked(itClicked);
        }

    }
    else if(event->button()==Qt::RightButton){
        if(itClicked->whatsThis() == "flag-nomine-novisit"){
            this->removeCellWidget(itClicked->row(),itClicked->column());
            itClicked->setWhatsThis("noflag-nomine-novisit");
        }
        else if(itClicked->whatsThis() == "flag-mine-novisit"){
            this->removeCellWidget(itClicked->row(),itClicked->column());
            itClicked->setWhatsThis("noflag-mine-novisit");
            this->mineCounter--;
        }
        else if(itClicked->whatsThis() == "noflag-nomine-novisit"){
            QLabel* wi;
            wi = new QLabel();
            wi->setPixmap(QPixmap(qApp->applicationDirPath() + "/flag.png"));
            wi->setScaledContents(true);
            this->setCellWidget(itClicked->row(),itClicked->column(),wi);
            itClicked->setWhatsThis("flag-nomine-novisit");
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
        }
    }
    qDebug() << "Nomines found: " << this->noMineCounter;
    qDebug() << "Mines found: " << this->mineCounter;
    if(this->mineCounter == this->noMineCounter){
        qDebug() << "You made it.";
        QMessageBox::about(this,"Congratulations", "You made it.");

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
    qDebug() << "Nomines found: " << this->noMineCounter;
    qDebug() << "Mines found: " << this->mineCounter;
    if(this->mineCounter == this->noMineCounter){
        qDebug() << "You made it.";
        QMessageBox::about(this,"Congratulations", "You made it.");
    }

}
