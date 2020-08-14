#include "nanotecstepperdriver.h"

NanotecStepperDriver::NanotecStepperDriver(QObject *parent) : QObject(parent)
{

    //initializing the motormap with a 1 to 1 mapping
    for(int i = 1;i < 255;i++){

        m_motorMap.insert(i, i);
    }
}

NanotecStepperDriver::~NanotecStepperDriver()
{

}

//setting the StepSize for all the given motors (keys) in the map to the values in the map, with the given priority
void NanotecStepperDriver::setStepSize(QHash<int, int> sizes, int priority)
{

		setStepSize(i.key(), i.value(), priority);
}

//setting the StepSize for the motor at address to the given size, with the given priority
void NanotecStepperDriver::setStepSize(int address, int size, int priority)
{

	sendData(QString("#%1g%2\r").arg(m_motorMap[address]).arg(size), priority);
}

//setting the StepSize for all the motors to the given size, with the given priority
void NanotecStepperDriver::setStepSizeAll(int size, int priority)
{

    sendData(QString("#*g%1\r").arg(size), priority);
}

//setting the MotorType for all the given motors (keys) in the map to the values in the map, with the given priority
void NanotecStepperDriver::setMotorType(QHash<int, int> types, int priority)
{

	for(QHash<int, int>::iterator i = types.begin();i != types.end(); i++)
		setMotorType(i.key(), i.value(), priority);
}

//setting the MotorType for the motor at address to the given type, with the given priority
void NanotecStepperDriver::setMotorType(int address, int type, int priority)
{

	sendData(QString("#%1:CL_motor_type=%2\r").arg(m_motorMap[address]).arg(type), priority);
}

//setting the MotorType for all the motors to the given type, with the given priority
void NanotecStepperDriver::setMotorTypeAll(int type, int priority)
{

    sendData(QString("#*:CL_motor_type=%1\r").arg(type), priority);
}

//setting the Backlash for all the motors (keys) in the map to the given value in the map, with the given priority
void NanotecStepperDriver::setBacklash(QHash<int, int> vals, int priority)
{

	for(QHash<int, int>::iterator i = vals.begin();i != vals.end(); i++)
		setBacklash(i.key(), i.value(), priority);
}

//setting the Backlash for the motor at address to the given value, with the given priority
void NanotecStepperDriver::setBacklash(int address, int val, int priority)
{

    sendData(QString("#%1z%2\r").arg(m_motorMap[address]).arg(val), priority);
}

//setting the Backlash for all the motors to the given value, with the given priority
void NanotecStepperDriver::setBacklashAll(int val, int priority)
{

    sendData(QString("#*z%1\r").arg(val), priority);
}

//setting the Phasecurrent for all the motors (keys) in the map to the given value in the map, with the given priority
void NanotecStepperDriver::setPhasecurrent(QHash<int, int> vals, int priority)
{

	for(QHash<int, int>::iterator i = vals.begin();i != vals.end(); i++)
		setPhasecurrent(i.key(), i.value(), priority);
}

//setting the Phasecurrent for the motor at address to the given value, with the given priority
void NanotecStepperDriver::setPhasecurrent(int address, int val, int priority)
{

    sendData(QString("#%1i%2\r").arg(m_motorMap[address]).arg(val), priority);
}

//setting the Backlash for all the motors to the given value, with the given priority
void NanotecStepperDriver::setPhasecurrentAll(int val, int priority)
{

    sendData(QString("#*i%1\r").arg(val), priority);
}

//setting the HaltPhasecurrent for all the motors (keys) in the map to the given value in the map,
//with the given priority
void NanotecStepperDriver::setHaltPhasecurrent(QHash<int, int> vals, int priority)
{

	for(QHash<int, int>::iterator i = vals.begin();i != vals.end(); i++)
		setHaltPhasecurrent(i.key(), i.value(), priority);
}

//setting the HaltPhasecurrent for the motor at address to the given value, with the given priority
void NanotecStepperDriver::setHaltPhasecurrent(int address, int val, int priority)
{

    sendData(QString("#%1r%2\r").arg(m_motorMap[address]).arg(val), priority);
}

//setting the HaltPhasecurrent for all the motors to the given value, with the given priority
void NanotecStepperDriver::setHaltPhasecurrentAll(int val, int priority)
{

    sendData(QString("#*r%1\r").arg(val), priority);
}

//setting the StopDecceleration for all the motors (keys) in the map to the given value in the map,
//with the given priority
void NanotecStepperDriver::setStopDecceleration(QHash<int, int> vals, int priority)
{

	for(QHash<int, int>::iterator i = vals.begin();i != vals.end(); i++)
		setStopDecceleration(i.key(), i.value(), priority);
}

//setting the StopDecceleration for the motor at address to the given value, with the given priority
void NanotecStepperDriver::setStopDecceleration(int address, int val, int priority)
{

    sendData(QString("#%1H%2\r").arg(m_motorMap[address]).arg(val), priority);
}

//setting the StopDecceleration for all the motors to the given value, with the given priority
void NanotecStepperDriver::setStopDeccelerationAll(int val, int priority)
{

    sendData(QString("#*H%1\r").arg(val), priority);
}

//starts the motors with the addresses which are given in the list, with the given priority
void NanotecStepperDriver::startMotor(QList<int> go, int priority)
{

	for(int i = 0;i != go.count(); i++)
		startMotor(go.at(i), priority);
}

//starts the motor with the given address, with the given priority
void NanotecStepperDriver::startMotor(int address, int priority)
{

    sendData(QString("#%1A\r").arg(m_motorMap[address]), priority);
}

//starts all the motors, with the given priority
void NanotecStepperDriver::startMotorAll(int priority)
{

    sendData(QString("#*A\r"), priority);
}

//stops the motors with the addresses which are given in the list, with the given priority
void NanotecStepperDriver::stopMotor(QList<int> go, int priority)
{

	for(int i = 0;i < go.count(); i++)
		stopMotor(go.at(i), priority);
}

//stops the motor with the given address, with the given priority
void NanotecStepperDriver::stopMotor(int address, int priority)
{

    sendData(QString("#%1S1\r").arg(m_motorMap[address]), priority);
}

//stops all the motors, with the given priority
void NanotecStepperDriver::stopMotorAll(int priority)
{

    sendData(QString("#*S1\r"), priority);
}

//quick stops the motors with the addresses which are given in the list, with the given priority
void NanotecStepperDriver::quickStopMotor(QList<int> go, int priority)
{

	for(int i = 0;i < go.count(); i++)
		quickStopMotor(go.at(i), priority);
}

//quick stops the motor with the given address, with the given priority
void NanotecStepperDriver::quickStopMotor(int address, int priority)
{

    sendData(QString("#%1S\r").arg(m_motorMap[address]), priority);
}

//quick stops all the motors
void NanotecStepperDriver::quickStopMotorAll(int priority)
{

    sendData(QString("#*S\r"), priority);
}

//setting the Positioningmode for all the motors (keys) in the map to the given value in the map,
//with the given priority
void NanotecStepperDriver::setPositioningmode(QHash<int, int> modes, int priority)
{

	for(QHash<int, int>::iterator i = modes.begin();i != modes.end(); i++)
		setPositioningmode(i.key(), i.value(), priority);
}

//setting the Positioningmode for the motor at address to the given value, with the given priority
void NanotecStepperDriver::setPositioningmode(int address, int mode, int priority)
{

    sendData(QString("#%1p%2\r").arg(m_motorMap[address]).arg(mode), priority);
}

//setting the Positioningmode for all the motors to the given value, with the given priority
void NanotecStepperDriver::setPositioningmodeAll(int mode, int priority)
{

    sendData(QString("#*p%1\r").arg(mode), priority);
}

//setting the way to drive for all the motors (keys) in the map to the given value in the map, with the given priority
void NanotecStepperDriver::setWay(QHash<int, long> ways, int priority)
{

	for(QHash<int, int>::iterator i = ways.begin();i != ways.end(); i++)
		setWay(i.key(), i.value(), priority);
}

//setting the way to drive for the motor at address to the given value, with the given priority
void NanotecStepperDriver::setWay(int address, long way, int priority)
{

    sendData(QString("#%1s%2\r").arg(m_motorMap[address]).arg(way), priority);
}

//setting the way to drive for all the motors to the given value, with the given priority
void NanotecStepperDriver::setWayAll(long way, int priority)
{

    sendData(QString("#*s%1\r").arg(way), priority);
}

//setting the frequenzy to start at for all the motors (keys) in the map to the given value in the map,
//with the given priority
void NanotecStepperDriver::setMinFrequenzy(QHash<int, long> vals, int priority)
{

	for(QHash<int, int>::iterator i = vals.begin();i != vals.end(); i++)
		setMinFrequenzy(i.key(), i.value(), priority);
}

//setting the frequenzy to start at for alle for the motor at address to the given value, with the given priority
void NanotecStepperDriver::setMinFrequenzy(int address, long val, int priority)
{

    sendData(QString("#%1u%2\r").arg(m_motorMap[address]).arg(val), priority);
}

//setting the frequenzy to start at for all the motors to the given value, with the given priority
void NanotecStepperDriver::setMinFrequenzyAll(long val, int priority)
{

    sendData(QString("#*s%1\r").arg(val), priority);
}

//setting the frequenzy to drive at for all the motors (keys) in the map to the given value in the map,
//with the given priority
void NanotecStepperDriver::setMaxFrequenzy(QHash<int, long> vals, int priority)
{

	for(QHash<int, int>::iterator i = vals.begin();i != vals.end(); i++)
		setMaxFrequenzy(i.key(), i.value(), priority);
}

//setting the frequenzy to drive at for alle for the motor at address to the given value, with the given priority
void NanotecStepperDriver::setMaxFrequenzy(int address, long val, int priority)
{

    sendData(QString("#%1o%2\r").arg(m_motorMap[address]).arg(val), priority);
}

//setting the frequenzy to drive at for all the motors to the given value, with the given priority
void NanotecStepperDriver::setMaxFrequenzyAll(long val, int priority)
{

    sendData(QString("#*o%1\r").arg(val), priority);
}

//setting the maximum acceleration for all the motors (keys) in the map to the given value in the map,
//with the given priority
void NanotecStepperDriver::setAccelerationCurve(QHash<int, long> vals, int priority)
{

	for(QHash<int, int>::iterator i = vals.begin();i != vals.end(); i++)
		setAccelerationCurve(i.key(), i.value(), priority);
}

//setting the maximum acceleration for the motor at address to the given value, with the given priority
void NanotecStepperDriver::setAccelerationCurve(int address, long val, int priority)
{

    sendData(QString("#%1b%2\r").arg(m_motorMap[address]).arg(val), priority);
}

//setting the maximum acceleration for all the motors to the given value, with the given priority
void NanotecStepperDriver::setAccelerationCurveAll(long val, int priority)
{

    sendData(QString("#*b%1\r").arg(val), priority);
}

//setting the maximum decceleration for all the motors (keys) in the map to the given value in the map,
//with the given priority
void NanotecStepperDriver::setDeccelerationCurve(QHash<int, long> vals, int priority)
{

	for(QHash<int, int>::iterator i = vals.begin();i != vals.end(); i++)
		setDeccelerationCurve(i.key(), i.value(), priority);
}

//setting the maximum decceleration for the motor at address to the given value, with the given priority
void NanotecStepperDriver::setDeccelerationCurve(int address, long val, int priority)
{

    sendData(QString("#%1B%2\r").arg(m_motorMap[address]).arg(val), priority);
}

//setting the maximum decceleration for all the motors to the given value, with the given priority
void NanotecStepperDriver::setDeccelerationCurveAll(long val, int priority)
{

    sendData(QString("#*B%1\r").arg(val), priority);
}

//setting the turningdirection for all the motors (keys) in the map to the given value in the map,
//with the given priority
void NanotecStepperDriver::setTurningdirection(QHash<int, bool> vals, int priority)
{

	for(QHash<int, bool>::iterator i = vals.begin();i != vals.end(); i++)
		setTurningdirection(i.key(), i.value(), priority);
}

//setting the turningdirection for the motor at address to the given value, with the given priority
void NanotecStepperDriver::setTurningdirection(int address, bool val, int priority)
{

	if(val == false)
		sendData(QString("#%1d0\r").arg(m_motorMap[address]), priority);

	else
		sendData(QString("#%1d1\r").arg(m_motorMap[address]), priority);
}

//setting the turningdirection for all the motors to the given value, with the given priority
void NanotecStepperDriver::setTurningdirectionAll(bool val, int priority)
{

	if(val == false)
		sendData(QString("#*d0\r"), priority);

	else
		sendData(QString("#*d1\r"), priority);
}

//setting the maximum jolt during acceleration for all the motors (keys) in the map to the given value in the map,
//with the given priority
void NanotecStepperDriver::setAccelerationJolt(QHash<int, long> vals, int priority)
{

	for(QHash<int, int>::iterator i = vals.begin();i != vals.end(); i++)
		setAccelerationJolt(i.key(), i.value(), priority);
}

//setting the maximum jolt during acceleration for the motor at address to the given value, with the given priority
void NanotecStepperDriver::setAccelerationJolt(int address, long val, int priority)
{

    sendData(QString("#%1:b%2\r").arg(m_motorMap[address]).arg(val), priority);
}

//setting the maximum jolt during acceleration for all the motors to the given value, with the given priority
void NanotecStepperDriver::setAccelerationJoltAll(long val, int priority)
{

    sendData(QString("#*:b%1\r").arg(val), priority);
}

//setting the maximum jolt during decceleration for all the motors (keys) in the map to the given value in the map,
//with the given priority
void NanotecStepperDriver::setDeccelerationJolt(QHash<int, long> vals, int priority)
{

	for(QHash<int, int>::iterator i = vals.begin();i != vals.end(); i++)
		setDeccelerationJolt(i.key(), i.value(), priority);
}

//setting the maximum jolt during decceleration for the motor at address to the given value, with the given priority
void NanotecStepperDriver::setDeccelerationJolt(int address, long val, int priority)
{

    sendData(QString("#%1:B%2\r").arg(m_motorMap[address]).arg(val), priority);
}

//setting the maximum jolt during decceleration for all the motors to the given value, with the given priority
void NanotecStepperDriver::setDeccelerationJoltAll(long val, int priority)
{

    sendData(QString("#*:B%1\r").arg(val), priority);
}

//increasing the rpm for all the motors with the addresses given in the list, with the given priority
void NanotecStepperDriver::increaseRPM(QList<int> go, int priority)
{

	for(int i = 0;i < go.count(); i++)
		increaseRPM(go.at(i), priority);
}

//increasing the rpm for the motor at address, with the given priority
void NanotecStepperDriver::increaseRPM(int address, int priority)
{

    sendData(QString("#%1+\r").arg(m_motorMap[address]), priority);
}

//increasing the rpm for all the motors, with the given priority
void NanotecStepperDriver::increaseRPMAll(int priority)
{

    sendData(QString("#*+\r"), priority);
}

//decreasing the rpm for all the motors with the addresses given in the list, with the given priority
void NanotecStepperDriver::decreaseRPM(QList<int> go, int priority)
{

	for(int i = 0;i < go.count(); i++)
		decreaseRPM(go.at(i), priority);
}

//decreasing the rpm for the motor at address, with the given priority
void NanotecStepperDriver::decreaseRPM(int address, int priority)
{

    sendData(QString("#%1-\r").arg(m_motorMap[address]), priority);
}

//decreasing the rpm for all the motors, with the given priority
void NanotecStepperDriver::decreaseRPMAll(int priority)
{

    sendData(QString("#*-\r"), priority);
}

//setting the motoraddressmap to the given map, this completely replaces the old map
void NanotecStepperDriver::setMotorAddressMap(QHash<int, int> addressmap)
{

    m_motorMap = addressmap;
}

//changing the given entries of the motoraddressmap, this only replaces the entries that are given in the parameters
//or creates new ones if don't exist yet
void NanotecStepperDriver::changeMotorAddressMap(QHash<int, int> addressmap)
{

	for(QHash<int, int>::iterator i = addressmap.begin();i != addressmap.end();i++)
		m_motorMap.insert(i.key(), i.value());
}

//returns the current motoraddressmap
QHash<int, int> NanotecStepperDriver::motorAddressMap()
{
    return m_motorMap;
}

//resets the motoraddressmap to 1 to 1 mapping
void NanotecStepperDriver::resetMotorAddressMap()
{

    m_motorMap.clear();

	for(int i = 1;i < 255;i++)
        m_motorMap.insert(i, i);
}

//requesting the postition from all the motors (keys) in the map, with the given priority
void NanotecStepperDriver::getPosition(QList<int> ok, int priority)
{

	for(int i = 0;i < ok.count(); i++)
        getPosition(ok.at(i), priority);
}

//requesting the postition from all the motor at address, with the given priority
void NanotecStepperDriver::getPosition(int address, int priority)
{

    sendData(QString("#%1C\r").arg(m_motorMap[address]), priority);
}

//requesting the postition from all the motors, with the given priority
void NanotecStepperDriver::getPositionAll(int priority)
{

    sendData(QString("#*C\r"), priority);
}

//requesting the temperature from all the motors (keys) in the map, with the given priority
void NanotecStepperDriver::getTemperature(QList<int> ok, int priority)
{

	for(int i = 0;i < ok.count(); i++)
		getTemperature(ok.at(i), priority);
}

//requesting the temperature from all the motor at address, with the given priority
void NanotecStepperDriver::getTemperature(int address, int priority)
{

    sendData(QString("#%1:temp_adc\r").arg(m_motorMap[address]), priority);
}

//requesting the temperature from all the motors, with the given priority
void NanotecStepperDriver::getTemperatureAll(int priority)
{

    sendData(QString("#*:temp_adc\r"), priority);
}

//requesting the rpm from all the motors (keys) in the map, with the given priority
void NanotecStepperDriver::getRPM(QList<int> ok, int priority)
{

	for(int i = 0;i < ok.count(); i++)
		getRPM(ok.at(i), priority);
}

//requesting the rpm from all the motor at address, with the given priority
void NanotecStepperDriver::getRPM(int address, int priority)
{

    sendData(QString("#%1:v\r").arg(m_motorMap[address]), priority);
}

//requesting the rpm from all the motors, with the given priority
void NanotecStepperDriver::getRPMAll(int priority)
{

    sendData(QString("#*:v\r"), priority);
}

//receiving the answers from the motors, and emitting the corresponging signals
void NanotecStepperDriver::receive(QByteArray data)
{

    QString dataString = QString(data);
	int adress = m_motorMap.key(removeAdress(&dataString));

    if(dataString.contains(QString("C")) == true){

        bool ok;
		emit position(adress, dataString.mid(1, dataString.count() - 2).toLong(&ok, 10));
        return;
    }

    else if(dataString.contains(QString(":temp_adc")) == true){

        bool ok;
		emit temperature(adress, dataString.mid(9, dataString.count() - 10).toLong(&ok, 10));
        return;
    }

    else if(dataString.contains(QString(":v")) == true){

        bool ok;
		emit rpm(adress, dataString.mid(2, dataString.count() - 3).toLong(&ok, 10));
    }
}

//converting the String to a bytearray and emitting the sending signal with the data
void NanotecStepperDriver::sendData(QString data, int priority)
{

    emit send(data.toLatin1(), priority);
}

//removes the motor address from the given string
int NanotecStepperDriver::removeAdress(QString *data)
{

    QString adress;

    if(data->contains(QChar(42)) == false){

		while(data->at(0).unicode() > 47 && data->at(0).unicode() < 58)
			adress.append(data->remove(0, 1));

        bool ok;
        return adress.toInt(&ok, 10);
    }

    return -1;
}
