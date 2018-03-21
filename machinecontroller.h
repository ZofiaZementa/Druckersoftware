#ifndef MACHINECONTROLLER_H
#define MACHINECONTROLLER_H

#include <QObject>

class MachineController : public QObject
{
    Q_OBJECT
public:
    explicit MachineController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MACHINECONTROLLER_H