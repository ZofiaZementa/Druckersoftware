#ifndef COMMANDLINEUI_H
#define COMMANDLINEUI_H

#include "machinecontroller.h"
#include "IO/iocontroller.h"
#include "Logging/logger.h"
#include <QObject>

class CommandlineUI : public QObject
{
    Q_OBJECT
public:
    explicit CommandlineUI(QObject *parent = nullptr);

signals:

    void machineControllerG0(qreal x, qreal y, qreal z, qreal e, qreal f, int s);    //rapid linear move
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

public slots:

    void mainLoop();

private:

    QStringList breakUpString(QString string);
    int checkCommands();
    void printhelp();

    char *m_input[400];
};

#endif // COMMANDLINEUI_H
