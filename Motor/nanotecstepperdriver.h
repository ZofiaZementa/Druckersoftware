#ifndef NANOTECSTEPPERDRIVER_H
#define NANOTECSTEPPERDRIVER_H

#include <QObject>
#include <QHash>

//translating the function calls to commands which then can be sent over
//a serial connection to the motor
class NanotecStepperDriver : public QObject
{

    Q_OBJECT

public:
    explicit NanotecStepperDriver(QObject *parent = 0);
    ~NanotecStepperDriver();

    void setStepSize(QHash<int, int> sizes, int priority = 3);
    void setStepSize(int address, int size, int priority = 3);
    void setStepSizeAll(int size, int priority = 3);
    void setMotorType(QHash<int, int> types, int priority = 3);
    void setMotorType(int address, int type, int priority = 3);
    void setMotorTypeAll(int type, int priority = 3);
    void setBacklash(QHash<int, int> vals, int priority = 3);
    void setBacklash(int address, int val, int priority = 3);
    void setBacklashAll(int val, int priority = 3);
    void setPhasecurrent(QHash<int, int> vals, int priority = 3);
    void setPhasecurrent(int address, int val, int priority = 3);
    void setPhasecurrentAll(int val, int priority = 3);
    void setHaltPhasecurrent(QHash<int, int> vals, int priority = 3);
    void setHaltPhasecurrent(int address, int val, int priority = 3);
    void setHaltPhasecurrentAll(int val, int priority = 3);
    void setStopDecceleration(QHash<int, int> vals, int priority = 3);
    void setStopDecceleration(int address, int val, int priority = 3);
    void setStopDeccelerationAll(int val, int priority = 3);
    void startMotor(QList<int> go, int priority = 3);
    void startMotor(int address, int priority = 3);
    void startMotorAll(int priority = 3);
    void stopMotor(QList<int> go, int priority = 3);
    void stopMotor(int address, int priority = 3);
    void stopMotorAll(int priority = 3);
    void quickStopMotor(QList<int> go, int priority = 3);
    void quickStopMotor(int address, int priority = 3);
    void quickStopMotorAll(int priority = 3);
    void setPositioningmode(QHash<int, int> modes, int priority = 3);
    void setPositioningmode(int address, int mode, int priority = 3);
    void setPositioningmodeAll(int mode, int priority = 3);
    void setWay(QHash<int, int> ways, int priority = 3);
    void setWay(int address, int way, int priority = 3);
    void setWayAll(int way, int priority = 3);
    void setMinFrequenzy(QHash<int, int> vals, int priority = 3);
    void setMinFrequenzy(int address, int val, int priority = 3);
    void setMinFrequenzyAll(int val, int priority = 3);
    void setMaxFrequenzy(QHash<int, int> vals, int priority = 3);
    void setMaxFrequenzy(int address, int val, int priority = 3);
    void setMaxFrequenzyAll(int val, int priority = 3);
    void setAccelerationCurve(QHash<int, int> vals, int priority = 3);
    void setAccelerationCurve(int address, int val, int priority = 3);
    void setAccelerationCurveAll(int val, int priority = 3);
    void setDeccelerationCurve(QHash<int, int> vals, int priority = 3);
    void setDeccelerationCurve(int adress, int val, int priority = 3);
    void setDeccelerationCurveAll(int val, int priority = 3);
    void setTurningdirection(QHash<int, bool> vals, int priority = 3);
    void setTurningdirection(int address, bool val, int priority = 3);
    void setTurningdirectionAll(bool val, int priority = 3);
    void setAccelerationJolt(QHash<int, int> vals, int priority = 3);
    void setAccelerationJolt(int address, int val, int priority = 3);
    void setAccelerationJoltAll(int val, int priority = 3);
    void setDeccelerationJolt(QHash<int, int> vals, int priority = 3);
    void setDeccelerationJolt(int address, int val, int priority = 3);
    void setDeccelerationJoltAll(int val, int priority = 3);
    void increaseRPM(QList<int> go, int priority = 3);
    void increaseRPM(int address, int priority = 3);
    void increaseRPMAll(int priority = 3);
    void decreaseRPM(QList<int> go, int priority = 3);
    void decreaseRPM(int address, int priority = 3);
    void decreaseRPMAll(int priority = 3);
    void setMotorAddressMap(QHash<int, int> addressmap);
    void changeMotorAddressMap(QHash<int, int> addressmap);
    QHash<int, int> motorAddressMap();
    void resetMotorAddressMap();

signals:

    void position(int adress, int position);
    void temperature(int adress, int temperature);
    void rpm(int adress, int rpm);
    void send(QByteArray data, int priority);

public slots:

    void getPosition(QList<int> ok, int priority = 3);
    void getPosition(int address, int priority = 3);
    void getPositionAll(int priority = 3);
    void getTemperature(QList<int> ok, int priority = 3);
    void getTemperature(int address, int priority = 3);
    void getTemperatureAll(int priority = 3);
    void getRPM(QList<int> ok, int priority = 3);
    void getRPM(int address, int priority = 3);
    void getRPMAll(int priority = 3);
    void receive(QByteArray data);

private:

    void sendData(QString data, int priority);
    int removeAdress(QString *data);

    QHash<int, int> m_motorMap;

};

#endif // NANOTECSTEPPERDRIVER_H
