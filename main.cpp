#include "game_gui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameGUI game_gui;
    game_gui.setWindowIcon(QIcon(QDir::currentPath() + QDir::separator() + "mine_icon.png"));
    game_gui.setWindowTitle("Minesweeper by Pavol Marak");
    game_gui.show();

    return a.exec();
}
