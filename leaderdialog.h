#ifndef LEADERDIALOG_H
#define LEADERDIALOG_H

#include <QObject>

class LeaderDialog : public QObject
{
    Q_OBJECT
public:
    explicit LeaderDialog(QObject *parent = nullptr);

signals:

public slots:
};

#endif // LEADERDIALOG_H