#include "gcodereader.h"

GCodeReader::GCodeReader(QObject *parent) : QObject(parent)
{

    //defining pointers

    m_lineNumber = new int;
    m_filePath = new QUrl;
}

GCodeReader::~GCodeReader()
{

    //deleting pointers

    delete m_lineNumber;
    delete m_filePath;

    //setting the pointers to NULL

    m_lineNumber = NULL;
    m_filePath = NULL;
}

void GCodeReader::setLineNumber(int lineNumber)
{

}

int GCodeReader::lineNumber()
{

}

void GCodeReader::setFilePath(QUrl filePath)
{

}

QUrl GCodeReader::filePath()
{

}

void GCodeReader::nextLine()
{

}

void GCodeReader::pauseReading()
{

}

void GCodeReader::continueReading()
{

}

void GCodeReader::clear()
{

}
