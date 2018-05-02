#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <QObject>
#include <QUrl>
#include <QSettings>
#include <QTimer>

struct CommandBuffer {

    QStringList buffer;
    QList<ushort> bufferInfo;
};

class MotorController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal m_currentXAxisPosition READ currentXAxisPosition WRITE setCurrentXAxisPosition NOTIFY currentXAxisPositionChanged)
    Q_PROPERTY(qreal m_currentYAxisPosition READ currentYAxisPosition WRITE setCurrentYAxisPosition NOTIFY currentYAxisPositionChanged)
    Q_PROPERTY(qreal m_currentZAxisPosition READ currentZAxisPosition WRITE setCurrentZAxisPosition NOTIFY currentZAxisPositionChanged)
    Q_PROPERTY(qreal m_currentExtruderPosition READ currentExtruderPosition WRITE setCurrentExtruderPosition NOTIFY currentExtruderPositionChanged)

public:
    explicit MotorController(QObject *parent = nullptr);
    ~MotorController();

    enum MotorState{Moving, Paused, Stopped, Idle};

    bool absoluteMoveXAxis(qreal position, qreal speed);
    bool relativeMoveXAxis(qreal value, qreal speed);
    bool absoluteMoveYAxis(qreal position, qreal speed);
    bool relativeMoveYAxis(qreal value, qreal speed);
    bool absoluteMoveZAxis(qreal position, qreal speed);
    bool relativeMoveZAxis(qreal value, qreal speed);
    bool absoluteMoveExtruder(qreal position, qreal speed);
    bool relativeMoveExtruder(qreal value, qreal speed);
    bool absoluteMove(qreal x, qreal y, qreal z, qreal e, qreal xSpeed, qreal ySpeed, qreal zSpeed, qreal eSpeed);
    bool relativeMove(qreal x, qreal y, qreal z, qreal e, qreal xSpeed, qreal ySpeed, qreal zSpeed, qreal eSpeed);
    void setXAxisMaxFeedrate(qreal xAxisMaxFeedrate);
    int xAxisMaxFeedrate();
    void setYAxisMaxFeedrate(qreal yAxisMaxFeedrate);
    int yAxisMaxFeedrate();
    void setZAxisMaxFeedrate(qreal zAxisMaxFeedrate);
    int zAxisMaxFeedrate();
    void setExtruderMaxFeedrate(qreal extruderMaxFeedrate);
    int extruderMaxFeedrate();
    void setDefaultPrintingAcceleration(int defaultPrintingAcceleration);
    int defaultPrintingAcceleration();
    void setDefaultTravelAcceleration(int defaultTravelAcceleration);
    int defaultTravelAcceleration();
    qreal currentXAxisPosition();
    qreal currentYAxisPosition();
    qreal currentZAxisPosition();
    qreal currentExtruderPosition();
    void setCurrentXAxisPosition(qreal currentXAxisPosition);
    void setCurrentYAxisPosition(qreal currentYAxisPosition);
    void setCurrentZAxisPosition(qreal currentZAxisPosition);
    void setCurrentExtruderPosition(qreal currentExtruderPosition);

signals:

    void error(QString errorMessage);
    void movementFinished();
    void send(QString text);
    void currentXAxisPositionChanged(qreal position);
    void currentYAxisPositionChanged(qreal position);
    void currentZAxisPositionChanged(qreal position);
    void currentExtruderPositionChanged(qreal position);

public slots:

    void receive(QString text);
    void clear();
    void pause();
    void play();
    void stop();

private slots:

    void checkMovement();

private:

    void motorSetup();
    void calculateMovementChange();
    void checkBuffer();

    MotorState *m_motorState;
    qreal *m_currentXAxisPosition;
    qreal *m_currentYAxisPosition;
    qreal *m_currentZAxisPosition;
    qreal *m_currentExtruderPosition;
    qreal *m_previousXAxisPosition;
    qreal *m_previousYAxisPosition;
    qreal *m_previousZAxisPosition;
    qreal *m_previousExtruderPosition;
    qint32 *m_currentXAxisMotorPosition;
    qint32 *m_currentYAxisMotorPosition;
    qint32 *m_currentZAxisMotorPosition;
    qint32 *m_currentExtruderMotorPosition;
    qint32 *m_desiredXAxisMotorPosition;
    qint32 *m_desiredYAxisMotorPosition;
    qint32 *m_desiredZAxisMotorPosition;
    qint32 *m_desiredExtruderMotorPosition;
    CommandBuffer *m_commandBuffer;
    QSettings *m_settings;
};

#endif // MOTORCONTROLLER_H
