#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <QObject>

class MotorController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int m_currentXAxisPosition READ currentXAxisPosition NOTIFY currentXAxisPositionChanged)
    Q_PROPERTY(int m_currentYAxisPosition READ currentYAxisPosition NOTIFY currentYAxisPositionChanged)
    Q_PROPERTY(int m_currentZAxisPosition READ currentZAxisPosition NOTIFY currentZAxisPositionChanged)
    Q_PROPERTY(int m_currentExtruderPosition READ currentExtruderPosition NOTIFY currentExtruderPositionChanged)

public:
    explicit MotorController(QObject *parent = nullptr);
    ~MotorController();

    bool absoluteMoveXAxis(int position);
    bool relativeMoveXAxis(int value);
    bool absoluteMoveYAxis(int position);
    bool relativeMoveYAxis(int value);
    bool absoluteMoveZAxis(int position);
    bool relativeMoveZAxis(int value);
    bool absoluteMoveExtruder(int position);
    bool relativeMoveExtruder(int value);
    bool absoluteMove(int x, int y, int z, int e);
    bool relativeMove(int x, int y, int z, int e);
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

signals:

    void currentXAxisPositionChanged(int position);
    void currentYAxisPositionChanged(int position);
    void currentZAxisPositionChanged(int position);
    void currentExtruderPositionChanged(int position);

public slots:

    void clear();
    void pause();
    void play();

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
