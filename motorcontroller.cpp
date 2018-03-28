#include "motorcontroller.h"
#include <QDebug>

MotorController::MotorController(QObject *parent) : QObject(parent)
{
    //defining pointers

    m_xAxisMaxPrintingAcceleration = new int;    //holds the maximum acceleration for the x-axis during printing
    m_xAxisMaxTravelAcceleration = new int;    //holds the maximum acceleration for the x-axis during travel
    m_yAxisMaxPrintingAcceleration = new int;    //holds the maximum acceleration for the y-axis during printing
    m_yAxisMaxTravelAcceleration = new int;    //holds the maximum acceleration for the y-axis during travel
    m_zAxisMaxPrintingAcceleration = new int;    //holds the maximum acceleration for the z-axis during printing
    m_zAxisMaxTravelAcceleration = new int;    //holds the maximum acceleration for the z-axis during travel
    m_extruderMaxPrintingAcceleration = new int;    //holds the maximum acceleration for the extruder during printing
    m_extruderMaxTravelAcceleration = new int;    //holds the maximum acceleration for the extruder during travel
    m_xAxisMaxFeedrate = new qreal;    //holds the maximum feedrate during movement on the x-axis
    m_yAxisMaxFeedrate = new qreal;    //holds the maximum feedrate during movement on the y-axis
    m_zAxisMaxFeedrate = new qreal;    //holds the maximum feedrate during movement on the z-axis
    m_extruderMaxFeedrate = new qreal;    //holds the maximum feedrate during movement on the extruder
    m_defaultPrintingAcceleration = new int;    //holds the default acceleration during printing for all axes including the extruder
    m_defaultTravelAcceleration = new int;    //holds the default acceleration during travel for all axes including the extruder
    m_currentXAxisPosition = new qreal;    //holds the current position on the x-axis
    m_currentYAxisPosition = new qreal;    //holds the current position on the y-axis
    m_currentZAxisPosition = new qreal;    //holds the current position on the z-axis
    m_currentExtruderPosition = new qreal;    //holds the current position on the extruder
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
}

//absolutely moves x-axis to position in mm, speed = the speed the head is going to move in mm/min
bool MotorController::absoluteMoveXAxis(qreal position, qreal speed)
{

}

//relatively moves x-axis by position in mm, speed = the speed the head is going to move in mm/min
bool MotorController::relativeMoveXAxis(qreal value, qreal speed)
{

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

}

//returns m_currentYAxisPosition
qreal MotorController::currentYAxisPosition()
{

}

//returns m_currentZAxisPosition
qreal MotorController::currentZAxisPosition()
{

}

//returns m_currentExtruderPosition
qreal MotorController::currentExtruderPosition()
{

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
