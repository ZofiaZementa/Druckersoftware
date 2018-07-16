#ifndef CMDUIMACHINECONTROLLERINTERFACE_H
#define CMDUIMACHINECONTROLLERINTERFACE_H

#include <QObject>
#include "machinecontroller.h"

class CmdUIMachineControllerInterface : public QObject
{
    Q_OBJECT
public:
    explicit CmdUIMachineControllerInterface(QObject *parent = nullptr);

    void setMachineController(MachineController *machineController);

signals:

public slots:

    void g0(qreal x, qreal y, qreal z, qreal e, qreal f, int s);    //rapid linear move
    void reset();
    void pause(bool *ret);
    void play(bool *ret);
    void print(bool *ret);
    void setFilePath(QUrl filePath);
    void setLine(int line);

private:

    MachineController *m_machineController;

};

#endif // CMDUIMACHINECONTROLLERINTERFACE_H
