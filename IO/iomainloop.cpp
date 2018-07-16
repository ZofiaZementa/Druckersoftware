#include "iomainloop.h"

IOMainLoop::IOMainLoop(QObject *parent) : QObject(parent)
{   

    //logEntry

    //there to make the conversion from QString to int work
    bool ok;
    //emitting the logEntry, which is connected to the Logger
    emit logEntry(QString("IOMainLoop started successfully"), QString("0x060001").toInt(&ok, 10));
}

IOMainLoop::~IOMainLoop()
{

    //logEntry

    //there to make the conversion from QString to int work
    bool ok;
    //emitting the logEntry, which is connected to the Logger
    emit logEntry(QString("IOMainLoop exited successfully"), QString("0x060000").toInt(&ok, 10));
}

//sets the pointer m_sensorListener to the actual, used sensorListener
void IOMainLoop::setSensorListener(SensorListener *sensorListener)
{

    //sets the pointer m_sensorListener to sensorListener
    m_sensorListener = sensorListener;
}

//sets the pointer m_fanController to the actual, used fanController
void IOMainLoop::setFanController(FanController *fanController)
{

    //sets the pointer m_sensorListener to sensorListener
    m_fanController = fanController;
}

//sets the pointer m_heatingController to the actual, used heatingController
void IOMainLoop::setHeatingController(HeatingController *heatingController)
{

    //sets the pointer m_heatingController to heatingController
    m_heatingController = heatingController;
}

//sets the pointer m_iOController to the actual, used iOController
void IOMainLoop::setIOController(IOController *iOController)
{

    //sets the pointer m_iOController to iOController
    m_iOController = iOController;
}

//sets the pointer m_lightingController to the actual, used lightingController
void IOMainLoop::setLightingController(LightingController *lightingController)
{

    //sets the pointer m_lightingController to lightingController
    m_lightingController = lightingController;
}

//starts the iomainloop
void IOMainLoop::startMainLoop()
{

    //logEntry

    //there to make the conversion from QString to int work
    bool ok;
    //emitting the logEntry, which is connected to the Logger
    emit logEntry(QString("Successfully started IOMainLoop"), QString("0x060002").toInt(&ok, 16));
    //actually starts the mainloop-function
    mainLoop();
}

//io mainloop
void IOMainLoop::mainLoop()
{

    //loop
    while(true){

        //calls function to check the value of any fan-related IO has been changed / has to be changed, transfers a pointer to the IOController
        m_fanController->checkChanged(m_iOController);
        //calls function to check the value of any heating-related IO has been changed / has to be changed, transfers a pointer to the IOController
        m_heatingController->checkChanged(m_iOController);
        //calls function to check the value of any sensor-related IO has been changed / has to be changed, transfers a pointer to the IOController
        m_sensorListener->checkChanged(m_iOController);
        //calls function to check the value of any lighting-related IO has been changed / has to be changed, transfers a pointer to the IOController
        m_lightingController->checkChanged(m_iOController);
    }
}
