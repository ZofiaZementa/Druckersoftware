#include "machinecontroller.h"

MachineController::MachineController(QObject *parent) : QObject(parent)
{

    //defining pointers

    m_absolutePositioning = new bool;    //holds wether the movement of the axes is absolute or not
    m_absoluteExtruder = new bool;    //holds wether the movement of the extruders is absolute or not
    m_printerBedMeasurements = new int[9];    //holds the printerbed measurements used to calculate the printerbed tilt
    m_printerBedXAxisTilt = new int;    //holds the tilt of the printerbed in the x-axis direction in degrees
    m_printerBedYAxisTilt = new int;    //holds the tilt of the printerbed in the y-axis direction in degrees
    m_gCodeReader = new GCodeReader(this);
    m_motorController = new MotorController(this);
    m_heatingController = new HeatingController(this);
    m_sensorListener = new SensorListener(this);
    m_serialInterface = new SerialInterface(this);


}

MachineController::~MachineController()
{

    //deleting pointers

    delete m_absolutePositioning;
    delete m_absoluteExtruder;
    delete m_printerBedMeasurements;
    delete m_printerBedXAxisTilt;
    delete m_printerBedYAxisTilt;
}

//rapid linear move
//x = the position to move to on the x axis in mm, y = the position to move to on the y axis in mm, z = the position to move to on the z axis in mm
//e = the amount to extrude between the starting point and ending point in mm, f = the feedrate per minute of the move between the starting point and ending point
//s = flag to check if an endstop was hit (0 to ignore, 1 to check, 2 to see note)
bool MachineController::g0(int x, int y, int z, int e, int f, int s)
{

}

//linear move
//x = the position to move to on the x axis in mm, y = the position to move to on the y axis in mm, z = the position to move to on the z axis in mm
//e = the amount to extrude between the starting point and ending point in mm, f = the feedrate per minute of the move between the starting point and ending point
//s = flag to check if an endstop was hit (0 to ignore, 1 to check, 2 to see note)
bool MachineController::g1(int x, int y, int z, int e, int f, int s)
{

}

//clockwise arc
//x = the position to move to on the x axis in mm, y = the position to move to on the y axis in mm
//i = the point in x space from the current x position to maintain a constant distance from, j = the point in x space from the current x position to maintain a constant distance from
//e = the amount to extrude between the starting point and ending point in mm, f = the feedrate per minute of the move between the starting point and ending point
bool MachineController::g2(int x, int y, int i, int j, int e, int f)
{

}

//counter-clockwise arc
//x = the position to move to on the x axis in mm, y = the position to move to on the y axis in mm
//i = the point in x space from the current x position to maintain a constant distance from, j = the point in x space from the current x position to maintain a constant distance from
//e = the amount to extrude between the starting point and ending point in mm, f = the feedrate per minute of the move between the starting point and ending point
bool MachineController::g3(int x, int y, int i, int j, int e, int f)
{

}

//pause the machine for a period of time
//p = time to wait in milliseconds
bool MachineController::g4(int p)
{

}

//retracts the filament
//s = retract length in mm
bool MachineController::g10(int s)
{

}

//unretracts the filament
//s = retract length in mm
bool MachineController::g11(int s)
{

}

//moves to origin/home
//x = wether to move to origin on x-axis, y = wether to move to origin on y-axis, z = wether to move to origin on z-axis
bool MachineController::g28(bool x, bool y, bool z)
{

}

//sets absolute positioning
void MachineController::g90()
{

}

//sets relative positioning
void MachineController::g91()
{

}

//sets position
//x = new x-axis position, y = new y-axis position, z = new z-axis position, e = new extruder position
bool MachineController::g92(int x, int y, int z, int e)
{

}

//stop
//p = time to wait in milliseconds, s = time to wait in seconds
void MachineController::m0(int p, int s)
{

}

//sleep
void MachineController::m1()
{

}

//sets extruder to absolut mode
void MachineController::m82()
{

}

//sets extuder to relative mode
void MachineController::m83()
{

}

//set extruder temperature
//s = temperature in degrees celsius
bool MachineController::m104(int s)
{

}

//turn fan on
//p = fan number, s = fan speed(0 - 255)
bool MachineController::m106(int p, int s)
{

}

//turn fan off
bool MachineController::m107()
{

}

// set extruder temperature and wait
//s = minimum target temperature, waits until cooling, r = maximum target temperature, waits until cooling
bool MachineController::m109(int s, int r)
{

}

//set current line number
//n = line number, thus the expected next line after this command will be n + 1
void MachineController::m110(int n)
{

}

//emergency stop
//all movements are stopped immediately, heaters and motors are turned off
void MachineController::m112()
{

}

//wait until heating/cooling finished
//p = tool number, h = heater number
bool MachineController::m116(int p, int h)
{

}

//wait for bed temperature to reach target temperature
//s = target temperaturein degrees celsius
bool MachineController::m190(int s)
{

}

//set filament diameter
//d = sets filament diameter in mm for all extruders
bool MachineController::m200(int d)
{

}

//set max printing acceleration
//x = acceleration for x-axis, y = acceleration for y-axis, z = acceleration for z-axis, e = acceleration for all extruders
bool MachineController::m201(int x, int y, int z, int e)
{

}

//set max travel acceleration
//x = acceleration for x-axis, y = acceleration for y-axis, z = acceleration for z-axis, e = acceleration for all extruders
bool MachineController::m202(int x, int y, int z, int e)
{

}

//set max feedrate
//x = feedrate for x-axis, y = feedrate for y-axis, z = feedrate for z-axis, e = feedrate for all extruders
bool MachineController::m203(int x, int y, int z, int e)
{

}

//set default acceleration
//p = acceleration for printing moves, t = acceleration for travel moves
bool MachineController::m204(int p, int t)
{

}

//wait for current moves to finish
void MachineController::m400()
{

}

//returns m_absolutePositioning
bool MachineController::absolutePositioning()
{

    return m_absolutePositioning;
}

bool MachineController::absoluteExtruder()
{

    return m_absoluteExtruder;
}

//returns m_absoluteExtruder
void MachineController::movementFinished()
{

}

//clears buffer and m_unit
void MachineController::endstopHit()
{

}

//triggered when heating is finished
void MachineController::heatingFinished()
{

}

//pauses the machine
void MachineController::pause()
{

}

//continues the machine
void MachineController::play()
{

}

//resets the machine
void MachineController::reset()
{

}

//prints the file at filePath
void MachineController::print(QUrl filePath)
{

}

//triggered whzen overheating, turns off all heaters and motors,
//ramps the fans to 100%, displays message
void MachineController::overheat()
{

}

void MachineController::printerHeadSensorTriggered()
{


}

bool MachineController::measurePrinterBedTilt()
{

}

bool MachineController::calculatePrinterBedTilt()
{

}

