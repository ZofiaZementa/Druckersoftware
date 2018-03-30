#include "motorcontroller.h"
#include <QTimer>
#include <QDebug>

#define MOTOR_POSITIONINGMODE 1    //holds the positioning mode of the motors, see nanotec programming manual, page 51
#define MOTOR_TYPE 0    //holds the type of the motor, see nanotec programming manual, page 18
#define MOTOR_STEPSIZE 64    //holds how many microsteps equal a step
#define MOTOR_PHASECURRENT 50    //holds the phasecurrent in percent, see nanotec programming manual, page 18
#define MOTOR_HALT_PHASECURRENT 25    //holds the phasecurrent during halt of the motor in percent, see nanotec programming manual, page 19
#define MOTOR_POSITIVE_TURNINGDIRECTION 0    //holds the positive turning direction of the motors, 0 being left, 1 being right, see nanotec programming manual, page 57
#define MOTOR_NEGATIVE_TURNINGDIRECTION 1    //holds the negative turning direction of the motors, 0 being left, 1 being right, see nanotec programming manual, page 57
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
#define XAXIS_MAXIMUM_BRAKE_DECCELERATION 500    //holds the maximum decceleration during braking of the x-axis in Hz/millisecond, see nanotec programming manual, page 55
#define YAXIS_MAXIMUM_BRAKE_DECCELERATION 500    //holds the maximum decceleration during braking of the y-axis in Hz/millisecond, see nanotec programming manual, page 55
#define ZAXIS_MAXIMUM_BRAKE_DECCELERATION 500    //holds the maximum decceleration during braking of the z-axis in Hz/millisecond, see nanotec programming manual, page 55
#define EXTRUDER_MAXIMUM_BRAKE_DECCELERATION 500    //holds the maximum decceleration during braking of the extruder in Hz/millisecond, see nanotec programming manual, page 55
#define XAXIS_MAXIMUM_ACCELERATION_CHANGE 100    //holds the maximum change of the acceleration during accelerating of the x-axis, see nanotec programming manual, page 59
#define YAXIS_MAXIMUM_ACCELERATION_CHANGE 100    //holds the maximum change of the acceleration during accelerating of the x-axis, see nanotec programming manual, page 59
#define ZAXIS_MAXIMUM_ACCELERATION_CHANGE 100    //holds the maximum change of the acceleration during accelerating of the x-axis, see nanotec programming manual, page 59
#define EXTRUDER_MAXIMUM_ACCELERATION_CHANGE 100    //holds the maximum change of the acceleration during accelerating of the x-axis, see nanotec programming manual, page 59
#define XAXIS_MAXIMUM_DECCELERATION_CHANGE 100    //holds the maximum change of the decceleration during braking of the x-axis, see nanotec programming manual, page 59
#define YAXIS_MAXIMUM_DECCELERATION_CHANGE 100    //holds the maximum change of the decceleration during braking of the x-axis, see nanotec programming manual, page 59
#define ZAXIS_MAXIMUM_DECCELERATION_CHANGE 100    //holds the maximum change of the decceleration during braking of the x-axis, see nanotec programming manual, page 59
#define EXTRUDER_MAXIMUM_DECCELERATION_CHANGE 100    //holds the maximum change of the decceleration during braking of the x-axis, see nanotec programming manual, page 59

MotorController::MotorController(QObject *parent) : QObject(parent)
{
    //defining pointers

    m_xAxisMaxPrintingAcceleration = new int;    //holds the maximum acceleration for the x-axis during printing in mm/s^2
    m_xAxisMaxTravelAcceleration = new int;    //holds the maximum acceleration for the x-axis during travel in mm/s^2
    m_yAxisMaxPrintingAcceleration = new int;    //holds the maximum acceleration for the y-axis during printing in mm/s^2
    m_yAxisMaxTravelAcceleration = new int;    //holds the maximum acceleration for the y-axis during travel in mm/s^2
    m_zAxisMaxPrintingAcceleration = new int;    //holds the maximum acceleration for the z-axis during printing in mm/s^2
    m_zAxisMaxTravelAcceleration = new int;    //holds the maximum acceleration for the z-axis during travel in mm/s^2
    m_extruderMaxPrintingAcceleration = new int;    //holds the maximum acceleration for the extruder during printing in mm/s^2
    m_extruderMaxTravelAcceleration = new int;    //holds the maximum acceleration for the extruder during travel in mm/s^2
    m_xAxisMaxFeedrate = new qreal;    //holds the maximum feedrate during movement on the x-axis in mm/min
    m_yAxisMaxFeedrate = new qreal;    //holds the maximum feedrate during movement on the y-axis in mm/min
    m_zAxisMaxFeedrate = new qreal;    //holds the maximum feedrate during movement on the z-axis in mm/min
    m_extruderMaxFeedrate = new qreal;    //holds the maximum feedrate during movement on the extruder in mm/min
    m_defaultPrintingAcceleration = new int;    //holds the default acceleration during printing for all axes including the extruder in mm/s^2
    m_defaultTravelAcceleration = new int;    //holds the default acceleration during travel for all axes including the extruder in mm/s^2
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
    m_commandBuffer = new CommandBuffer;    //holds all the commands that still need to be executed

    //motorsetup

    //sets the phasecurrent of all motors to MOTOR_PHASECURRENT and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#*i%1\r").arg(MOTOR_PHASECURRENT));
    m_commandBuffer->bufferInfo.append(0);
    //sets the phasecurrent during halt of all motors to MOTOR_HALT_PHASECURRENT and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#*r%1\r").arg(MOTOR_HALT_PHASECURRENT));
    m_commandBuffer->bufferInfo.append(0);
    //sets the motor type for all motors to MOTOR_TYPE and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#*:CL_motor_type=%1\r").arg(MOTOR_TYPE));
    m_commandBuffer->bufferInfo.append(0);
    //setting the positioningtype of all motors to MOTOR_POSITIONINGMODE
    m_commandBuffer->buffer.append(QString("#*p%1\r").arg(MOTOR_POSITIONINGMODE));
    m_commandBuffer->bufferInfo.append(0);
    //setting the stepmode of all motors to MOTOR_STEPSIZE
    m_commandBuffer->buffer.append(QString("#*g%1\r").arg(MOTOR_STEPSIZE));
    m_commandBuffer->bufferInfo.append(0);

    //sets the maximum decceleration

    //converts decceleration of the x-axis from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1B%2\r").arg(XAXIS_MOTORADRESS).arg((qint32)((qreal)(XAXIS_MAXIMUM_BRAKE_DECCELERATION) * (qreal)(XAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts decceleration of the y-axis from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1B%2\r").arg(YAXIS_MOTORADRESS).arg((qint32)((qreal)(YAXIS_MAXIMUM_BRAKE_DECCELERATION) * (qreal)(YAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts decceleration of the z-axis from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1B%2\r").arg(ZAXIS_MOTORADRESS).arg((qint32)((qreal)(ZAXIS_MAXIMUM_BRAKE_DECCELERATION) * (qreal)(ZAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts decceleration of the extruder from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1B%2\r").arg(EXTRUDER_MOTORADRESS).arg((qint32)(((qreal)(EXTRUDER_MAXIMUM_BRAKE_DECCELERATION) * (qreal)(EXTRUDER_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 1000.0))));
    m_commandBuffer->bufferInfo.append(0);

    //sets the maximum acceleration change

    //sets the maximum change of acceleration of the x-axis and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:b=%2\r").arg(XAXIS_MOTORADRESS).arg(XAXIS_MAXIMUM_ACCELERATION_CHANGE));
    m_commandBuffer->bufferInfo.append(0);
    //sets the maximum change of acceleration of the y-axis and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:b=%2\r").arg(YAXIS_MOTORADRESS).arg(YAXIS_MAXIMUM_ACCELERATION_CHANGE));
    m_commandBuffer->bufferInfo.append(0);
    //sets the maximum change of acceleration of the z-axis and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:b=%2\r").arg(ZAXIS_MOTORADRESS).arg(ZAXIS_MAXIMUM_ACCELERATION_CHANGE));
    m_commandBuffer->bufferInfo.append(0);
    //sets the maximum change of acceleration of the extruder and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:b=%2\r").arg(EXTRUDER_MOTORADRESS).arg(EXTRUDER_MAXIMUM_ACCELERATION_CHANGE));
    m_commandBuffer->bufferInfo.append(0);

    //set the maximum decceleration change

    //sets the maximum change of decceleration of the x-axis and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:B=%2\r").arg(XAXIS_MOTORADRESS).arg(XAXIS_MAXIMUM_DECCELERATION_CHANGE));
    m_commandBuffer->bufferInfo.append(0);
    //sets the maximum change of decceleration of the y-axis and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:B=%2\r").arg(YAXIS_MOTORADRESS).arg(YAXIS_MAXIMUM_DECCELERATION_CHANGE));
    m_commandBuffer->bufferInfo.append(0);
    //sets the maximum change of decceleration of the z-axis and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:B=%2\r").arg(ZAXIS_MOTORADRESS).arg(ZAXIS_MAXIMUM_DECCELERATION_CHANGE));
    m_commandBuffer->bufferInfo.append(0);
    //sets the maximum change of decceleration of the extruder and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1:B=%2\r").arg(EXTRUDER_MOTORADRESS).arg(EXTRUDER_MAXIMUM_DECCELERATION_CHANGE));
    m_commandBuffer->bufferInfo.append(0);

    checkBuffer();
}

MotorController::~MotorController()
{
    //deleting pointers

    delete m_xAxisMaxPrintingAcceleration;
    delete m_xAxisMaxTravelAcceleration;
    delete m_yAxisMaxPrintingAcceleration;
    delete m_yAxisMaxTravelAcceleration;
    delete m_zAxisMaxPrintingAcceleration;
    delete m_zAxisMaxTravelAcceleration;
    delete m_extruderMaxPrintingAcceleration;
    delete m_extruderMaxTravelAcceleration;
    delete m_xAxisMaxFeedrate;
    delete m_yAxisMaxFeedrate;
    delete m_zAxisMaxFeedrate;
    delete m_extruderMaxFeedrate;
    delete m_defaultPrintingAcceleration;
    delete m_defaultTravelAcceleration;
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
    delete m_commandBuffer;

    //setting the pointers to NULL

    m_xAxisMaxPrintingAcceleration = NULL;
    m_xAxisMaxTravelAcceleration = NULL;
    m_yAxisMaxPrintingAcceleration = NULL;
    m_yAxisMaxTravelAcceleration = NULL;
    m_zAxisMaxPrintingAcceleration = NULL;
    m_zAxisMaxTravelAcceleration = NULL;
    m_extruderMaxPrintingAcceleration = NULL;
    m_extruderMaxTravelAcceleration = NULL;
    m_xAxisMaxFeedrate = NULL;
    m_yAxisMaxFeedrate = NULL;
    m_zAxisMaxFeedrate = NULL;
    m_extruderMaxFeedrate = NULL;
    m_defaultPrintingAcceleration = NULL;
    m_defaultTravelAcceleration = NULL;
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
    m_commandBuffer = NULL;
}

//absolutely moves x-axis to position in mm, speed = the speed the head is going to move in mm/min
bool MotorController::absoluteMoveXAxis(qreal position, qreal speed)
{

    return relativeMoveXAxis(position - *m_currentXAxisPosition, speed);
}

//relatively moves x-axis by position in mm, speed = the speed the head is going to move in mm/min
bool MotorController::relativeMoveXAxis(qreal value, qreal speed)
{

    //sets speed at which to start and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1u%2\r").arg(XAXIS_MOTORADRESS).arg(XAXIS_MIN_STEPFREQUENCY));
    m_commandBuffer->bufferInfo.append(0);

    //converts acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1b%2\r").arg(XAXIS_MOTORADRESS).arg((qint32)((qreal)(*m_defaultTravelAcceleration) * (qreal)(XAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //checks if the speed is too high or too low
    if((qint32)(speed * (qreal)(XAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0) > 1000000 || (qint32)(speed * (qreal)(XAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0) < 1){

        return false;
    }

    else{

        //converts speed from mm/min to steps/second and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1o%2\r").arg(XAXIS_MOTORADRESS).arg((qint32)(speed * (qreal)(XAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0)));
        m_commandBuffer->bufferInfo.append(0);
    }

    //checks if the way to drive is negative
    if(value < 0){

        //sets the turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(XAXIS_MOTORADRESS).arg(MOTOR_NEGATIVE_TURNINGDIRECTION));
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
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(XAXIS_MOTORADRESS).arg(MOTOR_POSITIVE_TURNINGDIRECTION));
        m_commandBuffer->bufferInfo.append(0);
    }

    else{

        return false;
    }

    //sets the way to drive and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1s%2\r").arg(XAXIS_MOTORADRESS).arg((qint32)(value * (qreal)(XAXIS_MULTIPLIER))));
    m_commandBuffer->bufferInfo.append(0);
    //starts the motor and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1A\r").arg(XAXIS_MOTORADRESS));
    m_commandBuffer->bufferInfo.append(1);
    //sets the desired x-axis position to the position to drive to
    *m_desiredXAxisMotorPosition = (qint32)(value * (qreal)(XAXIS_MULTIPLIER));

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

    //sets speed at which to start and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1u%2\r").arg(YAXIS_MOTORADRESS).arg(YAXIS_MIN_STEPFREQUENCY));
    m_commandBuffer->bufferInfo.append(0);

    //converts acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1b%2\r").arg(YAXIS_MOTORADRESS).arg((qint32)((qreal)(*m_defaultTravelAcceleration) * (qreal)(YAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //checks if the speed is too high or too low
    if((qint32)(speed * (qreal)(YAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0) > 1000000 || (qint32)(speed * (qreal)(YAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0) < 1){

        return false;
    }

    else{

        //converts speed from mm/min to steps/second and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1o%2\r").arg(YAXIS_MOTORADRESS).arg((qint32)(speed * (qreal)(YAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0)));
        m_commandBuffer->bufferInfo.append(0);
    }

    //checks if the way to drive is negative
    if(value < 0){

        //sets the turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(YAXIS_MOTORADRESS).arg(MOTOR_NEGATIVE_TURNINGDIRECTION));
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
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(YAXIS_MOTORADRESS).arg(MOTOR_POSITIVE_TURNINGDIRECTION));
        m_commandBuffer->bufferInfo.append(0);
    }

    else{

        return false;
    }

    //sets the way to drive and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1s%2\r").arg(YAXIS_MOTORADRESS).arg((qint32)(value * (qreal)(YAXIS_MULTIPLIER))));
    m_commandBuffer->bufferInfo.append(0);
    //starts the motor and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1A\r").arg(YAXIS_MOTORADRESS));
    m_commandBuffer->bufferInfo.append(2);
    //sets the desired y-axis position to the position to drive to
    *m_desiredYAxisMotorPosition = (qint32)(value * (qreal)(YAXIS_MULTIPLIER));

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

    //sets speed at which to start and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1u%2\r").arg(ZAXIS_MOTORADRESS).arg(ZAXIS_MIN_STEPFREQUENCY));
    m_commandBuffer->bufferInfo.append(0);

    //converts acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1b%2\r").arg(ZAXIS_MOTORADRESS).arg((qint32)((qreal)(*m_defaultTravelAcceleration) * (qreal)(ZAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //checks if the speed is too high or too low
    if((qint32)(speed * (qreal)(ZAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0) > 1000000 || (qint32)(speed * (qreal)(ZAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0) < 1){

        return false;
    }

    else{

        //converts speed from mm/min to steps/second and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1o%2\r").arg(ZAXIS_MOTORADRESS).arg((qint32)(speed * (qreal)(ZAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0)));
        m_commandBuffer->bufferInfo.append(0);
    }

    //checks if the way to drive is negative
    if(value < 0){

        //sets the turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(ZAXIS_MOTORADRESS).arg(MOTOR_NEGATIVE_TURNINGDIRECTION));
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
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(ZAXIS_MOTORADRESS).arg(MOTOR_POSITIVE_TURNINGDIRECTION));
        m_commandBuffer->bufferInfo.append(0);
    }

    else{

        return false;
    }

    //sets the way to drive and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1s%2\r").arg(ZAXIS_MOTORADRESS).arg((qint32)(value * (qreal)(ZAXIS_MULTIPLIER))));
    m_commandBuffer->bufferInfo.append(0);
    //starts the motor and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1A\r").arg(ZAXIS_MOTORADRESS));
    m_commandBuffer->bufferInfo.append(3);
    //sets the desired z-axis position to the position to drive to
    *m_desiredZAxisMotorPosition = (qint32)(value * (qreal)(ZAXIS_MULTIPLIER));

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

    //sets speed at which to start and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1u%2\r").arg(EXTRUDER_MOTORADRESS).arg(EXTRUDER_MIN_STEPFREQUENCY));
    m_commandBuffer->bufferInfo.append(0);

    //converts acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1b%2\r").arg(EXTRUDER_MOTORADRESS).arg((qint32)((qreal)(*m_defaultTravelAcceleration) * (qreal)(EXTRUDER_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //checks if the speed is too high or too low
    if((qint32)(speed * (qreal)(EXTRUDER_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0) > 1000000 || (qint32)(speed * (qreal)(EXTRUDER_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0) < 1){

        return false;
    }

    else{

        //converts speed from mm/min to steps/second and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1o%2\r").arg(EXTRUDER_MOTORADRESS).arg((qint32)(speed * (qreal)(EXTRUDER_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0)));
        m_commandBuffer->bufferInfo.append(0);
    }

    //checks if the way to drive is negative
    if(value < 0){

        //sets the turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(EXTRUDER_MOTORADRESS).arg(MOTOR_NEGATIVE_TURNINGDIRECTION));
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
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(EXTRUDER_MOTORADRESS).arg(MOTOR_POSITIVE_TURNINGDIRECTION));
        m_commandBuffer->bufferInfo.append(0);
    }

    else{

        return false;
    }

    //sets the way to drive and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1s%2\r").arg(EXTRUDER_MOTORADRESS).arg((qint32)(value * (qreal)(EXTRUDER_MULTIPLIER))));
    m_commandBuffer->bufferInfo.append(0);
    //starts the motor and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1A\r").arg(EXTRUDER_MOTORADRESS));
    m_commandBuffer->bufferInfo.append(4);
    //sets the desired extruder position to the position to drive to
    *m_desiredExtruderMotorPosition = (qint32)(value * (qreal)(EXTRUDER_MULTIPLIER));

    checkBuffer();

    return true;
}

//absolutely moves all axes and extruder
//x = position to move to on the x-axis in mm, y = position to move to on the y-axis in mm
//z = position to move to on the z-axis in mm, e = position to move the extruder to in mm
//speed = the speed the head is going to move in mm/min
bool MotorController::absoluteMove(qreal x, qreal y, qreal z, qreal e, qreal speed)
{

    return relativeMove(x - *m_currentXAxisPosition, y - *m_currentXAxisPosition, z - *m_currentZAxisPosition, e - *m_currentExtruderPosition, speed);
}

//relatively moves all axes and extruder
//x = value to move by on the x-axis in mm, y = value to move by on the y-axis in mm
//z = value to move by on the z-axis in mm, e = value to move the extruder by in mm
//speed = the speed the head is going to move in mm/min
bool MotorController::relativeMove(qreal x, qreal y, qreal z, qreal e, qreal speed)
{

    qreal help;

    //sets x-axis speed at which to start and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1u%2\r").arg(XAXIS_MOTORADRESS).arg(XAXIS_MIN_STEPFREQUENCY));
    m_commandBuffer->bufferInfo.append(0);
    //sets y-axis speed at which to start and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1u%2\r").arg(YAXIS_MOTORADRESS).arg(YAXIS_MIN_STEPFREQUENCY));
    m_commandBuffer->bufferInfo.append(0);
    //sets z-axis speed at which to start and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1u%2\r").arg(ZAXIS_MOTORADRESS).arg(ZAXIS_MIN_STEPFREQUENCY));
    m_commandBuffer->bufferInfo.append(0);
    //sets extruder speed at which to start and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1u%2\r").arg(EXTRUDER_MOTORADRESS).arg(EXTRUDER_MIN_STEPFREQUENCY));
    m_commandBuffer->bufferInfo.append(0);

    //converts x-axis acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1b%2\r").arg(XAXIS_MOTORADRESS).arg((qint32)((qreal)(*m_defaultTravelAcceleration) * (qreal)(XAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts y-axis acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1b%2\r").arg(YAXIS_MOTORADRESS).arg((qint32)((qreal)(*m_defaultTravelAcceleration) * (qreal)(YAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts z-axis acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1b%2\r").arg(ZAXIS_MOTORADRESS).arg((qint32)((qreal)(*m_defaultTravelAcceleration) * (qreal)(ZAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);
    //converts extruder acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1b%2\r").arg(EXTRUDER_MOTORADRESS).arg((qint32)((qreal)(*m_defaultTravelAcceleration) * (qreal)(EXTRUDER_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 1000.0)));
    m_commandBuffer->bufferInfo.append(0);

    //checks if the speed is too high or too low
    if((qint32)(speed * (qreal)(XAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0) > 1000000 || (qint32)(speed * (qreal)(XAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0) < 1 ||
            (qint32)(speed * (qreal)(YAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0) > 1000000 || (qint32)(speed * (qreal)(YAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0) < 1 ||
            (qint32)(speed * (qreal)(ZAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0) > 1000000 || (qint32)(speed * (qreal)(ZAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0) < 1 ||
            (qint32)(speed * (qreal)(EXTRUDER_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0) > 1000000 || (qint32)(speed * (qreal)(EXTRUDER_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0) < 1){

        return false;
    }

    else{

        //converts x-axis speed from mm/min to steps/second and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1o%2\r").arg(XAXIS_MOTORADRESS).arg((qint32)(speed * (qreal)(XAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0)));
        m_commandBuffer->bufferInfo.append(0);
        //converts y-axis speed from mm/min to steps/second and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1o%2\r").arg(YAXIS_MOTORADRESS).arg((qint32)(speed * (qreal)(YAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0)));
        m_commandBuffer->bufferInfo.append(0);
        //converts z-axis speed from mm/min to steps/second and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1o%2\r").arg(ZAXIS_MOTORADRESS).arg((qint32)(speed * (qreal)(ZAXIS_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0)));
        m_commandBuffer->bufferInfo.append(0);
        //converts extruder speed from mm/min to steps/second and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1o%2\r").arg(EXTRUDER_MOTORADRESS).arg((qint32)(speed * (qreal)(EXTRUDER_MULTIPLIER) / (qreal)(MOTOR_STEPSIZE) / 60.0)));
        m_commandBuffer->bufferInfo.append(0);
    }

    //checks if the way to drive on the x-axis is negative
    if(x < 0){

        //sets the x-axis turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(XAXIS_MOTORADRESS).arg(MOTOR_NEGATIVE_TURNINGDIRECTION));
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
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(XAXIS_MOTORADRESS).arg(MOTOR_POSITIVE_TURNINGDIRECTION));
        m_commandBuffer->bufferInfo.append(0);
    }

    //checks if the way to drive on the y-axis is negative
    if(y < 0){

        //sets the y-axis turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(YAXIS_MOTORADRESS).arg(MOTOR_NEGATIVE_TURNINGDIRECTION));
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
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(YAXIS_MOTORADRESS).arg(MOTOR_POSITIVE_TURNINGDIRECTION));
        m_commandBuffer->bufferInfo.append(0);
    }

    //checks if the way to drive on the z-axis is negative
    if(z < 0){

        //sets the z-axis turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(ZAXIS_MOTORADRESS).arg(MOTOR_NEGATIVE_TURNINGDIRECTION));
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
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(ZAXIS_MOTORADRESS).arg(MOTOR_POSITIVE_TURNINGDIRECTION));
        m_commandBuffer->bufferInfo.append(0);
    }

    //checks if the way to drive on the extruder is negative
    if(e < 0){

        //sets the extruder turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(EXTRUDER_MOTORADRESS).arg(MOTOR_NEGATIVE_TURNINGDIRECTION));
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
        m_commandBuffer->buffer.append(QString("#%1d%2\r").arg(EXTRUDER_MOTORADRESS).arg(MOTOR_POSITIVE_TURNINGDIRECTION));
        m_commandBuffer->bufferInfo.append(0);
    }

    //sets the way to drive on the x-axis and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1s%2\r").arg(XAXIS_MOTORADRESS).arg((qint32)(x * (qreal)(XAXIS_MULTIPLIER))));
    m_commandBuffer->bufferInfo.append(0);
    //sets the way to drive on the y-axis and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1s%2\r").arg(YAXIS_MOTORADRESS).arg((qint32)(y * (qreal)(YAXIS_MULTIPLIER))));
    m_commandBuffer->bufferInfo.append(0);
    //sets the way to drive on the z-axis and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1s%2\r").arg(ZAXIS_MOTORADRESS).arg((qint32)(z * (qreal)(ZAXIS_MULTIPLIER))));
    m_commandBuffer->bufferInfo.append(0);
    //sets the way to drive on the extruder and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#%1s%2\r").arg(EXTRUDER_MOTORADRESS).arg((qint32)(e * (qreal)(EXTRUDER_MULTIPLIER))));
    m_commandBuffer->bufferInfo.append(0);

    //starts the motors and appends it to the buffer
    m_commandBuffer->buffer.append(QString("#*A\r"));
    m_commandBuffer->bufferInfo.append(5);

    //sets the desired x-axis position to the position to drive to
    *m_desiredXAxisMotorPosition = (qint32)(x * (qreal)(XAXIS_MULTIPLIER));
    //sets the desired y-axis position to the position to drive to
    *m_desiredYAxisMotorPosition = (qint32)(y * (qreal)(YAXIS_MULTIPLIER));
    //sets the desired z-axis position to the position to drive to
    *m_desiredZAxisMotorPosition = (qint32)(z * (qreal)(ZAXIS_MULTIPLIER));
    //sets the desired extruder position to the position to drive to
    *m_desiredExtruderMotorPosition = (qint32)(e * (qreal)(EXTRUDER_MULTIPLIER));

    checkBuffer();

    return true;
}

//sets *m_xAxisMaxPrintingAcceleration to xAxisMaxPrintingAcceleration
void MotorController::setXAxisMaxPrintingAcceleration(int xAxisMaxPrintingAcceleration)
{

    *m_xAxisMaxPrintingAcceleration = xAxisMaxPrintingAcceleration;
}

//returns m_xAxisMaxPrintingAcceleration
int MotorController::xAxisMaxPrintingAcceleration()
{

    return *m_xAxisMaxPrintingAcceleration;
}

//sets *m_xAxisMaxTravelAcceleration to xAxisMaxTravelAcceleration
void MotorController::setXAxisMaxTravelAcceleration(int xAxisMaxTravelAcceleration)
{

    *m_xAxisMaxTravelAcceleration = xAxisMaxTravelAcceleration;
}

//returns m_xAxisMaxTravelAcceleration
int MotorController::xAxisMaxTravelAcceleration()
{

    return *m_xAxisMaxTravelAcceleration;
}

//sets *m_yAxisMaxPrintingAcceleration to yAxisMaxPrintingAcceleration
void MotorController::setYAxisMaxPrintingAcceleration(int yAxisMaxPrintingAcceleration)
{

    *m_yAxisMaxPrintingAcceleration = yAxisMaxPrintingAcceleration;
}

//returns m_yAxisMaxPrintingAcceleration
int MotorController::yAxisMaxPrintingAcceleration()
{

    return *m_yAxisMaxPrintingAcceleration;
}

//sets *m_yAxisMaxTravelAcceleration to yAxisMaxTravelAcceleration
void MotorController::setYAxisMaxTravelAcceleration(int yAxisMaxTravelAcceleration)
{

    *m_yAxisMaxTravelAcceleration = yAxisMaxTravelAcceleration;
}

//returns m_yAxisMaxTravelAcceleration
int MotorController::yAxisMaxTravelAcceleration()
{

    return *m_yAxisMaxTravelAcceleration;
}

//sets *m_zAxisMaxPrintingAcceleration to zAxisMaxPrintingAcceleration
void MotorController::setZAxisMaxPrintingAcceleration(int zAxisMaxPrintingAcceleration)
{

    *m_zAxisMaxPrintingAcceleration = zAxisMaxPrintingAcceleration;
}

//returns m_zAxisMaxPrintingAcceleration
int MotorController::zAxisMaxPrintingAcceleration()
{

    return *m_zAxisMaxPrintingAcceleration;
}

//sets *m_zAxisMaxTravelAcceleration to zAxisMaxTravelAcceleration
void MotorController::setZAxisMaxTravelAcceleration(int zAxisMaxTravelAcceleration)
{

    *m_zAxisMaxTravelAcceleration = zAxisMaxTravelAcceleration;
}

//returns m_zAxisMaxTravelAcceleration
int MotorController::zAxisMaxTravelAcceleration()
{

    return *m_zAxisMaxTravelAcceleration;
}

//sets *m_extruderMaxPrintingAcceleration to extruderMaxPrintingAcceleration
void MotorController::setExtruderMaxPrintingAcceleration(int extruderMaxPrintingAcceleration)
{

    *m_extruderMaxPrintingAcceleration = extruderMaxPrintingAcceleration;
}

//returns m_extruderMaxPrintingAcceleration
int MotorController::extruderMaxPrintingAcceleration()
{

    return *m_extruderMaxPrintingAcceleration;
}
//sets *m_extruderMaxTravelAcceleration to extruderMaxTravelAcceleration
void MotorController::setExtruderMaxTravelAcceleration(int extruderMaxTravelAcceleration)
{

    *m_extruderMaxTravelAcceleration = extruderMaxTravelAcceleration;
}

//returns m_extruderMaxTravelAcceleration
int MotorController::extruderMaxTravelAcceleration()
{

    return *m_extruderMaxTravelAcceleration;
}

//sets m_xAxisMaxFeedrate to xAxisMaxFeedrate
void MotorController::setXAxisMaxFeedrate(qreal xAxisMaxFeedrate)
{

    *m_xAxisMaxFeedrate = xAxisMaxFeedrate;
}

//returns m_xAxisMaxFeedrate
int MotorController::xAxisMaxFeedrate()
{

    return *m_xAxisMaxFeedrate;
}

//sets m_yAxisMaxFeedrate to yAxisMaxFeedrate
void MotorController::setYAxisMaxFeedrate(qreal yAxisMaxFeedrate)
{

    *m_yAxisMaxFeedrate = yAxisMaxFeedrate;
}

//returns m_yAxisMaxFeedrate
int MotorController::yAxisMaxFeedrate()
{

    return *m_yAxisMaxFeedrate;
}

//sets m_zAxisMaxFeedrate to zAxisMaxFeedrate
void MotorController::setZAxisMaxFeedrate(qreal zAxisMaxFeedrate)
{

    *m_zAxisMaxFeedrate = zAxisMaxFeedrate;
}

//returns m_zAxisMaxFeedrate
int MotorController::zAxisMaxFeedrate()
{

    return *m_zAxisMaxFeedrate;
}

//sets m_extruderMaxFeedrate to extruderMaxFeedrate
void MotorController::setExtruderMaxFeedrate(qreal extruderMaxFeedrate)
{

    *m_extruderMaxFeedrate = extruderMaxFeedrate;
}

//returns m_extruderMaxFeedrate
int MotorController::extruderMaxFeedrate()
{

    return *m_extruderMaxFeedrate;
}

//sets *m_defaultPrintingAcceleration to defaultPrintingAcceleration
void MotorController::setDefaultPrintingAcceleration(int defaultPrintingAcceleration)
{

    *m_defaultPrintingAcceleration = defaultPrintingAcceleration;
}

//returns m_defaultPrintingAcceleration
int MotorController::defaultPrintingAcceleration()
{

    return *m_defaultPrintingAcceleration;
}

//sets *m_defaultTravelAcceleration to defaultTravelAcceleration
void MotorController::setDefaultTravelAcceleration(int defaultTravelAcceleration)
{

    *m_defaultTravelAcceleration = defaultTravelAcceleration;
}

//returns m_defaultTravelAcceleration
int MotorController::defaultTravelAcceleration()
{

    return *m_defaultTravelAcceleration;
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

//executed when the serialinterface receives a message
void MotorController::receive(QString text)
{

    //checks what the message says
    //executed when the message contains the position of an motor
    if(text.at(1) == "C"){

        //checks which motor the message is from
        //executed if the message is from the x-axis motor
        if(text.at(0) == QString("%1").arg(XAXIS_MOTORADRESS)){

            //sets the value of the current motorposition of the x-axis to the actual motorposition of the x-axis
            *m_currentXAxisMotorPosition = text.mid(1, text.indexOf("\r") - 2).toInt();
        }

        //executed if the message is from the y-axis motor
        else if(text.at(0) == QString("%1").arg(YAXIS_MOTORADRESS)){

            //sets the value of the current motorposition of the y-axis to the actual motorposition of the y-axis
            *m_currentYAxisMotorPosition = text.mid(1, text.indexOf("\r") - 2).toInt();
        }

        //executed if the message is from the z-axis motor
        else if(text.at(0) == QString("%1").arg(ZAXIS_MOTORADRESS)){

            //sets the value of the current motorposition of the z-axis to the actual motorposition of the z-axis
            *m_currentZAxisMotorPosition = text.mid(1, text.indexOf("\r") - 2).toInt();
        }

        //executed if the message is from the extruder motor
        else if(text.at(0) == QString("%1").arg(EXTRUDER_MOTORADRESS)){

            //sets the value of the current motorposition of the extruder to the actual motorposition of the extruder
            *m_currentExtruderMotorPosition = text.mid(1, text.indexOf("\r") - 2).toInt();
        }

        calculateMovementChange();
    }
}

//clears all the values
void MotorController::clear()
{

}

//pauses the motors
void MotorController::pause()
{

}

//continues the motors
void MotorController::play()
{

}

//stops all movement
void MotorController::stop()
{

}

//checks if the positions of the motors are the positions they should move to
void MotorController::checkMovement()
{

    //checks if the positions of the motors are the positions they should move to
    //executed if any of the positions is not
    if(*m_currentXAxisMotorPosition != *m_desiredXAxisMotorPosition || *m_currentYAxisMotorPosition != *m_desiredYAxisMotorPosition ||
            *m_currentZAxisMotorPosition != *m_desiredZAxisMotorPosition || *m_currentExtruderMotorPosition != *m_desiredExtruderMotorPosition){

        //sends the motors the command to return their current positions
        emit send(QString("#*C\r"));
        //starts a timer, that executes this function again after one millisecond
        QTimer::singleShot(1, this, SLOT(checkMovement()));
    }

    //executed when all the positions are
    else if(*m_currentXAxisMotorPosition == *m_desiredXAxisMotorPosition && *m_currentYAxisMotorPosition == *m_desiredYAxisMotorPosition &&
            *m_currentZAxisMotorPosition == *m_desiredZAxisMotorPosition && *m_currentExtruderMotorPosition == *m_desiredExtruderMotorPosition){

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

//checks if the positions on all axis are the actual positions and, if not, rights them
void MotorController::calculateMovementChange()
{

    //checks if the value of m_currentXAxisPosition is the actual current position on the x-axis
    //executed if the value of m_currentXAxisPosition is not the actual current position on the x-axis
    if(*m_currentXAxisPosition != *m_previousXAxisPosition + (qreal)(*m_currentXAxisMotorPosition) / (qreal)(XAXIS_MULTIPLIER)){

        //sets the value of m_currentXAxisPosition to the actual current position on the x-axis
        *m_currentXAxisPosition = *m_previousXAxisPosition + (qreal)(*m_currentXAxisMotorPosition) / (qreal)(XAXIS_MULTIPLIER);
        //emits the signal that the current position on the x-axis has changed
        emit currentXAxisPositionChanged(*m_currentXAxisPosition);
    }

    //checks if the value of m_currentYAxisPosition is the actual current position on the y-axis
    //executed if the value of m_currentYAxisPosition is not the actual current position on the y-axis
    if(*m_currentYAxisPosition != *m_previousYAxisPosition + (qreal)(*m_currentYAxisMotorPosition) / (qreal)(YAXIS_MULTIPLIER)){

        //sets the value of m_currentYAxisPosition to the actual current position on the y-axis
        *m_currentYAxisPosition = *m_previousYAxisPosition + (qreal)(*m_currentYAxisMotorPosition) / (qreal)(YAXIS_MULTIPLIER);
        //emits the signal that the current position on the y-axis has changed
        emit currentYAxisPositionChanged(*m_currentYAxisPosition);
    }

    //checks if the value of m_currentZAxisPosition is the actual current position on the z-axis
    //executed if the value of m_currentZAxisPosition is not the actual current position on the z-axis
    if(*m_currentZAxisPosition != *m_previousZAxisPosition + (qreal)(*m_currentZAxisMotorPosition) / (qreal)(ZAXIS_MULTIPLIER)){

        //sets the value of m_currentZAxisPosition to the actual current position on the z-axis
        *m_currentZAxisPosition = *m_previousZAxisPosition + (qreal)(*m_currentZAxisMotorPosition) / (qreal)(ZAXIS_MULTIPLIER);
        //emits the signal that the current position on the z-axis has changed
        emit currentZAxisPositionChanged(*m_currentZAxisPosition);
    }

    //checks if the value of m_currentExtruderPosition is the actual current position on the extruder
    //executed if the value of m_currentExxtruderPosition is not the actual current position on the extruder
    if(*m_currentExtruderPosition != *m_previousExtruderPosition + (qreal)(*m_currentExtruderMotorPosition) / (qreal)(EXTRUDER_MULTIPLIER)){

        //sets the value of m_currentExtruderPosition to the actual current position on the extruder
        *m_currentExtruderPosition = *m_previousExtruderPosition + (qreal)(*m_currentExtruderMotorPosition) / (qreal)(EXTRUDER_MULTIPLIER);
        //emits the signal that the current position on the extruder has changed
        emit currentExtruderPositionChanged(*m_currentExtruderPosition);
    }
}

//checks for commands in the buffer and executes them until the buffer is empty
void MotorController::checkBuffer()
{

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

            //sending the command to the buffer and removing it from the buffer
            emit send(m_commandBuffer->buffer.takeFirst());
            m_commandBuffer->bufferInfo.removeFirst();
        }

        //updates the movement in realtime and then executes this method again if there are still commands in the buffer
        checkMovement();
    }
}
