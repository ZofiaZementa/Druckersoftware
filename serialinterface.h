#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include <QObject>

class SerialInterface : public QObject
{
    Q_OBJECT
public:
    explicit SerialInterface(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SERIALINTERFACE_H