#ifndef IOCONTROLLER_H
#define IOCONTROLLER_H

#include <QObject>
#include <QSettings>

class IOController : public QObject
{
    Q_OBJECT
public:
    explicit IOController(QObject *parent = nullptr);
    ~IOController();

    void setPinValue(int pin, int value);
    int pinValue(int pin);

signals:

    void pin02ValueChanged(int value);
    void pin03ValueChanged(int value);
    void pin04ValueChanged(int value);
    void pin05ValueChanged(int value);
    void pin06ValueChanged(int value);
    void pin07ValueChanged(int value);
    void pin08ValueChanged(int value);
    void pin09ValueChanged(int value);
    void pin10ValueChanged(int value);
    void pin11ValueChanged(int value);
    void pin12ValueChanged(int value);
    void pin13ValueChanged(int value);
    void pin14ValueChanged(int value);
    void pin15ValueChanged(int value);
    void pin16ValueChanged(int value);
    void pin17ValueChanged(int value);
    void pin18ValueChanged(int value);
    void pin19ValueChanged(int value);
    void pin20ValueChanged(int value);
    void pin21ValueChanged(int value);
    void pin22ValueChanged(int value);
    void pin23ValueChanged(int value);
    void pin24ValueChanged(int value);
    void pin25ValueChanged(int value);
    void pin26ValueChanged(int value);
    void pin27ValueChanged(int value);
    void error(QString errorMessage);

public slots:

    void mainLoop();

private:

    void checkPins();
    void pinSetup();
    void emitPinChanged(int pin);

    QList<int> *m_pinValues;
    QSettings *m_settings;
    const int m_translationMatrix[28] = {-1, -1, 8, 9, 7, 21, 22, 11, 10, 13, 12, 14, 26, 23, 15, 16, 27, 0, 1, 24, 28, 29, 3, 4, 5, 6, 25, 2};
};

#endif // IOCONTROLLER_H
