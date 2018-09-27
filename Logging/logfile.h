#ifndef LOGFILE_H
#define LOGFILE_H

#include <QObject>
#include <QFile>
#include <QTime>
#include <QStringList>

class LogFile : public QObject
{
    Q_OBJECT
public:
    explicit LogFile(QObject *parent = nullptr);
    ~LogFile();

    //returns the filepath of the logfile
    QString filePath() const;
    //sets the filepath of the logfile
    void setFilePath(QString filePath);

signals:

public slots:

    //makes a logentry
    void log(QString logMessage, QString origin, int code) const;
    //reads the whole file and returns it
    QStringList readAll();

private:

    QString convertDecToHex(int decimal) const;

    //stores the filepath of the file
    QString *m_filePath;
};

#endif // LOGFILE_H
