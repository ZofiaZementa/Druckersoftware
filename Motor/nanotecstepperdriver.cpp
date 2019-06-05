#include "nanotecstepperdriver.h"

NanotecStepperDriver::NanotecStepperDriver(QObject *parent) : QObject(parent)
{

}

NanotecStepperDriver::~NanotecStepperDriver()
{

}

void NanotecStepperDriver::setStepSize(QList<int> sizes, int priority)
{

    if(sizes.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setStepSize(m_motorMap->at(i), sizes.at(i), priority);
        }
    }

    else{

        for(int i = 0;i < sizes.count(); i++){

            setStepSize(m_motorMap->at(i), sizes.at(i), priority);
        }
    }
}

void NanotecStepperDriver::setStepSize(int adress, int size, int priority)
{

    sendData(QString("#%1g%2\r").arg(adress).arg(size), priority);
}

void NanotecStepperDriver::setStepSizeAll(int size, int priority)
{

    sendData(QString("#*g%1\r").arg(size), priority);
}

void NanotecStepperDriver::setMotorType(QList<int> types)
{

    if(types.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setMotorType(m_motorMap->at(i), types.at(i), priority);
        }
    }

    else{

        for(int i = 0;i < types.count(); i++){

            setMotorType(m_motorMap->at(i), types.at(i), priority);
        }
    }
}

void NanotecStepperDriver::setMotorType(int adress, int type, int priority)
{

    sendData(QString("#%1:CL_motor_type=%2\r").arg(adress).arg(type), priority);
}

void NanotecStepperDriver::setMotorTypeAll(int type)
{

    sendData(QString("#*:CL_motor_type=%1\r").arg(type), priority);
}

void NanotecStepperDriver::setBacklash(QList<int> vals)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setBacklash(m_motorMap->at(i), vals.at(i), priority);
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setBacklash(m_motorMap->at(i), vals.at(i), priority);
        }
    }
}

void NanotecStepperDriver::setBacklash(int adress, int val, int priority)
{

    sendData(QString("#%1z%2\r").arg(adress).arg(val), priority);
}

void NanotecStepperDriver::setBacklashAll(int val, int priority)
{

    sendData(QString("#*z%1\r").arg(val), priority);
}

void NanotecStepperDriver::setPhasecurrent(QList<int> vals, int priority)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setPhasecurrent(m_motorMap->at(i), vals.at(i), priority);
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setPhasecurrent(m_motorMap->at(i), vals.at(i), priority);
        }
    }
}

void NanotecStepperDriver::setPhasecurrent(int adress, int val, int priority)
{

    sendData(QString("#%1i%2\r").arg(adress).arg(val), priority);
}

void NanotecStepperDriver::setPhasecurrentAll(int val, int priority)
{

    sendData(QString("#*i%1\r").arg(val), priority);
}

void NanotecStepperDriver::setHaltPhasecurrent(QList<int> vals, int priority)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setHaltPhasecurrent(m_motorMap->at(i), vals.at(i), priority);
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setHaltPhasecurrent(m_motorMap->at(i), vals.at(i), priority);
        }
    }
}

void NanotecStepperDriver::setHaltPhasecurrent(int adress, int val, int priority)
{

    sendData(QString("#%1r%2\r").arg(adress).arg(val), priority);
}

void NanotecStepperDriver::setHaltPhasecurrentAll(int val, int priority)
{

    sendData(QString("#*r%1\r").arg(val), priority);
}

void NanotecStepperDriver::setStopDecceleration(QList<int> vals, int priority)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setStopDecceleration(m_motorMap->at(i), vals.at(i), priority);
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setStopDecceleration(m_motorMap->at(i), vals.at(i), priority);
        }
    }
}

void NanotecStepperDriver::setStopDecceleration(int adress, int val, int priority)
{

    sendData(QString("#%1H%2\r").arg(adress).arg(val), priority);
}

void NanotecStepperDriver::setStopDeccelerationAll(int val, int priority)
{

    sendData(QString("#*H%1\r").arg(val), priority);
}

void NanotecStepperDriver::startMotor(QList<bool> go, int priority)
{

    if(go.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            if(go.at(i) == true){

                startMotor(m_motorMap->at(i), priority);
            }
        }
    }

    else{

        for(int i = 0;i < go.count(); i++){

            if(go.at(i) == true){

                startMotor(m_motorMap->at(i), priority);
            }
        }
    }
}

void NanotecStepperDriver::startMotor(int adress, int priority)
{

    sendData(QString("#%1A\r").arg(adress), priority);
}

void NanotecStepperDriver::startMotorAll(int priority)
{

    sendData(QString("#*A\r"), priority);
}

void NanotecStepperDriver::stopMotor(QList<bool> go, int priority)
{

    if(go.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            if(go.at(i) == true){

                stopMotor(m_motorMap->at(i), priority);
            }
        }
    }

    else{

        for(int i = 0;i < go.count(); i++){

            if(go.at(i) == true){

                stopMotor(m_motorMap->at(i), priority);
            }
        }
    }
}

void NanotecStepperDriver::stopMotor(int adress, int priority)
{

    sendData(QString("#%1S1\r").arg(adress), priority);
}

void NanotecStepperDriver::stopMotorAll(int priority)
{

    sendData(QString("#*S1\r"), priority);
}

void NanotecStepperDriver::quickStopMotorAll(int priority)
{

    if(go.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            if(go.at(i) == true){

                quickStopMotor(m_motorMap->at(i), priority);
            }
        }
    }

    else{

        for(int i = 0;i < go.count(); i++){

            if(go.at(i) == true){

                quickStopMotor(m_motorMap->at(i), priority);
            }
        }
    }
}

void NanotecStepperDriver::quickStopMotor(int adress, int priority)
{

    sendData(QString("#%1S\r").arg(adress), priority);
}

void NanotecStepperDriver::quickStopMotor(QList<bool> go, int priority)
{

    sendData(QString("#*S\r"), priority);
}

void NanotecStepperDriver::emergencyStop(int priority)
{

    sendData(QString("#*S\r"), priority);
}

void NanotecStepperDriver::setPositioningmode(QList<int> modes, int priority)
{

    if(modes.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setPositioningmode(m_motorMap->at(i), modes.at(i), priority);
        }
    }

    else{

        for(int i = 0;i < modes.count(); i++){

            setPositioningmode(m_motorMap->at(i), modes.at(i), priority);
        }
    }
}

void NanotecStepperDriver::setPositioningmode(int adress, int mode, int priority)
{

    sendData(QString("#%1p%2\r").arg(adress).arg(mode), priority);
}

void NanotecStepperDriver::setPositioningmodeAll(int mode, int priority)
{

    sendData(QString("#*p%1\r").arg(mode), priority);
}

void NanotecStepperDriver::setWay(QList<int> ways, int priority)
{

    if(ways.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setWay(m_motorMap->at(i), ways.at(i), priority);
        }
    }

    else{

        for(int i = 0;i < ways.count(); i++){

            setWay(m_motorMap->at(i), ways.at(i), priority);
        }
    }
}

void NanotecStepperDriver::setWay(int adress, int way, int priority)
{

    sendData(QString("#%1s%2\r").arg(adress).arg(way), priority);
}

void NanotecStepperDriver::setWayAll(int way, int priority)
{

    sendData(QString("#*s%1\r").arg(way), priority);
}

void NanotecStepperDriver::setMinFrequenzy(QList<int> vals, int priority)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setMinFrequenzy(m_motorMap->at(i), vals.at(i), priority);
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setMinFrequenzy(m_motorMap->at(i), vals.at(i), priority);
        }
    }
}

void NanotecStepperDriver::setMinFrequenzy(int adress, int val, int priority)
{

    sendData(QString("#%1u%2\r").arg(adress).arg(val), priority);
}

void NanotecStepperDriver::setMinFrequenzyAll(int val, int priority)
{

    sendData(QString("#*s%1\r").arg(val), priority);
}

void NanotecStepperDriver::setMaxFrequenzy(QList<int> vals, int priority)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setMaxFrequenzy(m_motorMap->at(i), vals.at(i), priority);
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setMaxFrequenzy(m_motorMap->at(i), vals.at(i), priority);
        }
    }
}

void NanotecStepperDriver::setMaxFrequenzy(int adress, int val, int priority)
{

    sendData(QString("#%1o%2\r").arg(adress).arg(val), priority);
}

void NanotecStepperDriver::setMaxFrequenzyAll(int val, int priority)
{

    sendData(QString("#*o%1\r").arg(val), priority);
}

void NanotecStepperDriver::setAccelerationCurve(QList<int> vals, int priority)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setAccelerationCurve(m_motorMap->at(i), vals.at(i), priority);
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setAccelerationCurve(m_motorMap->at(i), vals.at(i), priority);
        }
    }
}

void NanotecStepperDriver::setAccelerationCurve(int adress, int val, int priority)
{

    sendData(QString("#%1b%2\r").arg(adress).arg(val), priority);
}

void NanotecStepperDriver::setAccelerationCurveAll(int val, int priority)
{

    sendData(QString("#*b%1\r").arg(val), priority);
}

void NanotecStepperDriver::setDeccelerationCurve(QList<int> vals, int priority)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setDeccelerationCurve(m_motorMap->at(i), vals.at(i), priority);
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setDeccelerationCurve(m_motorMap->at(i), vals.at(i), priority);
        }
    }
}

void NanotecStepperDriver::setDeccelerationCurve(int adress, int val, int priority)
{

    sendData(QString("#%1B%2\r").arg(adress).arg(val), priority);
}

void NanotecStepperDriver::setDeccelerationCurveAll(int val, int priority)
{

    sendData(QString("#*B%1\r").arg(val), priority);
}

void NanotecStepperDriver::setTurningdirection(QList<bool> vals, int priority)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setTurningdirection(m_motorMap->at(i), vals.at(i), priority);
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setTurningdirection(m_motorMap->at(i), vals.at(i), priority);
        }
    }
}

void NanotecStepperDriver::setTurningdirection(int adress, bool val, int priority)
{

    if(val == false){

        sendData(QString("#%1d0\r").arg(adress), priority);
    }

    else{

        sendData(QString("#%1d1\r").arg(adress), priority);
    }
}

void NanotecStepperDriver::setTurningdirectionAll(bool val, int priority)
{

    if(val == false){

        sendData(QString("#*d0\r"), priority);
    }

    else{

        sendData(QString("#*d1\r"), priority);
    }
}

void NanotecStepperDriver::setAccelerationJolt(QList<int> vals, int priority)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setAccelerationJolt(m_motorMap->at(i), vals.at(i), priority);
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setAccelerationJolt(m_motorMap->at(i), vals.at(i), priority);
        }
    }
}

void NanotecStepperDriver::setAccelerationJolt(int adress, int val, int priority)
{

    sendData(QString("#%1:b%2\r").arg(adress).arg(val), priority);
}

void NanotecStepperDriver::setAccelerationJoltAll(int val, int priority)
{

    sendData(QString("#*:b%1\r").arg(val), priority);
}

void NanotecStepperDriver::setDeccelerationJolt(QList<int> vals, int priority)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setDeccelerationJolt(m_motorMap->at(i), vals.at(i), priority);
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setDeccelerationJolt(m_motorMap->at(i), vals.at(i), priority);
        }
    }
}

void NanotecStepperDriver::setDeccelerationJolt(int adress, int val, int priority)
{

    sendData(QString("#%1:B%2\r").arg(adress).arg(val), priority);
}

void NanotecStepperDriver::setDeccelerationJoltAll(int val, int priority)
{

    sendData(QString("#*:B%1\r").arg(val), priority);
}

void NanotecStepperDriver::increaseRPM(QList<bool> go, int priority)
{

    if(go.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            if(go.at(i) == true){

                increaseRPM(m_motorMap->at(i), priority);
            }
        }
    }

    else{

        for(int i = 0;i < go.count(); i++){

            if(go.at(i) == true){

                increaseRPM(m_motorMap->at(i), priority);
            }
        }
    }
}

void NanotecStepperDriver::increaseRPM(int adress, int priority)
{

    sendData(QString("#%1+\r").arg(adress), priority);
}

void NanotecStepperDriver::increaseRPMAll(int priority)
{

    sendData(QString("#*+\r"), priority);
}

void NanotecStepperDriver::decreaseRPM(QList<bool> go, int priority)
{

    if(go.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            if(go.at(i) == true){

                decreaseRPM(m_motorMap->at(i), priority);
            }
        }
    }

    else{

        for(int i = 0;i < go.count(); i++){

            if(go.at(i) == true){

                decreaseRPM(m_motorMap->at(i), priority);
            }
        }
    }
}

void NanotecStepperDriver::decreaseRPM(int adress, int priority)
{

    sendData(QString("#%1-\r").arg(adress), priority);
}

void NanotecStepperDriver::decreaseRPMAll(int priority)
{

    sendData(QString("#*-\r"), priority);
}

void NanotecStepperDriver::setMotorCount(int i)
{

    *m_motorCount = i;
}

int NanotecStepperDriver::motorCount()
{

    return *m_motorCount;
}

void NanotecStepperDriver::setMotorAdressMap(QList<int> adressmap)
{

    *m_motorMap = adressmap;
}

QList<int> NanotecStepperDriver::motorMap()
{
    return *m_motorMap;
}

void NanotecStepperDriver::resetMotorMap()
{

    m_motorMap->clear();

    for(int i = 0;i < 256;i++){

        m_motorMap->append(i + 1);
    }
}

void NanotecStepperDriver::getPosition(QList<bool> ok, int priority)
{

    if(ok.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            if(ok.at(i) == true){

                getPosition(m_motorMap->at(i), priority);
            }
        }
    }

    else{

        for(int i = 0;i < ok.count(); i++){

            if(ok.at(i) == true){

                getPosition(m_motorMap->at(i), priority);
            }
        }
    }
}

void NanotecStepperDriver::getPosition(int adress, int priority)
{

    sendData(QString("#%1C\r").arg(adress), priority);
}

void NanotecStepperDriver::getPositionAll(int priority)
{

    sendData(QString("#*C\r"), priority);
}

void NanotecStepperDriver::getTemperature(QList<bool> ok, int priority)
{

    if(ok.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            if(ok.at(i) == true){

                getTemperature(m_motorMap->at(i), priority);
            }
        }
    }

    else{

        for(int i = 0;i < ok.count(); i++){

            if(ok.at(i) == true){

                getTemperature(m_motorMap->at(i), priority);
            }
        }
    }
}

void NanotecStepperDriver::getTemperature(int adress, int priority)
{

    sendData(QString("#%1:temp_adc\r").arg(adress), priority);
}

void NanotecStepperDriver::getTemperatureAll(int priority)
{

    sendData(QString("#*:temp_adc\r"), priority);
}

void NanotecStepperDriver::getRPM(QList<bool> ok, int priority)
{

    if(ok.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            if(ok.at(i) == true){

                getRPM(m_motorMap->at(i), priority);
            }
        }
    }

    else{

        for(int i = 0;i < ok.count(); i++){

            if(ok.at(i) == true){

                getRPM(m_motorMap->at(i), priority);
            }
        }
    }
}

void NanotecStepperDriver::getRPM(int adress, int priority)
{

    sendData(QString("#%1:v\r").arg(adress), priority);
}

void NanotecStepperDriver::getRPMAll(int priority, int priority)
{

    sendData(QString("#*:v\r"), priority);
}

void NanotecStepperDriver::receive(QByteArray data)
{

    QString dataString = QString(data);
    int adress = removeAdress(&dataString);

    if(dataString.contains(QString("C")) == true){

        bool ok;
        emit position(adress, dataString.mid(1, dataString.count() - 2).toInt(&ok, 10));
        return;
    }

    else if(dataString.contains(QString(":temp_adc")) == true){

        bool ok;
        emit temperature(adress, dataString.mid(9, dataString.count() - 10).toInt(&ok, 10));
        return;
    }

    else if(dataString.contains(QString(":v")) == true){

        bool ok;
        emit rpm(adress, dataString.mid(2, dataString.count() - 3).toInt(&ok, 10));
    }
}

void NanotecStepperDriver::sendData(QString data, int priority)
{

    emit send(data.toLatin1(), priority);
}

int NanotecStepperDriver::removeAdress(QString *data)
{

    QString adress;

    if(data->contains(QChar(42)) == false){

        while(data->at(0).unicode() > 47 && data->at(0).unicode() < 58){

            adress.append(data->remove(0, 1));
        }

        bool ok;
        return adress.toInt(&ok, 10);
    }

    return -1;
}
