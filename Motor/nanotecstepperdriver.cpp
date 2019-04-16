#include "nanotecstepperdriver.h"

NanotecStepperDriver::NanotecStepperDriver(QObject *parent) : QObject(parent)
{

}

NanotecStepperDriver::~NanotecStepperDriver()
{

}

void NanotecStepperDriver::setStepSize(QList<int> sizes)
{

    if(sizes.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setStepSize(m_motorMap->at(i), sizes.at(i));
        }
    }

    else{

        for(int i = 0;i < sizes.count(); i++){

            setStepSize(m_motorMap->at(i), sizes.at(i));
        }
    }
}

void NanotecStepperDriver::setStepSize(int adress, int size)
{

    sendData(QString("#%1g%2\r").arg(adress).arg(size));
}

void NanotecStepperDriver::setStepSizeAll(int size)
{

    sendData(QString("#*g%1\r").arg(size));
}

void NanotecStepperDriver::setMotorType(QList<int> types)
{

    if(types.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setMotorType(m_motorMap->at(i), types.at(i));
        }
    }

    else{

        for(int i = 0;i < types.count(); i++){

            setMotorType(m_motorMap->at(i), types.at(i));
        }
    }
}

void NanotecStepperDriver::setMotorType(int adress, int type)
{

    sendData(QString("#%1:CL_motor_type=%2\r").arg(adress).arg(type));
}

void NanotecStepperDriver::setMotorTypeAll(int type)
{

    sendData(QString("#*:CL_motor_type=%1\r").arg(type));
}

void NanotecStepperDriver::setBacklash(QList<int> vals)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setBacklash(m_motorMap->at(i), vals.at(i));
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setBacklash(m_motorMap->at(i), vals.at(i));
        }
    }
}

void NanotecStepperDriver::setBacklash(int adress, int val)
{

    sendData(QString("#%1z%2\r").arg(adress).arg(val));
}

void NanotecStepperDriver::setBacklashAll(int val)
{

    sendData(QString("#*z%1\r").arg(val));
}

void NanotecStepperDriver::setPhasecurrent(QList<int> vals)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setPhasecurrent(m_motorMap->at(i), vals.at(i));
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setPhasecurrent(m_motorMap->at(i), vals.at(i));
        }
    }
}

void NanotecStepperDriver::setPhasecurrent(int adress, int val)
{

    sendData(QString("#%1i%2\r").arg(adress).arg(val));
}

void NanotecStepperDriver::setPhasecurrentAll(int val)
{

    sendData(QString("#*i%1\r").arg(val));
}

void NanotecStepperDriver::setHaltPhasecurrent(QList<int> vals)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setHaltPhasecurrent(m_motorMap->at(i), vals.at(i));
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setHaltPhasecurrent(m_motorMap->at(i), vals.at(i));
        }
    }
}

void NanotecStepperDriver::setHaltPhasecurrent(int adress, int val)
{

    sendData(QString("#%1r%2\r").arg(adress).arg(val));
}

void NanotecStepperDriver::setHaltPhasecurrentAll(int val)
{

    sendData(QString("#*r%1\r").arg(val));
}

void NanotecStepperDriver::setStopDecceleration(QList<int> vals)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setStopDecceleration(m_motorMap->at(i), vals.at(i));
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setStopDecceleration(m_motorMap->at(i), vals.at(i));
        }
    }
}

void NanotecStepperDriver::setStopDecceleration(int adress, int val)
{

    sendData(QString("#%1H%2\r").arg(adress).arg(val));
}

void NanotecStepperDriver::setStopDeccelerationAll(int val)
{

    sendData(QString("#*H%1\r").arg(val));
}

void NanotecStepperDriver::startMotor(QList<bool> go)
{

    if(go.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            if(go.at(i) == true){

                startMotor(m_motorMap->at(i));
            }
        }
    }

    else{

        for(int i = 0;i < go.count(); i++){

            if(go.at(i) == true){

                startMotor(m_motorMap->at(i));
            }
        }
    }
}

void NanotecStepperDriver::startMotor(int adress)
{

    sendData(QString("#%1A\r").arg(adress));
}

void NanotecStepperDriver::startMotorAll()
{

    sendData(QString("#*A\r"));
}

void NanotecStepperDriver::stopMotor(QList<bool> go)
{

    if(go.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            if(go.at(i) == true){

                stopMotor(m_motorMap->at(i));
            }
        }
    }

    else{

        for(int i = 0;i < go.count(); i++){

            if(go.at(i) == true){

                stopMotor(m_motorMap->at(i));
            }
        }
    }
}

void NanotecStepperDriver::stopMotor(int adress)
{

    sendData(QString("#%1S\r").arg(adress));
}

void NanotecStepperDriver::stopMotorAll()
{

    sendData(QString("#*S\r"));
}

void NanotecStepperDriver::setPositioningmode(QList<int> modes)
{

    if(modes.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setPositioningmode(m_motorMap->at(i), modes.at(i));
        }
    }

    else{

        for(int i = 0;i < modes.count(); i++){

            setPositioningmode(m_motorMap->at(i), modes.at(i));
        }
    }
}

void NanotecStepperDriver::setPositioningmode(int adress, int mode)
{

    sendData(QString("#%1p%2\r").arg(adress).arg(mode));
}

void NanotecStepperDriver::setPositioningmodeAll(int mode)
{

    sendData(QString("#*p%1\r").arg(mode));
}

void NanotecStepperDriver::setWay(QList<int> ways)
{

    if(ways.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setWay(m_motorMap->at(i), ways.at(i));
        }
    }

    else{

        for(int i = 0;i < ways.count(); i++){

            setWay(m_motorMap->at(i), ways.at(i));
        }
    }
}

void NanotecStepperDriver::setWay(int adress, int way)
{

    sendData(QString("#%1s%2\r").arg(adress).arg(way));
}

void NanotecStepperDriver::setWayAll(int way)
{

    sendData(QString("#*s%1\r").arg(way));
}

void NanotecStepperDriver::setMinFrequenzy(QList<int> vals)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setMinFrequenzy(m_motorMap->at(i), vals.at(i));
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setMinFrequenzy(m_motorMap->at(i), vals.at(i));
        }
    }
}

void NanotecStepperDriver::setMinFrequenzy(int adress, int val)
{

    sendData(QString("#%1u%2\r").arg(adress).arg(val));
}

void NanotecStepperDriver::setMinFrequenzyAll(int val)
{

    sendData(QString("#*s%1\r").arg(val));
}

void NanotecStepperDriver::setMaxFrequenzy(QList<int> vals)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setMaxFrequenzy(m_motorMap->at(i), vals.at(i));
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setMaxFrequenzy(m_motorMap->at(i), vals.at(i));
        }
    }
}

void NanotecStepperDriver::setMaxFrequenzy(int adress, int val)
{

    sendData(QString("#%1o%2\r").arg(adress).arg(val));
}

void NanotecStepperDriver::setMaxFrequenzyAll(int val)
{

    sendData(QString("#*o%1\r").arg(val));
}

void NanotecStepperDriver::setAccelerationCurve(QList<int> vals)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setAccelerationCurve(m_motorMap->at(i), vals.at(i));
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setAccelerationCurve(m_motorMap->at(i), vals.at(i));
        }
    }
}

void NanotecStepperDriver::setAccelerationCurve(int adress, int val)
{

    sendData(QString("#%1b%2\r").arg(adress).arg(val));
}

void NanotecStepperDriver::setAccelerationCurveAll(int val)
{

    sendData(QString("#*b%1\r").arg(val));
}

void NanotecStepperDriver::setDeccelerationCurve(QList<int> vals)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setDeccelerationCurve(m_motorMap->at(i), vals.at(i));
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setDeccelerationCurve(m_motorMap->at(i), vals.at(i));
        }
    }
}

void NanotecStepperDriver::setDeccelerationCurve(int adress, int val)
{

    sendData(QString("#%1B%2\r").arg(adress).arg(val));
}

void NanotecStepperDriver::setDeccelerationCurveAll(int val)
{

    sendData(QString("#*B%1\r").arg(val));
}

void NanotecStepperDriver::setTurningdirection(QList<bool> vals)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setTurningdirection(m_motorMap->at(i), vals.at(i));
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setTurningdirection(m_motorMap->at(i), vals.at(i));
        }
    }
}

void NanotecStepperDriver::setTurningdirection(int adress, bool val)
{

    if(val == false){

        sendData(QString("#%1d0\r").arg(adress));
    }

    else{

        sendData(QString("#%1d1\r").arg(adress));
    }
}

void NanotecStepperDriver::setTurningdirectionAll(bool val)
{

    if(val == false){

        sendData(QString("#*d0\r"));
    }

    else{

        sendData(QString("#*d1\r"));
    }
}

void NanotecStepperDriver::setAccelerationJolt(QList<int> vals)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setAccelerationJolt(m_motorMap->at(i), vals.at(i));
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setAccelerationJolt(m_motorMap->at(i), vals.at(i));
        }
    }
}

void NanotecStepperDriver::setAccelerationJolt(int adress, int val)
{

    sendData(QString("#%1:b%2\r").arg(adress).arg(val));
}

void NanotecStepperDriver::setAccelerationJoltAll(int val)
{

    sendData(QString("#*:b%1\r").arg(val));
}

void NanotecStepperDriver::setDeccelerationJolt(QList<int> vals)
{

    if(vals.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            setDeccelerationJolt(m_motorMap->at(i), vals.at(i));
        }
    }

    else{

        for(int i = 0;i < vals.count(); i++){

            setDeccelerationJolt(m_motorMap->at(i), vals.at(i));
        }
    }
}

void NanotecStepperDriver::setDeccelerationJolt(int adress, int val)
{

    sendData(QString("#%1:B%2\r").arg(adress).arg(val));
}

void NanotecStepperDriver::setDeccelerationJoltAll(int val)
{

    sendData(QString("#*:B%1\r").arg(val));
}

void NanotecStepperDriver::increaseRPM(QList<bool> go)
{

    if(go.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            if(go.at(i) == true){

                increaseRPM(m_motorMap->at(i));
            }
        }
    }

    else{

        for(int i = 0;i < go.count(); i++){

            if(go.at(i) == true){

                increaseRPM(m_motorMap->at(i));
            }
        }
    }
}

void NanotecStepperDriver::increaseRPM(int adress)
{

    sendData(QString("#%1+\r").arg(adress));
}

void NanotecStepperDriver::increaseRPMAll()
{

    sendData(QString("#*+\r"));
}

void NanotecStepperDriver::decreaseRPM(QList<bool> go)
{

    if(go.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            if(go.at(i) == true){

                decreaseRPM(m_motorMap->at(i));
            }
        }
    }

    else{

        for(int i = 0;i < go.count(); i++){

            if(go.at(i) == true){

                decreaseRPM(m_motorMap->at(i));
            }
        }
    }
}

void NanotecStepperDriver::decreaseRPM(int adress)
{

    sendData(QString("#%1-\r").arg(adress));
}

void NanotecStepperDriver::decreaseRPMAll()
{

    sendData(QString("#*-\r"));
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

void NanotecStepperDriver::resetMotorMap()
{

    m_motorMap->clear();

    for(int i = 0;i < 256;i++){

        m_motorMap->append(i + 1);
    }
}

void NanotecStepperDriver::getPosition(QList<bool> ok)
{

    if(ok.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            if(ok.at(i) == true){

                getPosition(m_motorMap->at(i));
            }
        }
    }

    else{

        for(int i = 0;i < ok.count(); i++){

            if(ok.at(i) == true){

                getPosition(m_motorMap->at(i));
            }
        }
    }
}

void NanotecStepperDriver::getPosition(int adress)
{

    sendData(QString("#%1C\r").arg(adress));
}

void NanotecStepperDriver::getPositionAll()
{

    sendData(QString("#*C\r"));
}

void NanotecStepperDriver::getTemperature(QList<bool> ok)
{

    if(ok.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            if(ok.at(i) == true){

                getTemperature(m_motorMap->at(i));
            }
        }
    }

    else{

        for(int i = 0;i < ok.count(); i++){

            if(ok.at(i) == true){

                getTemperature(m_motorMap->at(i));
            }
        }
    }
}

void NanotecStepperDriver::getTemperature(int adress)
{

    sendData(QString("#%1:temp_adc\r").arg(adress));
}

void NanotecStepperDriver::getTemperatureAll()
{

    sendData(QString("#*:temp_adc\r"));
}

void NanotecStepperDriver::getRPM(QList<bool> ok)
{

    if(ok.count() > *m_motorCount){

        for(int i = 0;i < *m_motorCount; i++){

            if(ok.at(i) == true){

                getRPM(m_motorMap->at(i));
            }
        }
    }

    else{

        for(int i = 0;i < ok.count(); i++){

            if(ok.at(i) == true){

                getRPM(m_motorMap->at(i));
            }
        }
    }
}

void NanotecStepperDriver::getRPM(int adress)
{

    sendData(QString("#%1:v\r").arg(adress));
}

void NanotecStepperDriver::getRPMAll()
{

    sendData(QString("#*:v\r"));
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

void NanotecStepperDriver::sendData(QString data)
{

    emit send(data.toLatin1());
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
