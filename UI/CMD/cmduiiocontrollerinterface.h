#ifndef CMDUIIOCONTROLLERINTERFACE_H
#define CMDUIIOCONTROLLERINTERFACE_H

#include <QObject>
#include "IO/iocontroller.h"

class CmdUIIOControllerInterface : public QObject
{
    Q_OBJECT
public:
    explicit CmdUIIOControllerInterface(QObject *parent = nullptr);

    void setIOController(IOController *iOController);

signals:

public slots:

    void iOControllerWrite(QString pinName, int value, bool *ret);
    void iOControllerRead(QString pinName, int *ret);

private:

    IOController *m_iOController;

};

#endif // CMDUIIOCONTROLLERINTERFACE_H
