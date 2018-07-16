#ifndef LIGHTINGCONTROLLER_H
#define LIGHTINGCONTROLLER_H

#include <QObject>
#include "iocontroller.h"

class LightingController : public QObject
{
    Q_OBJECT
public:
    explicit LightingController(QObject *parent = nullptr);
    ~LightingController();

    //called by the loop in IOMainLoop, checks if the value of any lighting-related IO has been changed / has to be changed
    void checkChanged(IOController *iOController);

signals:

    //emitted to make a logEntry
    void logEntry(QString logMessage, int code);
    //emitted to let everyone know that that the statusLED has changed
    void statusLEDChanged(int a1, int a2);

public slots:

    //sets the status LEDs A1 and A2 to the values a1 and a2
    void setStatusLED(int a1, int a2);

private:

    //initialises m_values
    void initialiseValues();

    //saves the values of the exits as they are supposed to be
    QList<int> *m_values;

};

#endif // LIGHTINGCONTROLLER_H
