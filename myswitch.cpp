#include "myswitch.h"

MySwitch::MySwitch()
{
    QPixmap p(QDir::currentPath() + QDir::separator() + "switch-off.png");
    this->setPixmap(p);
    this->setFixedSize(QSize(p.width(),p.height()));
    //this->setScaledContents(true);
    this->status = false;
}

void MySwitch::mousePressEvent(QMouseEvent *event)
{
//    if(event->button() == Qt::LeftButton){
//        if(this->status==true){
//            this->status = false;
//            this->setPixmap(QDir::currentPath() + QDir::separator() + "switch-off.png");
//        }
//        else{
//            this->status = true;
//            this->setPixmap(QDir::currentPath() + QDir::separator() + "switch-on.png");
//        }
//    }

}
