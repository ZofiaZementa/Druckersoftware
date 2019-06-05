#ifndef NANOTECSTEPPERDRIVER_H
#define NANOTECSTEPPERDRIVER_H

#include <QObject>

class NanotecStepperDriver : public QObject
{
    Q_OBJECT
public:
    explicit NanotecStepperDriver(QObject *parent = 0);
    ~NanotecStepperDriver();

    void setStepSize(QList<int> sizes, int priority = 3);
    void setStepSize(int adress, int size, int priority = 3);
    void setStepSizeAll(int size, int priority = 3);
    void setMotorType(QList<int> types, int priority = 3);
    void setMotorType(int adress, int type, int priority = 3);
    void setMotorTypeAll(int type, int priority = 3);
    void setBacklash(QList<int> vals, int priority = 3);
    void setBacklash(int adress, int val, int priority = 3);
    void setBacklashAll(int val, int priority = 3);
    void setPhasecurrent(QList<int> vals, int priority = 3);
    void setPhasecurrent(int adress, int val, int priority = 3);
    void setPhasecurrentAll(int val, int priority = 3);
    void setHaltPhasecurrent(QList<int> vals, int priority = 3);
    void setHaltPhasecurrent(int adress, int val, int priority = 3);
    void setHaltPhasecurrentAll(int val, int priority = 3);
    void setStopDecceleration(QList<int> vals, int priority = 3);
    void setStopDecceleration(int adress, int val, int priority = 3);
    void setStopDeccelerationAll(int val, int priority = 3);
    void startMotor(QList<bool> go, int priority = 3);
    void startMotor(int adress, int priority = 3);
    void startMotorAll(int priority = 3);
    void stopMotor(QList<bool> go, int priority = 3);
    void stopMotor(int adress, int priority = 3);
    void stopMotorAll(int priority = 3);
    void quickStopMotorAll(int priority = 3);
    void quickStopMotor(QList<bool> go, int priority = 3);
    void quickStopMotor(int adress, int priority = 3);
    void emergencyStop(int priority = 3);
    void setPositioningmode(QList<int> modes, int priority = 3);
    void setPositioningmode(int adress, int mode, int priority = 3);
    void setPositioningmodeAll(int mode, int priority = 3);
    void setWay(QList<int> ways, int priority = 3);
    void setWay(int adress, int way, int priority = 3);
    void setWayAll(int way, int priority = 3);
    void setMinFrequenzy(QList<int> vals, int priority = 3);
    void setMinFrequenzy(int adress, int val, int priority = 3);
    void setMinFrequenzyAll(int val, int priority = 3);
    void setMaxFrequenzy(QList<int> vals, int priority = 3);
    void setMaxFrequenzy(int adress, int val, int priority = 3);
    void setMaxFrequenzyAll(int val, int priority = 3);
    void setAccelerationCurve(QList<int> vals, int priority = 3);
    void setAccelerationCurve(int adress, int val, int priority = 3);
    void setAccelerationCurveAll(int val, int priority = 3);
    void setDeccelerationCurve(QList<int> vals, int priority = 3);
    void setDeccelerationCurve(int adress, int val, int priority = 3);
    void setDeccelerationCurveAll(int val, int priority = 3);
    void setTurningdirection(QList<bool> vals, int priority = 3);
    void setTurningdirection(int adress, bool val, int priority = 3);
    void setTurningdirectionAll(bool val, int priority = 3);
    void setAccelerationJolt(QList<int> vals, int priority = 3);
    void setAccelerationJolt(int adress, int val, int priority = 3);
    void setAccelerationJoltAll(int val, int priority = 3);
    void setDeccelerationJolt(QList<int> vals, int priority = 3);
    void setDeccelerationJolt(int adress, int val, int priority = 3);
    void setDeccelerationJoltAll(int val, int priority = 3);
    void increaseRPM(QList<bool> go, int priority = 3);
    void increaseRPM(int adress, int priority = 3);
    void increaseRPMAll(int priority = 3);
    void decreaseRPM(QList<bool> go, int priority = 3);
    void decreaseRPM(int adress, int priority = 3);
    void decreaseRPMAll(int priority = 3);
    void setMotorCount(int i);
    int motorCount();
    void setMotorAdressMap(QList<int> adressmap);
    QList<int> motorMap();
    void resetMotorMap();

signals:

    void position(int adress, int position);
    void temperature(int adress, int temperature);
    void rpm(int adress, int rpm);
    void send(QByteArray data, int priority);

public slots:

    void getPosition(QList<bool> ok, int priority = 3);
    void getPosition(int adress, int priority = 3);
    void getPositionAll(int priority = 3);
    void getTemperature(QList<bool> ok, int priority = 3);
    void getTemperature(int adress, int priority = 3);
    void getTemperatureAll(int priority = 3);
    void getRPM(QList<bool> ok, int priority = 3);
    void getRPM(int adress, int priority = 3);
    void getRPMAll(int priority = 3);
    void receive(QByteArray data);

private:

    void sendData(QString data, int priority);
    int removeAdress(QString *data);

    int *m_motorCount;
    QList<int> *m_motorMap;

};

#endif // NANOTECSTEPPERDRIVER_H
