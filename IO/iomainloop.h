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
    ~IOMainLoop();

    //sets the pointer m_sensorListener to the actual, used sensorListener
    void setSensorListener(SensorListener *sensorListener);
    //sets the pointer m_fanController to the actual, used fanController
    void setFanController(FanController *fanController);
    //sets the pointer m_heatingController to the actual, used heatingController
    void setHeatingController(HeatingController *heatingController);
    //sets the pointer m_iOController to the actual, used iOController
    void setIOController(IOController *iOController);
    //sets the pointer m_lightingController to the actual, used lightingController
    void setLightingController(LightingController *lightingController);

signals:

    //emitted to make a logEntry
    void logEntry(QString logMessage, int code);

public slots:

    //starts the iomainloop
    void startMainLoop();

private:

    //io mainloop
    void mainLoop();

    //pointer to the SensorListener
    SensorListener *m_sensorListener;
    //pointer to the SensorListener
    FanController *m_fanController;
    //pointer to the FanController
    HeatingController *m_heatingController;
    //pointer to the HeatingController
    IOController *m_iOController;
    //pointer to the LightingController
    LightingController *m_lightingController;

};

#endif // IOMAINLOOP_H
