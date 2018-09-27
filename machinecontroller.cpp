#include "machinecontroller.h"
#include <QtMath>
#include <QTimer>
#include <QDebug>

#define PRINTER_MAXSPEED 15000    //holds the printers top speed in mm/min
#define XAXIS_LENGTH 400.0    //holds the length of the x-axis in mm
#define YAXIS_LENGTH 400.0    //holds the length of the z-axis in mm
#define ZAXIS_LENGTH 400.0    //holds the length of the y-axis in mm
#define STANDARD_BAUDRATE 115200    //holds the standard baudrate for the serialinterface

MachineController::MachineController(QObject *parent) : QObject(parent)
{

    //defining pointers

    m_printerState = new PrinterState;    //holds the currrent state of the printer
    m_positioningMode = new PositioningMode;    //holds wether the movement of the axes is absolute or not
    m_extruderMode = new ExtruderMode;    //holds wether the movement of the extruders is absolute or not
    m_printerBedMeasurements = new QList<qreal>;    //holds the printerbed measurements used to calculate the printerbed tilt
    m_printerBedXAxisTilt = new qreal;    //holds the tilt of the printerbed in the x-axis direction in radiants
    m_printerBedYAxisTilt = new qreal;    //holds the tilt of the printerbed in the y-axis direction in radiants
    m_gCodeReader = new GCodeReader(this);
    m_settings = new QSettings(QString("./settings.ini"), QSettings::IniFormat, this);


    //initialising variables

    *m_printerState = MachineController::Idle;
    *m_positioningMode = MachineController::RelativePositioning;
    *m_extruderMode = MachineController::RelativeExtruder;
    *m_printerBedXAxisTilt = 0.0;
    *m_printerBedYAxisTilt = 0.0;    

    //Signals and Slots

    //connecting the GCodeReader

    QObject::connect(m_gCodeReader, SIGNAL(g0(qreal, qreal, qreal, qreal, qreal, int)), this, SLOT(g0(qreal, qreal, qreal, qreal, qreal, int)));
    QObject::connect(m_gCodeReader, SIGNAL(g1(qreal, qreal, qreal, qreal, qreal, int)), this, SLOT(g1(qreal, qreal, qreal, qreal, qreal, int)));
    QObject::connect(m_gCodeReader, SIGNAL(g2(qreal, qreal, qreal, qreal, qreal, qreal)), this, SLOT(g2(qreal, qreal, qreal, qreal, qreal, qreal)));
    QObject::connect(m_gCodeReader, SIGNAL(g3(qreal, qreal, qreal, qreal, qreal, qreal)), this, SLOT(g3(qreal, qreal, qreal, qreal, qreal, qreal)));
    QObject::connect(m_gCodeReader, SIGNAL(g4(int)), this, SLOT(g4(int)));
    QObject::connect(m_gCodeReader, SIGNAL(g10(qreal)), this, SLOT(g10(qreal)));
    QObject::connect(m_gCodeReader, SIGNAL(g11(qreal)), this, SLOT(g11(qreal)));
    QObject::connect(m_gCodeReader, SIGNAL(g28(bool,bool,bool)), this, SLOT(g28(bool,bool,bool)));
    QObject::connect(m_gCodeReader, SIGNAL(g90()), this, SLOT(g90()));
    QObject::connect(m_gCodeReader, SIGNAL(g91()), this, SLOT(g91()));
    QObject::connect(m_gCodeReader, SIGNAL(g92(bool, bool, bool, bool, qreal, qreal, qreal, qreal)), this, SLOT(g92(bool, bool, bool, bool, qreal, qreal, qreal, qreal)));
    QObject::connect(m_gCodeReader, SIGNAL(m0(int, int)), this, SLOT(m0(int, int)));
    QObject::connect(m_gCodeReader, SIGNAL(m1()),this, SLOT(m1()));
    QObject::connect(m_gCodeReader, SIGNAL(m82()), this, SLOT(m82()));
    QObject::connect(m_gCodeReader, SIGNAL(m83()), this, SLOT(m82()));
    QObject::connect(m_gCodeReader, SIGNAL(m104(int)), this, SLOT(m104(int)));
    QObject::connect(m_gCodeReader, SIGNAL(m106(int,int)), this, SLOT(m106(int,int)));
    QObject::connect(m_gCodeReader, SIGNAL(m107()), this, SLOT(m107()));
    QObject::connect(m_gCodeReader, SIGNAL(m109(int,int)), this, SLOT(m109(int,int)));
    QObject::connect(m_gCodeReader, SIGNAL(m110(int)), this, SLOT(m110(int)));
    QObject::connect(m_gCodeReader, SIGNAL(m112()), this, SLOT(m112()));
    QObject::connect(m_gCodeReader, SIGNAL(m116(int,int)), this, SLOT(m116(int,int)));
    QObject::connect(m_gCodeReader, SIGNAL(m190(int)), this, SLOT(m190(int)));
    QObject::connect(m_gCodeReader, SIGNAL(m200(int)), this, SLOT(m200(int)));
    QObject::connect(m_gCodeReader, SIGNAL(m201(qreal,qreal,qreal,qreal)), this, SLOT(m201(qreal,qreal,qreal,qreal)));
    QObject::connect(m_gCodeReader, SIGNAL(m202(qreal,qreal,qreal,qreal)), this, SLOT(m202(qreal,qreal,qreal,qreal)));
    QObject::connect(m_gCodeReader, SIGNAL(m203(qreal,qreal,qreal,qreal)), this, SLOT(m203(qreal,qreal,qreal,qreal)));
    QObject::connect(m_gCodeReader, SIGNAL(m204(qreal,qreal)), this, SLOT(m204(qreal,qreal)));
    QObject::connect(m_gCodeReader, SIGNAL(m400()), this, SLOT(m400()));
    QObject::connect(m_gCodeReader, SIGNAL(logEntry(QString,int)), this, SLOT(logEntryOccured(QString,int)));

    bool ok;
    emit logEntry("MachineController started successfully", QString("0x000001").toInt(&ok, 16));
    emit setStatusLED(1, 0);
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

    //setting the pointers to NULL

    m_printerState = NULL;
    m_positioningMode = NULL;
    m_extruderMode = NULL;
    m_printerBedMeasurements = NULL;
    m_printerBedXAxisTilt = NULL;
    m_printerBedYAxisTilt = NULL;

    emit logEntry("MachineController exited successfully", 0);
    emit setStatusLED(0, 0);
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

void MachineController::setFilePath(QUrl filePath)
{

    m_gCodeReader->setFilePath(filePath);
}

QUrl MachineController::filePath()
{

    return m_gCodeReader->filePath();
}

void MachineController::setLine(int line)
{

    m_gCodeReader->setLineNumber(line);
}

int MachineController::line()
{

    return m_gCodeReader->lineNumber();
}

void MachineController::setPrinterBedMeasurements(QList<qreal> printerBedMeasurements)
{

    *m_printerBedMeasurements = printerBedMeasurements;
}

QList<qreal> MachineController::printerBedMeasurements()
{

    return *m_printerBedMeasurements;
}

void MachineController::setSerialInterface(SerialInterface *serialInterface)
{

    m_serialInterface = serialInterface;
}

void MachineController::setMotorController(MotorController *motorCotroller)
{

    m_motorController = motorCotroller;
}

//rapid linear move
//uses the fastest speed possible
//x = the position to move to on the x axis in mm, y = the position to move to on the y axis in mm, z = the position to move to on the z axis in mm
//e = the amount to extrude between the starting point and ending point in mm, f = the feedrate per minute of the move between the starting point and ending point
//s = flag to check if an endstop was hit (0 to ignore, 1 to check, 2 to see note)
bool MachineController::g0(qreal x, qreal y, qreal z, qreal e, qreal f, int s)
{

    if(f == -1.0){

        f = m_settings->value("motorsettings/maxFeedrate", PRINTER_MAXSPEED).toReal();
    }

    x = x + (qSin(*m_printerBedXAxisTilt) * z);
    z = qCos(*m_printerBedXAxisTilt) * z;
    y = y + (qSin(*m_printerBedYAxisTilt) * z);
    z = qCos(*m_printerBedYAxisTilt) * z;

    if(*m_positioningMode == MachineController::AbsolutePositioning){

        qreal xSpeed = (x - m_motorController->currentXAxisPosition()) / (qSqrt((x * x) + (y * y) + (z * z)) / f);
        qreal ySpeed = (y - m_motorController->currentXAxisPosition())/ (qSqrt((x * x) + (y * y) + (z * z)) / f);
        qreal zSpeed = (z - m_motorController->currentXAxisPosition()) / (qSqrt((x * x) + (y * y) + (z * z)) / f);
        qreal eSpeed = (e - m_motorController->currentExtruderPosition()) / (qSqrt((x * x) + (y * y) + (z * z)) / f);

        m_motorController->absoluteMove(x, y, z, e, xSpeed, ySpeed, zSpeed, eSpeed);
        return true;
    }

    else if(*m_positioningMode == MachineController::RelativePositioning){

        qreal xSpeed = x / (qSqrt((x * x) + (y * y) + (z * z)) / f);
        qreal ySpeed = y / (qSqrt((x * x) + (y * y) + (z * z)) / f);
        qreal zSpeed = z / (qSqrt((x * x) + (y * y) + (z * z)) / f);
        qreal eSpeed = e / (qSqrt((x * x) + (y * y) + (z * z)) / f);

        m_motorController->relativeMove(x, y, z, e, xSpeed, ySpeed, zSpeed, eSpeed);
        return true;
    }

    else{

        emit error(QString("Invalid PoisitioningMode"));
        return false;
    }
}

//linear move
//x = the position to move to on the x axis in mm, y = the position to move to on the y axis in mm, z = the position to move to on the z axis in mm
//e = the amount to extrude between the starting point and ending point in mm, f = the feedrate per minute of the move between the starting point and ending point
//s = flag to check if an endstop was hit (0 to ignore, 1 to check, 2 to see note)
bool MachineController::g1(qreal x, qreal y, qreal z, qreal e, qreal f, int s)
{

    if(f == -1.0){

        f = m_settings->value("motorsettings/defaultFeedrate", PRINTER_MAXSPEED).toReal();
    }

    x = x + (qSin(*m_printerBedXAxisTilt) * z);
    z = qCos(*m_printerBedXAxisTilt) * z;
    y = y + (qSin(*m_printerBedYAxisTilt) * z);
    z = qCos(*m_printerBedYAxisTilt) * z;

    //changing the unit of f from mm/min to mm/sec
    f = f / 60;

    if(*m_positioningMode == MachineController::AbsolutePositioning){

        qreal xSpeed = (x - m_motorController->currentXAxisPosition()) / (qSqrt((x * x) + (y * y) + (z * z)) / f);
        qreal ySpeed = (y - m_motorController->currentYAxisPosition()) / (qSqrt((x * x) + (y * y) + (z * z)) / f);
        qreal zSpeed = (z - m_motorController->currentZAxisPosition()) / (qSqrt((x * x) + (y * y) + (z * z)) / f);
        qreal eSpeed = (e - m_motorController->currentExtruderPosition()) / (qSqrt((x * x) + (y * y) + (z * z)) / f);

        m_motorController->absoluteMove(x, y, z, e, xSpeed, ySpeed, zSpeed, eSpeed);
        return true;
    }

    else if(*m_positioningMode == MachineController::RelativePositioning){


        qreal xSpeed = x / (qSqrt((x * x) + (y * y) + (z * z)) / f);
        qreal ySpeed = y / (qSqrt((x * x) + (y * y) + (z * z)) / f);
        qreal zSpeed = z / (qSqrt((x * x) + (y * y) + (z * z)) / f);
        qreal eSpeed = e / (qSqrt((x * x) + (y * y) + (z * z)) / f);

        m_motorController->relativeMove(x, y, z, e, xSpeed, ySpeed, zSpeed, eSpeed);
        return true;
    }

    else{

        emit error(QString("Invalid PoisitioningMode"));
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
void MachineController::g4(int p)
{

    QTimer::singleShot(p, Qt::PreciseTimer, m_gCodeReader, SLOT(nextLine()));
}

//retracts the filament
//s = retract length in mm
void MachineController::g10(qreal s)
{

    m_motorController->relativeMoveExtruder(-s, 100.0);
}

//unretracts the filament
//s = retract length in mm
void MachineController::g11(qreal s)
{

    m_motorController->relativeMoveExtruder(s, 100.0);
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

            m_motorController->absoluteMoveXAxis(0.0, (qreal)(XAXIS_LENGTH) / (2.0 / 60.0));
        }

        if(y == true){

            m_motorController->absoluteMoveYAxis(0.0, (qreal)(YAXIS_LENGTH) / (2.0 / 60.0));
        }

        if(z == true){

            m_motorController->absoluteMoveZAxis(0.0, (qreal)(YAXIS_LENGTH) / (2.0 / 60.0));
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
//this method doesnt trigger any physical motion
bool MachineController::g92(bool xB, bool yB, bool zB, bool eB, qreal x, qreal y, qreal z, qreal e)
{

    if(xB){

        m_motorController->setCurrentXAxisPosition(x);
    }

    if(yB){

        m_motorController->setCurrentYAxisPosition(y);
    }

    if(zB){

        m_motorController->setCurrentZAxisPosition(z);
    }

    if(eB){

        m_motorController->setCurrentExtruderPosition(e);
    }
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

    m_gCodeReader->setLineNumber(n);
    m_gCodeReader->nextLine();
}

//emergency stop
//all movements are stopped immediately, heaters, fans and motors are turned off
void MachineController::m112()
{

    m_motorController->stop();
}

//wait until heating/cooling finished
//p = tool number, h = heater number
bool MachineController::m116(int p, int h)
{

}

//set bed temperature
//s = temperature
void MachineController::m140(int s)
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
void MachineController::m201(qreal x, qreal y, qreal z, qreal e)
{

//    m_motorController->setXAxisMaxPrintingAcceleration(x);
//    m_motorController->setYAxisMaxPrintingAcceleration(y);
//    m_motorController->setZAxisMaxPrintingAcceleration(z);
//    m_motorController->setExtruderMaxPrintingAcceleration(e);
}

//set max travel acceleration
//x = acceleration for x-axis, y = acceleration for y-axis, z = acceleration for z-axis, e = acceleration for all extruders
void MachineController::m202(qreal x, qreal y, qreal z, qreal e)
{

//    m_motorController->setXAxisMaxTravelAcceleration(x);
//    m_motorController->setYAxisMaxTravelAcceleration(y);
//    m_motorController->setZAxisMaxTravelAcceleration(z);
//    m_motorController->setExtruderMaxTravelAcceleration(e);
}

//set max feedrate
//x = feedrate for x-axis, y = feedrate for y-axis, z = feedrate for z-axis, e = feedrate for all extruders
void MachineController::m203(qreal x, qreal y, qreal z, qreal e)
{

    m_motorController->setXAxisMaxFeedrate(x);
    m_motorController->setYAxisMaxFeedrate(y);
    m_motorController->setZAxisMaxFeedrate(z);
    m_motorController->setExtruderMaxFeedrate(e);
}

//set default acceleration
//p = acceleration for printing moves, t = acceleration for travel moves
void MachineController::m204(qreal p, qreal t)
{

    m_motorController->setDefaultPrintingAcceleration(p);
    m_motorController->setDefaultTravelAcceleration(t);
}

//wait for current moves to finish
void MachineController::m400()
{

}

void MachineController::errorOccured(QString errorMessage)
{

    emit error(errorMessage);
}

void MachineController::logEntryOccured(QString logMessage, int code)
{

    emit logEntry(logMessage, code);
}

void MachineController::calibratePosition()
{

    *m_printerState = MachineController::CalibratingPosition;
    m_motorController->relativeMoveXAxis((qreal)(-XAXIS_LENGTH), 200);
}

void MachineController::calibrateBed()
{

    measurePrinterBedTilt();
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
bool MachineController::pause()
{

}

//continues the machine
bool MachineController::play()
{

}

//resets the machine
void MachineController::reset()
{

}

//prints the file at filePath
bool MachineController::print()
{

    if(m_gCodeReader->filePath().isEmpty() == false && m_serialInterface->status() == SerialInterface::Connected){

        m_gCodeReader->load();
        m_gCodeReader->startReading();
        measurePrinterBedTilt();
        return true;
    }

    else{

        return false;
    }
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

    bool ok;
    emit logEntry(QString("Positive endstop on the x-axis hit"), QString("0x00FFFF").toInt(&ok, 16));
    emit error(QString("Positive endstop on the x-axis hit"));

    return;
}

void MachineController::xAxisNegativeEndstopHit()
{

    //stops motors from moving
    m_motorController->stop();

    if(*m_printerState == MachineController::CalibratingPosition){

        m_motorController->setCurrentXAxisPosition(0.0);
        //starts moving the y*-axis
        m_motorController->relativeMoveYAxis((qreal)(-XAXIS_LENGTH), 200);
    }

    else{

        bool ok;
        emit logEntry(QString("Negative endstop on the x-axis hit"), QString("0x00FFFE").toInt(&ok, 16));
        emit error(QString("Negative endstop on the x-axis hit"));

        return;
    }
}

void MachineController::yAxisPositiveEndstopHit()
{

    //stops motors from moving
    m_motorController->stop();

    bool ok;
    emit logEntry(QString("Positive enstop on the y-axis hit"), QString("0x00FFFD").toInt(&ok, 16));
    emit error(QString("Positive enstop on the y-axis hit"));

    return;
}

void MachineController::yAxisNegativeEndstopHit()
{

    //stops motors from moving
    m_motorController->stop();

    if(*m_printerState == MachineController::CalibratingPosition){

        m_motorController->setCurrentYAxisPosition(0.0);
        //starts moving the z-axis
        m_motorController->relativeMoveZAxis((qreal)(-ZAXIS_LENGTH), 200);
    }

    else{

        bool ok;
        emit logEntry(QString("Negative endstop on the y-axis hit"), QString("0x00FFFC").toInt(&ok, 16));
        emit error(QString("Negative endstop on the y-axis hit"));

        return;
    }
}

void MachineController::zAxisPositiveEndstopHit()
{

    //stops motors from moving
    m_motorController->stop();

    bool ok;
    emit logEntry(QString("Positive endstop on the z-axis hit"), QString("0x00FFFB").toInt(&ok, 16));
    emit error(QString("Positive endstop on the z-axis hit"));

    return;
}

void MachineController::zAxisNegativeEndstopHit()
{

    //stops motors from moving
    m_motorController->stop();

    if(*m_printerState == MachineController::CalibratingPosition){

        m_motorController->setCurrentZAxisPosition(0.0);
        //sets printer to Idle
        *m_printerState = MachineController::Idle;
    }

    else if(*m_printerState == MachineController::CalibratingBed){

        m_printerBedMeasurements->append(m_motorController->currentZAxisPosition());
        measurePrinterBedTilt();
    }

    else{

        bool ok;
        emit logEntry(QString("Negative endstop on the z-axis hit"), QString("0x00FFFA").toInt(&ok, 16));
        emit error(QString("Negative endstop on the z-axis hit"));
        return;
    }
}

void MachineController::serialInterfaceSetup()
{

    m_serialInterface->setBaudRate(m_settings->value("serialinterface/baudrate", STANDARD_BAUDRATE).toInt());
    m_serialInterface->setOpenMode(QIODevice::ReadWrite);
    m_serialInterface->setPortName(m_settings->value("serialinterface/portname", "tty0").toString());
    m_serialInterface->connect();
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

    if(*m_printerState != MachineController::CalibratingBed){

        *m_printerState = MachineController::CalibratingBed;
    }

    if(m_printerBedMeasurements->count() == 0){

        m_printerBedMeasurements->clear();
        *m_printerBedXAxisTilt = 0.0;
        *m_printerBedYAxisTilt = 0.0;
        //moves printerbed 10 mm away from the printerhead
        m_motorController->absoluteMoveZAxis(10.0, (qreal)(ZAXIS_LENGTH) / (2.0 / 60.0));
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(-10.0, 30.0);
    }

    else if(m_printerBedMeasurements->count() == 1){

        //moves the printerbed back down to 10mm away from the printerhead
        m_motorController->absoluteMoveZAxis(10.0, 3600.0);
        //moves the printerhead to the middle of the x-axis
        m_motorController->absoluteMoveXAxis((qreal)(XAXIS_LENGTH) / 2.0, (qreal)(XAXIS_LENGTH) / (2.0 / 60.0));
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(-10.0, 30.0);
    }

    else if(m_printerBedMeasurements->count() == 2){

        //moves the printerbed back down to 10mm away from the printerhead
        m_motorController->absoluteMoveZAxis(10.0, 3600.0);
        //moves the printerhead to the end of the x-axis
        m_motorController->absoluteMoveXAxis((qreal)(XAXIS_LENGTH), (qreal)(XAXIS_LENGTH) / (2.0 / 60.0));
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(-10.0, 30.0);
    }

    else if(m_printerBedMeasurements->count() == 3){

        //moves the printerbed back down to 10mm away from the printerhead
        m_motorController->absoluteMoveZAxis(10.0, 3600.0);
        //moves the printerhead to the beginning of the x-axis and the middle of the y-axis
        g0(0.0, (qreal)(YAXIS_LENGTH) / 2.0, 0.0, 0.0, -1.0, 1);
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(-10.0, 30.0);
    }

    else if(m_printerBedMeasurements->count() == 4){

        //moves the printerbed back down to 10mm away from the printerhead
        m_motorController->absoluteMoveZAxis(10.0, 3600.0);
        //moves the printerhead to the middle of the x-axis
        m_motorController->absoluteMoveXAxis((qreal)(XAXIS_LENGTH) / 2.0, (qreal)(XAXIS_LENGTH) / (2.0 / 60.0));
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(-10.0, 30.0);
    }

    else if(m_printerBedMeasurements->count() == 5){

        //moves the printerbed back down to 10mm away from the printerhead
        m_motorController->absoluteMoveZAxis(10.0, 3600.0);
        //moves the printerhead to the end of the x-axis
        m_motorController->absoluteMoveXAxis((qreal)(XAXIS_LENGTH), (qreal)(XAXIS_LENGTH) / (2.0 / 60.0));
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(-10.0, 30.0);
    }

    else if(m_printerBedMeasurements->count() == 6){

        //moves the printerbed back down to 10mm away from the printerhead
        m_motorController->absoluteMoveZAxis(10.0, 3600.0);
        //moves the printerhead to the beginning of the x-axis and the end of the y-axis
        g0(0.0, (qreal)(YAXIS_LENGTH), 0.0, 0.0, -1.0, 0);
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(-10.0, 30.0);
    }

    else if(m_printerBedMeasurements->count() == 7){

        //moves the printerbed back down to 10mm away from the printerhead
        m_motorController->absoluteMoveZAxis(10.0, 3600.0);
        //moves the printerhead to the middle of the x-axis
        m_motorController->absoluteMoveXAxis((qreal)(XAXIS_LENGTH) / 2.0, (qreal)(XAXIS_LENGTH) / (2.0 / 60.0));
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(-10.0, 30.0);
    }

    else if(m_printerBedMeasurements->count() == 8){

        //moves the printerbed back down to 10mm away from the printerhead
        m_motorController->absoluteMoveZAxis(10.0, 3600.0);
        //moves the printerhead to the end of the x-axis
        m_motorController->absoluteMoveXAxis((qreal)(XAXIS_LENGTH), (qreal)(XAXIS_LENGTH) / (2.0 / 60.0));
        //slowly moves the bed towards the printerhead, it's designed to hit the printerhead
        m_motorController->absoluteMoveZAxis(-10.0, 30.0);
    }

    else if(m_printerBedMeasurements->count() == 9){

        //homes all 3 axes
        g28(true, true, true);
        //calculates the tilt of the bed
        calculatePrinterBedTilt();

        //checks if the printerState is CalibratingBed
        //executed if it is
        if(*m_printerState == MachineController::CalibratingBed){

            //sets the printerState to Printing
            *m_printerState = MachineController::Printing;
            //requests the next line from GCodeInterpreter
            m_gCodeReader->nextLine();
        }
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
        xAxisTiltList.append((qAtan((m_printerBedMeasurements->at(0) - m_printerBedMeasurements->at(1)) / ((qreal)(XAXIS_LENGTH) / 2.0)) + qAtan((m_printerBedMeasurements->at(1) - m_printerBedMeasurements->at(2)) / ((qreal)(XAXIS_LENGTH) / 2.0))) / 2.0);
        //appending the average tilt of the second measuring line on the x-axis
        xAxisTiltList.append((qAtan((m_printerBedMeasurements->at(3) - m_printerBedMeasurements->at(4)) / ((qreal)(XAXIS_LENGTH) / 2.0)) + qAtan((m_printerBedMeasurements->at(4) - m_printerBedMeasurements->at(5)) / ((qreal)(XAXIS_LENGTH) / 2.0))) / 2.0);
        //appending the average tilt of the third measuring line on the x-axis
        xAxisTiltList.append((qAtan((m_printerBedMeasurements->at(6) - m_printerBedMeasurements->at(7)) / ((qreal)(XAXIS_LENGTH) / 2.0)) + qAtan((m_printerBedMeasurements->at(7) - m_printerBedMeasurements->at(8)) / ((qreal)(XAXIS_LENGTH) / 2.0))) / 2.0);

        //appending the average tilt of the first measuring line on the y-axis
        yAxisTiltList.append((qAtan((m_printerBedMeasurements->at(0) - m_printerBedMeasurements->at(3)) / ((qreal)(YAXIS_LENGTH) / 2.0)) + qAtan((m_printerBedMeasurements->at(3) - m_printerBedMeasurements->at(6)) / ((qreal)(YAXIS_LENGTH) / 2.0))) / 2.0);
        //appending the average tilt of the second measuring line on the y-axis
        yAxisTiltList.append((qAtan((m_printerBedMeasurements->at(1) - m_printerBedMeasurements->at(4)) / ((qreal)(YAXIS_LENGTH) / 2.0)) + qAtan((m_printerBedMeasurements->at(4) - m_printerBedMeasurements->at(7)) / ((qreal)(YAXIS_LENGTH) / 2.0))) / 2.0);
        //appending the average tilt of the third measuring line on the y-axis
        yAxisTiltList.append((qAtan((m_printerBedMeasurements->at(2) - m_printerBedMeasurements->at(5)) / ((qreal)(YAXIS_LENGTH) / 2.0)) + qAtan((m_printerBedMeasurements->at(5) - m_printerBedMeasurements->at(8)) / ((qreal)(YAXIS_LENGTH) / 2.0))) / 2.0);

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
