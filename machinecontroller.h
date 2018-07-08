#ifndef MACHINECONTROLLER_H
#define MACHINECONTROLLER_H

#include <QObject>
//#include <QThread>
#include <QUrl>
#include <QSettings>
#include <QTimer>
#include "gcodereader.h"
#include "motorcontroller.h"
#include "serialinterface.h"

class MachineController : public QObject
{
    Q_OBJECT

public:
    explicit MachineController(QObject *parent = nullptr);
    ~MachineController();

    //defining enums

    enum PrinterState{Idle, CalibratingPosition, CalibratingBed, Printing, Paused};
    enum PositioningMode{AbsolutePositioning, RelativePositioning};
    enum ExtruderMode{AbsoluteExtruder, RelativeExtruder};

    //defining methods

    PositioningMode positioningMode();    //returns the PrintingMode
    ExtruderMode extruderMode();    //returns the ExtruderModes
    void setFilePath(QUrl filePath);
    QUrl filePath();
    void setLine(int line);
    int line();

public slots:

    bool g0(qreal x, qreal y, qreal z, qreal e, qreal f, int s);    //rapid linear move
    bool g1(qreal x, qreal y, qreal z, qreal e, qreal f, int s);    //linear move
    bool g2(qreal x, qreal y, qreal i, qreal j, qreal e, qreal f);    //clockwise arc
    bool g3(qreal x, qreal y, qreal i, qreal j, qreal e, qreal f);    //counter-clockwise arc
    void g4(int p);    //pause the machine for a period of time
    void g10(qreal s);    //retracts the filament
    void g11(qreal s);    //unretracts the filament
    bool g28(bool x, bool y, bool z);    //moves to origin/home
    void g90();    //sets absolute positioning
    void g91();    //sets relative positioning
    bool g92(bool xB, bool yB, bool zB, bool eB, qreal x, qreal y, qreal z, qreal e);    //set position
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
    void m140(int s);    //set bed temperature
    bool m190(int s);    //wait for bed temperature to reach target temperature
    bool m200(int d);    //set filament diameter
    void m201(qreal x, qreal y, qreal z, qreal e);    //set max printing acceleration
    void m202(qreal x, qreal y, qreal z, qreal e);    //set max travel acceleration
    void m203(qreal x, qreal y, qreal z, qreal e);    //set max feedrate
    void m204(qreal p, qreal t);    //set default acceleration
    void m400();    //wait for current moves to finish
    void errorOccured(QString errorMessage);
    void logEntryOccured(QString logMessage, int code);
    void calibratePosition();
    void calibrateBed();
    void movementFinished();
    void heatingFinished();
    bool pause();
    bool play();
    void reset();
    bool print();
    void overheat();
    void xAxisPositiveEndstopHit();
    void xAxisNegativeEndstopHit();
    void yAxisPositiveEndstopHit();
    void yAxisNegativeEndstopHit();
    void zAxisPositiveEndstopHit();
    void zAxisNegativeEndstopHit();
    void serialInterfaceSetup();

signals:

    void error(QString errorMessage);
    void logEntry(QString logMessage, int code);

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
    GCodeReader *m_gCodeReader;
    MotorController *m_motorController;
    SerialInterface *m_serialInterface;
    QSettings *m_settings;

};

#endif // MACHINECONTROLLER_H
