#include "machinecontroller.h"
#include <QtMath>
#include <QTimer>
#include <QDebug>

MachineController::MachineController(QObject *parent) : QObject(parent)
{

    //defining pointers

    m_printerState = new PrinterState;    //holds the currrent state of the printer
    m_positioningMode = new PositioningMode;    //holds wether the movement of the axes is absolute or not
    m_extruderMode = new ExtruderMode;    //holds wether the movement of the extruders is absolute or not
    m_printerBedMeasurements = new QList<qreal>;    //holds the printerbed measurements used to calculate the printerbed tilt
    m_printerBedXAxisTilt = new qreal;    //holds the tilt of the printerbed in the x-axis direction in radiants
    m_printerBedYAxisTilt = new qreal;    //holds the tilt of the printerbed in the y-axis direction in radiants
    m_printerXAxisLength = new qreal;    //holds the the dimensions of the printer in the x-axis in mm
    m_printerYAxisLength = new qreal;    //holds the the dimensions of the printer in the y-axis in mm
    m_printerZAxisLength = new qreal;    //holds the the dimensions of the printer in the z-axis in mm
    m_printerMaxSpeed = new int;    //the printers top speed in mm/min
    m_fanController = new FanController(this);
    m_gCodeReader = new GCodeReader(this);
    m_motorController = new MotorController(this);
    m_heatingController = new HeatingController(this);
    m_sensorListener = new SensorListener(this);
    m_serialInterface = new SerialInterface(this);


    //initialising variables

    *m_printerXAxisLength = 500.0;
    *m_printerYAxisLength = 500.0;
    *m_printerZAxisLength = 500.0;

    //Signals and Slots

    //connecting the SensorListener

    QObject::connect(m_sensorListener, SIGNAL(xAxisPositiveEndstopHit()), this, SLOT(xAxisPositiveEndstopHit()));
    QObject::connect(m_sensorListener, SIGNAL(xAxisNegativeEndstopHit()), this, SLOT(xAxisNegativeEndstopHit()));
    QObject::connect(m_sensorListener, SIGNAL(yAxisPositiveEndstopHit()), this, SLOT(yAxisPositiveEndstopHit()));
    QObject::connect(m_sensorListener, SIGNAL(yAxisNegativeEndstopHit()), this, SLOT(yAxisNegativeEndstopHit()));
    QObject::connect(m_sensorListener, SIGNAL(zAxisPositiveEndstopHit()), this, SLOT(zAxisPositiveEndstopHit()));
    QObject::connect(m_sensorListener, SIGNAL(zAxisNegativeEndstopHit()), this, SLOT(zAxisNegativeEndstopHit()));


    //printer startup

    *m_printerState = MachineController::Startup;
    m_motorController->relativeMoveXAxis(-*m_printerXAxisLength, 200);
}

MachineController::~MachineController()
{

    //deleting pointers

    delete m_printerState;
    delete m_positioningMode;
    delete m_extruderMode;
    delete m_printerBedMeasurements;
    delete m_printerBedXAxisTilt;
    delete m_printerBedYAxisTilt;
    delete m_printerXAxisLength;
    delete m_printerYAxisLength;
    delete m_printerZAxisLength;
    delete m_printerMaxSpeed;

    //setting the pointers to NULL

    m_printerState = NULL;
    m_positioningMode = NULL;
    m_extruderMode = NULL;
    m_printerBedMeasurements = NULL;
    m_printerBedXAxisTilt = NULL;
    m_printerBedYAxisTilt = NULL;
    m_printerXAxisLength = NULL;
    m_printerYAxisLength = NULL;
    m_printerZAxisLength = NULL;
    m_printerMaxSpeed = NULL;

}

//rapid linear move
//uses the fastest speed possible
//x = the position to move to on the x axis in mm, y = the position to move to on the y axis in mm, z = the position to move to on the z axis in mm
//e = the amount to extrude between the starting point and ending point in mm
//s = flag to check if an endstop was hit (0 to ignore, 1 to check, 2 to see note)
bool MachineController::g0(qreal x, qreal y, qreal z, qreal e, qreal s)
{

    x = x + (qSin(*m_printerBedXAxisTilt) * z);
    z = qCos(*m_printerBedXAxisTilt) * z;
    y = y + (qSin(*m_printerBedYAxisTilt) * z);
    z = qCos(*m_printerBedYAxisTilt) * z;

    if(*m_positioningMode == MachineController::AbsolutePositioning){

        m_motorController->absoluteMove(x, y, z, e, *m_printerMaxSpeed);
        return true;
    }

    else if(*m_positioningMode == MachineController::RelativePositioning){

        m_motorController->relativeMove(x, y, z, e, *m_printerMaxSpeed);
        return true;
    }

    else{

        return false;
    }
}

//linear move
//x = the position to move to on the x axis in mm, y = the position to move to on the y axis in mm, z = the position to move to on the z axis in mm
//e = the amount to extrude between the starting point and ending point in mm, f = the feedrate per minute of the move between the starting point and ending point
//s = flag to check if an endstop was hit (0 to ignore, 1 to check, 2 to see note)
bool MachineController::g1(qreal x, qreal y, qreal z, qreal e, qreal f, qreal s)
{

    x = x + (qSin(*m_printerBedXAxisTilt) * z);
    z = qCos(*m_printerBedXAxisTilt) * z;
    y = y + (qSin(*m_printerBedYAxisTilt) * z);
    z = qCos(*m_printerBedYAxisTilt) * z;

    if(*m_positioningMode == MachineController::AbsolutePositioning){

        m_motorController->absoluteMove(x, y, z, e, f);
        return true;
    }

    else if(*m_positioningMode == MachineController::RelativePositioning){

        m_motorController->relativeMove(x, y, z, e, f);
        return true;
    }

    else{

        return false;
    }
}

//clockwise arc
//x = the position to move to on the x axis in mm, y = the position to move to on the y axis in mm
//i = the point in x space from the current x position to maintain a constant distance from, j = the point in x space from the current x position to maintain a constant distance from
//e = the amount to extrude between the starting point and ending point in mm, f = the feedrate per minute of the move between the starting point and ending point
bool MachineController::g2(qreal x, qreal y, qreal i, qreal j, qreal e, qreal f)
{

}

//counter-clockwise arc
//x = the position to move to on the x axis in mm, y = the position to move to on the y axis in mm
//i = the point in x space from the current x position to maintain a constant distance from, j = the point in x space from the current x position to maintain a constant distance from
//e = the amount to extrude between the starting point and ending point in mm, f = the feedrate per minute of the move between the starting point and ending point
bool MachineController::g3(qreal x, qreal y, qreal i, qreal j, qreal e, qreal f)
{

}

//pause the machine for a period of time
//p = time to wait in milliseconds
bool MachineController::g4(int p)
{

    QTimer::singleShot(p, m_gCodeReader, SLOT(nextLine()));
    return true;
}

//retracts the filament
//s = retract length in mm
bool MachineController::g10(qreal s)
{

}

//unretracts the filament
//s = retract length in mm
bool MachineController::g11(qreal s)
{

}

//moves to origin/home
//x = wether to move to origin on x-axis, y = wether to move to origin on y-axis, z = wether to move to origin on z-axis
bool MachineController::g28(bool x, bool y, bool z)
{

    if(x == false && y == false && z == false){

        return false;
    }

    else{

        if(x == true){

            m_motorController->absoluteMoveXAxis(0.0, *m_printerXAxisLength / (2.0 / 60.0));
        }

        if(y == true){

            m_motorController->absoluteMoveYAxis(0.0, *m_printerYAxisLength / (2.0 / 60.0));
        }

        if(z == true){

            m_motorController->absoluteMoveZAxis(0.0, *m_printerYAxisLength / (2.0 / 60.0));
        }

        return true;
    }
}

//sets absolute positioning
void MachineController::g90()
{

    *m_positioningMode = MachineController::AbsolutePositioning;
}

//sets relative positioning
void MachineController::g91()
{

    *m_positioningMode = MachineController::RelativePositioning;
}

//sets position
//x = new x-axis position, y = new y-axis position, z = new z-axis position, e = new extruder position
bool MachineController::g92(qreal x, qreal y, qreal z, qreal e)
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

    *m_extruderMode = MachineController::AbsoluteExtruder;
}

//sets extuder to relative mode
void MachineController::m83()
{

    *m_extruderMode = MachineController::RelativeExtruder;
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

    m_motorController->setXAxisMaxPrintingAcceleration(x);
    m_motorController->setYAxisMaxPrintingAcceleration(y);
    m_motorController->setZAxisMaxPrintingAcceleration(z);
    m_motorController->setExtruderMaxPrintingAcceleration(e);
}

//set max travel acceleration
//x = acceleration for x-axis, y = acceleration for y-axis, z = acceleration for z-axis, e = acceleration for all extruders
bool MachineController::m202(int x, int y, int z, int e)
{

    m_motorController->setXAxisMaxTravelAcceleration(x);
    m_motorController->setYAxisMaxTravelAcceleration(y);
    m_motorController->setZAxisMaxTravelAcceleration(z);
    m_motorController->setExtruderMaxTravelAcceleration(e);
}

//set max feedrate
//x = feedrate for x-axis, y = feedrate for y-axis, z = feedrate for z-axis, e = feedrate for all extruders
bool MachineController::m203(qreal x, qreal y, qreal z, qreal e)
{

}

//set default acceleration
//p = acceleration for printing moves, t = acceleration for travel moves
bool MachineController::m204(int p, int t)
{

    m_motorController->setDefaultPrintingAcceleration(p);
    m_motorController->setDefaultTravelAcceleration(t);
}

//wait for current moves to finish
void MachineController::m400()
{

}

//returns m_positioningMode
MachineController::PositioningMode MachineController::positioningMode()
{

    return *m_positioningMode;
}

//returns m_extruderMode
MachineController::ExtruderMode MachineController::extruderMode()
{

    return *m_extruderMode;
}

//triggered when movement is finished
void MachineController::movementFinished()
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
    measurePrinterBedTilt();
    m_gCodeReader->read(filePath);
}

//triggered whzen overheating, turns off all heaters and motors,
//ramps the fans to 100%, displays message
void MachineController::overheat()
{

}

void MachineController::xAxisPositiveEndstopHit()
{

    //stops motors from moving
    m_motorController->stop();
}

void MachineController::xAxisNegativeEndstopHit()
{

    //stops motors from moving
    m_motorController->stop();

    if(*m_printerState == MachineController::Printing){


    }

    else if(*m_printerState == MachineController::Startup){

        m_motorController->setCurrentXAxisPosition(0.0);
        //starts moving the y*-axis
        m_motorController->relativeMoveYAxis(-*m_printerYAxisLength, 200);
    }
}

void MachineController::yAxisPositiveEndstopHit()
{

    //stops motors from moving
    m_motorController->stop();
}

void MachineController::yAxisNegativeEndstopHit()
{

    //stops motors from moving
    m_motorController->stop();

    if(*m_printerState == MachineController::Printing){


    }

    else if(*m_printerState == MachineController::Startup){

        m_motorController->setCurrentYAxisPosition(0.0);
        //starts moving the z-axis
        m_motorController->relativeMoveZAxis(-*m_printerZAxisLength, 200);
    }
}

void MachineController::zAxisPositiveEndstopHit()
{

    //stops motors from moving
    m_motorController->stop();

    if(*m_printerState == MachineController::Printing){


    }

    else if(*m_printerState == MachineController::PrePrintSetup){

        m_printerBedMeasurements->append(m_motorController->currentZAxisPosition());
        measurePrinterBedTilt();
    }
}

void MachineController::zAxisNegativeEndstopHit()
{

    //stops motors from moving
    m_motorController->stop();

    if(*m_printerState == MachineController::Printing){


    }

    else if(*m_printerState == MachineController::Startup){

        m_motorController->setCurrentZAxisPosition(0.0);
        //sets printer to Idle
        *m_printerState = MachineController::Idle;
    }
}

//measures the tilt of the printerbed by measuring when it hits the z-axis positive endstop at 9 positions
//and then calculating the tilt in x and y direction
//the measurements are stored in m_printerBedMeasurements like this
//      876y
//      543y
//      210y
//      xxx
void MachineController::measurePrinterBedTilt()
{

    if(*m_printerState != MachineController::PrePrintSetup){

        *m_printerState = MachineController::PrePrintSetup;
    }

    if(m_printerBedMeasurements->count() == 0){

        m_printerBedMeasurements->clear();
        //moves printerbed 10 mm away from the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength - 10.0, *m_printerZAxisLength / (2.0 / 60.0));
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength + 10.0, 30);
    }

    else if(m_printerBedMeasurements->count() == 1){

        //moves the printerbed back down to 10mm away from the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength - 10.0, 3600);
        //moves the printerhead to the middle of the x-axis
        m_motorController->absoluteMoveXAxis(*m_printerXAxisLength / 2.0, *m_printerXAxisLength / (2.0 / 60.0));
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength + 10.0, 30);
    }

    else if(m_printerBedMeasurements->count() == 2){

        //moves the printerbed back down to 10mm away from the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength - 10.0, 3600);
        //moves the printerhead to the end of the x-axis
        m_motorController->absoluteMoveXAxis(*m_printerXAxisLength, *m_printerXAxisLength / (2.0 / 60.0));
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength + 10.0, 30);
    }

    else if(m_printerBedMeasurements->count() == 3){

        //moves the printerbed back down to 10mm away from the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength - 10.0, 3600);
        //moves the printerhead to the beginning of the x-axis and the middle of the y-axis
        m_motorController->absoluteMove(0, *m_printerYAxisLength / 2.0, -1.0, -1.0, *m_printerXAxisLength / (2.0 / 60.0));
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength + 10.0, 30);
    }

    else if(m_printerBedMeasurements->count() == 4){

        //moves the printerbed back down to 10mm away from the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength - 10.0, 3600);
        //moves the printerhead to the middle of the x-axis
        m_motorController->absoluteMoveXAxis(*m_printerXAxisLength / 2.0, *m_printerXAxisLength / (2.0 / 60.0));
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength + 10.0, 30);
    }

    else if(m_printerBedMeasurements->count() == 5){

        //moves the printerbed back down to 10mm away from the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength - 10.0, 3600);
        //moves the printerhead to the end of the x-axis
        m_motorController->absoluteMoveXAxis(*m_printerXAxisLength, *m_printerXAxisLength / (2.0 / 60.0));
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength + 10.0, 30);
    }

    else if(m_printerBedMeasurements->count() == 6){

        //moves the printerbed back down to 10mm away from the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength - 10.0, 3600);
        //moves the printerhead to the beginning of the x-axis and the end of the y-axis
        m_motorController->absoluteMove(0, *m_printerYAxisLength, -1.0, -1.0, *m_printerXAxisLength / (2.0 / 60.0));
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength + 10.0, 30);
    }

    else if(m_printerBedMeasurements->count() == 7){

        //moves the printerbed back down to 10mm away from the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength - 10.0, 3600);
        //moves the printerhead to the middle of the x-axis
        m_motorController->absoluteMoveXAxis(*m_printerXAxisLength / 2.0, *m_printerXAxisLength / (2.0 / 60.0));
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength + 10.0, 30);
    }

    else if(m_printerBedMeasurements->count() == 8){

        //moves the printerbed back down to 10mm away from the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength - 10.0, 3600);
        //moves the printerhead to the end of the x-axis
        m_motorController->absoluteMoveXAxis(*m_printerXAxisLength, *m_printerXAxisLength / (2.0 / 60.0));
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(*m_printerZAxisLength + 10.0, 30);
    }

    else if(m_printerBedMeasurements->count() == 9){

        //homes all 3 axes
        g28(true, true, true);
        //calculates the tilt of the bed
        calculatePrinterBedTilt();
        *m_printerState = MachineController::Printing;
        m_gCodeReader->nextLine();
    }

}

//calculates the tilt of the printer bed for the x and y-axis individually using the data collected with measurePrinterBedTilt()
//if the result is a positive angle, it means the printerbed is tilted towards the positive end of the axis,
//if the result is a negative angle, it means the printerbed is tilted towards the negative end of the axis
bool MachineController::calculatePrinterBedTilt()
{

    if(m_printerBedMeasurements->count() == 9){

        QList<qreal> xAxisTiltList;
        QList<qreal> yAxisTiltList;

        //appending the average tilt of the first measuring line on the x-axis
        xAxisTiltList.append((qAtan((m_printerBedMeasurements->at(0) - m_printerBedMeasurements->at(1)) / (*m_printerXAxisLength / 2.0)) + qAtan((m_printerBedMeasurements->at(1) - m_printerBedMeasurements->at(2)) / (*m_printerXAxisLength / 2.0))) / 2.0);
        //appending the average tilt of the second measuring line on the x-axis
        xAxisTiltList.append((qAtan((m_printerBedMeasurements->at(3) - m_printerBedMeasurements->at(4)) / (*m_printerXAxisLength / 2.0)) + qAtan((m_printerBedMeasurements->at(4) - m_printerBedMeasurements->at(5)) / (*m_printerXAxisLength / 2.0))) / 2.0);
        //appending the average tilt of the third measuring line on the x-axis
        xAxisTiltList.append((qAtan((m_printerBedMeasurements->at(6) - m_printerBedMeasurements->at(7)) / (*m_printerXAxisLength / 2.0)) + qAtan((m_printerBedMeasurements->at(7) - m_printerBedMeasurements->at(8)) / (*m_printerXAxisLength / 2.0))) / 2.0);

        //appending the average tilt of the first measuring line on the y-axis
        yAxisTiltList.append((qAtan((m_printerBedMeasurements->at(0) - m_printerBedMeasurements->at(3)) / (*m_printerYAxisLength / 2.0)) + qAtan((m_printerBedMeasurements->at(3) - m_printerBedMeasurements->at(6)) / (*m_printerYAxisLength / 2.0))) / 2.0);
        //appending the average tilt of the second measuring line on the y-axis
        yAxisTiltList.append((qAtan((m_printerBedMeasurements->at(1) - m_printerBedMeasurements->at(4)) / (*m_printerYAxisLength / 2.0)) + qAtan((m_printerBedMeasurements->at(4) - m_printerBedMeasurements->at(7)) / (*m_printerYAxisLength / 2.0))) / 2.0);
        //appending the average tilt of the third measuring line on the y-axis
        yAxisTiltList.append((qAtan((m_printerBedMeasurements->at(2) - m_printerBedMeasurements->at(5)) / (*m_printerYAxisLength / 2.0)) + qAtan((m_printerBedMeasurements->at(5) - m_printerBedMeasurements->at(8)) / (*m_printerYAxisLength / 2.0))) / 2.0);

        qreal help;

        //adding up all the values of all three measuring lines on the x-axis to help
        for(int i = 0;i < xAxisTiltList.count();i++){

            help = help + xAxisTiltList.at(i);
        }

        //calculating and writing the average of all three measuring lines on the x-axis to m_printerBedXAxisTilt
        *m_printerBedXAxisTilt = help / xAxisTiltList.count();

        //resetting help
        help = 0.0;

        //adding up all the values of all three measuring lines on the y-axis to help
        for(int i = 0;i < yAxisTiltList.count();i++){

            help = help + yAxisTiltList.at(i);
        }

        //calculating and writing the average of all three measuring lines on the y-axis to m_printerBedYAxisTilt
        *m_printerBedYAxisTilt = help / yAxisTiltList.count();

        return true;
    }

    else{

        return false;
    }
}

