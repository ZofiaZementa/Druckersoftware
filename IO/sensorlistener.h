#ifndef SENSORLISTENER_H
#define SENSORLISTENER_H

#include <QObject>
#include "iocontroller.h"

class SensorListener : public QObject
{
    Q_OBJECT
public:
    explicit SensorListener(QObject *parent = nullptr);
    ~SensorListener();

    //called by the loop in IOMainLoop, checks if the value of any sensor-related IO has been changed / has to be changed
    void checkChanged(IOController *iOController);
    int hotEndTemp();
    int bedTemp();

signals:

    //emitted when the XAxisPositiveEndstop is hit
    void xAxisPositiveEndstopHit();
    //emitted when the XAxisNegativeEndstop is hit
    void xAxisNegativeEndstopHit();
    //emitted when the YAxisPositiveEndstop is hit
    void yAxisPositiveEndstopHit();
    //emitted when the YAxisNegativeEndstop is hit
    void yAxisNegativeEndstopHit();
    //emitted when the ZAxisPositiveEndstop is hit
    void zAxisPositiveEndstopHit();
    //emitted when the ZAxisNegativeEndstop is hit
    void zAxisNegativeEndstopHit();
    void hotEndTempChanged(int hotEndTemp);
    void bedTempChanged(int bedTemp);
    //emitted to make a logEntry
    void logEntry(QString logMessage, int code);

private:

    void initialiseVariables();

    QList<int> *m_values;

};

#endif // SENSORLISTENER_H
