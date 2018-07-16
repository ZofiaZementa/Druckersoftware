#include "cmduimachinecontrollerinterface.h"

CmdUIMachineControllerInterface::CmdUIMachineControllerInterface(QObject *parent) : QObject(parent)
{

}

void CmdUIMachineControllerInterface::setMachineController(MachineController *machineController)
{

    m_machineController = machineController;
}

void CmdUIMachineControllerInterface::g0(qreal x, qreal y, qreal z, qreal e, qreal f, int s)
{

    m_machineController->g0(x, y, z, e, f, s);
}

void CmdUIMachineControllerInterface::reset()
{

    m_machineController->reset();
}

void CmdUIMachineControllerInterface::pause(bool *ret)
{

    *ret = m_machineController->pause();
}

void CmdUIMachineControllerInterface::play(bool *ret)
{

    *ret = m_machineController->play();
}

void CmdUIMachineControllerInterface::print(bool *ret)
{

    *ret = m_machineController->print();
}

void CmdUIMachineControllerInterface::setFilePath(QUrl filePath)
{

    m_machineController->setFilePath(filePath);
}

void CmdUIMachineControllerInterface::setLine(int line)
{

    m_machineController->setLine(line);
}
