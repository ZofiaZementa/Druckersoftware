#include "iomainloop.h"

IOMainLoop::IOMainLoop(QObject *parent) : QObject(parent)
{

}

void IOMainLoop::setSensorListener(SensorListener *sensorListener)
{

    m_sensorListener = sensorListener;
}

void IOMainLoop::setFanController(FanController *fanController)
{

    m_fanController = fanController;
}

void IOMainLoop::setHeatingController(HeatingController *heatingController)
{

    m_heatingController = heatingController;
}

void IOMainLoop::setIOController(IOController *iOController)
{

    m_iOController = iOController;
}

void IOMainLoop::startMainLoop()
{

    bool ok;
    emit logEntry(QString("Successfully started IOMainLoop"), QString("0x060002").toInt(&ok, 16));
    mainLoop();
}

void IOMainLoop::mainLoop()
{

    while(true){

        m_fanController->checkChanged(m_iOController);
        m_heatingController->checkChanged(m_iOController);
        m_sensorListener->checkChanged(m_iOController);
    }
}
