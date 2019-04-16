#include "motorcontroller.h"

#define MOTOR_POSITIONINGMODE 1    //holds the positioning mode of the motors, see nanotec programming manual, page 51
#define MOTOR_TYPE 0    //holds the type of the motor, see nanotec programming manual, page 18
#define MOTOR_STEPSIZE 64    //holds how many microsteps equal a step
#define MOTOR_PHASECURRENT 10    //holds the phasecurrent in percent, see nanotec programming manual, page 18
#define MOTOR_HALT_PHASECURRENT 10    //holds the phasecurrent during halt of the motor in percent, see nanotec programming manual, page 19
#define MOTOR_POSITIVE_TURNINGDIRECTION 0    //holds the positive turning direction of the motors, 0 being left, 1 being right, see nanotec programming manual, page 57
#define MOTOR_NEGATIVE_TURNINGDIRECTION 1    //holds the negative turning direction of the motors, 0 being left, 1 being right, see nanotec programming manual, page 57
#define MOTOR_STOP_DECCELERATION 8000    //holds the decceleration of the motors during an emergency stop in Hz/ms, see nanotec programming manual, page 45
#define XAXIS_MOTORADRESS 1    //holds the adress of the x-axis motor
#define YAXIS_MOTORADRESS 2    //holds the adress of the y-axis motor
#define ZAXIS_MOTORADRESS 3    //holds the adress of the z-axis motor
#define EXTRUDER_MOTORADRESS 4    //holds the adress of the extruder motor
#define XAXIS_MULTIPLIER 1.0    //holds the multiplier which times the position to drive to in mm results in the number of microsteps to go to reach the new position
#define YAXIS_MULTIPLIER 1.0    //holds the multiplier which times the position to drive to in mm results in the number of microsteps to go to reach the new position
#define ZAXIS_MULTIPLIER 1.0    //holds the multiplier which times the position to drive to in mm results in the number of microsteps to go to reach the new position
#define EXTRUDER_MULTIPLIER 1.0    //holds the multiplier which times the position to drive to in mm results in the number of microsteps to go to reach the new position
#define XAXIS_MIN_STEPFREQUENCY 1    //holds the minimal step frequency of the x-axis in Hz, see nanotec programming manual, page 53
#define YAXIS_MIN_STEPFREQUENCY 1    //holds the minimal step frequency of the y-axis in Hz, see nanotec programming manual, page 53
#define ZAXIS_MIN_STEPFREQUENCY 1    //holds the minimal step frequency of the z-axis in Hz, see nanotec programming manual, page 53
#define EXTRUDER_MIN_STEPFREQUENCY 1    //holds the minimal step frequency of the extruder in Hz, see nanotec programming manual, page 53
#define MAXIMUM_PRINTING_ACCELERATION 100.0    //holds the maximum acceleration during printing in mm/s^2
#define MAXIMUM_TRAVEL_ACCELERATION 100.0    //holds the maximum acceleration during travel in mm/s^2
#define MAXIMUM_PRINTING_DECCELERATION 500.0    //holds the maximum decceleration during braking during printing in mm/s^2
#define MAXIMUM_TRAVEL_DECCELERATION 500.0   //holds the maximum decceleration during braking during travel in mm/s^2
#define MAXIMUM_ACCELERATION_CHANGE 100.0    //holds the maximum change of the acceleration during accelerating in mm/second/second/second
#define MAXIMUM_DECCELERATION_CHANGE 100.0    //holds the maximum change of the decceleration during braking in mm/second/second/second
#define TEMPCHECKINTERVAL 1000   //holds the interval in which to check the temperature in milliseconds

MotorController::MotorController(QObject *parent) : QObject(parent)
{

    m_driver = new NanotecStepperDriver;
    m_settings = new QSettings(this);

    m_driver->setMotorCount(4);

    QObject::connect(m_driver, SIGNAL(send(QByteArray)), this, SLOT(onSend(QByteArray)));

    motorSetup();
}

MotorController::~MotorController()
{

    delete m_driver;

    m_driver = NULL;
}

void MotorController::relativeMove(QList<qreal> s, QList<qreal> v, QList<qreal> a, QList<qreal> j, QList<qreal> ad, QList<qreal> jd)
{

    convertUnits(&s, &v, &a, &j, &ad, &aj);

    m_driver->setPositioningmodeAll(1);

    m_driver->setWay(s);
    m_driver->setMaxFrequenzy(v);
    m_driver->setAccelerationCurve(a);
    m_driver->setAccelerationJolt(j);

    m_driver->setDeccelerationCurve(ad);
    m_driver->setDeccelerationJolt(jd);
    m_driver->startMotorAll();
}

void MotorController::relativeMove(QList<qreal> s, QList<qreal> v, qreal a, qreal j, qreal ad, qreal jd)
{

    QList<qreal> a2;
    QList<qreal> j2;
    QList<qreal> ad2;
    QList<qreal> jd2;

    for(int i = 0;i < m_driver->motorCount();i++){

        a2.append(a);
        j2.append(j);
        ad2.append(ad);
        jd2.append(jd);
    }

    relativeMove(s, v, a2, j2, ad2, jd2);
}

void MotorController::absoluteMove(QList<qreal> s, QList<qreal> v, QList<qreal> a, QList<qreal> j, QList<qreal> ad, QList<qreal> jd)
{

    convertUnits(&s, &v, &a, &j, &ad, &aj);

    m_driver->setPositioningmodeAll(2);

    m_driver->setWay(s);
    m_driver->setMaxFrequenzy(v);
    m_driver->setAccelerationCurve(a);
    m_driver->setAccelerationJolt(j);

    m_driver->setDeccelerationCurve(ad);
    m_driver->setDeccelerationJolt(jd);
    m_driver->startMotorAll();

}

void MotorController::absoluteMove(QList<qreal> s, QList<qreal> v, qreal a, qreal j, qreal ad, qreal jd)
{

    QList<qreal> a2;
    QList<qreal> j2;
    QList<qreal> ad2;
    QList<qreal> jd2;

    for(int i = 0;i < m_driver->motorCount();i++){

        a2.append(a);
        j2.append(j);
        ad2.append(ad);
        jd2.append(jd);
    }

    absoluteMove(s, v, a2, j2, ad2, jd2);
}

void MotorController::rpmMove(QList<qreal> s, QList<qreal> v, QList<qreal> a, QList<qreal> j, QList<qreal> ad, QList<qreal> jd, bool correction)
{

    convertUnits(&s, &v, &a, &j, &ad, &aj);

    m_driver->setPositioningmodeAll(5);

    m_driver->setWay(s);
    m_driver->setMaxFrequenzy(v);
    m_driver->setAccelerationCurve(a);
    m_driver->setAccelerationJolt(j);

    m_driver->setDeccelerationCurve(ad);
    m_driver->setDeccelerationJolt(jd);
    m_driver->startMotorAll();
}

void MotorController::rpmMove(QList<qreal> s, QList<qreal> v, qreal a, qreal j, qreal ad, qreal jd, bool correction)
{

    QList<qreal> a2;
    QList<qreal> j2;
    QList<qreal> ad2;
    QList<qreal> jd2;

    for(int i = 0;i < m_driver->motorCount();i++){

        a2.append(a);
        j2.append(j);
        ad2.append(ad);
        jd2.append(jd);
    }

    rpmMove(s, v, a2, j2, ad2, jd2, correction);
}

void MotorController::receive(QByteArray data)
{

    m_driver->receive(data);
}

void MotorController::onSend(QByteArray data)
{

    emit send(data);
}

void MotorController::motorSetup()
{

    QList<int> map;

    map.append(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt());
    map.append(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt());
    map.append(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt());
    map.append(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt());

    m_driver->setMotorAdressMap(map);

    //ckecks if the phasecurrent is above 100%
    //executed if it isn't
    if(m_settings->value("motorsettings/phasecurrent", MOTOR_PHASECURRENT).toInt() < 100){

        //sets the phasecurrent of all motors to MOTOR_PHASECURRENT and appends it to the buffer
        m_driver->setPhasecurrentAll(m_settings->value("motorsettings/phasecurrent", MOTOR_PHASECURRENT).toInt());
    }

    //executed if it is
    else{

        emit error(QString("Phasecurent too high"));
        return;
    }

    //ckecks if the halt phasecurrent is set higher than the phasecurrent during driving
    //executed if it isn't
    if(m_settings->value("motorsettings/haltphasecurrent", MOTOR_HALT_PHASECURRENT).toInt() < m_settings->value("motorsettings/phasecurrent", MOTOR_PHASECURRENT).toInt()){

        //sets the phasecurrent during halt of all motors to MOTOR_HALT_PHASECURRENT and appends it to the buffer
        m_driver->setHaltPhasecurrentAll(m_settings->value("motorsettings/haltphasecurrent", MOTOR_HALT_PHASECURRENT).toInt());
    }

    //executed if it is
    else{

        emit error(QString("Halt phasecurrent is higher than phascurrent during driving"));
        return;
    }

    //ckecks if the motor type is set to 1
    //exected if it is
    if(m_settings->value("motorsettings/motor_type", MOTOR_TYPE).toInt() == 0){

        //sets the motor type for all motors to MOTOR_TYPE and appends it to the buffer
        m_driver->setMotorTypeAll(m_settings->value("motorsettings/motor_type", MOTOR_TYPE).toInt());
    }

    //executed if it isn't
    else{

        emit error(QString("Wrong motortype set"));
        return;
    }

    //checks if the x-axis backlash is in the allowed range
    //triggered if it is
    if(m_settings->value("motorsettings/xaxis/backlash", 0).toInt() >= 0 && m_settings->value("motorsettings/xaxis/backlash", 0).toInt() <= 9999){


        //setting the backlash for the x-axis
        m_driver->setBacklash(0, m_settings->value("motorsettings/xaxis/backlash", 0).toInt());
    }

    //triggerd if it isn't
    else{

        emit error(QString("X-Axis backlash is not in the allowed range"));
        return;
    }

    //checks if the ý-axis backlash is in the allowed range
    //triggered if it is
    if(m_settings->value("motorsettings/yaxis/backlash", 0).toInt() >= 0 && m_settings->value("motorsettings/yaxis/backlash", 0).toInt() <= 9999){


        //setting the backlash for the y-axis
        m_driver->setBacklash(1, m_settings->value("motorsettings/yaxis/backlash", 0).toInt());
    }

    //triggerd if it isn't
    else{

        emit error(QString("Y-Axis backlash is not in the allowed range"));
        return;
    }

    //checks if the z-axis backlash is in the allowed range
    //triggered if it is
    if(m_settings->value("motorsettings/zaxis/backlash", 0).toInt() >= 0 && m_settings->value("motorsettings/zaxis/backlash", 0).toInt() <= 9999){


        //setting the backlash for the z-axis
        m_driver->setBacklash(2, m_settings->value("motorsettings/zaxis/backlash", 0).toInt());

    }

    //triggerd if it isn't
    else{

        emit error(QString("Z-Axis backlash is not in the allowed range"));
        return;
    }

    //checks if the extruder backlash is in the allowed range
    //triggered if it is
    if(m_settings->value("motorsettings/extruder/backlash", 0).toInt() >= 0 && m_settings->value("motorsettings/extruder/backlash", 0).toInt() <= 9999){


        //setting the backlash for the extruder
        m_driver->setBacklash(3, m_settings->value("motorsettings/extruder/backlash", 0).toInt());
    }

    //triggerd if it isn't
    else{

        emit error(QString("Extruder backlash is not in the allowed range"));
        return;
    }

    //setting the stepmode of all motors to MOTOR_STEPSIZE
    m_driver->setStepSizeAll(m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toInt());
    //sets the decceleration for all motors during an emergency stop to MOTOR_STOP_DECCELERATION
    m_driver->setStopDeccelerationAll(m_settings->value("motorsettings/stop_decceleration", MOTOR_STOP_DECCELERATION).toInt());
}

void MotorController::convertUnits(QList<qreal> *s, QList<qreal> *v, QList<qreal> *a, QList<qreal> *j, QList<qreal> *ad, QList<qreal> *jd)
{

    (*s)[0] = (qint32)(s->at(0) * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal());
    (*s)[1] = (qint32)(s->at(1) * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal());
    (*s)[2] = (qint32)(s->at(2) * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal());
    (*s)[3] = (qint32)(s->at(3) * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal());

    (*v)[0] = (qint32)(v->at(0) * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60);
    (*v)[1] = (qint32)(v->at(1) * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60);
    (*v)[2] = (qint32)(v->at(2) * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60);
    (*v)[3] = (qint32)(v->at(3) * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60);

    (*a)[0] = (qint16)(a->at(0) * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0);
    (*a)[1] = (qint16)(a->at(1) * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0);
    (*a)[2] = (qint16)(a->at(2) * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0);
    (*a)[3] = (qint16)(a->at(3) * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0);

    (*j)[0] = (qint32)(j->at(0) * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0);
    (*j)[1] = (qint32)(j->at(1) * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0);
    (*j)[2] = (qint32)(j->at(2) * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0);
    (*j)[3] = (qint32)(j->at(3) * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0);

    (*ad)[0] = (qint16)(ad->at(0) * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0);
    (*ad)[1] = (qint16)(ad->at(1) * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0);
    (*ad)[2] = (qint16)(ad->at(2) * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0);
    (*ad)[3] = (qint16)(ad->at(3) * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0);

    (*jd)[0] = (qint32)(jd->at(0) * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0);
    (*jd)[1] = (qint32)(jd->at(1) * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0);
    (*jd)[2] = (qint32)(jd->at(2) * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0);
    (*jd)[3] = (qint32)(jd->at(3) * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() * m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0);
}
