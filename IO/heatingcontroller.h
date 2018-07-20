#ifndef HEATINGCONTROLLER_H
#define HEATINGCONTROLLER_H

#include <QObject>
#include "iocontroller.h"
#include "sensorlistener.h"

class HeatingController : public QObject
{
    Q_OBJECT

    enum HeatingState{Idle, MaintainingTemp, WaitingForBedToReachTargetTemp, WaitingForHotEndToReachTargetTemp};

public:
    explicit HeatingController(QObject *parent = nullptr);
    ~HeatingController();

    void checkChanged(IOController *iOController, SensorListener *sensorListener);

signals:

    void hotEndReachedTargetTemp(int temp);
    void bedReachedTargetTemp(int temp);
    void logEntry(QString logMessage, int code);
    void error(QString errorMessage);

public slots:

    void waitForHotEndToReachTargetTemp(int targetTemp);
    void waitForBedToReachTargetTemp(int targetTemp);
    bool heatHotEnd(int targetTemp);
    bool heatBed(int targetTemp);
    void stopHeatingHotEnd();
    void stopHeatingBed();

private:

    QList<int> *m_targetTemps;
    HeatingState *m_heatingState;

};

#endif // HEATINGCONTROLLER_H
