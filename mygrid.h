#ifndef MYGRID_H
#define MYGRID_H

#include <QApplication>
#include <QTableWidget>
#include <QObject>
#include <QMouseEvent>
#include <QDebug>
#include <QLabel>
#include <QDir>
#include <QMessageBox>
#include <QAbstractItemView>
#include <QElapsedTimer>
#include <QTimer>
#include <QPushButton>
#include <QDialog>

class MyGrid : public QTableWidget
{
    Q_OBJECT
public:
    MyGrid(QWidget*);
    virtual ~MyGrid();

    QTableWidgetItem *getItClicked() const;
    void setItClicked(QTableWidgetItem *value);

    QTableWidgetItem *getItHover() const;
    void setItHover(QTableWidgetItem *value);

private slots:
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
public slots:

signals:
    void rightClickSignal(QTableWidgetItem* item);
    void leftClickSignal(QTableWidgetItem* item);

private:
    QTableWidgetItem* itClicked;
    QTableWidgetItem* itHover;
};

#endif // MYGRID_H
