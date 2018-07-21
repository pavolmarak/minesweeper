#include "mygrid.h"

MyGrid::MyGrid(QWidget *)
{
    this->itClicked = nullptr;
    this->itHover = nullptr;
}

MyGrid::~MyGrid()
{

}

void MyGrid::mousePressEvent(QMouseEvent *event)
{
    this->itClicked = this->itemAt(event->pos().x(),event->pos().y());
    if(event->button() == Qt::LeftButton){
        emit leftClickSignal(this->itClicked);
    }
    else if(event->button() == Qt::RightButton){
        emit rightClickSignal(this->itClicked);
    }
    else{
        qDebug() << "Button not registered.";
    }
}
void MyGrid::mouseReleaseEvent(QMouseEvent *event)
{

}

void MyGrid::mouseMoveEvent(QMouseEvent *event)
{
    if(this->itHover){
        if(this->itemAt(event->pos()) != this->itHover && this->itHover->backgroundColor() == QColor(100,100,100)){
            this->itHover->setBackgroundColor(QColor(150,150,150));
        }
    }
    this->itHover = this->itemAt(event->pos());

    if(this->itHover){
        if(this->itHover->backgroundColor() == QColor(150,150,150)){
            this->itHover->setBackgroundColor(QColor(100,100,100));
        }
    }


}

QTableWidgetItem *MyGrid::getItHover() const
{
    return itHover;
}

void MyGrid::setItHover(QTableWidgetItem *value)
{
    itHover = value;
}

QTableWidgetItem *MyGrid::getItClicked() const
{
    return itClicked;
}

void MyGrid::setItClicked(QTableWidgetItem *value)
{
    itClicked = value;
}

