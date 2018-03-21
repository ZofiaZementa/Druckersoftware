#include "gcodeinterpreter.h"

GCodeInterpreter::GCodeInterpreter(QObject *parent) : QObject(parent)
{

    m_unit = -1;
}

GCodeInterpreter::~GCodeInterpreter()
{

}

//rapid linear move
//x = the position to move to on the x axis in mm, y = the position to move to on the y axis in mm, z = the position to move to on the z axis in mm
//e = the amount to extrude between the starting point and ending point in mm, f = the feedrate per minute of the move between the starting point and ending point
//s = flag to check if an endstop was hit (0 to ignore, 1 to check, 2 to see note)
bool GCodeInterpreter::g0(int x, int y, int z, int e, int f, int s)
{

}

//linear move
//x = the position to move to on the x axis in mm, y = the position to move to on the y axis in mm, z = the position to move to on the z axis in mm
//e = the amount to extrude between the starting point and ending point in mm, f = the feedrate per minute of the move between the starting point and ending point
//s = flag to check if an endstop was hit (0 to ignore, 1 to check, 2 to see note)
bool GCodeInterpreter::g1(int x, int y, int z, int e, int f, int s)
{

}

//clockwise arc
//x = the position to move to on the x axis in mm, y = the position to move to on the y axis in mm
//i = the point in x space from the current x position to maintain a constant distance from, j = the point in x space from the current x position to maintain a constant distance from
//e = the amount to extrude between the starting point and ending point in mm, f = the feedrate per minute of the move between the starting point and ending point
bool GCodeInterpreter::g2(int x, int y, int i, int j, int e, int f)
{

}

//counter-clockwise arc
//x = the position to move to on the x axis in mm, y = the position to move to on the y axis in mm
//i = the point in x space from the current x position to maintain a constant distance from, j = the point in x space from the current x position to maintain a constant distance from
//e = the amount to extrude between the starting point and ending point in mm, f = the feedrate per minute of the move between the starting point and ending point
bool GCodeInterpreter::g3(int x, int y, int i, int j, int e, int f)
{

}

//pause the machine for a period of time
//p = time to wait in milliseconds
bool GCodeInterpreter::g4(int p)
{

}

//retracts the filament
//s = retract length in mm
bool GCodeInterpreter::g10(int s)
{

}

//unretracts the filament
//s = retract length in mm
bool GCodeInterpreter::g11(int s)
{

}

//sets unit to inches
void GCodeInterpreter::g20()
{

}

//sets unit to millimeters
void GCodeInterpreter::g21()
{

}

//moves to origin/home
//x = wether to move to origin on x-axis, y = wether to move to origin on y-axis, z = wether to move to origin on z-axis
bool GCodeInterpreter::g28(bool x, bool y, bool z)
{

}

//sets absolute positioning
void GCodeInterpreter::g90()
{

}

//sets relative positioning
void GCodeInterpreter::g91()
{

}

//sets position
//x = new x-axis position, y = new y-axis position, z = new z-axis position, e = new extruder position
bool GCodeInterpreter::g92(int x, int y, int z, int e)
{

}

//stop
//p = time to wait in milliseconds, s = time to wait in seconds
void GCodeInterpreter::m0(int p, int s)
{

}

//sleep
void GCodeInterpreter::m1()
{

}

//sets extruder to absolut mode
void GCodeInterpreter::m82()
{

}

//sets extuder to relative mode
void GCodeInterpreter::m83()
{

}

//set extruder temperature
//s = temperature in degrees celsius
bool GCodeInterpreter::m104(int s)
{

}

//turn fan on
//p = fan number, s = fan speed(0 - 255)
bool GCodeInterpreter::m106(int p, int s)
{

}

//turn fan off
bool GCodeInterpreter::m107()
{

}

// set extruder temperature and wait
//s = minimum target temperature, waits until cooling, r = maximum target temperature, waits until cooling
bool GCodeInterpreter::m109(int s, int r)
{

}

//set current line number
//n = line number, thus the expected next line after this command will be n + 1
void GCodeInterpreter::m110(int n)
{

}

//emergency stop
//all movements are stopped immediately, heaters and motors are turned off
void GCodeInterpreter::m112()
{

}

//wait until heating/cooling finished
//p = tool number, h = heater number
bool GCodeInterpreter::m116(int p, int h)
{

}

//wait for bed temperature to reach target temperature
//s = target temperaturein degrees celsius
bool GCodeInterpreter::m190(int s)
{

}

//set filament diameter
//d = sets filament diameter in mm for all extruders
bool GCodeInterpreter::m200(int d)
{

}

//set max printing acceleration
//x = acceleration for x-axis, y = acceleration for y-axis, z = acceleration for z-axis, e = acceleration for all extruders
bool GCodeInterpreter::m201(int x, int y, int z, int e)
{

}

//set max travel acceleration
//x = acceleration for x-axis, y = acceleration for y-axis, z = acceleration for z-axis, e = acceleration for all extruders
bool GCodeInterpreter::m202(int x, int y, int z, int e)
{

}

//set max feedrate
//x = feedrate for x-axis, y = feedrate for y-axis, z = feedrate for z-axis, e = feedrate for all extruders
bool GCodeInterpreter::m203(int x, int y, int z, int e)
{

}

//set default acceleration
//p = acceleration for printing moves, t = acceleration for travel moves
bool GCodeInterpreter::m204(int p, int t)
{

}

//wait for current moves to finish
void GCodeInterpreter::m400()
{

}

void GCodeInterpreter::movementFinished()
{

}

//clears buffer and m_unit
void GCodeInterpreter::clear()
{

}

