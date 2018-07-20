#include "sensorlistener.h"

#define VALUES_LENGTH 2

SensorListener::SensorListener(QObject *parent) : QObject(parent)
{

    //initialising variables

    initialiseVariables();

    //logEntry

    //there to make the conversion from QString to int work
    bool ok;
    //emitting the logEntry, which is connected to the Logger
    emit logEntry(QString("SensorListener started successfully"), QString("0x050001").toInt(&ok, 10));
}

SensorListener::~SensorListener()
{

    //deleting pointers

    delete m_values;

    //setting pointers to null

    m_values = NULL;

    //logEntry

    //there to make the conversion from QString to int work
    bool ok;
    //emitting the logEntry, which is connected to the Logger
    emit logEntry(QString("SensorListener exited successfully"), QString("0x050000").toInt(&ok, 10));
}

//called by the loop in IOMainLoop, checks if the value of any sensor-related IO has been changed / has to be changed
//iOController is a pointer to the actual IOController to get access to the IO
void SensorListener::checkChanged(IOController *iOController)
{

    //checks if the XAxisPositiveEndstop was hit
    if(iOController->readVariableValue("xAxisPEndstop") == 1){

        //logEntry

        //there to make the conversion from QString to int work
        bool ok;
        //emitting the logEntry, which is connected to the Logger
        emit logEntry(QString("Positive endstop on the x-axis hit"), QString("0x05FFFF").toInt(&ok, 16));
        //emitting signal that the XAxisPositiveEndstop was hit
        emit xAxisPositiveEndstopHit();
    }

    //checks if the XAxisNegativeEndstop was hit
    if(iOController->readVariableValue("xAxisNEndstop") == 1){

        //logEntry

        //there to make the conversion from QString to int work
        bool ok;
        //emitting the logEntry, which is connected to the Logger
        emit logEntry(QString("Negative endstop on the x-axis hit"), QString("0x05FFFE").toInt(&ok, 16));
        //emitting signal that the XAxisNegativeEndstop
        emit xAxisNegativeEndstopHit();
    }

    //checks if the YAxisPositiveEndstop was hit
    if(iOController->readVariableValue("yAxisPEndstop") == 1){

        //logEntry

        //there to make the conversion from QString to int work
        bool ok;
        //emitting the logEntry, which is connected to the Logger
        emit logEntry(QString("Positive endstop on the y-axis hit"), QString("0x05FFFD").toInt(&ok, 16));
        //emitting signal that the YAxisPositiveEndstop
        emit yAxisPositiveEndstopHit();
    }

    //checks if the YAxisNegativeEndstop was hit
    if(iOController->readVariableValue("yAxisNEndstop") == 1){

        //logEntry

        //there to make the conversion from QString to int work
        bool ok;
        //emitting the logEntry, which is connected to the Logger
        emit logEntry(QString("Negative endstop on the y-axis hit"), QString("0x05FFFC").toInt(&ok, 16));
        //emitting signal that the YAxisNegativeEndstop
        emit yAxisNegativeEndstopHit();
    }

    //checks if the ZAxisPositiveEndstop was hit
    if(iOController->readVariableValue("zAxisPEndstop") == 1){

        //logEntry

        //there to make the conversion from QString to int work
        bool ok;
        //emitting the logEntry, which is connected to the Logger
        emit logEntry(QString("Positive endstop on the z-axis hit"), QString("0x05FFFB").toInt(&ok, 16));
        //emitting signal that the ZAxisPositiveEndstop
        emit zAxisPositiveEndstopHit();
    }

    //checks if the ZAxisNegativeEndstop was hit
    if(iOController->readVariableValue("zAxisNEndstop") == 1){

        //logEntry

        //there to make the conversion from QString to int work
        bool ok;
        //emitting the logEntry, which is connected to the Logger
        emit logEntry(QString("Negative endstop on the z-axis hit"), QString("0x05FFFA").toInt(&ok, 16));
        //emitting signal that the ZAxisNegativeEndstop
        emit zAxisNegativeEndstopHit();
    }

    if(iOController->readVariableValue(QString("hotEndTemp")) != m_values->at(0)){

        (*m_values)[0] = iOController->readVariableValue(QString("hotEndTemp"));
        emit hotEndTempChanged(m_values->at(0));
    }

    if(iOController->readVariableValue(QString("bedTemp")) != m_values->at(1)){

        (*m_values)[1] = iOController->readVariableValue(QString("bedTemp"));
        emit bedTempChanged(m_values->at(1));
    }
}

int SensorListener::hotEndTemp()
{

    return m_values->at(0);
}

int SensorListener::bedTemp()
{

    return m_values->at(1);
}

void SensorListener::initialiseVariables()
{

    //initialising pointers

    m_values = new QList<int>;

    for(int i = 0;i < VALUES_LENGTH;i++){

        m_values->append(0);
    }
}
