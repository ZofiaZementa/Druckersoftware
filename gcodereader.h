#ifndef GCODEREADER_H
#define GCODEREADER_H

#include <QObject>

class GCodeReader : public QObject
{
    Q_OBJECT
public:
    explicit GCodeReader(QObject *parent = nullptr);

signals:

public slots:
};

#endif // GCODEREADER_H