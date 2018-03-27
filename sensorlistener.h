#ifndef SENSORLISTENER_H
#define SENSORLISTENER_H

#include <QObject>

class SensorListener : public QObject
{
    Q_OBJECT
public:
    explicit SensorListener(QObject *parent = nullptr);

signals:

    void xAxisPositiveEndstopHit();
    void xAxisNegativeEndstopHit();
    void yAxisPositiveEndstopHit();
    void yAxisNegativeEndstopHit();
    void zAxisPositiveEndstopHit();
    void zAxisNegativeEndstopHit();

public slots:
};

#endif // SENSORLISTENER_H
