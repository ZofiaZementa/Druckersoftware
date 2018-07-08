#ifndef HEATINGCONTROLLER_H
#define HEATINGCONTROLLER_H

#include <QObject>
#include "iocontroller.h"

class HeatingController : public QObject
{
    Q_OBJECT
public:
    explicit HeatingController(QObject *parent = nullptr);

    void checkChanged(IOController *iOController);

signals:

public slots:
};

#endif // HEATINGCONTROLLER_H
