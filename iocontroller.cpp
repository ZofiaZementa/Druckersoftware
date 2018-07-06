#include "iocontroller.h"

IOController::IOController(QObject *parent) : QObject(parent)
{

    bool ok;
    emit logEntry(QString("IOController started successfully"), QString("0x020001").toInt(&ok, 16));
}

int IOController::readVariableValue(QString pinName)
{

    int rc;
    SPIVariable sPiVariable;
    SPIValue sPIValue;
    uint8_t i8uValue;
    uint16_t i16uValue;
    uint32_t i32uValue;
    QByteArray dat = pinName.toLatin1();

    strncpy(sPiVariable.strVarName, dat.data(), sizeof(sPiVariable.strVarName));
    rc = piControlGetVariableInfo(&sPiVariable);

    if(rc < 0){

        bool ok;
        emit logEntry(QString("Cannot find pin name %1").arg(pinName), QString("0x02FFFF").toInt(&ok, 16));
        emit error(QString("Cannot find pin name %1").arg(pinName));
        return 0;
    }

    if (sPiVariable.i16uLength == 1) {

        sPIValue.i16uAddress = sPiVariable.i16uAddress;
        sPIValue.i8uBit = sPiVariable.i8uBit;
        rc = piControlGetBitValue(&sPIValue);

        if (rc < 0){

            bool ok;
            emit logEntry(QString("Set bit error"), QString("0x02FFFE").toInt(&ok, 16));
            emit error(QString("Set bit error"));
            return 0;
        }

        else{

            bool ok;
            emit logEntry(QString("Read value %1 at pin %2").arg((int)sPIValue.i8uValue).arg(pinName), QString("0x020004").toInt(&ok, 16));
            return (int)sPIValue.i8uValue;
        }
    }

    else if (sPiVariable.i16uLength == 8) {

        rc = piControlRead(sPiVariable.i16uAddress, 1, (uint8_t *) & i8uValue);

        if(rc < 0){

            bool ok;
            emit logEntry(QString("Read error"), QString("0x02FFFC").toInt(&ok, 16));
            emit error(QString("Read error"));
            return 0;
        }

        else{

            bool ok;
            emit logEntry(QString("Read value %1 at pin %2").arg((int)i8uValue).arg(pinName), QString("0x020004").toInt(&ok, 16));
            return (int)i8uValue;
        }
    }

    else if(sPiVariable.i16uLength == 16){

        rc = piControlRead(sPiVariable.i16uAddress, 2, (uint8_t *) & i16uValue);

        if (rc < 0){

            bool ok;
            emit logEntry(QString("Read error"), QString("0x02FFFC").toInt(&ok, 16));
            emit error(QString("Read error"));
            return 0;
        }

        else{

            bool ok;
            emit logEntry(QString("Read value %1 at pin %2").arg((int)i16uValue).arg(pinName), QString("0x020004").toInt(&ok, 16));
            return (int)i16uValue;
        }
    }

    else if (sPiVariable.i16uLength == 32) {

        rc = piControlRead(sPiVariable.i16uAddress, 4, (uint8_t *) & i32uValue);

        if (rc < 0){

            bool ok;
            emit logEntry(QString("Read error"), QString("0x02FFFC").toInt(&ok, 16));
            emit error(QString("Read error"));
            return 0;
        }

        else{

            bool ok;
            emit logEntry(QString("Read value %1 at pin %2").arg((int)i32uValue).arg(pinName), QString("0x020004").toInt(&ok, 16));
            return (int)i32uValue;
        }
    }

    else{

        bool ok;
        emit logEntry(QString("Could not read variable %1. Internal Error").arg(pinName), QString("0x02FFFB").toInt(&ok, 16));
        emit error(QString("Could not read variable %1. Internal Error").arg(pinName));
        return 0;
    }
}

bool IOController::writeVariableValue(QString pinName, int value)
{

    int rc;
    SPIVariable sPiVariable;
    SPIValue sPIValue;
    uint8_t i8uValue;
    uint16_t i16uValue;
    QByteArray dat = pinName.toLatin1();

    strncpy(sPiVariable.strVarName, dat.data(), sizeof(sPiVariable.strVarName));
    rc = piControlGetVariableInfo(&sPiVariable);

    if(rc < 0){

        bool ok;
        emit logEntry(QString("Cannot find pin name %1").arg(pinName), QString("0x02FFFF").toInt(&ok, 16));
        emit error(QString("Cannot find pin name %1").arg(pinName));
        return false;
    }

    if(sPiVariable.i16uLength == 1){

        sPIValue.i16uAddress = sPiVariable.i16uAddress;
        sPIValue.i8uBit = sPiVariable.i8uBit;
        sPIValue.i8uValue = (uint8_t)(value);
        rc = piControlSetBitValue(&sPIValue);

        if(rc < 0){

            bool ok;
            emit logEntry(QString("Set bit error"), QString("0x02FFFE").toInt(&ok, 16));
            emit error(QString("Set bit error"));
            return false;
        }

        else{

            bool ok;
            emit logEntry(QString("Set bit %1 on byte at offset %2. Value %3").arg(sPIValue.i8uBit).arg(sPIValue.i16uAddress).arg(sPIValue.i8uValue), QString("0x0020002").toInt(&ok, 16));
            return true;
        }
    }

    else if(sPiVariable.i16uLength == 8){

        i8uValue = (uint8_t)value;
        rc = piControlWrite(sPiVariable.i16uAddress, 1, (uint8_t *) & i8uValue);

        if(rc < 0){

            bool ok;
            emit logEntry(QString("Write error"), QString("0x02FFFD").toInt(&ok, 16));
            emit error(QString("Write error"));
            return false;
        }

        else{

            bool ok;
            emit logEntry(QString("Write value %1 dez to offset %3").arg(i8uValue).arg(i8uValue).arg(sPiVariable.i16uAddress), QString("0x0020003").toInt(&ok, 16));
            return true;
        }
    }

    else if(sPiVariable.i16uLength == 16){

        i16uValue = (uint16_t)value;
        rc = piControlWrite(sPiVariable.i16uAddress, 2, (uint8_t *) & i16uValue);

        if(rc < 0){

            bool ok;
            emit logEntry(QString("Write error"), QString("0x02FFFD").toInt(&ok, 16));
            emit error(QString("Write error"));
            return false;
        }

        else{

            bool ok;
            emit logEntry(QString("Write value %1 dez to offset %3").arg(i16uValue).arg(i16uValue).arg(sPiVariable.i16uAddress), QString("0x0020003").toInt(&ok, 16));
            return true;
        }
    }

    else if(sPiVariable.i16uLength == 32){

        uint32_t i32uValue = (uint32_t)value;
        rc = piControlWrite(sPiVariable.i16uAddress, 4, (uint8_t *) & i32uValue);

        if (rc < 0){

            bool ok;
            emit logEntry(QString("Write error"), QString("0x02FFFD").toInt(&ok, 16));
            emit error(QString("Write error"));
            return false;
        }

        else{

            bool ok;
            emit logEntry(QString("Write value %1 dez to offset %3").arg((uint32_t)value).arg((uint32_t)value).arg(sPiVariable.i16uAddress), QString("0x0020003").toInt(&ok, 16));
            return true;
        }
    }
}

int IOController::piControlGetVariableInfo(SPIVariable *pSpiVariable)
{

    piControlOpen();

    if (PiControlHandle_g < 0)
    return -ENODEV;

    if (ioctl(PiControlHandle_g, KB_FIND_VARIABLE, pSpiVariable) < 0)
    return errno;

    return 0;
}

int IOController::piControlGetBitValue(SPIValue *pSpiValue)
{

    piControlOpen();

    if (PiControlHandle_g < 0)
    return -ENODEV;

    pSpiValue->i16uAddress += pSpiValue->i8uBit / 8;
    pSpiValue->i8uBit %= 8;

    if (ioctl(PiControlHandle_g, KB_GET_VALUE, pSpiValue) < 0)
    return errno;

    return 0;
}

int IOController::piControlRead(uint32_t Offset, uint32_t Length, uint8_t *pData)
{

    int BytesRead = 0;

    piControlOpen();

    if (PiControlHandle_g < 0)
    return -ENODEV;

    /* seek */
    if (lseek(PiControlHandle_g, Offset, SEEK_SET) < 0)
    {
    return errno;
    }

    /* read */
    BytesRead = read(PiControlHandle_g, pData, Length);
    if (BytesRead < 0)
    {
    return errno;
    }

    return BytesRead;
}

int IOController::piControlWrite(uint32_t Offset, uint32_t Length, uint8_t *pData)
{

    int BytesWritten = 0;

    piControlOpen();

    if (PiControlHandle_g < 0)
    return -ENODEV;

    /* seek */
    if (lseek(PiControlHandle_g, Offset, SEEK_SET) < 0)
    {
    return errno;
    }

    /* Write */
    BytesWritten = write(PiControlHandle_g, pData, Length);
    if (BytesWritten < 0)
    {
    return errno;
    }

    return BytesWritten;
}

void IOController::piControlOpen()
{

    /* open handle if needed */
    if (PiControlHandle_g < 0){

        PiControlHandle_g = open(PICONTROL_DEVICE, O_RDWR);
    }
}

int IOController::piControlSetBitValue(SPIValue *pSpiValue)
{

    piControlOpen();

    if (PiControlHandle_g < 0)
    return -ENODEV;

    pSpiValue->i16uAddress += pSpiValue->i8uBit / 8;
    pSpiValue->i8uBit %= 8;

    if (ioctl(PiControlHandle_g, KB_SET_VALUE, pSpiValue) < 0)
    return errno;

    return 0;
}
