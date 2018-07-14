#include "mytable.h"

MyTable::MyTable(QWidget *)
{

}

void MyTable::mousePressEvent(QMouseEvent *e)
{
    QTableWidgetItem * itClicked = this->itemAt(e->pos());
    if(e->button()==Qt::LeftButton){
        if(itClicked->whatsThis() == "false"){
           emit itemClicked(itClicked);
        }

    }
    else if(e->button()==Qt::RightButton){
        if(itClicked->whatsThis() == "true"){
            this->removeCellWidget(itClicked->row(),itClicked->column());
            itClicked->setWhatsThis("false");
        }
        else{
            QLabel* wi;
            wi = new QLabel();
            wi->setPixmap(QPixmap(qApp->applicationDirPath() + "/flag.png"));
            wi->setScaledContents(true);
            this->setCellWidget(itClicked->row(),itClicked->column(),wi);
            itClicked->setWhatsThis("true");
        }
    }

}
