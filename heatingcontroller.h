#ifndef HEATINGCONTROLLER_H
#define HEATINGCONTROLLER_H

#include <QObject>

class HeatingController : public QObject
{
    Q_OBJECT
public:
    explicit HeatingController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // HEATINGCONTROLLER_H