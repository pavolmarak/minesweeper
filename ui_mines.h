/********************************************************************************
** Form generated from reading UI file 'mines.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINES_H
#define UI_MINES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mytable.h"

QT_BEGIN_NAMESPACE

class Ui_Mines
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *show_leaderboard_button;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer;
    MyTable *visibleGrid;
    QGroupBox *gameinfo_groupbox;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *flagcounter_label;
    QLabel *flag_counter;
    QFrame *line;
    QPushButton *pause_time_button;
    QLabel *time_label;
    QLabel *time;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *config_groupbox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label;
    QComboBox *gridsize_selector;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *no_mines_label;
    QSpinBox *noMinesSpinBox;
    QPushButton *start_game_button;
    QSpacerItem *horizontalSpacer_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Mines)
    {
        if (Mines->objectName().isEmpty())
            Mines->setObjectName(QStringLiteral("Mines"));
        Mines->resize(514, 821);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Mines->sizePolicy().hasHeightForWidth());
        Mines->setSizePolicy(sizePolicy);
        Mines->setMinimumSize(QSize(514, 0));
        Mines->setMaximumSize(QSize(514, 821));
        centralWidget = new QWidget(Mines);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        show_leaderboard_button = new QPushButton(centralWidget);
        show_leaderboard_button->setObjectName(QStringLiteral("show_leaderboard_button"));

        horizontalLayout_5->addWidget(show_leaderboard_button);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        visibleGrid = new MyTable(centralWidget);
        visibleGrid->setObjectName(QStringLiteral("visibleGrid"));
        visibleGrid->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(visibleGrid->sizePolicy().hasHeightForWidth());
        visibleGrid->setSizePolicy(sizePolicy1);
        visibleGrid->setMinimumSize(QSize(500, 500));
        visibleGrid->setMaximumSize(QSize(500, 500));
        visibleGrid->setMouseTracking(true);
        visibleGrid->setTabletTracking(true);
        visibleGrid->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        visibleGrid->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        visibleGrid->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        visibleGrid->setSelectionMode(QAbstractItemView::SingleSelection);
        visibleGrid->setSelectionBehavior(QAbstractItemView::SelectItems);
        visibleGrid->setTextElideMode(Qt::ElideNone);
        visibleGrid->setCornerButtonEnabled(false);
        visibleGrid->setRowCount(0);
        visibleGrid->setColumnCount(0);
        visibleGrid->horizontalHeader()->setVisible(false);
        visibleGrid->horizontalHeader()->setHighlightSections(false);
        visibleGrid->verticalHeader()->setVisible(false);
        visibleGrid->verticalHeader()->setHighlightSections(false);

        verticalLayout->addWidget(visibleGrid);

        gameinfo_groupbox = new QGroupBox(centralWidget);
        gameinfo_groupbox->setObjectName(QStringLiteral("gameinfo_groupbox"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(gameinfo_groupbox->sizePolicy().hasHeightForWidth());
        gameinfo_groupbox->setSizePolicy(sizePolicy2);
        verticalLayout_3 = new QVBoxLayout(gameinfo_groupbox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        flagcounter_label = new QLabel(gameinfo_groupbox);
        flagcounter_label->setObjectName(QStringLiteral("flagcounter_label"));

        horizontalLayout_3->addWidget(flagcounter_label);

        flag_counter = new QLabel(gameinfo_groupbox);
        flag_counter->setObjectName(QStringLiteral("flag_counter"));

        horizontalLayout_3->addWidget(flag_counter);

        line = new QFrame(gameinfo_groupbox);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line);

        pause_time_button = new QPushButton(gameinfo_groupbox);
        pause_time_button->setObjectName(QStringLiteral("pause_time_button"));
        pause_time_button->setEnabled(false);
        pause_time_button->setMouseTracking(true);
        pause_time_button->setCheckable(true);
        pause_time_button->setAutoRepeat(false);

        horizontalLayout_3->addWidget(pause_time_button);

        time_label = new QLabel(gameinfo_groupbox);
        time_label->setObjectName(QStringLiteral("time_label"));

        horizontalLayout_3->addWidget(time_label);

        time = new QLabel(gameinfo_groupbox);
        time->setObjectName(QStringLiteral("time"));
        time->setMinimumSize(QSize(0, 0));
        time->setScaledContents(false);
        time->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(time);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(gameinfo_groupbox);

        config_groupbox = new QGroupBox(centralWidget);
        config_groupbox->setObjectName(QStringLiteral("config_groupbox"));
        sizePolicy2.setHeightForWidth(config_groupbox->sizePolicy().hasHeightForWidth());
        config_groupbox->setSizePolicy(sizePolicy2);
        verticalLayout_2 = new QVBoxLayout(config_groupbox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        label = new QLabel(config_groupbox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_4->addWidget(label);

        gridsize_selector = new QComboBox(config_groupbox);
        gridsize_selector->setObjectName(QStringLiteral("gridsize_selector"));

        horizontalLayout_4->addWidget(gridsize_selector);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        no_mines_label = new QLabel(config_groupbox);
        no_mines_label->setObjectName(QStringLiteral("no_mines_label"));

        horizontalLayout_2->addWidget(no_mines_label);

        noMinesSpinBox = new QSpinBox(config_groupbox);
        noMinesSpinBox->setObjectName(QStringLiteral("noMinesSpinBox"));
        noMinesSpinBox->setMinimum(0);
        noMinesSpinBox->setMaximum(100);
        noMinesSpinBox->setValue(10);

        horizontalLayout_2->addWidget(noMinesSpinBox);

        start_game_button = new QPushButton(config_groupbox);
        start_game_button->setObjectName(QStringLiteral("start_game_button"));

        horizontalLayout_2->addWidget(start_game_button);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(config_groupbox);


        horizontalLayout->addLayout(verticalLayout);

        Mines->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(Mines);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Mines->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Mines);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Mines->setStatusBar(statusBar);

        retranslateUi(Mines);

        QMetaObject::connectSlotsByName(Mines);
    } // setupUi

    void retranslateUi(QMainWindow *Mines)
    {
        Mines->setWindowTitle(QApplication::translate("Mines", "Mines", nullptr));
        show_leaderboard_button->setText(QApplication::translate("Mines", "Leaderboard", nullptr));
        gameinfo_groupbox->setTitle(QApplication::translate("Mines", "Game info", nullptr));
        flagcounter_label->setText(QApplication::translate("Mines", "Flag counter:", nullptr));
        flag_counter->setText(QString());
        pause_time_button->setText(QApplication::translate("Mines", "Pause", nullptr));
        time_label->setText(QApplication::translate("Mines", "Time:", nullptr));
        time->setText(QApplication::translate("Mines", "<html><head/><body><p align=\"right\"><br/></p></body></html>", nullptr));
        config_groupbox->setTitle(QApplication::translate("Mines", "Configuration", nullptr));
        label->setText(QApplication::translate("Mines", "Difficulty:", nullptr));
        no_mines_label->setText(QApplication::translate("Mines", "Number of mines:", nullptr));
        start_game_button->setText(QApplication::translate("Mines", "Start game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mines: public Ui_Mines {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINES_H
