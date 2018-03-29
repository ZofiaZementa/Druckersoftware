#include "motorcontroller.h"
#include <QDebug>

#define MOTOR_POSITIONINGMODE 1    //holds the positioning mode of the motors, see nanotec programming manual, page 51
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
    m_commandBuffer = new QStringList;    //holds all the commands that still need to be executed

    //motorsetup

    //setting the positioningtype to MOTOR_POSITIONINGMODE on al motors
    m_commandBuffer->append(QString("#*p%1\r").arg(MOTOR_POSITIONINGMODE));

    //sets the maximum decceleration

    //converts decceleration of the x-axis from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->append(QString("#%1B%2\r").arg(XAXIS_MOTORADRESS, (int)(XAXIS_MAXIMUM_BRAKE_DECCELERATION * XAXIS_MULTIPLIER / 64 / 1000)));
    //converts decceleration of the y-axis from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->append(QString("#%1B%2\r").arg(YAXIS_MOTORADRESS, (int)(YAXIS_MAXIMUM_BRAKE_DECCELERATION * YAXIS_MULTIPLIER / 64 / 1000)));
    //converts decceleration of the z-axis from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->append(QString("#%1B%2\r").arg(ZAXIS_MOTORADRESS, (int)(ZAXIS_MAXIMUM_BRAKE_DECCELERATION * ZAXIS_MULTIPLIER / 64 / 1000)));
    //converts decceleration of the extruder from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->append(QString("#%1B%2\r").arg(EXTRUDER_MOTORADRESS, (int)(EXTRUDER_MAXIMUM_BRAKE_DECCELERATION * EXTRUDER_MULTIPLIER / 64 / 1000)));

    //sets the maximum acceleration change

    //sets the maximum change of acceleration of the x-axis and appends it to the buffer
    m_commandBuffer->append(QString("#%1:b%2\r").arg(XAXIS_MOTORADRESS, XAXIS_MAXIMUM_ACCELERATION_CHANGE));
    //sets the maximum change of acceleration of the y-axis and appends it to the buffer
    m_commandBuffer->append(QString("#%1:b%2\r").arg(YAXIS_MOTORADRESS, YAXIS_MAXIMUM_ACCELERATION_CHANGE));
    //sets the maximum change of acceleration of the z-axis and appends it to the buffer
    m_commandBuffer->append(QString("#%1:b%2\r").arg(ZAXIS_MOTORADRESS, ZAXIS_MAXIMUM_ACCELERATION_CHANGE));
    //sets the maximum change of acceleration of the extruder and appends it to the buffer
    m_commandBuffer->append(QString("#%1:b%2\r").arg(EXTRUDER_MOTORADRESS, EXTRUDER_MAXIMUM_ACCELERATION_CHANGE));

    //set the maximum decceleration change

    //sets the maximum change of decceleration of the x-axis and appends it to the buffer
    m_commandBuffer->append(QString("#%1:B%2\r").arg(XAXIS_MOTORADRESS, XAXIS_MAXIMUM_DECCELERATION_CHANGE));
    //sets the maximum change of decceleration of the y-axis and appends it to the buffer
    m_commandBuffer->append(QString("#%1:B%2\r").arg(YAXIS_MOTORADRESS, YAXIS_MAXIMUM_DECCELERATION_CHANGE));
    //sets the maximum change of decceleration of the z-axis and appends it to the buffer
    m_commandBuffer->append(QString("#%1:B%2\r").arg(ZAXIS_MOTORADRESS, ZAXIS_MAXIMUM_DECCELERATION_CHANGE));
    //sets the maximum change of decceleration of the extruder and appends it to the buffer
    m_commandBuffer->append(QString("#%1:B%2\r").arg(EXTRUDER_MOTORADRESS, EXTRUDER_MAXIMUM_DECCELERATION_CHANGE));
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
    m_commandBuffer->append(QString("#%1u%2\r").arg(XAXIS_MOTORADRESS, XAXIS_MIN_STEPFREQUENCY));

    //converts acceleration from mm/s^2 to steps/second/millisecond and appends it to the buffer
    m_commandBuffer->append(QString("#%1b%2\r").arg(XAXIS_MOTORADRESS, (int)(*m_defaultTravelAcceleration * XAXIS_MULTIPLIER / 64 / 1000)));

    //checks if the speed is too high or too low
    if((int)(speed * XAXIS_MULTIPLIER / 64 / 60) > 1000000 || (int)(speed * XAXIS_MULTIPLIER / 64 / 60) < 1){

        return false;
    }

    else{

        //converts speed form mm/min to steps/second and appends it to the buffer
        m_commandBuffer->append(QString("#%1o%2\r").arg(XAXIS_MOTORADRESS, (int)(speed * XAXIS_MULTIPLIER / 64 / 60)));
    }

    //checks if the way to drive is negative
    if(value < 0){

        //sets the turning direction to MOTOR_NEGATIVE_TURNINGDIRECTION and appends it to the buffer
        m_commandBuffer->append(QString("#%1d%2\r").arg(XAXIS_MOTORADRESS, MOTOR_NEGATIVE_TURNINGDIRECTION));


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
        m_commandBuffer->append(QString("#%1d%2\r").arg(XAXIS_MOTORADRESS, MOTOR_POSITIVE_TURNINGDIRECTION));
    }

    else{

        return false;
    }

    //if the way to drive is too big, the motor is being driven multiple times
    while((int)(value * XAXIS_MULTIPLIER) > 100000000){

            value = value - 100000000;
            //sets the way to drive and appends it to the buffer
            m_commandBuffer->append(QString("#%1s100000000\r").arg(XAXIS_MOTORADRESS));
            //starts the motor and appends it to the buffer
            m_commandBuffer->append(QString("#%1A\r").arg(XAXIS_MOTORADRESS));
    }

    //sets the way to drive and appends it to the buffer
    m_commandBuffer->append(QString("#%1s%2\r").arg(XAXIS_MOTORADRESS, (int)(value * XAXIS_MULTIPLIER)));
    //starts the motor and appends it to the buffer
    m_commandBuffer->append(QString("#%1A\r").arg(XAXIS_MOTORADRESS));

    return true;
}

//absolutely moves y-axis to position in mm, speed = the speed the head is going to move in mm/min
bool MotorController::absoluteMoveYAxis(qreal position, qreal speed)
{

}

//relatively moves y-axis by value in mm, speed = the speed the head is going to move in mm/min
bool MotorController::relativeMoveYAxis(qreal value, qreal speed)
{

}

//absolutely moves z-axis to position in mm, speed = the speed the head is going to move in mm/min
bool MotorController::absoluteMoveZAxis(qreal position, qreal speed)
{

}

//relatively moves z-axis by value in mm, speed = the speed the head is going to move in mm/min
bool MotorController::relativeMoveZAxis(qreal value, qreal speed)
{

}

//absolutely moves extruder to position in mm, speed = the speed the head is going to move in mm/min
bool MotorController::absoluteMoveExtruder(qreal position, qreal speed)
{

}

//relatively moves extruder by value in mm, speed = the speed the head is going to move in mm/min
bool MotorController::relativeMoveExtruder(qreal value, qreal speed)
{

}

//absolutely moves all axes and extruder
//x = position to move to on the x-axis in mm, y = position to move to on the y-axis in mm
//z = position to move to on the z-axis in mm, e = position to move the extruder to in mm
//speed = the speed the head is going to move in mm/min
bool MotorController::absoluteMove(qreal x, qreal y, qreal z, qreal e, qreal speed)
{

}

//relatively moves all axes and extruder
//x = value to move by on the x-axis in mm, y = value to move by on the y-axis in mm
//z = value to move by on the z-axis in mm, e = value to move the extruder by in mm
//speed = the speed the head is going to move in mm/min
bool MotorController::relativeMove(qreal x, qreal y, qreal z, qreal e, qreal speed)
{

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
