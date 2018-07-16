#ifndef CMDUILOGGERINTERFACE_H
#define CMDUILOGGERINTERFACE_H

#include <QObject>
#include "Logging/logger.h"

class CmdUILoggerInterface : public QObject
{
    Q_OBJECT
public:
    explicit CmdUILoggerInterface(QObject *parent = nullptr);

    void setLogger(Logger *logger);

signals:

public slots:

    void setLogFolderPath(QString folderPath);
    void changeLogFolderPath(QString folderPath);
    void logFolderPath(QString *ret);
    void logFiles(QStringList *ret);
    void addLog(QList<int> types, QString logName);
    void editLog(QList<int> types, QString logName);
    void deleteLog(QString logName);
    void readFile(QString fileName, QStringList *ret);
    void log(QString logMessage, int code);

private:

    Logger *m_logger;

};

#endif // CMDUILOGGERINTERFACE_H
