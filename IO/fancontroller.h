#ifndef FANCONTROLLER_H
#define FANCONTROLLER_H

#include <QObject>
#include "iocontroller.h"

class FanController : public QObject
{
    Q_OBJECT
public:
    explicit FanController(QObject *parent = nullptr);

    void checkChanged(IOController *iOController);

signals:

public slots:
};

#endif // FANCONTROLLER_H
