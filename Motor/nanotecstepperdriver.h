#ifndef NANOTECSTEPPERDRIVER_H
#define NANOTECSTEPPERDRIVER_H

#include <QObject>

class NanotecStepperDriver : public QObject
{
    Q_OBJECT
public:
    explicit NanotecStepperDriver(QObject *parent = 0);
    ~NanotecStepperDriver();

    void setStepSize(QList<int> sizes);
    void setStepSize(int adress, int size);
    void setStepSizeAll(int size);
    void setMotorType(QList<int> types);
    void setMotorType(int adress, int type);
    void setMotorTypeAll(int type);
    void setBacklash(QList<int> vals);
    void setBacklash(int adress, int val);
    void setBacklashAll(int val);
    void setPhasecurrent(QList<int> vals);
    void setPhasecurrent(int adress, int val);
    void setPhasecurrentAll(int val);
    void setHaltPhasecurrent(QList<int> vals);
    void setHaltPhasecurrent(int adress, int val);
    void setHaltPhasecurrentAll(int val);
    void setStopDecceleration(QList<int> vals);
    void setStopDecceleration(int adress, int val);
    void setStopDeccelerationAll(int val);
    void startMotor(QList<bool> go);
    void startMotor(int adress);
    void startMotorAll();
    void stopMotor(QList<bool> go);
    void stopMotor(int adress);
    void stopMotorAll();
    void setPositioningmode(QList<int> modes);
    void setPositioningmode(int adress, int mode);
    void setPositioningmodeAll(int mode);
    void setWay(QList<int> ways);
    void setWay(int adress, int way);
    void setWayAll(int way);
    void setMinFrequenzy(QList<int> vals);
    void setMinFrequenzy(int adress, int val);
    void setMinFrequenzyAll(int val);
    void setMaxFrequenzy(QList<int> vals);
    void setMaxFrequenzy(int adress, int val);
    void setMaxFrequenzyAll(int val);
    void setAccelerationCurve(QList<int> vals);
    void setAccelerationCurve(int adress, int val);
    void setAccelerationCurveAll(int val);
    void setDeccelerationCurve(QList<int> vals);
    void setDeccelerationCurve(int adress, int val);
    void setDeccelerationCurveAll(int val);
    void setTurningdirection(QList<bool> vals);
    void setTurningdirection(int adress, bool val);
    void setTurningdirectionAll(bool val);
    void setAccelerationJolt(QList<int> vals);
    void setAccelerationJolt(int adress, int val);
    void setAccelerationJoltAll(int val);
    void setDeccelerationJolt(QList<int> vals);
    void setDeccelerationJolt(int adress, int val);
    void setDeccelerationJoltAll(int val);
    void increaseRPM(QList<bool> go);
    void increaseRPM(int adress);
    void increaseRPMAll();
    void decreaseRPM(QList<bool> go);
    void decreaseRPM(int adress);
    void decreaseRPMAll();
    void setMotorCount(int i);
    int motorCount();
    void setMotorAdressMap(QList<int> adressmap);
    void resetMotorMap();

signals:

    void position(int adress, int position);
    void temperature(int adress, int temperature);
    void rpm(int adress, int rpm);
    void send(QByteArray data);

public slots:

    void getPosition(QList<bool> ok);
    void getPosition(int adress);
    void getPositionAll();
    void getTemperature(QList<bool> ok);
    void getTemperature(int adress);
    void getTemperatureAll();
    void getRPM(QList<bool> ok);
    void getRPM(int adress);
    void getRPMAll();
    void receive(QByteArray data);

private:

    void sendData(QString data);
    int removeAdress(QString *data);

    int *m_motorCount;
    QList<int> *m_motorMap;

};

#endif // NANOTECSTEPPERDRIVER_H
