#ifndef IOCONTROLLER_H
#define IOCONTROLLER_H

#include <QObject>
#include <QSettings>
#include "piControl.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

class IOController : public QObject
{
    Q_OBJECT
public:
    explicit IOController(QObject *parent = nullptr);
    ~IOController();

public slots:

    int readVariableValue(QString pinName);
    bool writeVariableValue(QString pinName, int value);

signals:

    void logEntry(QString logMessage, int code);
    void error(QString errorMessage);

private:

    int piControlGetVariableInfo(SPIVariable *pSpiVariable);
    int piControlGetBitValue(SPIValue *pSpiValue);
    int piControlRead(uint32_t Offset, uint32_t Length, uint8_t *pData);
    int piControlWrite(uint32_t Offset, uint32_t Length, uint8_t *pData);
    void piControlOpen();
    int piControlSetBitValue(SPIValue *pSpiValue);

    int PiControlHandle_g = -1;
};

#endif // IOCONTROLLER_H
