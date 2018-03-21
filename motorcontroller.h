#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <QObject>

class MotorController : public QObject
{
    Q_OBJECT
public:
    explicit MotorController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MOTORCONTROLLER_H