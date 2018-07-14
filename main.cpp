#include "mines.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mines w;
    w.setWindowIcon(QIcon("icon.png"));
    w.setWindowTitle("Mines by Pavol Marak");
    w.show();

    return a.exec();
}
