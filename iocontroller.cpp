#include "iocontroller.h"

IOController::IOController(QObject *parent) : QObject(parent)
{

    m_pinValues = new QList<int>;
    m_settings = new QSettings(this);


    for(int i = 0;i < 28;i++){

        m_pinValues->append(0);
    }

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

    if(pin >= 2 && pin <= 27){

        if(m_settings->value("io/pinModes").toList().at(pin).toInt() == 0){

            if(value == 0){

                //digitalWrite(m_translationMatrix[pin], LOW);
            }

            else if(value == 1){

                //digitalWrite(m_translationMatrix[pin], HIGH);
            }
        }
    }

    else{

        emit error(QString("Pin does not exist"));
    }
}

int IOController::pinValue(int pin)
{

    if(pin >= 2 && pin <= 27){

        if(digitalRead(m_translationMatrix[pin]) == LOW){

            if(m_pinValues->at(pin) != 0){

                (*m_pinValues)[pin] = 0;
                emitPinChanged(pin);
            }

            return 0;
        }

        else if(digitalRead(m_translationMatrix[pin]) == HIGH){

            if(m_pinValues->at(pin) != 1){

                (*m_pinValues)[pin] = 1;
                emitPinChanged(pin);
            }

            return 1;
        }
    }

    else{

        emit error(QString("Pin does not exist"));
    }
}

void IOController::mainLoop()
{

    while(true){

        checkPins();
    }
}

void IOController::checkPins()
{

    for(int i = 2;i < 28;i++){

        pinValue(i);
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
            return;
        }
    }
}

void IOController::emitPinChanged(int pin)
{
    switch(pin){

    case 2:{

        emit pin02ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 3:{

        emit pin03ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 4:{

        emit pin04ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 5:{

        emit pin05ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 6:{

        emit pin06ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 7:{

        emit pin07ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 8:{

        emit pin08ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 9:{

        emit pin09ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 10:{

        emit pin10ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 11:{

        emit pin11ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 12:{

        emit pin12ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 13:{

        emit pin13ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 14:{

        emit pin14ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 15:{

        emit pin15ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 16:{

        emit pin16ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 17:{

        emit pin17ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 18:{

        emit pin18ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 19:{

        emit pin19ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 20:{

        emit pin20ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 21:{

        emit pin21ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 22:{

        emit pin22ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 23:{

        emit pin23ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 24:{

        emit pin24ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 25:{

        emit pin25ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 26:{

        emit pin26ValueChanged(m_pinValues->at(pin));
        break;
    }

    case 27:{

        emit pin27ValueChanged(m_pinValues->at(pin));
        break;
    }

    default:{

        emit error(QString("Pin does not exist"));
    }

    }
}
