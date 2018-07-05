#include "logfile.h"

LogFile::LogFile(QObject *parent) : QObject(parent)
{

    m_filePath = new QString();
}

LogFile::~LogFile()
{

    delete m_filePath;

    m_filePath = NULL;
}

QString LogFile::filePath() const
{

    return *m_filePath;
}

void LogFile::setFilePath(QString filePath)
{

    *m_filePath = filePath;
}

void LogFile::log(QString logMessage, QString origin, int code) const
{

    QFile file(*m_filePath);

    if(file.open(QIODevice::WriteOnly) == false){

        return;
    }

    QByteArray line;
    QString hexCode;

    hexCode.setNum(code, 16);
    hexCode.insert(0, QString("0x"));
    line.append(QString("At %1:%2:%3:%4 from %5 with code %6: %7;\r\n").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).arg(QTime::currentTime().second()).arg(QTime::currentTime().msec()).arg(origin).arg(hexCode).arg(logMessage));
    file.write(line);
    file.flush();
    file.close();
}

QStringList LogFile::readAll() const
{
    QFile file(*m_filePath);
    QStringList output;

    if(file.open(QIODevice::ReadOnly) == false){

        return output;
    }

    while(file.canReadLine()){

        output.append(file.readLine());
    }

    file.close();

    return output;
}
