#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QSettings>
#include <QDirIterator>
#include <QTime>
#include <QDate>
#include "logfile.h"

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);
    ~Logger();

    void setLogFolderPath(QString folderPath);
    void changeLogFolderPath(QString folderPath);
    QString logFolderPath();
    QStringList logFiles() const;
    void addLog(QList<int> types, QString logName);
    void editLog(QList<int> types, QString logName);
    void deleteLog(QString logName);

signals:

    void lineWritten(QString filePath);

public slots:

    QStringList readFile(QString fileName) const;
    void log(int code, QString logMessage);

private:

    void moveLogFiles(QString newFolderPath);
    void updateLogFiles();

    QList<LogFile> *m_logFileList;
    QSettings *m_settings;

};

#endif // LOGGER_H
