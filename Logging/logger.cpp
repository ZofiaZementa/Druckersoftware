#include "logger.h"

Logger::Logger(QObject *parent) : QObject(parent)
{

    m_logFileList = new QList<LogFile>;
    m_settings = new QSettings(QString("./settings.ini"), QSettings::IniFormat, this);
}

Logger::~Logger()
{

    delete m_logFileList;

    m_logFileList = NULL;
}

void Logger::setLogFolderPath(QString folderPath)
{

    m_settings->setValue("logger/folderPath", folderPath);
    m_settings->sync();
}

void Logger::changeLogFolderPath(QString folderPath)
{

    moveLogFiles(folderPath);
    m_settings->setValue("logger/folderPath", folderPath);
    m_settings->sync();
}

QString Logger::logFolderPath()
{

    return m_settings->value("logger/folderPath", QString("./logs/")).toString();
}

QStringList Logger::logFiles() const
{

    QDirIterator iterator(m_settings->value("logger/folderPath", QString("./logs/")).toString(), QDirIterator::Subdirectories);
    QStringList output;

    while(iterator.hasNext()){

        output.append(iterator.fileName());
    }

    return output;
}

void Logger::addLog(QList<int> types, QString logName)
{

    QList<QVariant> logNames = m_settings->value("logger/logNames").toList();

    if(logNames.contains(logName) == false){

        QList<QVariant> typesList = m_settings->value("logger/types").toList();

        logNames.append(qVariantFromValue(logName));
        m_settings->setValue("logger/logNames", logNames);
        m_settings->sync();
        typesList.append(qVariantFromValue(types));
        m_settings->setValue("logger/types", typesList);
        m_settings->sync();
    }
}

void Logger::editLog(QList<int> types, QString logName)
{

    QList<QVariant> logNames = m_settings->value("logger/logNames").toList();
    QList<QVariant> typesList = m_settings->value("logger/types").toList();

    if(logNames.contains(logName) == true && typesList.at(logNames.indexOf(qVariantFromValue(types))) != qVariantFromValue(types)){

        typesList[logNames.indexOf(qVariantFromValue(types))] = qVariantFromValue(types);
        m_settings->setValue("logger/types", typesList);
        m_settings->sync();
    }
}

void Logger::deleteLog(QString logName)
{

    QList<QVariant> logNames = m_settings->value("logger/logNames").toList();

    if(logNames.contains(logName) == true){

        QList<QVariant> typesList = m_settings->value("logger/types").toList();

        typesList.removeAt(logNames.indexOf(logName));
        m_settings->setValue("logger/types", typesList);
        m_settings->sync();
        logNames.removeOne(logName);
        m_settings->setValue("logger/logNames", logNames);
        m_settings->sync();
    }
}

QStringList Logger::readFile(QString fileName) const
{

    QDirIterator iterator(m_settings->value("logger/folderPath", QString("./logs/")).toString(), QDirIterator::Subdirectories);
    QStringList output;

    while(iterator.hasNext()){

        if(iterator.fileName() == fileName){

            LogFile logFile;

            logFile.setFilePath(iterator.filePath());
            output = logFile.readAll();

            break;
        }
    }

    return output;
}

void Logger::log(QString logMessage, int code)
{

    QList<QVariant> typesList = m_settings->value("logger/types").toList();
    QString origin;


    if(code / 65536 == 0){

        origin = QString("MachineController");
    }

    else if(code / 65536 == 1){

        origin = QString("MotorController");
    }

    else if(code / 65536 == 2){

        origin = QString("IOController");
    }

    else if(code / 65536 == 3){

        origin = QString("HeatingController");
    }

    else if(code / 65536 == 4){

        origin = QString("SerialInterface");
    }

    else if(code / 65536 == 5){

        origin = QString("SensorListener");
    }

    else if(code / 65536 == 6){

        origin = QString("IOMainLoop");
    }

    else if(code / 65536 == 7){

        origin = QString("SerialInterface");
    }

    else if(code / 65536 == 8){

        origin = QString("GCodeReader");
    }

    for(int i = 0;i < m_logFileList->count();i++){

        if(typesList.at(i).toList().contains(qVariantFromValue(-1)) == true || typesList.at(i).toList().contains(qVariantFromValue(code / 65536)) == true){

            m_logFileList->at(i).log(logMessage, origin, code);
            emit lineWritten(m_logFileList->at(i).filePath());
        }
    }
}

void Logger::moveLogFiles(QString newFolderPath)
{

    QDir directory(m_settings->value("logger/folderPath", QString("./logs/")).toString());

    directory.rename(m_settings->value("logger/folderPath", QString("./logs/")).toString(), newFolderPath);
}

void Logger::updateLogFiles()
{

    QList<QVariant> logNames = m_settings->value("logger/logNames").toList();
    QString folderPath;

    m_logFileList->clear();

    for(int i = 0;i < logNames.count();i++){

        LogFile logFile;

        folderPath = m_settings->value("logger/folderPath", QString("./logs/")).toString();
        folderPath.append(logNames.at(i).toString());
        folderPath.append(QString("-%1.%2.%3-%4:%5:%6.txt").arg(QDate::currentDate().day()).arg(QDate::currentDate().month()).arg(QDate::currentDate().year()).arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute()).arg(QTime::currentTime().second()));
        logFile.setFilePath(folderPath);
    }
}
