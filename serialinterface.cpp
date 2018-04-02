#include "serialinterface.h"
#include <QtSerialPort>

SerialInterface::SerialInterface(QObject *parent) : QObject(parent)
{

    //defining pointers

    m_serialPort = new QSerialPort(this);
    m_openMode = new QIODevice::OpenMode;
    m_status = new SerialInterface::Status;
    m_buffer = new QStringList;

    //initialising pointers

    *m_status = SerialInterface::Disconnected;
    *m_openMode = QIODevice::ReadWrite;
    *m_buffer = QStringList();

    //emits that the status has changed

    emit statusChanged(*m_status);

    //signals and slots

    QObject::connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(onReadReady()));
}

SerialInterface::~SerialInterface()
{

    //deleting pointers

    delete m_openMode;
    delete m_status;
    delete m_buffer;

    //setting pointers to NULL

    m_openMode = NULL;
    m_status = NULL;
    m_buffer = NULL;
}

//disconnects the connection, sets the baudrate and reconects
bool SerialInterface::setBaudRate(qint32 baudRate)
{

    //checks if the connection is open
    //exected if it is
    if(m_serialPort->isOpen() == true){

        QIODevice::OpenMode mode;

        //stores the openmode
        mode = m_serialPort->openMode();
        //closes the connection
        m_serialPort->close();
        //sets the status to disconnected
        *m_status = SerialInterface::Disconnected;
        //emits that the status has changed
        emit statusChanged(*m_status);

        //checks if the settings of the baudrate was succesful
        //executed if it wasn't
        if(m_serialPort->setBaudRate(baudRate) == true){

            //emits that the baudRate has changed
            emit baudRateChanged(m_serialPort->baudRate());

            //checks if the opening of the connection was succesful
            //executed if it was
            if(m_serialPort->open(mode) == true){

                //sets the status to connected
                *m_status = SerialInterface::Connected;
                //emits that the status has changed
                emit statusChanged(*m_status);
                return true;
            }

            //executed if it wasn't
            else{

                //sets the status to Error
                *m_status = SerialInterface::Error;
                //emits that the status has changed
                emit statusChanged(*m_status);
                //emits that an error occured
                emit error(QString("Connection failed"));
                return false;
            }
        }

        //executed if it wasn't
        else{

            return false;
        }
    }

    //executed if it isn't
    else{

        //checks if the settings of the baudrate was succesful
        //executed if it is
        if(m_serialPort->setBaudRate(baudRate) == true){

            //emits that the baudrate has changed
            emit baudRateChanged(m_serialPort->baudRate());
            return true;
        }

        //executed if it wasn't
        else{

            return false;
        }
    }
}

//sets the portname
bool SerialInterface::setPortName(QString portName)
{

    //checks if the connection is open
    //exected if it is
    if(m_serialPort->isOpen() == true){

        QIODevice::OpenMode mode;

        //stores the openmode
        mode = m_serialPort->openMode();
        //closes the connection
        m_serialPort->close();
        //sets the status to Disconnected
        *m_status = SerialInterface::Disconnected;
        //emits that the status has changed
        emit statusChanged(*m_status);
        //sets the portname
        m_serialPort->setPortName(portName);
        //emits that the portname has changed
        emit portNameChanged(m_serialPort->portName());

        //checks if the opening of the connection was succesful
        //executed if it was
        if(m_serialPort->open(mode) == true){

            //sets the status to Connected
            *m_status = SerialInterface::Connected;
            //emits that the status has changed
            emit statusChanged(*m_status);
            return true;
        }

        //executed if it wasn't
        else{

            //sets the status to error
            *m_status = SerialInterface::Error;
            //emits that the status has changed
            emit statusChanged(*m_status);
            //emits that an error has occured
            emit error(QString("Connection failed"));
            return false;
        }
    }

    //executed if it is
    else{

        //sets the portname
        m_serialPort->setPortName(portName);
        //emits that the portname has changed
        emit portNameChanged(m_serialPort->portName());
        return true;
    }
}

QString SerialInterface::readData()
{

    return QString(m_serialPort->readAll());
}

//returns a list of all the availible ports
QStringList SerialInterface::availablePortNames()
{

    QStringList portNameList;

    //appends all the portnames to portNameList
    foreach(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts()){

        portNameList.append(portInfo.portName());

    }

    return portNameList;
}

//returns a list of all the standard baudrates
QStringList SerialInterface::standardBaudRates()
{

    QStringList baudRateList;

    //appends all the baudRates to baudRateList
    foreach (qint32 baudRate, QSerialPortInfo::standardBaudRates()) {

        baudRateList.append(QString::number(baudRate));
    }

    return baudRateList;
}

//returns the currently set openmode
QIODevice::OpenMode SerialInterface::openMode()
{

    return *m_openMode;
}

//sets the openmode to mode
void SerialInterface::setOpenMode(QIODevice::OpenMode mode)
{

    *m_openMode = mode;
}

//writes data to the serial connection
bool SerialInterface::send(QString data)
{

    //checks if the connection is open
    //exected if it is
    if(m_serialPort->isOpen() == true){

        QByteArray m_data;

        //appends data to m_data
        m_data.append(data);
        //writes m_data to the port
        m_serialPort->write(m_data);
        return true;
    }

    //executed if it isn't
    else{

        //sets the status to error
        *m_status = SerialInterface::Error;
        //emits that the status has changed
        emit statusChanged(*m_status);
        //emits that an error has occured
        emit error(QString("Not connected"));
        return false;
    }
}

//reconnects the serial connection
bool SerialInterface::reconnect()
{

    //disconnects
    SerialInterface::disconnect();
    //connects
    return SerialInterface::connect();
}

//reconnects the serial connection using mode
bool SerialInterface::reconnect(QIODevice::OpenMode mode)
{

    //disconnects
    SerialInterface::disconnect();
    //connects with mode
    return SerialInterface::connect(mode);
}

//triggered when there is data to read
void SerialInterface::onReadReady()
{

    QString data;

    data = m_serialPort->readAll();

    while(data.isEmpty() == false){

        if(data.contains(QString("\r")) == false){

            m_buffer->append(data);
            break;
        }

        else{

            if(m_buffer->last().contains(QString("\r")) == false){

                m_buffer->last().append(data.mid(0, data.indexOf(QString("\r")) + 1));
            }

            else{

                m_buffer->append(data.mid(0, data.indexOf(QString("\r")) + 1));
            }

            data.remove(0, data.indexOf(QString("\r")));
        }
    }

    checkBuffer();
}

//checks if there are command left in the buffer and if yes, clears them
void SerialInterface::checkBuffer()
{

    if(m_buffer->first().contains(QString("\r"))){

        emit dataReceived(m_buffer->takeFirst());
        checkBuffer();
    }
}

//connects the serial connection
bool SerialInterface::connect()
{

    //checks if the opening of the connection was succesful
    //executed if it is
    if(m_serialPort->open(*m_openMode) == true){

        //sets the status to Connected
        *m_status = SerialInterface::Connected;
        //emits that the status has changed
        emit statusChanged(*m_status);
        return true;
    }

    //executed if it isn't
    else{

        //sets the status to Error
        *m_status = SerialInterface::Error;
        //emits that the status has changed
        emit statusChanged(*m_status);
        //emits that an error has occured
        emit error(QString("Connection failed"));
        return false;
    }
}

//connects the serial connection using openmode
bool SerialInterface::connect(QIODevice::OpenMode mode)
{

    //checks if the opening of the connection was succesful
    //executed if it is
    if(m_serialPort->open(mode) == true){

        //sets the status to Connected
        *m_status = SerialInterface::Connected;
        //emits that the status has changed
        emit statusChanged(*m_status);
        return true;
    }

    //executed if it isn't
    else{

        //sets the status to Error
        *m_status = SerialInterface::Error;
        //emits that the status has changed
        emit statusChanged(*m_status);
        //emits that an error has occured
        emit error(QString("Connection failed"));
        return false;
    }
}

//disconnects the serial connection
void SerialInterface::disconnect()
{

    //checks if the connection is open
    //exected if it is
    if(m_serialPort->isOpen() == true){

        //closes the connection
        m_serialPort->close();
        //sets the status to Disconnected
        *m_status = SerialInterface::Disconnected;
        //emits that the status has changed
        emit statusChanged(*m_status);
    }
}

//returns the currently set portname
QString SerialInterface::portName()
{

    return m_serialPort->portName();
}

//returns the currently set baudrate
qint32 SerialInterface::baudRate()
{

    return m_serialPort->baudRate();
}

//returns the current status
SerialInterface::Status SerialInterface::status()
{

    return *m_status;
}
