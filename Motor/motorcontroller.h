#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "nanotecstepperdriver.h"
#include "motorgraph.h"
#include <QObject>
#include <QSettings>

struct CommandBufferItem{

    QByteArray command;
    //priority is a variable to determine how urgent a given command is, lower gets sent first
    //0 is for emergencies like to emergencystop all motors
    //1 is for later usage
    //2 is for later usage
    //3 is for general stuff like movement commands
    //4 is for later usage
    //5 is for settings
    //6 is for status commands and such things like getting the position
    //7 is for later usage
    int priority;
};

class MotorController : public QObject
{
    Q_OBJECT
public:

    enum MotorControllerMode{CommandDriven, GraphDriven};
    enum ConversationStatus{Ready, WaitingForReply};

    explicit MotorController(QObject *parent = 0);
    ~MotorController();

    void setMode(MotorController::MotorControllerMode mode);
    MotorController::MotorControllerMode mode();
    void setMotorGraph(MotorGraph *motorGraph);
    MotorGraph *motorGraph();
    void relativeMove(QList<qreal> s, QList<qreal> v, QList<qreal> a, QList<qreal> j, QList<qreal> ad, QList<qreal> jd);
    void relativeMove(QList<qreal> s, QList<qreal> v, qreal a, qreal j, qreal ad, qreal jd);
    void absoluteMove(QList<qreal> s, QList<qreal> v, QList<qreal> a, QList<qreal> j, QList<qreal> ad, QList<qreal> jd);
    void absoluteMove(QList<qreal> s, QList<qreal> v, qreal a, qreal j, qreal ad, qreal jd);
    void rpmMove(QList<qreal> s, QList<qreal> v, QList<qreal> a, QList<qreal> j, QList<qreal> ad, QList<qreal> jd, bool correction);
    void rpmMove(QList<qreal> s, QList<qreal> v, qreal a, qreal j, qreal ad, qreal jd, bool correction);

signals:

    void modeChanged(MotorController::MotorControllerMode mode);
    void send(QByteArray data);
    void error(QString error);

public slots:

    void play();
    void pause();
    void stop();
    void settingsChanged();
    void receive(QByteArray data);

private slots:

    void getMotorPositions(int adress, int position);
    void onSend(QByteArray data, int priority);

private:

    void initialiseValueScope();
    void motorSetup();
    void convertUnits(QList<qreal> *s, QList<qreal> *v, QList<qreal> *a, QList<qreal> *j, QList<qreal> *ad, QList<qreal> *jd);
    void mode2Loop();
    void checkInputBuffer();
    void checkOutputBuffer();
    int retrieveAddress(QByteArray command);
    int findAddressInMotorMap(int address);

    QList<ConversationStatus> *m_conversationStatus;
    QList<CommandBufferItem> *m_outputBuffer;
    QByteArray *m_inputBuffer;
    MotorControllerMode *m_mode;
    NanotecStepperDriver *m_driver;
    MotorGraph *m_motorGraph;
    QSettings *m_settings;
};

#endif // MOTORCONTROLLER_H
