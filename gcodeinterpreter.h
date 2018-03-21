#ifndef GCODEINTERPRETER_H
#define GCODEINTERPRETER_H

#include <QObject>

class GCodeInterpreter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int m_unit READ unit WRITE setUnit NOTIFY unitChanged)

public:
    explicit GCodeInterpreter(QObject *parent = nullptr);
    ~GCodeInterpreter();

    bool g0(int x, int y, int z, int e, int f, int s);    //rapid linear move
    bool g1(int x, int y, int z, int e, int f, int s);    //linear move
    bool g2(int x, int y, int i, int j, int e, int f);    //clockwise arc
    bool g3(int x, int y, int i, int j, int e, int f);    //counter-clockwise arc
    bool g4(int p);    //pause the machine for a period of time
    bool g10(int s);    //retracts the filament
    bool g11(int s);    //unretracts the filament
    void g20();    //sets unit to inches
    void g21();    //sets unit to millimeters
    bool g28(bool x, bool y, bool z);    //moves to origin/home
    void g90();    //sets absolute positioning
    void g91();    //sets relative positioning
    bool g92(int x, int y, int z, int e);    //set position
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
    bool m203(int x, int y, int z, int e);    //set max feedrate
    bool m204(int p, int t);    //set default acceleration
    void m400();    //wait for current moves to finish

public slots:

    void movementFinished();
    void clear();

signals:

private:

    int m_unit;

};

#endif // GCODEINTERPRETER_H
