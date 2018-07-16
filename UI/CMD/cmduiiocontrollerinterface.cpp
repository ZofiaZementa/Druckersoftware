#include "cmduiiocontrollerinterface.h"

CmdUIIOControllerInterface::CmdUIIOControllerInterface(QObject *parent) : QObject(parent)
{

}

void CmdUIIOControllerInterface::setIOController(IOController *iOController)
{

    m_iOController = iOController;
}

void CmdUIIOControllerInterface::iOControllerWrite(QString pinName, int value, bool *ret)
{

    *ret = m_iOController->writeVariableValue(pinName, value);
}

void CmdUIIOControllerInterface::iOControllerRead(QString pinName, int *ret)
{

    *ret = m_iOController->readVariableValue(pinName);
}
