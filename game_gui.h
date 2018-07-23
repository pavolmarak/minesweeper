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
#include <QResizeEvent>
#include <QGroupBox>
#include <QSpacerItem>

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
    void addCustomizeGridControls(int width, int height, int mine_count);

private slots:
    void on_start_game_button_clicked();
    void on_pause_time_button_clicked(bool checked);
    void on_show_leaderboard_button_clicked();
    void resizeEvent(QResizeEvent* event);

    void on_gridsize_selector_activated(int index);

    void on_stop_game_button_clicked();

public slots:
    void timeoutSlot();
    void rightClickSlot(QTableWidgetItem *item);
    void leftClickSlot(QTableWidgetItem *item);
    void leaderboardClosedSlot();
    void startGame();
    void onCustomGridWidthSpinboxChanged(int v);
    void onCustomGridHeightSpinboxChanged(int v);

private:
    Ui::GameGUI *ui;
    Game game;
    QLabel* statusbar_message;
    MySwitch* switch_on_off;
    bool resized;
    QGroupBox* customizeGridBox;
    QSpinBox* custom_grid_width_spinbox;
    QSpinBox* custom_grid_height_spinbox;
    QSpinBox* custom_mine_count_spinbox;

};

#endif // GAME_GUI_H
