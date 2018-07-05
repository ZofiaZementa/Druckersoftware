#ifndef LOGFILE_H
#define LOGFILE_H

#include <QObject>
#include <QFile>
#include <QTime>

class LogFile : public QObject
{
    Q_OBJECT
public:
    explicit LogFile(QObject *parent = nullptr);
    ~LogFile();

    QString filePath() const;
    void setFilePath(QString filePath);

signals:

public slots:

    void log(QString logMessage, QString origin, int code) const;
    QStringList readAll() const;

private:

    QString *m_filePath;
};

#endif // LOGFILE_H
