#ifndef FANCONTROLLER_H
#define FANCONTROLLER_H

#include <QObject>

class FanController : public QObject
{
    Q_OBJECT
public:
    explicit FanController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // FANCONTROLLER_H