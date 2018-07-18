#include "logfile.h"

LogFile::LogFile(QObject *parent) : QObject(parent)
{

    //initalising pointers

    m_filePath = new QString();
}

LogFile::~LogFile()
{

    //deleting pointers

    delete m_filePath;

    //setting pointers to null

    m_filePath = NULL;
}

//returns the filepath of the logfile
QString LogFile::filePath() const
{

    //returns the filepath
    return *m_filePath;
}

//sets the filepath of the logfile
void LogFile::setFilePath(QString filePath)
{

    //stores the filepath of the logfile to filePath
    *m_filePath = filePath;
}

//makes a logentry
void LogFile::log(QString logMessage, QString origin, int code) const
{

    //creates a QFile object
    QFile file(*m_filePath);

    //opens the file an checks if it was succesfull
    //triggered if it wasn't
    if(file.open(QIODevice::WriteOnly) == false){

        return;
    }

    //variable for the line which to write
    QByteArray line;
    //variable for the hex-errorcode
    QString hexCode;

    //writes the errorcode into a string
    hexCode.setNum(code, 16);
    //inserts the "0x" in front of the string
    hexCode.insert(0, QString("0x"));
    //writes the line into the bytearray
    line.append(QString("At %1:%2:%3:%4 from %5 with code %6: %7;\r\n").arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).arg(QTime::currentTime().second()).arg(QTime::currentTime().msec()).arg(origin).arg(hexCode).arg(logMessage));
    //writes the line into the file
    file.write(line);
    //flushes the file
    file.flush();
    //closes the file
    file.close();
}

//reads the whole file and returns it
QStringList LogFile::readAll()
{

    //creates a QFile object
    QFile file(*m_filePath);
    //variable for the output
    QStringList output;

    //opens the file an checks if it was succesfull
    //triggered if it wasn't
    if(file.open(QIODevice::ReadOnly) == false){

        return output;
    }

    //loop executed while there is a line to read
    while(file.atEnd() == false){

        //appends the read line to the outputlist
        output.append(file.readLine());
    }

    //closes the file
    file.close();

    return output;
}
