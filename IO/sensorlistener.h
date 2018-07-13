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

    void checkChanged(IOController *iOController);

signals:

    void xAxisPositiveEndstopHit();
    void xAxisNegativeEndstopHit();
    void yAxisPositiveEndstopHit();
    void yAxisNegativeEndstopHit();
    void zAxisPositiveEndstopHit();
    void zAxisNegativeEndstopHit();
    void logEntry(QString logMessage, int code);

private:

    QList<int> *m_values;

};

#endif // SENSORLISTENER_H
