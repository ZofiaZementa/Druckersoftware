#ifndef COMMANDLINEUI_H
#define COMMANDLINEUI_H

#include "machinecontroller.h"
#include "IO/iocontroller.h"
#include "Logging/logger.h"
#include <QObject>
#include <QThread>
#include <QSettings>

class CommandlineUI : public QObject
{
    Q_OBJECT
public:
    explicit CommandlineUI(QObject *parent = nullptr);

signals:

    void machineControllerG0(qreal x, qreal y, qreal z, qreal e, qreal f, int s);
    void machineControllerReset();
    void machineControllerPause(bool *ret);
    void machineControllerPlay(bool *ret);
    void machineControllerPrint(bool *ret);
    void machineControllerSetFilePath(QUrl filePath);
    void machineControllerSetLine(int line);
    void iOControllerWrite(QString pinName, int value, bool *ret);
    void iOControllerRead(QString pinName, int *ret);
    void loggerSetLogFolderPath(QString folderPath);
    void loggerChangeLogFolderPath(QString folderPath);
    void loggerLogFolderPath(QString *ret);
    void loggerLogFiles(QStringList *ret);
    void loggerAddLog(QList<int> types, QString logName);
    void loggerEditLog(QList<int> types, QString logName);
    void loggerDeleteLog(QString logName);
    void loggerReadFile(QString fileName, QStringList *ret);
    void loggerLog(QString logMessage, int code);
    void serialInterfaceSend(QString text);
    void serialInterfaceConnect();
    void serialInterfaceDisconnect();

public slots:

    //mainloop to provide a consistent commandline interface
    void mainLoop();

private:

    //breaks up String at the spaces
    QStringList breakUpString(QString string);
    //checks the m_input for commands and executes them
    int checkCommands();
    //prints the help
    void printhelp();

    //the input
    char *m_input[400];
    QSettings *m_settings;
};

#endif // COMMANDLINEUI_H
