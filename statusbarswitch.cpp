#include "statusbarswitch.h"

StatusBarSwitch::StatusBarSwitch()
{
    this->setPixmap(QDir::currentPath() + QDir::separator() + "switch-off.png");
    this->setScaledContents(true);
    this->status = false;
}

void StatusBarSwitch::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(this->status==true){
            this->status = false;
            this->setPixmap(QDir::currentPath() + QDir::separator() + "switch-off.png");
        }
        else{
            this->status = true;
            this->setPixmap(QDir::currentPath() + QDir::separator() + "switch-on.png");
        }
    }

}
