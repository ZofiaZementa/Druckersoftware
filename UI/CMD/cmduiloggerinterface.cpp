#include "cmduiloggerinterface.h"

CmdUILoggerInterface::CmdUILoggerInterface(QObject *parent) : QObject(parent)
{

}

void CmdUILoggerInterface::setLogger(Logger *logger)
{

    m_logger = logger;
}

void CmdUILoggerInterface::setLogFolderPath(QString folderPath)
{

    m_logger->setLogFolderPath(folderPath);
}

void CmdUILoggerInterface::changeLogFolderPath(QString folderPath)
{

    m_logger->changeLogFolderPath(folderPath);
}

void CmdUILoggerInterface::logFolderPath(QString *ret)
{

    *ret = m_logger->logFolderPath();
}

void CmdUILoggerInterface::logFiles(QStringList *ret)
{

    *ret = m_logger->logFiles();
}

void CmdUILoggerInterface::addLog(QList<int> types, QString logName)
{

    m_logger->addLog(types, logName);
}

void CmdUILoggerInterface::editLog(QList<int> types, QString logName)
{

    m_logger->editLog(types, logName);
}

void CmdUILoggerInterface::deleteLog(QString logName)
{

    m_logger->deleteLog(logName);
}

void CmdUILoggerInterface::readFile(QString fileName, QStringList *ret)
{

    *ret = m_logger->readFile(fileName);
}

void CmdUILoggerInterface::log(QString logMessage, int code)
{

    m_logger->log(logMessage, code);
}
