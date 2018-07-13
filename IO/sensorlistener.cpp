#include "sensorlistener.h"

SensorListener::SensorListener(QObject *parent) : QObject(parent)
{

    m_values = new QList<int>;
}

SensorListener::~SensorListener()
{

    delete m_values;

    m_values = NULL;
}

void SensorListener::checkChanged(IOController *iOController)
{

    if(iOController->readVariableValue("xAxisPEndstop") == 1){

        bool ok;
        emit logEntry(QString("Positive endstop on the x-axis hit"), QString("0x05FFFF").toInt(&ok, 16));
        emit xAxisPositiveEndstopHit();
    }

    if(iOController->readVariableValue("xAxisNEndstop") == 1){

        bool ok;
        emit logEntry(QString("Negative endstop on the x-axis hit"), QString("0x05FFFE").toInt(&ok, 16));
        emit xAxisNegativeEndstopHit();
    }

    if(iOController->readVariableValue("yAxisPEndstop") == 1){

        bool ok;
        emit logEntry(QString("Positive endstop on the y-axis hit"), QString("0x05FFFD").toInt(&ok, 16));
        emit yAxisPositiveEndstopHit();
    }

    if(iOController->readVariableValue("yAxisNEndstop") == 1){

        bool ok;
        emit logEntry(QString("Negative endstop on the y-axis hit"), QString("0x05FFFC").toInt(&ok, 16));
        emit yAxisNegativeEndstopHit();
    }

    if(iOController->readVariableValue("zAxisPEndstop") == 1){

        bool ok;
        emit logEntry(QString("Positive endstop on the z-axis hit"), QString("0x05FFFB").toInt(&ok, 16));
        emit zAxisPositiveEndstopHit();
    }

    if(iOController->readVariableValue("zAxisNEndstop") == 1){

        bool ok;
        emit logEntry(QString("Negative endstop on the z-axis hit"), QString("0x05FFFA").toInt(&ok, 16));
        emit zAxisNegativeEndstopHit();
    }
}
