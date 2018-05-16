#include "gcodereader.h"
#include <QFile>

GCodeReader::GCodeReader(QObject *parent) : QObject(parent)
{

    //defining pointers

    m_lineNumber = new int;
    m_filePath = new QUrl;

    m_lineNumber = 0;
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

bool GCodeReader::readline(int lineNumber)
{
    QFile file(m_filePath->toString());

    if(file.open(QIODevice::ReadOnly) == false){

        emit error(QString("File doesn't exist or is open in another program"));
        return false;
    }

    file.seek(lineNumber);

    QByteArray line = file.readLine();
    QStringList lineParts = breakUpString(QString(line));

    //check if the command is g0
    if(lineParts.at(0) == QString("G0") || lineParts.at(0) == QString("g0")){

        qreal x = 0.0;
        qreal y = 0.0;
        qreal z = 0.0;
        qreal e = 0.0;
        int s = 0;

        for(int i = 1;i < lineParts.count();i++){

            if(lineParts.at(i).at(0) == QString("X") || lineParts.at(i).at(0) == QString("x")){

                lineParts[i].remove(0, 1);
                x = lineParts.at(i).toDouble();
            }

            else if(lineParts.at(i).at(0) == QString("Y") || lineParts.at(i).at(0) == QString("y")){

                lineParts[i].remove(0, 1);
                y = lineParts.at(i).toDouble();
            }

            else if(lineParts.at(i).at(0) == QString("Z") || lineParts.at(i).at(0) == QString("z")){

                lineParts[i].remove(0, 1);
                z = lineParts.at(i).toDouble();
            }

            else if(lineParts.at(i).at(0) == QString("E") || lineParts.at(i).at(0) == QString("e")){

                lineParts[i].remove(0, 1);
                e = lineParts.at(i).toDouble();
            }

            else if(lineParts.at(i).at(0) == QString("S") || lineParts.at(i).at(0) == QString("s")){

                lineParts[i].remove(0, 1);
                s = lineParts.at(i).toInt();
            }

            else{

                emit error(QString("Invalid command in line %1").arg(lineNumber));
                return false;
            }
        }

        emit g0(x, y, z, e, s);
    }

    //check if the command is g1
    else if(lineParts.at(0) == QString("G1") || lineParts.at(0) == QString("g1")){

        qreal x = 0.0;
        qreal y = 0.0;
        qreal z = 0.0;
        qreal e = 0.0;
        qreal f = 0.0;
        int s = 0;

        for(int i = 1;i < lineParts.count();i++){

            if(lineParts.at(i).at(0) == QString("X") || lineParts.at(i).at(0) == QString("x")){

                lineParts[i].remove(0, 1);
                x = lineParts.at(i).toDouble();
            }

            else if(lineParts.at(i).at(0) == QString("Y") || lineParts.at(i).at(0) == QString("y")){

                lineParts[i].remove(0, 1);
                y = lineParts.at(i).toDouble();
            }

            else if(lineParts.at(i).at(0) == QString("Z") || lineParts.at(i).at(0) == QString("z")){

                lineParts[i].remove(0, 1);
                z = lineParts.at(i).toDouble();
            }

            else if(lineParts.at(i).at(0) == QString("E") || lineParts.at(i).at(0) == QString("e")){

                lineParts[i].remove(0, 1);
                e = lineParts.at(i).toDouble();
            }

            else if(lineParts.at(i).at(0) == QString("F") || lineParts.at(i).at(0) == QString("f")){

                lineParts[i].remove(0, 1);
                f = lineParts.at(i).toDouble();
            }

            else if(lineParts.at(i).at(0) == QString("S") || lineParts.at(i).at(0) == QString("s")){

                lineParts[i].remove(0, 1);
                s = lineParts.at(i).toInt();
            }

            else{

                emit error(QString("Invalid command in line %1").arg(lineNumber));
                return false;
            }
        }

        emit g1(x, y, z, e, f, s);
    }
}

QStringList GCodeReader::breakUpString(QString string)
{

    int help = -1;

    QStringList retString;

    for(int i = 0;i < string.count();i++){

        if(string.at(i) == QString(" ") && i - help > 1){

            retString.append(string.mid((help + 1), (i - help - 1)));
            help = i;
        }

        else if(string.at(i) == QString(" ")){

            help = i;
        }
    }

    if(string.count() - 1 - help > 1){

        retString.append(string.mid((help + 1), (string.count() - help - 1)));
    }

    return retString;
}
