#ifndef IOMAINLOOP_H
#define IOMAINLOOP_H

#include <QObject>
#include "sensorlistener.h"
#include "fancontroller.h"
#include "heatingcontroller.h"
#include "iocontroller.h"
#include "lightingcontroller.h"

class IOMainLoop : public QObject
{
    Q_OBJECT
public:
    explicit IOMainLoop(QObject *parent = nullptr);

    void setSensorListener(SensorListener *sensorListener);
    void setFanController(FanController *fanController);
    void setHeatingController(HeatingController *heatingController);
    void setIOController(IOController *iOController);
    void setLightingController(LightingController *lightingController);

signals:

    void logEntry(QString logMessage, int code);

public slots:

    void startMainLoop();

private:

    void mainLoop();

    SensorListener *m_sensorListener;
    FanController *m_fanController;
    HeatingController *m_heatingController;
    IOController *m_iOController;
    LightingController *m_lightingController;

};

#endif // IOMAINLOOP_H
