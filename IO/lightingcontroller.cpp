#include "lightingcontroller.h"


LightingController::LightingController(QObject *parent) : QObject(parent)
{

    //intitialising variables

    initialiseValues();

    //logEntry

    //there to make the conversion from QString to int work
    bool ok;
    //emitting the logEntry, which is connected to the Logger
    emit logEntry(QString("LightingController started successfully"), QString("0x080001").toInt(&ok, 10));
}

LightingController::~LightingController()
{

    //deleting pointers

    delete m_values;

    //setting pointers to null

    m_values = NULL;

    //logEntry

    //there to make the conversion from QString to int work
    bool ok;
    //emitting the logEntry, which is connected to the Logger
    emit logEntry(QString("LightingController exited successfully"), QString("0x080000").toInt(&ok, 10));
}

//called by the loop in IOMainLoop, checks if the value of any lighting-related IO has been changed / has to be changed
//iOController is a pointer to the actual IOController to get access to the IO
void LightingController::checkChanged(IOController *iOController)
{

    //checks if the value of the Status LEDs of the RevPi has been set to another value in m_values
    //triggered if the value in m_values is different than the current value in the programmer
    if(iOController->readVariableValue(QString("RevPiLED")) != m_values->at(0)){

        //sets the current programmervalue to the coreresponding value in m_values
        iOController->writeVariableValue(QString("RevPiLED"), m_values->at(0));

        //defines a1 and initialises it as the current value in m_values
        int a1 = m_values->at(0);

        //calculates the actual value of the A1 LED out of the value in m_values
        a1 = a1 - (a1 / 4 * 4);
        //emits that the statusLED has changed
        emit statusLEDChanged(a1, m_values->at(0) - a1);
    }
}

//sets the status LEDs A1 and A2 to the values a1 and a2
//0 is off, 1 is red, 2 is green and 3 is orange
void LightingController::setStatusLED(int a1, int a2)
{

    //calculates the actual byte-value out of a1 and a2, which is to be written into the programmer
    (*m_values)[0] = a1 + (a2 * 4);

    //logEntry

    //there to make the conversion from QString to int work
    bool ok;
    //emitting the logEntry, which is connected to the Logger
    emit logEntry(QString("A1 changed to %1 and A2 changed to %2").arg(a1).arg(a2), QString("0x080002").toInt(&ok, 10));
}

//initialises m_valuess
void LightingController::initialiseValues()
{

    //initialises m_values
    m_values = new QList<int>;

    //appends a 0 to m_values
    m_values->append(0);
}
