#include "gcodereader.h"
#include <QFile>

GCodeReader::GCodeReader(QObject *parent) : QObject(parent)
{

    //defining pointers

    m_lineNumber = new int;
    m_filePath = new QUrl;
    m_unit = new qreal;

    *m_lineNumber = 0;
    *m_unit = 1.0;
}

GCodeReader::~GCodeReader()
{

    //deleting pointers

    delete m_lineNumber;
    delete m_filePath;
    delete m_unit;

    //setting the pointers to NULL

    m_lineNumber = NULL;
    m_filePath = NULL;
    m_unit = NULL;
}

void GCodeReader::setLineNumber(int lineNumber)
{

    if(*m_lineNumber != lineNumber){

        *m_lineNumber = lineNumber;
        emit lineNumberChanged(*m_lineNumber);
    }
}

int GCodeReader::lineNumber()
{

    return *m_lineNumber;
}

void GCodeReader::setFilePath(QUrl filePath)
{

    if(*m_filePath != filePath){

        *m_filePath = filePath;
        emit filePathChanged(*m_filePath);
    }
}

QUrl GCodeReader::filePath()
{

    return *m_filePath;
}

void GCodeReader::nextLine()
{

    (*m_lineNumber)++;
    readline(*m_lineNumber);
}

void GCodeReader::clear()
{

    *m_lineNumber = 0;
    m_filePath->clear();
    *m_unit = 1;
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

    file.close();

    //check if the command is g0
    if(lineParts.at(0) == QString("G0") || lineParts.at(0) == QString("g0")){

        qreal x = 0.0;
        qreal y = 0.0;
        qreal z = 0.0;
        qreal e = 0.0;
        qreal f = -1.0;
        int s = 0;

        if(lineParts.count() > 1){

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

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit g0((x **m_unit), (y * *m_unit), (z * *m_unit), (e * *m_unit), (f * *m_unit), s);
    }

    //check if the command is g1
    else if(lineParts.at(0) == QString("G1") || lineParts.at(0) == QString("g1")){

        qreal x = 0.0;
        qreal y = 0.0;
        qreal z = 0.0;
        qreal e = 0.0;
        qreal f = -1.0;
        int s = 0;

        if(lineParts.count() > 1){

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

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit g1(x, y, z, e, f, s);
    }

    //check if the command is g2
    else if(lineParts.at(0) == QString("G2") || lineParts.at(0) == QString("g2")){

        qreal x = 0.0;
        qreal y = 0.0;
        qreal i = 0.0;
        qreal j = 0.0;
        qreal e = 0.0;
        qreal f = 0.0;

        if(lineParts.count() > 1){

            for(int n = 0;n < lineParts.count();n++){

                if(lineParts.at(n).at(0) == QString("X") || lineParts.at(n).at(0) == QString("x")){

                    lineParts[n].remove(0, 1);
                    x = lineParts.at(n).toDouble();
                }

                else if(lineParts.at(n).at(0) == QString("Y") || lineParts.at(n).at(0) == QString("y")){

                    lineParts[n].remove(0, 1);
                    y = lineParts.at(n).toDouble();
                }

                else if(lineParts.at(n).at(0) == QString("I") || lineParts.at(n).at(0) == QString("i")){

                    lineParts[n].remove(0, 1);
                    i = lineParts.at(n).toDouble();
                }

                else if(lineParts.at(n).at(0) == QString("J") || lineParts.at(n).at(0) == QString("j")){

                    lineParts[n].remove(0, 1);
                    j = lineParts.at(n).toDouble();
                }

                else if(lineParts.at(n).at(0) == QString("E") || lineParts.at(n).at(0) == QString("e")){

                    lineParts[n].remove(0, 1);
                    e = lineParts.at(n).toDouble();
                }

                else if(lineParts.at(n).at(0) == QString("F") || lineParts.at(n).at(0) == QString("f")){

                    lineParts[n].remove(0, 1);
                    f = lineParts.at(n).toDouble();
                }

                else if(lineParts.at(n).at(0) == QString(";")){

                    for(int k = n;k < lineParts.count();k++){

                        lineParts.removeAt(n + k);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit g2((x * *m_unit), (y * *m_unit), (i * *m_unit), (j * *m_unit), (e * *m_unit), (f * *m_unit));
    }

    //check if the command is g3
    else if(lineParts.at(0) == QString("G3") || lineParts.at(0) == QString("g3")){

        qreal x = 0.0;
        qreal y = 0.0;
        qreal i = 0.0;
        qreal j = 0.0;
        qreal e = 0.0;
        qreal f = 0.0;

        if(lineParts.count() > 1){

            for(int n = 0;n < lineParts.count();n++){

                if(lineParts.at(n).at(0) == QString("X") || lineParts.at(n).at(0) == QString("x")){

                    lineParts[n].remove(0, 1);
                    x = lineParts.at(n).toDouble();
                }

                else if(lineParts.at(n).at(0) == QString("Y") || lineParts.at(n).at(0) == QString("y")){

                    lineParts[n].remove(0, 1);
                    y = lineParts.at(n).toDouble();
                }

                else if(lineParts.at(n).at(0) == QString("I") || lineParts.at(n).at(0) == QString("i")){

                    lineParts[n].remove(0, 1);
                    i = lineParts.at(n).toDouble();
                }

                else if(lineParts.at(n).at(0) == QString("J") || lineParts.at(n).at(0) == QString("j")){

                    lineParts[n].remove(0, 1);
                    j = lineParts.at(n).toDouble();
                }

                else if(lineParts.at(n).at(0) == QString("E") || lineParts.at(n).at(0) == QString("e")){

                    lineParts[n].remove(0, 1);
                    e = lineParts.at(n).toDouble();
                }

                else if(lineParts.at(n).at(0) == QString("F") || lineParts.at(n).at(0) == QString("f")){

                    lineParts[n].remove(0, 1);
                    f = lineParts.at(n).toDouble();
                }

                else if(lineParts.at(n).at(0) == QString(";")){

                    for(int k = n;k < lineParts.count();k++){

                        lineParts.removeAt(n + k);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit g3((x * *m_unit), (y * *m_unit), (i * *m_unit), (j * *m_unit), (e * *m_unit), (f * *m_unit));
    }

    //check if the command is g4
    else if(lineParts.at(0) == QString("G4") || lineParts.at(0) == QString("g4")){

        int p = 0;

        if(lineParts.count() > 1){

            for(int i = 1;i < lineParts.count();i++){

                if(lineParts.at(i).at(0) == QString("P") || lineParts.at(i).at(0) == QString("p")){

                    lineParts[i].remove(0, 1);
                    p = lineParts.at(i).toInt();
                }

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit g4(p);
    }

    //check if the command is g10
    else if(lineParts.at(0) == QString("G10") || lineParts.at(0) == QString("g10")){

        qreal s = 0.0;

        if(lineParts.count() > 1){

            for(int i = 1;i < lineParts.count();i++){

                if(lineParts.at(i).at(0) == QString("S") || lineParts.at(i).at(0) == QString("s")){

                    lineParts[i].remove(0, 1);
                    s = lineParts.at(i).toDouble();
                }

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit g10(s * *m_unit);
    }

    //check if the command is g11
    else if(lineParts.at(0) == QString("G11") || lineParts.at(0) == QString("g11")){

        qreal s = 0.0;

        if(lineParts.count() > 1){

            for(int i = 1;i < lineParts.count();i++){

                if(lineParts.at(i).at(0) == QString("S") || lineParts.at(i).at(0) == QString("s")){

                    lineParts[i].remove(0, 1);
                    s = lineParts.at(i).toDouble();
                }

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit g11(s * *m_unit);
    }

    //check if the command is g20
    else if(lineParts.at(0) == QString("G20") || lineParts.at(0) == QString("g20")){

        *m_unit = 25.4;
    }

    //check if the command is g21
    else if(lineParts.at(0) == QString("G21") || lineParts.at(0) == QString("g21")){

        *m_unit = 1;
    }

    //check if the command is g28
    else if(lineParts.at(0) == QString("G28") || lineParts.at(0) == QString("g28")){

        bool x = true;
        bool y = true;
        bool z = true;

        if(lineParts.count() > 1){

            x = false;
            y = false;
            z = false;

            for(int i = 1;i < lineParts.count();i++){

                if(lineParts.at(1).at(0) == QString("X") || lineParts.at(1).at(0) == QString("x")){

                    x = true;
                }

                else if(lineParts.at(1).at(0) == QString("Y") || lineParts.at(1).at(0) == QString("y")){

                    y = true;
                }

                else if(lineParts.at(1).at(0) == QString("Z") || lineParts.at(1).at(0) == QString("z")){

                    z = true;
                }

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        emit g28(x, y, z);
    }

    //check if the command is g90
    else if(lineParts.at(0) == QString("G90") || lineParts.at(0) == QString("g90")){

        emit g90();
    }

    //check if the command is g91
    else if(lineParts.at(0) == QString("G91") || lineParts.at(0) == QString("g91")){

        emit g91();
    }

    //check if the command is g92
    else if(lineParts.at(0) == QString("G92") || lineParts.at(0) == QString("g92")){

        bool xB = true;
        bool yB = true;
        bool zB = true;
        bool eB = true;
        qreal x = 0.0;
        qreal y = 0.0;
        qreal z = 0.0;
        qreal e = 0.0;

        if(lineParts.count() > 1){

            xB = false;
            yB = false;
            zB = false;
            eB = false;

            for(int i = 1;i < lineParts.count();i++){

                if(lineParts.at(i).at(0) == QString("X") || lineParts.at(i).at(0) == QString("x")){

                    lineParts[i].remove(0, 1);
                    x = lineParts.at(i).toDouble();
                    xB = true;
                }

                else if(lineParts.at(i).at(0) == QString("Y") || lineParts.at(i).at(0) == QString("y")){

                    lineParts[i].remove(0, 1);
                    y = lineParts.at(i).toDouble();
                    yB = true;
                }

                else if(lineParts.at(i).at(0) == QString("Z") || lineParts.at(i).at(0) == QString("z")){

                    lineParts[i].remove(0, 1);
                    z = lineParts.at(i).toDouble();
                    zB = true;
                }

                else if(lineParts.at(i).at(0) == QString("E") || lineParts.at(i).at(0) == QString("e")){

                    lineParts[i].remove(0, 1);
                    e = lineParts.at(i).toDouble();
                    eB = true;
                }

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        emit g92(xB, yB, zB, eB, x, y, z, e);
    }

    //check if the command is m0
    else if(lineParts.at(0) == QString("M0") || lineParts.at(0) == QString("m0")){

        int p = 0;
        int s = 0;

        if(lineParts.count() > 1){

            for(int i = 1; i < lineParts.count();i++){

                if(lineParts.at(i).at(0) == QString("P") || lineParts.at(i).at(0) == QString("p")){

                    lineParts[i].remove(0, 1);
                    p = lineParts.at(i).toInt();
                }

                else if(lineParts.at(i).at(0) == QString("S") || lineParts.at(i).at(0) == QString("s")){

                    lineParts[i].remove(0, 1);
                    s = lineParts.at(i).toInt();
                }

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        emit m0(p, s);
    }

    //check if the command is m1
    else if(lineParts.at(0) == QString("M1") || lineParts.at(0) == QString("m1")){

        emit m1();
    }

    //check if the command is m82
    else if(lineParts.at(0) == QString("M82") || lineParts.at(0) == QString("m82")){

        emit m82();
    }

    //check if the command is m83
    else if(lineParts.at(0) == QString("M83") || lineParts.at(0) == QString("m83")){

        emit m83();
    }

    //check if the command is m104
    else if(lineParts.at(0) == QString("M104") || lineParts.at(0) == QString("m104")){

        int s = 0;

        if(lineParts.count() > 1){

            for(int i = 1;i < lineParts.count();i++){

                if(lineParts.at(i).at(0) == QString("S") || lineParts.at(i).at(0) == QString("s")){

                    lineParts[i].remove(0, 1);
                    s = lineParts.at(i).toInt();
                }

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit m104(s);
    }

    //check if the command is m106
    else if(lineParts.at(0) == QString("M106") || lineParts.at(0) == QString("m106")){

        int p = 0;
        int s = 0;

        if(lineParts.count() > 1){

            for(int i = 1;i < lineParts.count();i++){

                if(lineParts.at(i).at(0) == QString("P") || lineParts.at(i).at(0) == QString("p")){

                    lineParts[i].remove(0, 1);
                    p = lineParts.at(i).toInt();
                }

                else if(lineParts.at(i).at(0) == QString("S") || lineParts.at(i).at(0) == QString("s")){

                    lineParts[i].remove(0, 1);
                    s = lineParts.at(i).toInt();
                }

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit m106(p, s);
    }

    //check if the command is m107
    else if(lineParts.at(0) == QString("M107") || lineParts.at(0) == QString("m107")){

        emit m107();
    }

    //check if the command is m109
    else if(lineParts.at(0) == QString("M109") || lineParts.at(0) == QString("m109")){

        int s = -1;
        int r = -1;

        if(lineParts.count() > 1){

            for(int i = 1;i < lineParts.count();i++){

                if(lineParts.at(i).at(0) == QString("S") || lineParts.at(i).at(0) == QString("s")){

                    lineParts[i].remove(0, 1);
                    s = lineParts.at(i).toInt();
                }

                else if(lineParts.at(i).at(0) == QString("R") || lineParts.at(i).at(0) == QString("r")){

                    lineParts[i].remove(0, 1);
                    r = lineParts.at(i).toInt();
                }

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit m109(s, r);
    }

    //check if the command is m110
    else if(lineParts.at(0) == QString("M110") || lineParts.at(0) == QString("m110")){

        int n = 0;

        if(lineParts.count() > 1){

            for(int i = 1;i < lineParts.count();i++){

                if(lineParts.at(i).at(0) == QString("N") || lineParts.at(i).at(0) == QString("n")){

                    lineParts[i].remove(0, 1);
                    n = lineParts.at(i).toInt();
                }
#
                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit m110(n);
    }

    //check if the command is m112
    else if(lineParts.at(0) == QString("M112") || lineParts.at(0) == QString("m112")){

        emit m112();
    }

    //check if the command is m116
    else if(lineParts.at(0) == QString("M116") || lineParts.at(0) == QString("m116")){

        int p = -1;
        int h = -1;

        if(lineParts.count() > 1){

            for(int i = 1;i < lineParts.count();i++){

                if(lineParts.at(i).at(0) == QString("P") || lineParts.at(i).at(0) == QString("p")){

                    lineParts[i].remove(0, 1);
                    p = lineParts.at(i).toInt();
                }

                else if(lineParts.at(i).at(0) == QString("H") || lineParts.at(i).at(0) == QString("h")){

                    lineParts[i].remove(0, 1);
                    h = lineParts.at(i).toInt();
                }

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        emit m116(p, h);
    }

    //check if the command is m140
    else if(lineParts.at(0) == QString("M140") || lineParts.at(0) == QString("m140")){

        int s = 0;

        if(lineParts.count() > 1){

            for(int i = 1;i < lineParts.count();i++){

                if(lineParts.at(i).at(0) == QString("S") || lineParts.at(i).at(0) == QString("s")){

                    lineParts[i].remove(0, 1);
                    s = lineParts.at(i).toInt();
                }

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit m140(s);
    }

    //check if the command is m190
    else if(lineParts.at(0) == QString("M190") || lineParts.at(0) == QString("m190")){

        int s = 0;

        if(lineParts.count() > 1){

            for(int i = 1;i < lineParts.count();i++){

                if(lineParts.at(i).at(0) == QString("S") || lineParts.at(i).at(0) == QString("s")){

                    lineParts[i].remove(0, 1);
                    s = lineParts.at(i).toInt();
                }

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit m190(s);
    }

    //check if the command is m200
    else if(lineParts.at(0) == QString("M200") || lineParts.at(0) == QString("m200")){

        qreal d = 0;

        if(lineParts.count() > 1){

            for(int i = 1;i < lineParts.count();i++){

                if(lineParts.at(i).at(0) == QString("D") || lineParts.at(i).at(0) == QString("d")){

                    lineParts[i].remove(0, 1);
                    d = lineParts.at(i).toDouble();
                }

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit m200(d);
    }

    //check if the command is m201
    else if(lineParts.at(0) == QString("M201") || lineParts.at(0) == QString("m201")){

        qreal x = -1.0;
        qreal y = -1.0;
        qreal z = -1.0;
        qreal e = -1.0;

        if(lineParts.count() > 1){

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

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit m201(x, y, z, e);
    }

    //check if the command is m202
    else if(lineParts.at(0) == QString("M202") || lineParts.at(0) == QString("m202")){

        qreal x = -1.0;
        qreal y = -1.0;
        qreal z = -1.0;
        qreal e = -1.0;

        if(lineParts.count() > 1){

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

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit m202(x, y, z, e);
    }

    //check if the command is m203
    else if(lineParts.at(0) == QString("M203") || lineParts.at(0) == QString("m203")){

        qreal x = -1.0;
        qreal y = -1.0;
        qreal z = -1.0;
        qreal e = -1.0;

        if(lineParts.count() > 1){

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

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit m203(x, y, z, e);
    }

    //check if the command is m204
    else if(lineParts.at(0) == QString("M204") || lineParts.at(0) == QString("m204")){

        qreal p = -1;
        qreal t = -1;

        if(lineParts.count() > 1){

            for(int i = 1;i < lineParts.count();i++){

                if(lineParts.at(i).at(0) == QString("P") || lineParts.at(i).at(0) == QString("p")){

                    lineParts[i].remove(0, 1);
                    p = lineParts.at(i).toDouble();
                }

                else if(lineParts.at(i).at(0) == QString("T") || lineParts.at(i).at(0) == QString("t")){

                    lineParts[i].remove(0, 1);
                    t = lineParts.at(i).toDouble();
                }

                else if(lineParts.at(i).at(0) == QString(";")){

                    for(int n = i;n < lineParts.count();n++){

                        lineParts.removeAt(i + n);
                    }
                }

                else{

                    emit error(QString("Invalid command in line %1").arg(lineNumber));
                    return false;
                }
            }
        }

        else{

            emit error(QString("Invalid command in line %1").arg(lineNumber));
            return false;
        }

        emit m204(p, t);
    }

    //check if the command is m400
    else if(lineParts.at(0) == QString("M400") || lineParts.at(0) == QString("m400")){

        emit m400();
    }

    else if(lineParts.at(0) == QString(";")){

        for(int n = 0;n < lineParts.count();n++){

            lineParts.removeAt(n);
        }
    }

    else{

        emit error(QString("Invalid command in line %1").arg(lineNumber));
        return false;
    }

    return true;
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
