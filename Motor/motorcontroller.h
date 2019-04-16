#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "nanotecstepperdriver.h"
#include <QObject>
#include <QSettings>

class MotorController : public QObject
{
    Q_OBJECT
public:
    explicit MotorController(QObject *parent = 0);
    ~MotorController();

    void relativeMove(QList<qreal> s, QList<qreal> v, QList<qreal> a, QList<qreal> j, QList<qreal> ad, QList<qreal> jd);
    void relativeMove(QList<qreal> s, QList<qreal> v, qreal a, qreal j, qreal ad, qreal jd);
    void absoluteMove(QList<qreal> s, QList<qreal> v, QList<qreal> a, QList<qreal> j, QList<qreal> ad, QList<qreal> jd);
    void absoluteMove(QList<qreal> s, QList<qreal> v, qreal a, qreal j, qreal ad, qreal jd);
    void rpmMove(QList<qreal> s, QList<qreal> v, QList<qreal> a, QList<qreal> j, QList<qreal> ad, QList<qreal> jd, bool correction);
    void rpmMove(QList<qreal> s, QList<qreal> v, qreal a, qreal j, qreal ad, qreal jd, bool correction);

signals:

    void send(QByteArray data);
    void error(QString error);

public slots:

    void play();
    void pause();
    void stop();
    void settingsChanged();
    void receive(QByteArray data);

private slots:

    void onSend(QByteArray data);

private:

    void motorSetup();
    void convertUnits(QList<qreal> *s, QList<qreal> *v, QList<qreal> *a, QList<qreal> *j, QList<qreal> *ad, QList<qreal> *jd);

    NanotecStepperDriver *m_driver;
    QSettings *m_settings;
};

#endif // MOTORCONTROLLER_H
