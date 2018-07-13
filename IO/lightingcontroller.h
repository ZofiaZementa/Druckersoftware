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

    void checkChanged(IOController *iOController);

signals:

    void logEntry(QString logMessage, int code);
    void statusLEDChanged(int a1, int a2);

public slots:

    void setStatusLED(int a1, int a2);

private:

    QList<int> *m_values;

};

#endif // LIGHTINGCONTROLLER_H
