#include "heatingcontroller.h"

HeatingController::HeatingController(QObject *parent) : QObject(parent)
{

    //initialising pointers

    m_targetTemps = new QList<int>;
    m_heatingState = new HeatingState;

    *m_heatingState = HeatingState::Idle;

    //there to make the conversion from QString to int work
    bool ok;
    //emitting the logEntry, which is connected to the Logger
    emit logEntry(QString("HeatingController started successfully"), QString("0x030001").toInt(&ok, 10));
}

HeatingController::~HeatingController()
{

    //deleting pointers

    delete m_targetTemps;
    delete m_heatingState;

    //setting pointers to NULL

    m_targetTemps = NULL;
    m_heatingState = NULL;

    //there to make the conversion from QString to int work
    bool ok;
    //emitting the logEntry, which is connected to the Logger
    emit logEntry(QString("HeatingController exited successfully"), QString("0x030000").toInt(&ok, 10));
}

void HeatingController::checkChanged(IOController *iOController, SensorListener *sensorListener)
{

    //checks if the status of the hotEnd needs to be changed
    //triggered if it has to be changed to 1
    if(sensorListener->hotEndTemp() < m_targetTemps->at(0) && iOController->readVariableValue(QString("hotEnd")) == 0){

        //checks if the setting of the hotEnd value was successfull
        //triggered if it was
        if(iOController->writeVariableValue(QString("hotEnd"), 1) == true){

            //there to make the conversion from QString to int work
            bool ok;
            //emitting the logEntry, which is connected to the Logger
            emit logEntry(QString("HotEnd heater turned on"), QString("0x030002").toInt(&ok, 10));
        }

        //triggered if it wasn't
        else{

            //there to make the conversion from QString to int work
            bool ok;
            //emitting the logEntry, which is connected to the Logger
            emit logEntry(QString("HotEnd heater couldn't be turned on"), QString("0x03FFFF").toInt(&ok, 10));
            emit error(QString("HotEnd heater couldn't be turned on"));
        }
    }

    //checks if the status of the hotEnd needs to be changed
    //triggered if it has to be changed to 0
    else if(sensorListener->hotEndTemp() >= m_targetTemps->at(0) && iOController->readVariableValue(QString("hotEnd")) == 1){

        //checks if the setting of the hotEnd value was successfull
        //triggered if it was
        if(iOController->writeVariableValue(QString("hotEnd"), 0) == true){

            //there to make the conversion from QString to int work
            bool ok;
            //emitting the logEntry, which is connected to the Logger
            emit logEntry(QString("HotEnd heater turned off"), QString("0x030003").toInt(&ok, 10));
        }

        //triggered if it wasn't
        else{

            //there to make the conversion from QString to int work
            bool ok;
            //emitting the logEntry, which is connected to the Logger
            emit logEntry(QString("HotEnd heater couldn't be turned off"), QString("0x03FFFE").toInt(&ok, 10));
            emit error(QString("HotEnd heater couldn't be turned off"));
        }

        //checks wether to let everyone know that the HotEnd has reached TargetTemp
        //triggered if it has to
        if(*m_heatingState == HeatingState::WaitingForHotEndToReachTargetTemp){

            //lets everyone know that the HotEnd has reached TargetTemp
            emit hotEndReachedTargetTemp(m_targetTemps->at(0));
            //sets the HeatingState to MaintainingTemp
            *m_heatingState = HeatingState::MaintainingTemp;
        }
    }

    //checks if the status of the bed needs to be changed
    //triggered if it has to be changed to 1
    if(sensorListener->bedTemp() < m_targetTemps->at(0) && iOController->readVariableValue(QString("bed")) == 0){

        //checks if the setting of the bed value was successfull
        //triggered if it was
        if(iOController->writeVariableValue(QString("bed"), 1) == true){

            //there to make the conversion from QString to int work
            bool ok;
            //emitting the logEntry, which is connected to the Logger
            emit logEntry(QString("Bed heater turned on"), QString("0x030004").toInt(&ok, 10));
        }

        //triggered if it wasn't
        else{

            //there to make the conversion from QString to int work
            bool ok;
            //emitting the logEntry, which is connected to the Logger
            emit logEntry(QString("Bed heater couldn't be turned on"), QString("0x03FFFD").toInt(&ok, 10));
            emit error(QString("Bed heater couldn't be turned on"));
        }
    }

    //triggered if it has to be changed to 0
    else if(sensorListener->bedTemp() >= m_targetTemps->at(0) && iOController->readVariableValue(QString("bed")) == 1){

        //checks if the setting of the bed value was successfull
        //triggered if it was
        if(iOController->writeVariableValue(QString("bed"), 0) == true){

            //there to make the conversion from QString to int work
            bool ok;
            //emitting the logEntry, which is connected to the Logger
            emit logEntry(QString("Bed heater turned off"), QString("0x030005").toInt(&ok, 10));
        }

        //triggered if it wasn't
        else{

            //there to make the conversion from QString to int work
            bool ok;
            //emitting the logEntry, which is connected to the Logger
            emit logEntry(QString("Bed heater couldn't be turned off"), QString("0x03FFFC").toInt(&ok, 10));
            emit error(QString("Bed heater couldn't be turned off"));
        }

        //checks wether to let everyone know that the Bed has reached TargetTemp
        //triggered if it has to
        if(*m_heatingState == HeatingState::WaitingForBedToReachTargetTemp){

            //lets everyone know that the Bed has reached TargetTemp
            emit bedReachedTargetTemp(m_targetTemps->at(1));
            //sets the HeatingState to MaintainingTemp
            *m_heatingState = HeatingState::MaintainingTemp;
        }
    }

}

//sets the hotEnd target temperature to targetTemp, and sets the HeatingState to WaitingForHotEndToReachTargetTemp so the checkChanged function knows to wait for
//the HotEnd to reach the targetTemp
void HeatingController::waitForHotEndToReachTargetTemp(int targetTemp)
{

    //sets the heatingState to WaitingForHotEndToReachTargetTemp
    *m_heatingState = HeatingState::WaitingForHotEndToReachTargetTemp;
    //sets the HotEnd TargetTemp to targetTemp
    (*m_targetTemps)[0] = targetTemp;

    //there to make the conversion from QString to int work
    bool ok;
    //emitting the logEntry, which is connected to the Logger
    emit logEntry(QString("Set HotEnd target temperature to %1 and waiting to reach it").arg(targetTemp), QString("0x030006").toInt(&ok, 10));
}

//sets the bed target temperature to targetTemp, and sets the HeatingState to WaitingForBedToReachTargetTemp so the checkChanged function knows to wait for
//the bed to reach the targetTemp
void HeatingController::waitForBedToReachTargetTemp(int targetTemp)
{

    //sets the heatingState to WaitingForBedToReachTargetTemp
    *m_heatingState = HeatingState::WaitingForBedToReachTargetTemp;
    //sets the Bed TargetTemp to targetTemp
    (*m_targetTemps)[1] = targetTemp;

    //there to make the conversion from QString to int work
    bool ok;
    //emitting the logEntry, which is connected to the Logger
    emit logEntry(QString("Set Bed target temperature to %1 and waiting to reach it").arg(targetTemp), QString("0x030007").toInt(&ok, 10));
}

//sets the hotEnd TargetTemp to targetTemp
//return = success / non-success
bool HeatingController::heatHotEnd(int targetTemp)
{

    //checks if the heater is waiting for another object to rech its target temp
    //triggered if it isn't
    if(*m_heatingState != HeatingState::WaitingForHotEndToReachTargetTemp && *m_heatingState != HeatingState::WaitingForBedToReachTargetTemp){

        //sets the TargetTemp of the HotEnd to targetTemp
        (*m_targetTemps)[0] = targetTemp;
        //sets the HeatingState to MaintainingTemp
        *m_heatingState = HeatingState::MaintainingTemp;

        //there to make the conversion from QString to int work
        bool ok;
        //emitting the logEntry, which is connected to the Logger
        emit logEntry(QString("Set HotEnd target temperature to %1").arg(targetTemp), QString("0x030008").toInt(&ok, 10));
        return true;
    }

    //triggered if it is
    else{

        //there to make the conversion from QString to int work
        bool ok;
        //emitting the logEntry, which is connected to the Logger
        emit logEntry(QString("Couldn't set HotEnd target temperature"), QString("0x03FFFB").toInt(&ok, 10));
        emit error(QString("Couldn't set HotEnd target temperature"));
        return false;
    }
}

//sets the bed TargetTemp to targetTemp
//return = success / non-success
bool HeatingController::heatBed(int targetTemp)
{

    //checks if the heater is waiting for another object to rech its target temp
    //triggered if it isn't
    if(*m_heatingState != HeatingState::WaitingForHotEndToReachTargetTemp && *m_heatingState != HeatingState::WaitingForBedToReachTargetTemp){

        //sets the TargetTemp of the Bed to targetTemp
        (*m_targetTemps)[1] = targetTemp;
        //sets the HeatingState to MaintainingTemp
        *m_heatingState = HeatingState::MaintainingTemp;

        //there to make the conversion from QString to int work
        bool ok;
        //emitting the logEntry, which is connected to the Logger
        emit logEntry(QString("Set Bed target temperature to %1").arg(targetTemp), QString("0x030009").toInt(&ok, 10));
        return true;
    }

    //triggered if it is
    else{

        //there to make the conversion from QString to int work
        bool ok;
        //emitting the logEntry, which is connected to the Logger
        emit logEntry(QString("Couldn't set Bed target temperature"), QString("0x03FFFA").toInt(&ok, 10));
        emit error(QString("Couldn't set Bed target temperature"));
        return false;
    }
}

//stops heating the HotEnd
void HeatingController::stopHeatingHotEnd()
{

    //sets the Heating state according to the current heatingstate
    //triggered if HeatingState is WaitingForHotEndToReachTargetTemp and the Targettemp of the bed isn't -1
    if(*m_heatingState == HeatingState::WaitingForHotEndToReachTargetTemp && m_targetTemps->at(1) != -1){

        //sets the HeatingState to MaintainingTemp
        *m_heatingState = HeatingState::MaintainingTemp;
    }

    //triggered if HeatingState is WaitingForHotEndToReachTargetTemp
    else if(*m_heatingState == HeatingState::WaitingForHotEndToReachTargetTemp){

        //sets the HeatingState to Idle
        *m_heatingState = HeatingState::Idle;
    }

    //triggered if HeatingState is MaintainingTemp and the Targettemp of the bed isn't -1
    else if(*m_heatingState == HeatingState::MaintainingTemp && m_targetTemps->at(1) == -1){

        //sets the HeatingState to Idle
        *m_heatingState = HeatingState::Idle;
    }

    //sets the TargetTemp of the HotEnd to -1
    (*m_targetTemps)[0] = -1;
    //there to make the conversion from QString to int work
    bool ok;
    //emitting the logEntry, which is connected to the Logger
    emit logEntry(QString("Stopped heating the HotEnd"), QString("0x03000A").toInt(&ok, 10));
}

//stops heating the Bed
void HeatingController::stopHeatingBed()
{

    //sets the Heating state according to the current heatingstate
    //triggered if HeatingState is WaitingForBedToReachTargetTemp and the Targettemp of the hotEnd isn't -1
    if(*m_heatingState == HeatingState::WaitingForBedToReachTargetTemp && m_targetTemps->at(0) != -1){

        //sets the HeatingState to MaintainingTemp
        *m_heatingState = HeatingState::MaintainingTemp;
    }

    //triggered if HeatingState is WaitingForBedToReachTargetTemp
    else if(*m_heatingState == HeatingState::WaitingForBedToReachTargetTemp){

        //sets the HeatingState to Idle
        *m_heatingState = HeatingState::Idle;
    }

    //triggered if HeatingState is MaintainingTemp and the Targettemp of the hotEnd isn't -1
    else if(*m_heatingState == HeatingState::MaintainingTemp && m_targetTemps->at(0) == -1){

        //sets the HeatingState to Idle
        *m_heatingState = HeatingState::Idle;
    }

    //sets the TargetTemp of the Bed to -1
    (*m_targetTemps)[1] = -1;
    //there to make the conversion from QString to int work
    bool ok;
    //emitting the logEntry, which is connected to the Logger
    emit logEntry(QString("Stopped heating the Bed"), QString("0x03000B").toInt(&ok, 10));
}
