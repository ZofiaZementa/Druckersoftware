#include "lightingcontroller.h"


LightingController::LightingController(QObject *parent) : QObject(parent)
{

    m_values = new QList<int>;
}

LightingController::~LightingController()
{
    delete m_values;

    m_values = NULL;
}

void LightingController::checkChanged(IOController *iOController)
{

    if(iOController->readVariableValue(QString("RevPiLED")) != m_values->at(0)){

        iOController->writeVariableValue(QString("RevPiLED"), m_values->at(0));

        int a1 = m_values->at(0);

        a1 = a1 - (a1 / 4 * 4);
        emit statusLEDChanged(a1, m_values->at(0) - a1);
    }
}

void LightingController::setStatusLED(int a1, int a2)
{


    (*m_values)[1] = a1 + (a2 * 4);
}
