#ifndef GAME_GUI_H
#define GAME_GUI_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <QPoint>
#include <QDebug>
#include <QSet>
#include <QMouseEvent>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QTimer>
#include <QComboBox>
#include <QSpinBox>
#include <QDialog>
#include <QHeaderView>

#include "game.h"
#include "myswitch.h"

namespace Ui {
class GameGUI;
}

class GameGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameGUI(QWidget *parent = 0);
    ~GameGUI();
    void resetGui();

private slots:
    void on_start_game_button_clicked();
    void on_pause_time_button_clicked(bool checked);
    void on_show_leaderboard_button_clicked();
    void on_noMinesSpinBox_valueChanged(int arg1);

public slots:
    void timeoutSlot();
    void rightClickSlot(QTableWidgetItem *item);
    void leftClickSlot(QTableWidgetItem *item);
    void leaderboardClosedSlot();

private:
    Ui::GameGUI *ui;
    Game game;
    QLabel* statusbar_message;
    MySwitch* switch_on_off;

};

#endif // GAME_GUI_H
