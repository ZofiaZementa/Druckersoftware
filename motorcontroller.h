#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <QObject>

class MotorController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int m_currentXAxisPosition READ currentXAxisPosition WRITE setCurrentXAxisPosition NOTIFY currentXAxisPositionChanged)
    Q_PROPERTY(int m_currentYAxisPosition READ currentYAxisPosition WRITE setCurrentYAxisPosition NOTIFY currentYAxisPositionChanged)
    Q_PROPERTY(int m_currentZAxisPosition READ currentZAxisPosition WRITE setCurrentZAxisPosition NOTIFY currentZAxisPositionChanged)
    Q_PROPERTY(int m_currentExtruderPosition READ currentExtruderPosition WRITE setCurrentExtruderPosition NOTIFY currentExtruderPositionChanged)

public:
    explicit MotorController(QObject *parent = nullptr);
    ~MotorController();

    bool absoluteMoveXAxis(int position, int speed);
    bool relativeMoveXAxis(int value, int speed);
    bool absoluteMoveYAxis(int position, int speed);
    bool relativeMoveYAxis(int value, int speed);
    bool absoluteMoveZAxis(int position, int speed);
    bool relativeMoveZAxis(int value, int speed);
    bool absoluteMoveExtruder(int position, int speed);
    bool relativeMoveExtruder(int value, int speed);
    bool absoluteMove(int x, int y, int z, int e, int speed);
    bool relativeMove(int x, int y, int z, int e, int speed);
    void setXAxisMaxPrintingAcceleration(int xAxisMaxPrintingAcceleration);
    int xAxisMaxPrintingAcceleration();
    void setXAxisMaxTravelAcceleration(int xAxisMaxTravelAcceleration);
    int xAxisMaxTravelAcceleration();
    void setYAxisMaxPrintingAcceleration(int yAxisMaxPrintingAcceleration);
    int yAxisMaxPrintingAcceleration();
    void setYAxisMaxTravelAcceleration(int yAxisMaxTravelAcceleration);
    int yAxisMaxTravelAcceleration();
    void setZAxisMaxPrintingAcceleration(int zAxisMaxPrintingAcceleration);
    int zAxisMaxPrintingAcceleration();
    void setZAxisMaxTravelAcceleration(int zAxisMaxTravelAcceleration);
    int zAxisMaxTravelAcceleration();
    void setExtruderMaxPrintingAcceleration(int extruderMaxPrintingAcceleration);
    int extruderMaxPrintingAcceleration();
    void setExtruderMaxTravelAcceleration(int extruderMaxTravelAcceleration);
    int extruderMaxTravelAcceleration();
    void setXAxisMaxFeedrate(int xAxisMaxFeedrate);
    int xAxisMaxFeedrate();
    void setYAxisMaxFeedrate(int yAxisMaxFeedrate);
    int yAxisMaxFeedrate();
    void setZAxisMaxFeedrate(int zAxisMaxFeedrate);
    int zAxisMaxFeedrate();
    void setExtruderMaxFeedrate(int extruderMaxFeedrate);
    int extruderMaxFeedrate();
    void setDefaultPrintingAcceleration(int defaultPrintingAcceleration);
    int defaultPrintingAcceleration();
    void setDefaultTravelAcceleration(int defaultTravelAcceleration);
    int defaultTravelAcceleration();
    int currentXAxisPosition();
    int currentYAxisPosition();
    int currentZAxisPosition();
    int currentExtruderPosition();
    int setCurrentXAxisPosition(int currentXAxisPosition);
    int setCurrentYAxisPosition(int currentYAxisPosition);
    int setCurrentZAxisPosition(int currentZAxisPosition);
    int setCurrentExtruderPosition(int currentExtruderPosition);

signals:

    void currentXAxisPositionChanged(int position);
    void currentYAxisPositionChanged(int position);
    void currentZAxisPositionChanged(int position);
    void currentExtruderPositionChanged(int position);

public slots:

    void clear();
    void pause();
    void play();
    void stop();

private:

    int *m_xAxisMaxPrintingAcceleration;
    int *m_xAxisMaxTravelAcceleration;
    int *m_yAxisMaxPrintingAcceleration;
    int *m_yAxisMaxTravelAcceleration;
    int *m_zAxisMaxPrintingAcceleration;
    int *m_zAxisMaxTravelAcceleration;
    int *m_extruderMaxPrintingAcceleration;
    int *m_extruderMaxTravelAcceleration;
    int *m_xAxisMaxFeedrate;
    int *m_yAxisMaxFeedrate;
    int *m_zAxisMaxFeedrate;
    int *m_extruderMaxFeedrate;
    int *m_defaultPrintingAcceleration;
    int *m_defaultTravelAcceleration;
    int *m_currentXAxisPosition;
    int *m_currentYAxisPosition;
    int *m_currentZAxisPosition;
    int *m_currentExtruderPosition;

};

#endif // MOTORCONTROLLER_H
