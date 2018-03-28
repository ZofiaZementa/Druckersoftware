#include "gcodereader.h"

GCodeReader::GCodeReader(QObject *parent) : QObject(parent)
{

    //defining pointers

    m_lineNumber = new int;
}

GCodeReader::~GCodeReader()
{

    //deleting pointers

    delete m_lineNumber;

    //setting the pointers to NULL

    m_lineNumber = NULL;
}

void GCodeReader::setLineNumber(int lineNumber)
{

}

int GCodeReader::lineNumber()
{

}

void GCodeReader::read(QUrl filePath)
{

}

void GCodeReader::nextLine()
{

}

void GCodeReader::puseReading()
{

}

void GCodeReader::continueReading()
{

}

void GCodeReader::clear()
{

}
