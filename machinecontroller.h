#ifndef MACHINECONTROLLER_H
#define MACHINECONTROLLER_H

#include <QObject>
//#include <QThread>
#include <QUrl>
#include "fancontroller.h"
#include "gcodereader.h"
#include "motorcontroller.h"
#include "heatingcontroller.h"
#include "sensorlistener.h"
#include "serialinterface.h"

class MachineController : public QObject
{
    Q_OBJECT

public:
    explicit MachineController(QObject *parent = nullptr);
    ~MachineController();

    //defining enums

    enum PrinterState{Idle, Startup, PrePrintSetup, Printing, Paused};
    enum PositioningMode{AbsolutePositioning, RelativePositioning};
    enum ExtruderMode{AbsoluteExtruder, RelativeExtruder};

    //defining methods

    bool g0(qreal x, qreal y, qreal z, qreal e, qreal s);    //rapid linear move
    bool g1(qreal x, qreal y, qreal z, qreal e, qreal f, qreal s);    //linear move
    bool g2(qreal x, qreal y, qreal i, qreal j, qreal e, qreal f);    //clockwise arc
    bool g3(qreal x, qreal y, qreal i, qreal j, qreal e, qreal f);    //counter-clockwise arc
    bool g4(int p);    //pause the machine for a period of time
    bool g10(qreal s);    //retracts the filament
    bool g11(qreal s);    //unretracts the filament
    bool g28(bool x, bool y, bool z);    //moves to origin/home
    void g90();    //sets absolute positioning
    void g91();    //sets relative positioning
    bool g92(qreal x, qreal y, qreal z, qreal e);    //set position
    void m0(int p, int s);    //stop
    void m1();    //sleep
    void m82();    //sets extruder to absolut mode
    void m83();    //sets extuder to relative mode
    bool m104(int s);   //set extruder temperature
    bool m106(int p, int s);    //turn fan on
    bool m107();    //turn fan off
    bool m109(int s, int r);    //set extruder temperature and wait
    void m110(int n);    //set current line number
    void m112();    //emergency stop
    bool m116(int p, int h);    //wait until heating/cooling finished
    bool m190(int s);    //wait for bed temperature to reach target temperature
    bool m200(int d);    //set filament diameter
    bool m201(int x, int y, int z, int e);    //set max printing acceleration
    bool m202(int x, int y, int z, int e);    //set max travel acceleration
    bool m203(qreal x, qreal y, qreal z, qreal e);    //set max feedrate
    bool m204(int p, int t);    //set default acceleration
    void m400();    //wait for current moves to finish
    PositioningMode positioningMode();    //returns the PrintingMode
    ExtruderMode extruderMode();    //returns the ExtruderModes

public slots:

    void movementFinished();
    void heatingFinished();
    void pause();
    void play();
    void reset();
    void print(QUrl filePath);
    void overheat();
    void xAxisPositiveEndstopHit();
    void xAxisNegativeEndstopHit();
    void yAxisPositiveEndstopHit();
    void yAxisNegativeEndstopHit();
    void zAxisPositiveEndstopHit();
    void zAxisNegativeEndstopHit();

signals:

private:

    //defining methods

    void measurePrinterBedTilt();
    bool calculatePrinterBedTilt();

    //defining pointers

    PrinterState *m_printerState;
    PositioningMode *m_positioningMode;
    ExtruderMode *m_extruderMode;
    QList<qreal> *m_printerBedMeasurements;
    qreal *m_printerBedXAxisTilt;
    qreal *m_printerBedYAxisTilt;
    int *m_printerMaxSpeed;
    FanController *m_fanController;
    GCodeReader *m_gCodeReader;
    MotorController *m_motorController;
    HeatingController *m_heatingController;
    SensorListener *m_sensorListener;
    SerialInterface *m_serialInterface;
    qreal *m_printerXAxisLength;
    qreal *m_printerYAxisLength;
    qreal *m_printerZAxisLength;

};

#endif // MACHINECONTROLLER_H
