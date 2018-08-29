#include "motorcontroller.h"
#include "math.h"
#include <QDebug>
#include <QtMath>

#define MOTOR_POSITIONINGMODE 1    //holds the positioning mode of the motors, see nanotec programming manual, page 51
#define MOTOR_TYPE 0    //holds the type of the motor, see nanotec programming manual, page 18
#define MOTOR_STEPSIZE 64    //holds how many microsteps equal a step
#define MOTOR_PHASECURRENT 50    //holds the phasecurrent in percent, see nanotec programming manual, page 18
#define MOTOR_HALT_PHASECURRENT 25    //holds the phasecurrent during halt of the motor in percent, see nanotec programming manual, page 19
#define MOTOR_POSITIVE_TURNINGDIRECTION 0    //holds the positive turning direction of the motors, 0 being left, 1 being right, see nanotec programming manual, page 57
#define MOTOR_NEGATIVE_TURNINGDIRECTION 1    //holds the negative turning direction of the motors, 0 being left, 1 being right, see nanotec programming manual, page 57
#define MOTOR_STOP_DECCELERATION 8000    //holds the decceleration of the motors during an emergency stop in Hz/ms, see nanotec programming manual, page 45
#define XAXIS_MOTORADRESS 1    //holds the adress of the x-axis motor
#define YAXIS_MOTORADRESS 2    //holds the adress of the y-axis motor
#define ZAXIS_MOTORADRESS 3    //holds the adress of the z-axis motor
#define EXTRUDER_MOTORADRESS 4    //holds the adress of the extruder motor
#define XAXIS_MULTIPLIER 100    //holds the multiplier which times the position to drive to in mm results in the number of microsteps to go to reach the new position
#define YAXIS_MULTIPLIER 100    //holds the multiplier which times the position to drive to in mm results in the number of microsteps to go to reach the new position
#define ZAXIS_MULTIPLIER 100    //holds the multiplier which times the position to drive to in mm results in the number of microsteps to go to reach the new position
#define EXTRUDER_MULTIPLIER 100    //holds the multiplier which times the position to drive to in mm results in the number of microsteps to go to reach the new position
#define XAXIS_MIN_STEPFREQUENCY 100    //holds the minimal step frequency of the x-axis in Hz, see nanotec programming manual, page 53
#define YAXIS_MIN_STEPFREQUENCY 100    //holds the minimal step frequency of the y-axis in Hz, see nanotec programming manual, page 53
#define ZAXIS_MIN_STEPFREQUENCY 100    //holds the minimal step frequency of the z-axis in Hz, see nanotec programming manual, page 53
#define EXTRUDER_MIN_STEPFREQUENCY 100    //holds the minimal step frequency of the extruder in Hz, see nanotec programming manual, page 53
#define XAXIS_MAXIMUM_FEEDRATE 100.0    //holds the maximum feedrate of the x-axis in mm/min
#define YAXIS_MAXIMUM_FEEDRATE 100.0    //holds the maximum feedrate of the y-axis in mm/min
#define ZAXIS_MAXIMUM_FEEDRATE 100.0    //holds the maximum feedrate of the z-axis in mm/min
#define EXTRUDER_MAXIMUM_FEEDRATE 100.0    //holds the maximum feedrate of the extruder in mm/min
#define MAXIMUM_PRINTING_ACCELERATION 100.0    //holds the maximum acceleration during printing in mm/s^2
#define MAXIMUM_TRAVEL_ACCELERATION 100.0    //holds the maximum acceleration during travel in mm/s^2
#define MAXIMUM_PRINTING_DECCELERATION 500.0    //holds the maximum decceleration during braking during printing in mm/s^2
#define MAXIMUM_TRAVEL_DECCELERATION 500.0   //holds the maximum decceleration during braking during travel in mm/s^2
#define MAXIMUM_ACCELERATION_CHANGE 100.0    //holds the maximum change of the acceleration during accelerating in mm/second/second/second
#define MAXIMUM_DECCELERATION_CHANGE 100.0    //holds the maximum change of the decceleration during braking in mm/second/second/second
#define TEMPCHECKINTERVAL 1000   //holds the interval in which to check the temperature in milliseconds

MotorController::MotorController(QObject *parent) : QObject(parent)
{
    //defining pointers

    m_motorState = new MotorState;    //holds the current state of the motors
    m_currentXAxisPosition = new qreal;    //holds the current position on the x-axis
    m_currentYAxisPosition = new qreal;    //holds the current position on the y-axis
    m_currentZAxisPosition = new qreal;    //holds the current position on the z-axis
    m_currentExtruderPosition = new qreal;    //holds the current position on the extruder
    m_previousXAxisPosition = new qreal;    //holds the previous position on the x-axis in mm
    m_previousYAxisPosition = new qreal;    //holds the previous position on the y-axis in mm
    m_previousZAxisPosition = new qreal;    //holds the previous position on the z-axis in mm
    m_previousExtruderPosition = new qreal;    //holds the previous position on the extruder in mm
    m_currentXAxisMotorPosition = new qint32;    //holds the current motorpositoion of the x-axis relative to the last motorposition in microsteps
    m_currentYAxisMotorPosition = new qint32;    //holds the current motorpositoion of the y-axis relative to the last motorposition in microsteps
    m_currentZAxisMotorPosition = new qint32;    //holds the current motorpositoion of the z-axis relative to the last motorposition in microsteps
    m_currentExtruderMotorPosition = new qint32;    //holds the current motorpositoion of the extruder relative to the last motorposition in microsteps
    m_desiredXAxisMotorPosition = new qint32;    //holds the desired motorposition of the x-axis in microsteps
    m_desiredYAxisMotorPosition = new qint32;    //holds the desired motorposition of the y-axis in microsteps
    m_desiredZAxisMotorPosition = new qint32;    //holds the desired motorposition of the z-axis in microsteps
    m_desiredExtruderMotorPosition = new qint32;    //holds the desired motorposition of the extruder in microsteps
    m_currentXAxisTemp = new int;   //holds the current temperature of the x-axis
    m_currentYAxisTemp = new int;   //holds the current temperature of the y-axis
    m_currentZAxisTemp = new int;   //holds the current temperature of the z-axis
    m_currentExtruderTemp = new int;   //holds the current temperature of the extruder
    m_commandBuffer = new CommandBuffer;    //holds all the commands that still need to be executed
    m_settings = new QSettings(this);

    //initialising variables

    *m_motorState = MotorController::Idle;
    *m_currentXAxisPosition = 0.0;
    *m_currentYAxisPosition = 0.0;
    *m_currentZAxisPosition = 0.0;
    *m_currentExtruderPosition = 0.0;
    *m_previousXAxisPosition = 0.0;
    *m_previousYAxisPosition = 0.0;
    *m_previousZAxisPosition = 0.0;
    *m_previousExtruderPosition = 0.0;
    *m_currentXAxisMotorPosition = 0;
    *m_currentYAxisMotorPosition = 0;
    *m_currentZAxisMotorPosition = 0;
    *m_currentExtruderMotorPosition = 0;
    *m_desiredXAxisMotorPosition = 0;
    *m_desiredYAxisMotorPosition = 0;
    *m_desiredZAxisMotorPosition = 0;
    *m_desiredExtruderMotorPosition = 0;
    *m_currentXAxisTemp = 0;
    *m_currentYAxisTemp = 0;
    *m_currentZAxisTemp = 0;
    *m_currentExtruderTemp = 0;

    //motorsetup

    motorSetup();
    checkBuffer();
}

MotorController::~MotorController()
{
    //deleting pointers

    delete m_motorState;
    delete m_currentXAxisPosition;
    delete m_currentYAxisPosition;
    delete m_currentZAxisPosition;
    delete m_currentExtruderPosition;
    delete m_previousXAxisPosition;
    delete m_previousYAxisPosition;
    delete m_previousZAxisPosition;
    delete m_previousExtruderPosition;
    delete m_currentXAxisMotorPosition;
    delete m_currentYAxisMotorPosition;
    delete m_currentZAxisMotorPosition;
    delete m_currentExtruderMotorPosition;
    delete m_desiredXAxisMotorPosition;
    delete m_desiredYAxisMotorPosition;
    delete m_desiredZAxisMotorPosition;
    delete m_desiredExtruderMotorPosition;
    delete m_currentXAxisTemp;
    delete m_currentYAxisTemp;
    delete m_currentZAxisTemp;
    delete m_currentExtruderTemp;
    delete m_commandBuffer;

    //setting the pointers to NULL

    m_motorState = NULL;
    m_currentXAxisPosition = NULL;
    m_currentYAxisPosition = NULL;
    m_currentZAxisPosition = NULL;
    m_currentExtruderPosition = NULL;
    m_previousXAxisPosition = NULL;
    m_previousYAxisPosition = NULL;
    m_previousZAxisPosition = NULL;
    m_previousExtruderPosition = NULL;
    m_currentXAxisMotorPosition = NULL;
    m_currentYAxisMotorPosition = NULL;
    m_currentZAxisMotorPosition = NULL;
    m_currentExtruderMotorPosition = NULL;
    m_desiredXAxisMotorPosition = NULL;
    m_desiredYAxisMotorPosition = NULL;
    m_desiredZAxisMotorPosition = NULL;
    m_desiredExtruderMotorPosition = NULL;
    m_currentXAxisTemp = NULL;
    m_currentYAxisTemp = NULL;
    m_currentZAxisTemp = NULL;
    m_currentExtruderTemp = NULL;
    m_commandBuffer = NULL;
}

bool MotorController::xAxisReferenceDrive()
{

}

bool MotorController::yAxisReferenceDrive()
{

}

bool MotorController::zAxisReferenceDrive()
{

}

//absolutely moves x-axis to position in mm, speed = the speed the head is going to move in mm/min
bool MotorController::absoluteMoveXAxis(qreal position, qreal speed)
{

    return relativeMoveXAxis(position - *m_currentXAxisPosition, speed);
}

//relatively moves x-axis by position in mm, speed = the speed the head is going to move in mm/min
bool MotorController::relativeMoveXAxis(qreal value, qreal speed)
{

    //checks if the speed is too high or too low
    if((qint32)(speed * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0) > 1000000 || (qint32)(speed * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0) < 1){

        emit error(QString("Speed to high/low"));
        return false;
    }

    else{

        //checks if the feedrate of the x-axis is bigger than the maximum feedrate of the x-axis and, if necessary, adjusts it
        if(m_settings->value("motorsettings/xaxis/maximum_feedrate", XAXIS_MAXIMUM_FEEDRATE).toReal() < speed){

            speed = m_settings->value("motorsettings/xaxis/maximum_feedrate", XAXIS_MAXIMUM_FEEDRATE).toReal();
        }

        //converts speed from mm/min to steps/second and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1o%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg((qint32)(speed * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0)));
        m_commandBuffer->bufferInfo.append(0);
    }

    //sets speed at which to start and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1u%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/xaxis/min_stepfrequency", XAXIS_MIN_STEPFREQUENCY).toInt()));
    m_commandBuffer->bufferInfo.append(0);

    //converts acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1b%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg((qint32)(m_settings->value("motorsettings/maximum_travel_acceleration", MAXIMUM_TRAVEL_ACCELERATION).toReal() * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //converts the x-axis maximum acceleration change from mm/s^3 to steps/second/millisecond/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:b%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg((quint32)(m_settings->value("motorsettings/maximum_acceleration_change", MAXIMUM_ACCELERATION_CHANGE).toReal() * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //converts x-axis decceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1B%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg((qint32)(m_settings->value("motorsettings/maximum_travel_decceleration", MAXIMUM_TRAVEL_DECCELERATION).toReal() * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //converts the x-axis maximum decceleration change from mm/s^3 to steps/second/millisecond/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:B%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg((quint32)(m_settings->value("motorsettings/maximum_decceleration_change", MAXIMUM_DECCELERATION_CHANGE).toReal() * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //checks if the way to drive is negative
    if(value < 0){

        //sets the turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/negative_turningdirection", MOTOR_NEGATIVE_TURNINGDIRECTION).toInt()));
        m_commandBuffer->bufferInfo.append(0);

        //changes the sign of value
        qreal help;

        while(value != 0){

            value++;
            help++;
        }

        value = help;
    }

    //checks if the way to drive is positive
    else if(value > 0){

        //sets the turning direction to MOTOR_POSITIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/positive_turningdirection", MOTOR_POSITIVE_TURNINGDIRECTION).toInt()));
        m_commandBuffer->bufferInfo.append(0);
    }

    else{

        emit error(QString("Way to drive is 0"));
        return false;
    }

    //sets the way to drive and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1s%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg((qint32)(value * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal())));
    m_commandBuffer->bufferInfo.append(0);
    //starts the motor and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1A\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()));
    m_commandBuffer->bufferInfo.append(1);
    //sets the desired x-axis position to the position to drive to
    *m_desiredXAxisMotorPosition = (qint32)(value * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal());

    checkBuffer();

    return true;
}

//absolutely moves y-axis to position in mm, speed = the speed the head is going to move in mm/min
bool MotorController::absoluteMoveYAxis(qreal position, qreal speed)
{

    return relativeMoveYAxis(position - *m_currentYAxisPosition, speed);
}

//relatively moves y-axis by value in mm, speed = the speed the head is going to move in mm/min
bool MotorController::relativeMoveYAxis(qreal value, qreal speed)
{

    //checks if the speed is too high or too low
    if((qint32)(speed * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0) > 1000000 || (qint32)(speed * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0) < 1){

        emit error(QString("Speed to high/low"));
        return false;
    }

    else{

        //checks if the feedrate of the y-axis is bigger than the maximum feedrate of the y-axis and, if necessary, adjusts it
        if(m_settings->value("motorsettings/yaxis/maximum_feedrate", YAXIS_MAXIMUM_FEEDRATE).toReal() < speed){

            speed = m_settings->value("motorsettings/yaxis/maximum_feedrate", YAXIS_MAXIMUM_FEEDRATE).toReal();
        }

        //converts speed from mm/min to steps/second and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1o%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg((qint32)(speed * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0)));
        m_commandBuffer->bufferInfo.append(0);
    }

    //sets speed at which to start and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1u%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/yaxis/min_stepfrequency", YAXIS_MIN_STEPFREQUENCY).toInt()));
    m_commandBuffer->bufferInfo.append(0);

    //converts acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1b%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg((qint32)(m_settings->value("motorsettings/maximum_travel_acceleration", MAXIMUM_TRAVEL_ACCELERATION).toReal() * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //converts the y-axis maximum acceleration change from mm/s^3 to steps/second/millisecond/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:b%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg((quint32)(m_settings->value("motorsettings/maximum_acceleration_change", MAXIMUM_ACCELERATION_CHANGE).toReal() * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //converts y-axis decceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1B%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg((qint32)(m_settings->value("motorsettings/maximum_travel_decceleration", MAXIMUM_TRAVEL_DECCELERATION).toReal() * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //converts the y-axis maximum decceleration change from mm/s^3 to steps/second/millisecond/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:B%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg((quint32)(m_settings->value("motorsettings/maximum_decceleration_change", MAXIMUM_DECCELERATION_CHANGE).toReal() * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //checks if the way to drive is negative
    if(value < 0){

        //sets the turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/negative_turningdirection", MOTOR_NEGATIVE_TURNINGDIRECTION).toInt()));
        m_commandBuffer->bufferInfo.append(0);

        //changes the sign of value
        qreal help;

        while(value != 0){

            value++;
            help++;
        }

        value = help;
    }

    //checks if the way to drive is positive
    else if(value > 0){

        //sets the turning direction to MOTOR_POSITIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/positive_turningdirection", MOTOR_POSITIVE_TURNINGDIRECTION).toInt()));
        m_commandBuffer->bufferInfo.append(0);
    }

    else{

        emit error(QString("Way to drive is 0"));
        return false;
    }

    //sets the way to drive and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1s%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg((qint32)(value * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal())));
    m_commandBuffer->bufferInfo.append(0);
    //starts the motor and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1A\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()));
    m_commandBuffer->bufferInfo.append(2);
    //sets the desired y-axis position to the position to drive to
    *m_desiredYAxisMotorPosition = (qint32)(value * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal());

    checkBuffer();

    return true;
}

//absolutely moves z-axis to position in mm, speed = the speed the head is going to move in mm/min
bool MotorController::absoluteMoveZAxis(qreal position, qreal speed)
{

    return relativeMoveZAxis(position - *m_currentZAxisPosition, speed);
}

//relatively moves z-axis by value in mm, speed = the speed the head is going to move in mm/min
bool MotorController::relativeMoveZAxis(qreal value, qreal speed)
{

    //checks if the speed is too high or too low
    if((qint32)(speed * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0) > 1000000 || (qint32)(speed * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0) < 1){

        emit error(QString("Speed to high/low"));
        return false;
    }

    else{

        //checks if the feedrate of the z-axis is bigger than the maximum feedrate of the z-axis and, if necessary, adjusts it
        if(m_settings->value("motorsettings/zaxis/maximum_feedrate", ZAXIS_MAXIMUM_FEEDRATE).toReal() < speed){

            speed = m_settings->value("motorsettings/zaxis/maximum_feedrate", ZAXIS_MAXIMUM_FEEDRATE).toReal();
        }

            //converts speed from mm/min to steps/second and appends it to the buffer
            m_commandBuffer->buffer.append(QString("#%1o%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg((qint32)(speed * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0)));
            m_commandBuffer->bufferInfo.append(0);
    }

    //sets speed at which to start and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1u%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/zaxis/min_stepfrequency", ZAXIS_MIN_STEPFREQUENCY).toInt()));
    m_commandBuffer->bufferInfo.append(0);

    //converts acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1b%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg((qint32)(m_settings->value("motorsettings/maximum_travel_acceleration", MAXIMUM_TRAVEL_ACCELERATION).toReal() * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //converts the z-axis maximum acceleration change from mm/s^3 to steps/second/millisecond/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:b%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg((quint32)(m_settings->value("motorsettings/maximum_acceleration_change", MAXIMUM_ACCELERATION_CHANGE).toReal() * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //converts z-axis decceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1B%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg((qint32)(m_settings->value("motorsettings/maximum_travel_decceleration", MAXIMUM_TRAVEL_DECCELERATION).toReal() * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //converts the z-axis maximum decceleration change from mm/s^3 to steps/second/millisecond/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:B%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg((quint32)(m_settings->value("motorsettings/maximum_decceleration_change", MAXIMUM_DECCELERATION_CHANGE).toReal() * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //checks if the way to drive is negative
    if(value < 0){

        //sets the turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/negative_turningdirection", MOTOR_NEGATIVE_TURNINGDIRECTION).toInt()));
        m_commandBuffer->bufferInfo.append(0);

        //changes the sign of value
        qreal help;

        while(value != 0){

            value++;
            help++;
        }

        value = help;
    }

    //checks if the way to drive is positive
    else if(value > 0){

        //sets the turning direction to MOTOR_POSITIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/positive_turningdirection", MOTOR_POSITIVE_TURNINGDIRECTION).toInt()));
        m_commandBuffer->bufferInfo.append(0);
    }

    else{

        emit error(QString("Way to drive is 0"));
        return false;
    }

    //sets the way to drive and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1s%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg((qint32)(value * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal())));
    m_commandBuffer->bufferInfo.append(0);
    //starts the motor and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1A\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()));
    m_commandBuffer->bufferInfo.append(3);
    //sets the desired z-axis position to the position to drive to
    *m_desiredZAxisMotorPosition = (qint32)(value * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal());

    checkBuffer();

    return true;
}

//absolutely moves extruder to position in mm, speed = the speed the head is going to move in mm/min
bool MotorController::absoluteMoveExtruder(qreal position, qreal speed)
{

    return relativeMoveExtruder(position - *m_currentExtruderPosition, speed);
}

//relatively moves extruder by value in mm, speed = the speed the head is going to move in mm/min
bool MotorController::relativeMoveExtruder(qreal value, qreal speed)
{

    //checks if the speed is too high or too low
    if((qint32)(speed * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0) > 1000000 || (qint32)(speed * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0) < 1){

        emit error(QString("Speed to high/low"));
        return false;
    }

    else{

        //checks if the feedrate of the extruder is bigger than the maximum feedrate of the extruder and, if necessary, adjusts it
        if(m_settings->value("motorsettings/extruder/maximum_feedrate", EXTRUDER_MAXIMUM_FEEDRATE).toReal() < speed){

            speed = m_settings->value("motorsettings/extruder/maximum_feedrate", EXTRUDER_MAXIMUM_FEEDRATE).toReal();
        }

            //converts speed from mm/min to steps/second and appends it to the buffer
            m_commandBuffer->buffer.append(QString("#%1o%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg((qint32)(speed * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0)));
            m_commandBuffer->bufferInfo.append(0);
    }

    //sets speed at which to start and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1u%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/extruder/min_stepfrequency", EXTRUDER_MIN_STEPFREQUENCY).toInt()));
    m_commandBuffer->bufferInfo.append(0);

    //converts acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1b%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg((qint32)(m_settings->value("motorsettings/maximum_travel_acceleration", MAXIMUM_TRAVEL_ACCELERATION).toReal() * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //converts the extruder maximum acceleration change from mm/s^3 to steps/second/millisecond/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:b%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg((quint32)(m_settings->value("motorsettings/maximum_acceleration_change", MAXIMUM_ACCELERATION_CHANGE).toReal() * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //converts extruder decceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1B%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg((qint32)(m_settings->value("motorsettings/maximum_travel_decceleration", MAXIMUM_TRAVEL_DECCELERATION).toReal() * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal()/ m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //converts the extruder maximum decceleration change from mm/s^3 to steps/second/millisecond/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:B%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg((quint32)(m_settings->value("motorsettings/maximum_decceleration_change", MAXIMUM_DECCELERATION_CHANGE).toReal() * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //checks if the way to drive is negative
    if(value < 0){

        //sets the turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/negative_turningdirection", MOTOR_NEGATIVE_TURNINGDIRECTION).toInt()));
        m_commandBuffer->bufferInfo.append(0);

        //changes the sign of value
        qreal help;

        while(value != 0){

            value++;
            help++;
        }

        value = help;
    }

    //checks if the way to drive is positive
    else if(value > 0){

        //sets the turning direction to MOTOR_POSITIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/positive_turningdirection", MOTOR_POSITIVE_TURNINGDIRECTION).toInt()));
        m_commandBuffer->bufferInfo.append(0);
    }

    else{

        emit error(QString("Way to drive is 0"));
        return false;
    }

    //sets the way to drive and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1s%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg((qint32)(value * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal())));
    m_commandBuffer->bufferInfo.append(0);
    //starts the motor and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1A\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()));
    m_commandBuffer->bufferInfo.append(4);
    //sets the desired extruder position to the position to drive to
    *m_desiredExtruderMotorPosition = (qint32)(value * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal());

    checkBuffer();

    return true;
}

//absolutely moves all axes and extruder
//x = position to move to on the x-axis in mm, y = position to move to on the y-axis in mm
//z = position to move to on the z-axis in mm, e = position to move the extruder to in mm
//speed = the speed the head is going to move in mm/min
bool MotorController::absoluteMove(qreal x, qreal y, qreal z, qreal e, qreal xSpeed, qreal ySpeed, qreal zSpeed, qreal eSpeed)
{

    return relativeMove(x - *m_currentXAxisPosition, y - *m_currentXAxisPosition, z - *m_currentZAxisPosition, e - *m_currentExtruderPosition, xSpeed, ySpeed, zSpeed, eSpeed);
}

//relatively moves all axes and extruder
//x = value to move by on the x-axis in mm, y = value to move by on the y-axis in mm
//z = value to move by on the z-axis in mm, e = value to move the extruder by in mm
//speed = the speed the head is going to move in mm/min
bool MotorController::relativeMove(qreal x, qreal y, qreal z, qreal e, qreal xSpeed, qreal ySpeed, qreal zSpeed, qreal eSpeed)
{

    qreal help;

    //checks if the speed is too high or too low
    if((qint32)(xSpeed * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0) > 1000000 || (qint32)(xSpeed * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0) < 1 ||
            (qint32)(ySpeed * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0) > 1000000 || (qint32)(ySpeed * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0) < 1 ||
            (qint32)(zSpeed * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0) > 1000000 || (qint32)(zSpeed * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0) < 1 ||
            (qint32)(eSpeed * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0) > 1000000 || (qint32)(eSpeed * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0) < 1){

        emit error(QString("Speed to high/low"));
        return false;
    }

    else{

        while(m_settings->value("motorsettings/xaxis/maximum_feedrate", XAXIS_MAXIMUM_FEEDRATE).toReal() < xSpeed ||
              m_settings->value("motorsettings/yaxis/maximum_feedrate", YAXIS_MAXIMUM_FEEDRATE).toReal() < ySpeed ||
              m_settings->value("motorsettings/zaxis/maximum_feedrate", ZAXIS_MAXIMUM_FEEDRATE).toReal() < zSpeed ||
              m_settings->value("motorsettings/extruder/maximum_feedrate", EXTRUDER_MAXIMUM_FEEDRATE).toReal() < eSpeed){

            help = 0.0;

            if(m_settings->value("motorsettings/xaxis/maximum_feedrate", XAXIS_MAXIMUM_FEEDRATE).toReal() < xSpeed){

                xSpeed = m_settings->value("motorsettings/xaxis/maximum_feedrate", XAXIS_MAXIMUM_FEEDRATE).toReal();

                help = x / (qSqrt((x * x) + (y * y) + (z * z)) / xSpeed);
                ySpeed = y / (qSqrt((x * x) + (y * y) + (z * z)) / help);
                zSpeed = z / (qSqrt((x * x) + (y * y) + (z * z)) / help);
                eSpeed = e / (qSqrt((x * x) + (y * y) + (z * z)) / help);
            }

            else if(m_settings->value("motorsettings/yaxis/maximum_feedrate", YAXIS_MAXIMUM_FEEDRATE).toReal() < ySpeed){

                ySpeed = m_settings->value("motorsettings/yaxis/maximum_feedrate", YAXIS_MAXIMUM_FEEDRATE).toReal();

                help = y / (qSqrt((x * x) + (y * y) + (z * z)) / ySpeed);
                xSpeed = x / (qSqrt((x * x) + (y * y) + (z * z)) / help);
                zSpeed = z / (qSqrt((x * x) + (y * y) + (z * z)) / help);
                eSpeed = e / (qSqrt((x * x) + (y * y) + (z * z)) / help);
            }

            else if(m_settings->value("motorsettings/zaxis/maximum_feedrate", ZAXIS_MAXIMUM_FEEDRATE).toReal() < zSpeed){

                zSpeed = m_settings->value("motorsettings/zaxis/maximum_feedrate", ZAXIS_MAXIMUM_FEEDRATE).toReal();

                help = z / (qSqrt((x * x) + (y * y) + (z * z)) / zSpeed);
                xSpeed = x / (qSqrt((x * x) + (y * y) + (z * z)) / help);
                ySpeed = y / (qSqrt((x * x) + (y * y) + (z * z)) / help);
                eSpeed = e / (qSqrt((x * x) + (y * y) + (z * z)) / help);
            }

            else if(m_settings->value("motorsettings/extruder/maximum_feedrate", EXTRUDER_MAXIMUM_FEEDRATE).toReal() < eSpeed){

                eSpeed = m_settings->value("motorsettings/extruder/maximum_feedrate", EXTRUDER_MAXIMUM_FEEDRATE).toReal();

                help = e / (qSqrt((x * x) + (y * y) + (z * z)) / eSpeed);
                xSpeed = x / (qSqrt((x * x) + (y * y) + (z * z)) / help);
                ySpeed = y / (qSqrt((x * x) + (y * y) + (z * z)) / help);
                zSpeed = z / (qSqrt((x * x) + (y * y) + (z * z)) / help);
            }
        }

        //converts x-axis speed from mm/min to steps/second and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1o%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg((qint32)(xSpeed * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0)));
        m_commandBuffer->bufferInfo.append(0);
        //converts y-axis speed from mm/min to steps/second and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1o%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg((qint32)(ySpeed * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0)));
        m_commandBuffer->bufferInfo.append(0);
        //converts z-axis speed from mm/min to steps/second and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1o%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg((qint32)(zSpeed * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0)));
        m_commandBuffer->bufferInfo.append(0);
        //converts extruder speed from mm/min to steps/second and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1o%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg((qint32)(eSpeed * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 60.0)));
        m_commandBuffer->bufferInfo.append(0);
    }

    //sets x-axis speed at which to start and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1u%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/xaxis/min_stepfrequency", XAXIS_MIN_STEPFREQUENCY).toInt()));
    m_commandBuffer->bufferInfo.append(0);
    //sets y-axis speed at which to start and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1u%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/yaxis/min_stepfrequency", YAXIS_MIN_STEPFREQUENCY).toInt()));
    m_commandBuffer->bufferInfo.append(0);
    //sets z-axis speed at which to start and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1u%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/zaxis/min_stepfrequency", ZAXIS_MIN_STEPFREQUENCY).toInt()));
    m_commandBuffer->bufferInfo.append(0);
    //sets extruder speed at which to start and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1u%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/extruder/min_stepfrequency", EXTRUDER_MIN_STEPFREQUENCY).toInt()));
    m_commandBuffer->bufferInfo.append(0);

    qreal t1 = m_settings->value("motorsettings/maximum_printing_acceleration", MAXIMUM_PRINTING_ACCELERATION).toReal() / m_settings->value("motorsettings/maximum_acceleration_change", MAXIMUM_ACCELERATION_CHANGE).toReal();
    qreal vt1 = m_settings->value("motorsettings/maximum_acceleration_change", MAXIMUM_ACCELERATION_CHANGE).toReal() * t1 * t1;
    qreal vmax = x / (qSqrt((x * x) + (y * y) + (z * z)) / (xSpeed / 60));

    qreal vxt1 = (vt1 / vmax) * (xSpeed / 60);
    qreal aChangeXmax = vxt1 / t1 / t1;
    qreal axmax = t1 * aChangeXmax;

    qreal vyt1 = (vt1 / vmax) * (ySpeed / 60);
    qreal aChangeYmax = vyt1 / t1 / t1;
    qreal aymax = t1 * aChangeYmax;

    qreal vzt1 = (vt1 / vmax) * (zSpeed / 60);
    qreal aChangeZmax = vzt1 / t1 / t1;
    qreal azmax = t1 * aChangeZmax;

    //sets all the accelerations

    //converts x-axis acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1b%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg((qint32)(axmax * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts y-axis acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1b%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg((qint32)(aymax * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts z-axis acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1b%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg((qint32)(azmax * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts extruder acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1b%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg((qint32)(m_settings->value("motorsettings/maximum_printing_acceleration", MAXIMUM_PRINTING_ACCELERATION).toReal() * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal()/ m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //sets all the acceleration changes

    //converts the x-axis maximum acceleration change from mm/s^3 to steps/second/millisecond/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:b%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg((quint32)(aChangeXmax * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts the y-axis maximum acceleration change from mm/s^3 to steps/second/millisecond/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:b%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg((quint32)(aChangeYmax * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts the z-axis maximum acceleration change from mm/s^3 to steps/second/millisecond/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:b%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg((quint32)(aChangeZmax * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts the extruder maximum acceleration change from mm/s^3 to steps/second/millisecond/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:b%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg((quint32)(m_settings->value("motorsettings/maximum_acceleration_change", MAXIMUM_ACCELERATION_CHANGE).toReal() * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //calculates all the values for the deccelerationcurve

    qreal dt1 = m_settings->value("motorsettings/maximum_printing_decceleration", MAXIMUM_PRINTING_DECCELERATION).toReal() / m_settings->value("motorsettings/maximum_decceleration_change", MAXIMUM_DECCELERATION_CHANGE).toReal();
    qreal dvt1 = m_settings->value("motorsettings/maximum_decceleration_change", MAXIMUM_DECCELERATION_CHANGE).toReal() * t1 * t1;
    qreal dvmax = x / (qSqrt((x * x) + (y * y) + (z * z)) / (xSpeed / 60));

    qreal dvxt1 = (dvt1 / dvmax) * (xSpeed / 60);
    qreal daChangeXmax = dvxt1 / t1 / t1;
    qreal daxmax = t1 * daChangeXmax;

    qreal dvyt1 = (dvt1 / dvmax) * (ySpeed / 60);
    qreal daChangeYmax = dvyt1 / t1 / t1;
    qreal daymax = dt1 * daChangeYmax;

    qreal dvzt1 = (dvt1 / dvmax) * (zSpeed / 60);
    qreal daChangeZmax = dvzt1 / dt1 / dt1;
    qreal dazmax = dt1 * daChangeZmax;

    //sets all the deccelerations

    //converts x-axis decceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1B%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg((qint32)(daxmax * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts y-axis decceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1B%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg((qint32)(daymax * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts z-axis decceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1B%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg((qint32)(dazmax * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts extruder decceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1B%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg((qint32)(m_settings->value("motorsettings/maximum_printing_decceleration", MAXIMUM_PRINTING_DECCELERATION).toReal() * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal()/ m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //sets all the acceleration changes

    //converts the x-axis maximum acceleration change from mm/s^3 to steps/second/millisecond/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:B%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg((quint32)(daChangeXmax * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts the y-axis maximum acceleration change from mm/s^3 to steps/second/millisecond/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:B%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg((quint32)(daChangeYmax * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts the z-axis maximum acceleration change from mm/s^3 to steps/second/millisecond/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:B%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg((quint32)(daChangeZmax * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts the extruder maximum acceleration change from mm/s^3 to steps/second/millisecond/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:B%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg((quint32)(m_settings->value("motorsettings/maximum_decceleration_change", MAXIMUM_DECCELERATION_CHANGE).toReal() * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0 / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //checks if the way to drive on the x-axis is negative
    if(x < 0){

        //sets the x-axis turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/negative_turningdirection", MOTOR_NEGATIVE_TURNINGDIRECTION).toInt()));
        m_commandBuffer->bufferInfo.append(0);

        //changes the sign of x
        help = 0.0;

        while(x != 0){

            x++;
            help++;
        }

        x = help;
    }

    //checks if the way to drive on the x-axis is positive
    else if(x > 0){

        //sets the x-axis turning direction to MOTOR_POSITIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/positive_turningdirection", MOTOR_POSITIVE_TURNINGDIRECTION).toInt()));
        m_commandBuffer->bufferInfo.append(0);
    }

    //checks if the way to drive on the y-axis is negative
    if(y < 0){

        //sets the y-axis turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/negative_turningdirection", MOTOR_NEGATIVE_TURNINGDIRECTION).toInt()));
        m_commandBuffer->bufferInfo.append(0);

        //changes the sign of y
        help = 0.0;

        while(y != 0){

            y++;
            help++;
        }

        y = help;
    }

    //checks if the way to drive on the y-axis is positive
    else if(y > 0){

        //sets the y-axis turning direction to MOTOR_POSITIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/positive_turningdirection", MOTOR_POSITIVE_TURNINGDIRECTION).toInt()));
        m_commandBuffer->bufferInfo.append(0);
    }

    //checks if the way to drive on the z-axis is negative
    if(z < 0){

        //sets the z-axis turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/negative_turningdirection", MOTOR_NEGATIVE_TURNINGDIRECTION).toInt()));
        m_commandBuffer->bufferInfo.append(0);

        //changes the sign of z
        help = 0.0;

        while(z != 0){

            z++;
            help++;
        }

        z = help;
    }

    //checks if the way to drive on the z-axis is positive
    else if(z > 0){

        //sets the z-axis turning direction to MOTOR_POSITIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/positive_turningdirection", MOTOR_POSITIVE_TURNINGDIRECTION).toInt()));
        m_commandBuffer->bufferInfo.append(0);
    }

    //checks if the way to drive on the extruder is negative
    if(e < 0){

        //sets the extruder turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/negative_turningdirection", MOTOR_NEGATIVE_TURNINGDIRECTION).toInt()));
        m_commandBuffer->bufferInfo.append(0);

        //changes the sign of e
        help = 0.0;

        while(e != 0){

            e++;
            help++;
        }

        e = help;
    }

    //checks if the way to drive on the extruder is positive
    else if(e > 0){

        //sets the extruder turning direction to MOTOR_POSITIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/positive_turningdirection", MOTOR_POSITIVE_TURNINGDIRECTION).toInt()));
        m_commandBuffer->bufferInfo.append(0);
    }

    //sets the way to drive on the x-axis and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1s%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg((qint32)(x * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal())));
    m_commandBuffer->bufferInfo.append(0);
    //sets the way to drive on the y-axis and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1s%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg((qint32)(y * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal())));
    m_commandBuffer->bufferInfo.append(0);
    //sets the way to drive on the z-axis and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1s%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg((qint32)(z * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal())));
    m_commandBuffer->bufferInfo.append(0);
    //sets the way to drive on the extruder and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1s%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg((qint32)(e * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal())));
    m_commandBuffer->bufferInfo.append(0);

    //starts the motors and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#*A\r"));
    m_commandBuffer->bufferInfo.append(5);

    //sets the desired x-axis position to the position to drive to
    *m_desiredXAxisMotorPosition = (qint32)(x * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal());
    //sets the desired y-axis position to the position to drive to
    *m_desiredYAxisMotorPosition = (qint32)(y * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal());
    //sets the desired z-axis position to the position to drive to
    *m_desiredZAxisMotorPosition = (qint32)(z * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal());
    //sets the desired extruder position to the position to drive to
    *m_desiredExtruderMotorPosition = (qint32)(e * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal());

    checkBuffer();

    return true;
}

//sets m_xAxisMaxFeedrate to xAxisMaxFeedrate
void MotorController::setXAxisMaxFeedrate(qreal xAxisMaxFeedrate)
{

    m_settings->setValue("motorsettings/xaxis/maximum_feedrate", xAxisMaxFeedrate);
}

//returns m_xAxisMaxFeedrate
qreal MotorController::xAxisMaxFeedrate()
{

    return m_settings->value("motorsettings/xaxis/maximum_feedrate", XAXIS_MAXIMUM_FEEDRATE).toReal();
}

//sets m_yAxisMaxFeedrate to yAxisMaxFeedrate
void MotorController::setYAxisMaxFeedrate(qreal yAxisMaxFeedrate)
{

    m_settings->setValue("motorsettings/yaxis/maximum_feedrate", yAxisMaxFeedrate);
}

//returns m_yAxisMaxFeedrate
qreal MotorController::yAxisMaxFeedrate()
{

    return m_settings->value("motorsettings/yaxis/maximum_feedrate", YAXIS_MAXIMUM_FEEDRATE).toReal();
}

//sets m_zAxisMaxFeedrate to zAxisMaxFeedrate
void MotorController::setZAxisMaxFeedrate(qreal zAxisMaxFeedrate)
{

    m_settings->setValue("motorsettings/zaxis/maximum_feedrate", zAxisMaxFeedrate);
}

//returns m_zAxisMaxFeedrate
qreal MotorController::zAxisMaxFeedrate()
{

    return m_settings->value("motorsettings/zaxis/maximum_feedrate", ZAXIS_MAXIMUM_FEEDRATE).toReal();
}

//sets m_extruderMaxFeedrate to extruderMaxFeedrate
void MotorController::setExtruderMaxFeedrate(qreal extruderMaxFeedrate)
{

    m_settings->setValue("motorsettings/extruder/maximum_feedrate", extruderMaxFeedrate);
}

//returns m_extruderMaxFeedrate
qreal MotorController::extruderMaxFeedrate()
{

    return m_settings->value("motorsettings/extruder/maximum_feedrate", EXTRUDER_MAXIMUM_FEEDRATE).toInt();
}

//sets the value at "motorsettings/maximum_printing_acceleration" to defaultPrintingAcceleration
void MotorController::setDefaultPrintingAcceleration(qreal defaultPrintingAcceleration)
{

    //checks if defaultPrintingAcceleration is too high or low
    //executed if it is
    if((qint32)(defaultPrintingAcceleration * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0) > 65535 || (qint32)(defaultPrintingAcceleration * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0) < 1 ||
            (qint32)(defaultPrintingAcceleration * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0) > 65535 || (qint32)(defaultPrintingAcceleration * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0) < 1 ||
            (qint32)(defaultPrintingAcceleration * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0) > 65535 || (qint32)(defaultPrintingAcceleration * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0) < 1 ||
            (qint32)(defaultPrintingAcceleration * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0) > 65535 || (qint32)(defaultPrintingAcceleration * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0) < 1){

        emit error(QString("PrintingAcceleration set too high/low"));
        return;
    }

    //executed if it isn't
    else{

       m_settings->setValue("motorsettings/maximum_printing_acceleration", defaultPrintingAcceleration);
    }
}

//returns m_defaultPrintingAcceleration
qreal MotorController::defaultPrintingAcceleration()
{

    return m_settings->value("motorsettings/maximum_printing_acceleration", MAXIMUM_PRINTING_ACCELERATION).toReal();
}

//sets "motorsettings/maximum_travel_acceleration" to defaultTravelAcceleration
void MotorController::setDefaultTravelAcceleration(qreal defaultTravelAcceleration)
{

    //checks if defaultTravelAcceleration is too high or low
    //executed if it is
    if((qint32)(defaultTravelAcceleration * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0) > 65535 || (qint32)(defaultTravelAcceleration * m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0) < 1 ||
            (qint32)(defaultTravelAcceleration * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0) > 65535 || (qint32)(defaultTravelAcceleration * m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0) < 1 ||
            (qint32)(defaultTravelAcceleration * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0) > 65535 || (qint32)(defaultTravelAcceleration * m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0) < 1 ||
            (qint32)(defaultTravelAcceleration * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0) > 65535 || (qint32)(defaultTravelAcceleration * m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal() / m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toReal() / 1000.0) < 1){

        emit error(QString("PrintingAcceleration set too high/low"));
        return;
    }

    //executed if it isn't
    else{

       m_settings->setValue("motorsettings/maximum_travel_acceleration", defaultTravelAcceleration);
    }}

//returns m_defaultTravelAcceleration
qreal MotorController::defaultTravelAcceleration()
{

    return m_settings->value("motorsettings/maximum_travel_acceleration", MAXIMUM_TRAVEL_ACCELERATION).toReal();
}

//returns m_currentXAxisPosition
qreal MotorController::currentXAxisPosition()
{

    return *m_currentXAxisPosition;
}

//returns m_currentYAxisPosition
qreal MotorController::currentYAxisPosition()
{

    return *m_currentYAxisPosition;
}

//returns m_currentZAxisPosition
qreal MotorController::currentZAxisPosition()
{

    return *m_currentZAxisPosition;
}

//returns m_currentExtruderPosition
qreal MotorController::currentExtruderPosition()
{

    return *m_currentExtruderPosition;
}

//this method doesn't change the position on the x-axis
//this method is only to setup the the printer after startup
//sets m_setCurrentXAxisPosition to currentXAxisPosition
void MotorController::setCurrentXAxisPosition(qreal currentXAxisPosition)
{

    *m_currentXAxisPosition = currentXAxisPosition;
}

//this method doesn't change the position on the y-axis
//this method is only to setup the the printer after startup
//sets m_setCurrentYAxisPosition to currentYAxisPosition
void MotorController::setCurrentYAxisPosition(qreal currentYAxisPosition)
{

    *m_currentYAxisPosition = currentYAxisPosition;
}

//this method doesn't change the position on the z-axis
//this method is only to setup the the printer after startup
//sets m_currentZAxisPosition to currentZAxisPosition
void MotorController::setCurrentZAxisPosition(qreal currentZAxisPosition)
{

    *m_currentZAxisPosition = currentZAxisPosition;
}

//this method doesn't change the position on the extruder
//this method is only to setup the the printer after stratup
//sets m_currentExtruderPosition to currentExtruderPosition
void MotorController::setCurrentExtruderPosition(qreal currentExtruderPosition)
{

    *m_currentExtruderPosition = currentExtruderPosition;
}

int MotorController::currentXAxisTemp()
{

    return *m_currentXAxisTemp;
}

int MotorController::currentYAxisTemp()
{

    return *m_currentYAxisTemp;
}

int MotorController::currentZAxisTemp()
{

    return *m_currentZAxisTemp;
}

int MotorController::currentExtruderTemp()
{

    return *m_currentExtruderTemp;
}

//executed when the serialinterface receives a message
void MotorController::receive(QString text)
{

    if(text.contains(QString("?"))){

        emit error(QString("Motor replied that a command was invalid.\nReply: %1").arg(text));
        return;
    }
    //checks what the message says
    //executed when the message contains the position of an motor
    else if(text.at(1) == QString("C")){

        //checks which motor the message is from
        //executed if the message is from the x-axis motor
        if(text.at(0) == QString("%1").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt())){

            //sets the value of the current motorposition of the x-axis to the actual motorposition of the x-axis
            *m_currentXAxisMotorPosition = text.mid(2, text.indexOf("\r") - 2).toInt();
        }

        //executed if the message is from the y-axis motor
        else if(text.at(0) == QString("%1").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt())){

            //sets the value of the current motorposition of the y-axis to the actual motorposition of the y-axis
            *m_currentYAxisMotorPosition = text.mid(2, text.indexOf("\r") - 2).toInt();
        }

        //executed if the message is from the z-axis motor
        else if(text.at(0) == QString("%1").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt())){

            //sets the value of the current motorposition of the z-axis to the actual motorposition of the z-axis
            *m_currentZAxisMotorPosition = text.mid(2, text.indexOf("\r") - 2).toInt();
        }

        //executed if the message is from the extruder motor
        else if(text.at(0) == QString("%1").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt())){

            //sets the value of the current motorposition of the extruder to the actual motorposition of the extruder
            *m_currentExtruderMotorPosition = text.mid(2, text.indexOf("\r") - 2).toInt();
        }

        calculateMovementChange();
    }

    else if(text.contains(QString(":temp_adc")) == true){

        //taking the given value out of the text and writing it into tempRaw
        int tempRaw = text.mid(10, text.indexOf("\r")).toDouble();
        //calculating the temp in degrees celcius out of the raw value
        int temp = (1266500.0 / (4250.0 + log10(0.33 * ((tempRaw / 1023.0) / (1.0 - (tempRaw / 1023.0)))) * 298.0)) - 273.0;

        //checks which motor the message is from
        //executed if the message is from the x-axis motor
        if(text.at(0) == QString("%1").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt())){

            //checks if the x-axis temperature has changed
            //triggered if it has
            if(temp != *m_currentXAxisTemp){

                //sets the value of m_currentXAxisTemp to the value of temp
                *m_currentXAxisTemp = temp;
                //emits that the x-axis temperature has changed
                emit currentXAxisTempChanged(*m_currentXAxisTemp);
            }

            //triggered if it hasn't
            else{

                //sets the value of m_currentXAxisTemp to the value of temp
                *m_currentXAxisTemp = temp;
            }
        }

        //executed if the message is from the y-axis motor
        else if(text.at(0) == QString("%1").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt())){

            //checks if the y-axis temperature has changed
            //triggered if it has
            if(temp != *m_currentYAxisTemp){

                //sets the value of m_currentYAxisTemp to the value of temp
                *m_currentYAxisTemp = temp;
                //emits that the y-axis temperature has changed
                emit currentYAxisTempChanged(*m_currentYAxisTemp);
            }

            //triggered if it hasn't
            else{

                //sets the value of m_currentYAxisTemp to the value of temp
                *m_currentYAxisTemp = temp;
            }
        }

        //executed if the message is from the z-axis motor
        else if(text.at(0) == QString("%1").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt())){

            //checks if the z-axis temperature has changed
            //triggered if it has
            if(temp != *m_currentZAxisTemp){

                //sets the value of m_currentZAxisTemp to the value of temp
                *m_currentZAxisTemp = temp;
                //emits that the z-axis temperature has changed
                emit currentZAxisTempChanged(*m_currentZAxisTemp);
            }

            //triggered if it hasn't
            else{

                //sets the value of m_currentZAxisTemp to the value of temp
                *m_currentZAxisTemp = temp;
            }
        }

        //executed if the message is from the extruder motor
        else if(text.at(0) == QString("%1").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt())){

            //checks if the extruder temperature has changed
            //triggered if it has
            if(temp != *m_currentExtruderTemp){

                //sets the value of m_currentExtruderTemp to the value of temp
                *m_currentExtruderTemp = temp;
                //emits that the extruder temperature has changed
                emit currentExtruderTempChanged(*m_currentExtruderTemp);
            }

            //triggered if it hasn't
            else{

                //sets the value of m_currentExtruderTemp to the value of temp
                *m_currentExtruderTemp = temp;
            }
        }
    }
}

//clears all the values
void MotorController::clear()
{
    *m_currentXAxisPosition = 0.0;
    *m_currentYAxisPosition = 0.0;
    *m_currentZAxisPosition = 0.0;
    *m_currentExtruderPosition = 0.0;
    *m_previousXAxisPosition = 0.0;
    *m_previousYAxisPosition = 0.0;
    *m_previousZAxisPosition = 0.0;
    *m_previousExtruderPosition = 0.0;
    *m_currentXAxisMotorPosition = 0;
    *m_currentYAxisMotorPosition = 0;
    *m_currentZAxisMotorPosition = 0;
    *m_currentExtruderMotorPosition = 0;
    *m_desiredXAxisMotorPosition = 0;
    *m_desiredYAxisMotorPosition = 0;
    *m_desiredZAxisMotorPosition = 0;
    *m_desiredExtruderMotorPosition = 0;
    m_commandBuffer->buffer.clear();
    m_commandBuffer->bufferInfo.clear();
}

//pauses the motors
void MotorController::pause()
{

    //sets the motorState to Paused
    *m_motorState = MotorController::Paused;
}

//continues the motors
void MotorController::play()
{

    //sets the motorState to Idle
    *m_motorState = MotorController::Idle;
    checkBuffer();
}

//stops all movement
//after executing this function, printing wont be able to continue
void MotorController::stop()
{

    //sends to stop the motors
    emit send(QString("#*S0\r"));
    //clears the buffer
    m_commandBuffer->buffer.clear();
    m_commandBuffer->bufferInfo.clear();
    //sets the motorState to Stopped
    *m_motorState = MotorController::Stopped;
}

//checks if the positions of the motors are the positions they should move to
void MotorController::checkMovement()
{

    //checks if the motorState is Stopped
    //executed if it is not
    if(*m_motorState != MotorController::Stopped){

        //checks if the positions of the motors are the positions they should move to
        //executed if any of the positions is not
        if(*m_currentXAxisMotorPosition != *m_desiredXAxisMotorPosition || *m_currentYAxisMotorPosition != *m_desiredYAxisMotorPosition ||
                *m_currentZAxisMotorPosition != *m_desiredZAxisMotorPosition || *m_currentExtruderMotorPosition != *m_desiredExtruderMotorPosition){

            //sends the motors the command to return their current positions
            emit send(QString("#*C\r"));
            //starts a timer, that executes this function again after one millisecond
            QTimer::singleShot(1, Qt::PreciseTimer, this, SLOT(checkMovement()));
        }

        //executed when all the positions are
        else if(*m_currentXAxisMotorPosition == *m_desiredXAxisMotorPosition && *m_currentYAxisMotorPosition == *m_desiredYAxisMotorPosition &&
                *m_currentZAxisMotorPosition == *m_desiredZAxisMotorPosition && *m_currentExtruderMotorPosition == *m_desiredExtruderMotorPosition){

            //checks if the motorState is Moving
            //executed if it is
            if(*m_motorState == MotorController::Moving){

                //sets the motorState to Idle
                *m_motorState = MotorController::Idle;
            }

            //checks if the buffer is empty
            //executed if it is
            if(m_commandBuffer->buffer.isEmpty()){

                //emits the signal that all the movements are finished
                emit movementFinished();
            }

            //executed if it's not
            else{

                //checks the buffer again
                checkBuffer();
            }
        }
    }
}

void MotorController::checkTemp()
{

    emit send(QString("#*:temp_adc\r"));
    QTimer::singleShot(m_settings->value("motorsettings/tempcheckinterval", TEMPCHECKINTERVAL).toInt(), Qt::PreciseTimer, this, SLOT(checkTemp()));
}

void MotorController::motorSetup()
{

    //ckecks if the phasecurrent is above 100%
    //executed if it isn't
    if(m_settings->value("motorsettings/phasecurrent", MOTOR_PHASECURRENT).toInt() < 100){

        //sets the phasecurrent of all motors to MOTOR_PHASECURRENT and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#*i%1\r").arg(m_settings->value("motorsettings/phasecurrent", MOTOR_PHASECURRENT).toInt()));
        m_commandBuffer->bufferInfo.append(0);
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
        m_commandBuffer->buffer.append(QString("#*r%1\r").arg(m_settings->value("motorsettings/haltphasecurrent", MOTOR_HALT_PHASECURRENT).toInt()));
        m_commandBuffer->bufferInfo.append(0);
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
        m_commandBuffer->buffer.append(QString("#*:CL_motor_type=%1\r").arg(m_settings->value("motorsettings/motor_type", MOTOR_TYPE).toInt()));
        m_commandBuffer->bufferInfo.append(0);
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
        m_commandBuffer->buffer.append(QString("#%1z%2\r").arg(m_settings->value("motorsettings/xaxis/motoradress", XAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/xaxis/backlash", 0).toInt()));
        m_commandBuffer->bufferInfo.append(0);
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
        m_commandBuffer->buffer.append(QString("#%1z%2\r").arg(m_settings->value("motorsettings/yaxis/motoradress", YAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/yaxis/backlash", 0).toInt()));
        m_commandBuffer->bufferInfo.append(0);
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
        m_commandBuffer->buffer.append(QString("#%1z%2\r").arg(m_settings->value("motorsettings/zaxis/motoradress", ZAXIS_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/zaxis/backlash", 0).toInt()));
        m_commandBuffer->bufferInfo.append(0);
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
        m_commandBuffer->buffer.append(QString("#%1z%2\r").arg(m_settings->value("motorsettings/extruder/motoradress", EXTRUDER_MOTORADRESS).toInt()).arg(m_settings->value("motorsettings/extruder/backlash", 0).toInt()));
        m_commandBuffer->bufferInfo.append(0);
    }

    //triggerd if it isn't
    else{

        emit error(QString("Extruder backlash is not in the allowed range"));
        return;
    }

    //setting the positioningtype of all motors to MOTOR_POSITIONINGMODE
    m_commandBuffer->buffer.append(QString("#*p%1\r").arg(m_settings->value("motorsettings/positioningmode", MOTOR_POSITIONINGMODE).toInt()));
    m_commandBuffer->bufferInfo.append(0);
    //setting the stepmode of all motors to MOTOR_STEPSIZE
    m_commandBuffer->buffer.append(QString("#*g%1\r").arg(m_settings->value("motorsettings/stepsize", MOTOR_STEPSIZE).toInt()));
    m_commandBuffer->bufferInfo.append(0);
    //sets the decceleration for all motors during an emergency stop to MOTOR_STOP_DECCELERATION
    m_commandBuffer->buffer.append(QString("#*H%1\r").arg(m_settings->value("motorsettings/stop_decceleration", MOTOR_STOP_DECCELERATION).toInt()));
    m_commandBuffer->bufferInfo.append(0);

    checkBuffer();
}

//checks if the positions on all axis are the actual positions and, if not, rights them
void MotorController::calculateMovementChange()
{

    //checks if the value of m_currentXAxisPosition is the actual current position on the x-axis
    //executed if the value of m_currentXAxisPosition is not the actual current position on the x-axis
    if(*m_currentXAxisPosition != *m_previousXAxisPosition + (qreal)(*m_currentXAxisMotorPosition) / m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal()){

        //sets the value of m_currentXAxisPosition to the actual current position on the x-axis
        *m_currentXAxisPosition = *m_previousXAxisPosition + (qreal)(*m_currentXAxisMotorPosition) / m_settings->value("motorsettings/xaxis/multiplier", XAXIS_MULTIPLIER).toReal();
        //emits the signal that the current position on the x-axis has changed
        emit currentXAxisPositionChanged(*m_currentXAxisPosition);
    }

    //checks if the value of m_currentYAxisPosition is the actual current position on the y-axis
    //executed if the value of m_currentYAxisPosition is not the actual current position on the y-axis
    if(*m_currentYAxisPosition != *m_previousYAxisPosition + (qreal)(*m_currentYAxisMotorPosition) / m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal()){

        //sets the value of m_currentYAxisPosition to the actual current position on the y-axis
        *m_currentYAxisPosition = *m_previousYAxisPosition + (qreal)(*m_currentYAxisMotorPosition) / m_settings->value("motorsettings/yaxis/multiplier", YAXIS_MULTIPLIER).toReal();
        //emits the signal that the current position on the y-axis has changed
        emit currentYAxisPositionChanged(*m_currentYAxisPosition);
    }

    //checks if the value of m_currentZAxisPosition is the actual current position on the z-axis
    //executed if the value of m_currentZAxisPosition is not the actual current position on the z-axis
    if(*m_currentZAxisPosition != *m_previousZAxisPosition + (qreal)(*m_currentZAxisMotorPosition) / m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal()){

        //sets the value of m_currentZAxisPosition to the actual current position on the z-axis
        *m_currentZAxisPosition = *m_previousZAxisPosition + (qreal)(*m_currentZAxisMotorPosition) / m_settings->value("motorsettings/zaxis/multiplier", ZAXIS_MULTIPLIER).toReal();
        //emits the signal that the current position on the z-axis has changed
        emit currentZAxisPositionChanged(*m_currentZAxisPosition);
    }

    //checks if the value of m_currentExtruderPosition is the actual current position on the extruder
    //executed if the value of m_currentExxtruderPosition is not the actual current position on the extruder
    if(*m_currentExtruderPosition != *m_previousExtruderPosition + (qreal)(*m_currentExtruderMotorPosition) / m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal()){

        //sets the value of m_currentExtruderPosition to the actual current position on the extruder
        *m_currentExtruderPosition = *m_previousExtruderPosition + (qreal)(*m_currentExtruderMotorPosition) / m_settings->value("motorsettings/extruder/multiplier", EXTRUDER_MULTIPLIER).toReal();
        //emits the signal that the current position on the extruder has changed
        emit currentExtruderPositionChanged(*m_currentExtruderPosition);
    }
}

//checks for commands in the buffer and executes them until the buffer is empty
void MotorController::checkBuffer()
{

    //checks if the motorState is Paused or Stopped
    //executed if it is not
    if(*m_motorState != MotorController::Paused && *m_motorState != MotorController::Stopped){

        //checks if the command is moving the motors or not
        //executed if the motors are not moved
        if(m_commandBuffer->bufferInfo.first() == 0){

            //sending the command to the buffer and removing it from the buffer
            emit send(m_commandBuffer->buffer.takeFirst());
            m_commandBuffer->bufferInfo.removeFirst();

            //checks if there is another command left in the buffer
            //executed if there is another command in the buffer
            if(m_commandBuffer->buffer.isEmpty() == false){

                checkBuffer();
            }
        }

        //executed if the motors are moved
        else if(m_commandBuffer->bufferInfo.first() > 0){

            //this loop is there to send all the commands that move the motor at nearly the same time
            while(m_commandBuffer->bufferInfo.first() > 0){

                //checks which axis is moved by the command
                //executed if the command moves the x-axis
                if(m_commandBuffer->bufferInfo.first() == 1){

                    *m_previousXAxisPosition = *m_currentXAxisPosition;
                }

                //executed if the command moves the y-axis
                else if(m_commandBuffer->bufferInfo.first() == 2){

                    *m_previousYAxisPosition = *m_currentYAxisPosition;
                }

                //executed if the command moves the z-axis
                else if(m_commandBuffer->bufferInfo.first() == 3){

                    *m_previousZAxisPosition = *m_currentZAxisPosition;
                }

                //executed if the command moves the extruder
                else if(m_commandBuffer->bufferInfo.first() == 4){

                    *m_previousExtruderPosition = *m_currentExtruderPosition;
                }

                //executed if the command moves all motors
                else if(m_commandBuffer->bufferInfo.first() == 5){

                    *m_previousXAxisPosition = *m_currentXAxisPosition;
                    *m_previousYAxisPosition = *m_currentYAxisPosition;
                    *m_previousZAxisPosition = *m_currentZAxisPosition;
                    *m_previousExtruderPosition = *m_currentExtruderPosition;
                }

                else{

                    emit error(QString("Invalid value in bufferInfo"));
                    return;
                }

                //sending the command to the buffer and removing it from the buffer
                emit send(m_commandBuffer->buffer.takeFirst());
                m_commandBuffer->bufferInfo.removeFirst();
            }

            //sets the motorState to moving
            *m_motorState = MotorController::Moving;
            //updates the movement in realtime and then executes this method again if there are still commands in the buffer
            checkMovement();
        }

        else{

            emit error(QString("Invalid value in bufferInfo"));
            return;
        }
    }
}
