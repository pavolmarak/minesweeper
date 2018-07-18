#include "mines.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mines w;
    w.setWindowIcon(QIcon(qApp->applicationDirPath() + "/mine_icon.png"));
    w.setWindowTitle("Minesweeper by Pavol Marak");
    w.show();

    return a.exec();
}
