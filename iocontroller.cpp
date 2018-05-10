#include "iocontroller.h"

IOController::IOController(QObject *parent) : QObject(parent)
{

    m_pinValues = new QList<int>;
    m_settings = new QSettings(this);


    //wiringPiSetup();

    pinSetup();
}

IOController::~IOController()
{

    delete m_pinValues;

    m_pinValues = NULL;
}

void IOController::setPinValue(int pin, int value)
{


}

int IOController::pinValue(int pin)
{

}

void IOController::mainLoop()
{

    while(true){

    }
}

void IOController::pinSetup()
{

    QList<QVariant> pinModes = m_settings->value("io/pinModes").toList();

    for(int i = 0;i < pinModes.count();i++){

        if(pinModes.at(i).toInt() == 0 && m_translationMatrix[i] > -1){

            //pinMode(m_translationMatrix[i], INPUT);
        }

        else if(pinModes.at(i).toInt() == 1 && m_translationMatrix[i] > -1){

            //pinMode(m_translationMatrix[i], OUTPUT);
        }

        else if(pinModes.at(i).toInt() == 2 && m_translationMatrix[i] > -1){

            //pinMode(m_translationMatrix[i], PWM_OUTPUT);
        }

        else if(pinModes.at(i).toInt() == 3 && m_translationMatrix[i] > -1){

            //pinMode(m_translationMatrix[i], GPIO_CLOCK);
        }

        else{

            emit error("Wrong pinMode");
        }
    }
}
