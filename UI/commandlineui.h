#ifndef COMMANDLINEUI_H
#define COMMANDLINEUI_H

#include "machinecontroller.h"
#include "IO/iocontroller.h"
#include <QObject>

class CommandlineUI : public QObject
{
    Q_OBJECT
public:
    explicit CommandlineUI(QObject *parent = nullptr);

    void setMachineController(MachineController *machineController);
    void setIOController(IOController *iOController);

signals:

public slots:

    void mainLoop();

private:

    QStringList breakUpString(QString string);
    int checkCommands();
    void printhelp();

    char *m_input[400];
    MachineController *m_machineController;
    IOController *m_iOController;
};

#endif // COMMANDLINEUI_H
