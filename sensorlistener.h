#ifndef SENSORLISTENER_H
#define SENSORLISTENER_H

#include <QObject>

class SensorListener : public QObject
{
    Q_OBJECT
public:
    explicit SensorListener(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SENSORLISTENER_H