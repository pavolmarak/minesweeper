#include "mygrid.h"

MyGrid::MyGrid(QWidget *)
{
    this->itClicked=nullptr;
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

}

