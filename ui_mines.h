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
    QSpacerItem *verticalSpacer;
    MyTable *tableWidget;
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
        Mines->resize(514, 743);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Mines->sizePolicy().hasHeightForWidth());
        Mines->setSizePolicy(sizePolicy);
        Mines->setMinimumSize(QSize(514, 0));
        Mines->setMaximumSize(QSize(514, 743));
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
        verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        tableWidget = new MyTable(centralWidget);
        if (tableWidget->columnCount() < 10)
            tableWidget->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        if (tableWidget->rowCount() < 10)
            tableWidget->setRowCount(10);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem19);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setMinimumSize(QSize(500, 500));
        tableWidget->setMaximumSize(QSize(500, 500));
        tableWidget->setMouseTracking(true);
        tableWidget->setTabletTracking(true);
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        tableWidget->setTextElideMode(Qt::ElideNone);
        tableWidget->setCornerButtonEnabled(false);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setHighlightSections(false);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setHighlightSections(false);

        verticalLayout->addWidget(tableWidget);

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
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Mines", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Mines", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Mines", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("Mines", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("Mines", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("Mines", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("Mines", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("Mines", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("Mines", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("Mines", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem10->setText(QApplication::translate("Mines", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem11->setText(QApplication::translate("Mines", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem12->setText(QApplication::translate("Mines", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem13->setText(QApplication::translate("Mines", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem14->setText(QApplication::translate("Mines", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem15->setText(QApplication::translate("Mines", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem16->setText(QApplication::translate("Mines", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem17->setText(QApplication::translate("Mines", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem18->setText(QApplication::translate("Mines", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem19->setText(QApplication::translate("Mines", "New Row", nullptr));
        gameinfo_groupbox->setTitle(QApplication::translate("Mines", "Game info", nullptr));
        flagcounter_label->setText(QApplication::translate("Mines", "Flag counter:", nullptr));
        flag_counter->setText(QString());
        pause_time_button->setText(QApplication::translate("Mines", "Pause", nullptr));
        time_label->setText(QApplication::translate("Mines", "Time:", nullptr));
        time->setText(QApplication::translate("Mines", "<html><head/><body><p align=\"right\"><br/></p></body></html>", nullptr));
        config_groupbox->setTitle(QApplication::translate("Mines", "Configuration", nullptr));
        no_mines_label->setText(QApplication::translate("Mines", "Number of mines:", nullptr));
        start_game_button->setText(QApplication::translate("Mines", "Start game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mines: public Ui_Mines {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINES_H
