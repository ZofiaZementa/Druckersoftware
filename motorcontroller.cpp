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
    m_xAxisMaxFeedrate = new int;    //holds the maximum feedrate during movement on the x-axis
    m_yAxisMaxFeedrate = new int;    //holds the maximum feedrate during movement on the y-axis
    m_zAxisMaxFeedrate = new int;    //holds the maximum feedrate during movement on the z-axis
    m_extruderMaxFeedrate = new int;    //holds the maximum feedrate during movement on the extruder
    m_defaultPrintingAcceleration = new int;    //holds the default acceleration during printing for all axes including the extruder
    m_defaultTravelAcceleration = new int;    //holds the default acceleration during travel for all axes including the extruder
    m_currentXAxisPosition = new int;    //holds the current position on the x-axis
    m_currentYAxisPosition = new int;    //holds the current position on the y-axis
    m_currentZAxisPosition = new int;    //holds the current position on the z-axis
    m_currentExtruderPosition = new int;    //holds the current position on the extruder
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
}

//absolutely moves x-axis to position in mm
bool MotorController::absoluteMoveXAxis(int position)
{

}

//relatively moves x-axis by position in mm
bool MotorController::relativeMoveXAxis(int value)
{

}

//absolutely moves y-axis to position in mm
bool MotorController::absoluteMoveYAxis(int position)
{

}

//relatively moves y-axis by value in mm
bool MotorController::relativeMoveYAxis(int value)
{

}

//absolutely moves z-axis to position in mm
bool MotorController::absoluteMoveZAxis(int position)
{

}

//relatively moves z-axis by value in mm
bool MotorController::relativeMoveZAxis(int value)
{

}

//absolutely moves extruder to position in mm
bool MotorController::absoluteMoveExtruder(int position)
{

}

//relatively moves extruder by value in mm
bool MotorController::relativeMoveExtruder(int value)
{

}

//absolutely moves all axes and extruder
//x = position to move to on the x-axis, y = position to move to on the y-axis
//z = position to move to on the z-axis, e = position to move the extruder to
bool MotorController::absoluteMove(int x, int y, int z, int e)
{

}

//relatively moves all axes and extruder
//x = value to move by on the x-axis, y = value to move by on the y-axis
//z = value to move by on the z-axis, e = value to move the extruder by
bool MotorController::relativeMove(int x, int y, int z, int e)
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
void MotorController::setXAxisMaxFeedrate(int xAxisMaxFeedrate)
{

    *m_xAxisMaxFeedrate = xAxisMaxFeedrate;
}

//returns m_xAxisMaxFeedrate
int MotorController::xAxisMaxFeedrate()
{

    return *m_xAxisMaxFeedrate;
}

//sets m_yAxisMaxFeedrate to yAxisMaxFeedrate
void MotorController::setYAxisMaxFeedrate(int yAxisMaxFeedrate)
{

    *m_yAxisMaxFeedrate = yAxisMaxFeedrate;
}

//returns m_yAxisMaxFeedrate
int MotorController::yAxisMaxFeedrate()
{

    return *m_yAxisMaxFeedrate;
}

//sets m_zAxisMaxFeedrate to zAxisMaxFeedrate
void MotorController::setZAxisMaxFeedrate(int zAxisMaxFeedrate)
{

    *m_zAxisMaxFeedrate = zAxisMaxFeedrate;
}

//returns m_zAxisMaxFeedrate
int MotorController::zAxisMaxFeedrate()
{

    return *m_zAxisMaxFeedrate;
}

//sets m_extruderMaxFeedrate to extruderMaxFeedrate
void MotorController::setExtruderMaxFeedrate(int extruderMaxFeedrate)
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
