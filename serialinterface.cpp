#include "serialinterface.h"
#include <QtSerialPort>

SerialInterface::SerialInterface(QObject *parent) : QObject(parent)
{

}

SerialInterface::~SerialInterface()
{

    //deleting pointers

    delete m_openMode;
    delete m_status;
    delete m_converstionStatus;
    delete m_inputBuffer;
    delete m_outputBuffer;

    //setting pointers to NULL

    m_openMode = NULL;
    m_status = NULL;
    m_converstionStatus = NULL;
    m_inputBuffer = NULL;
    m_outputBuffer = NULL;
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

            emit error(QString("Baudrate couldn't be changed"));
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

            emit error(QString("Baudrate couldn't be changed"));
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
void SerialInterface::send(QString data)
{

    QByteArray dat;

    dat.append(data);
    m_outputBuffer->append(dat);
    checkOutputBuffer();
}

void SerialInterface::send(QByteArray data)
{

    m_outputBuffer->append(data);
    checkOutputBuffer();
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

    data = QString(m_serialPort->readAll());

    while(data.isEmpty() == false){

        if(data.contains(QString("\r")) == false){

            m_inputBuffer->append(data);
            break;
        }

        else{

            if(m_inputBuffer->isEmpty() == false && m_inputBuffer->last().contains(QString("\r")) == false){

                m_inputBuffer->last().append(data.mid(0, data.indexOf(QString("\r")) + 1));
            }

            else{

                m_inputBuffer->append(data.mid(0, data.indexOf(QString("\r")) + 1));
            }

            data.remove(0, data.indexOf(QString("\r")) + 1);
        }
    }

    checkInputBuffer();
}

//checks if there are command left in the buffer and if yes, clears them
void SerialInterface::checkInputBuffer()
{

    if(m_inputBuffer->isEmpty() == false && m_inputBuffer->first().contains(QString("\r"))){

        if(QString(m_inputBuffer->first().at(0)).toInt() == m_settings->value("motorsettings/xaxis/motoradress", 1).toInt()){

            (*m_converstionStatus)[0] = ConversationStatus::Ready;
        }

        else if(QString(m_inputBuffer->first().at(0)).toInt() == m_settings->value("motorsettings/yaxis/motoradress", 2).toInt()){

            (*m_converstionStatus)[1] = ConversationStatus::Ready;
        }

        else if(QString(m_inputBuffer->first().at(0)).toInt() == m_settings->value("motorsettings/zaxis/motoradress", 3).toInt()){

            (*m_converstionStatus)[2] = ConversationStatus::Ready;
        }

        else if(QString(m_inputBuffer->first().at(0)).toInt() == m_settings->value("motorsettings/extruder/motoradress", 4).toInt()){

            (*m_converstionStatus)[3] = ConversationStatus::Ready;
        }

        else if(m_inputBuffer->first().at(0)== QChar('*')){

            for(int i = 0;i < m_converstionStatus->count();i++){

                (*m_converstionStatus)[i] = ConversationStatus::Ready;
            }
        }

        else{

            emit error("invalid Adress");
            return;
        }

        emit dataReceived(m_inputBuffer->takeFirst());
        checkInputBuffer();
    }
}

void SerialInterface::checkOutputBuffer()
{

    if(m_outputBuffer->isEmpty() == false){

        if(m_converstionStatus->at(0) == ConversationStatus::Ready || m_converstionStatus->at(1) == ConversationStatus::Ready || m_converstionStatus->at(2) == ConversationStatus::Ready || m_converstionStatus->at(3) == ConversationStatus::Ready){

            for(int i = 0;i < m_outputBuffer->length();i++){

                if(m_converstionStatus->at(0) == ConversationStatus::Ready && m_outputBuffer->at(i).at(1) == QString("%1").arg(m_settings->value("motorsettings/xaxis/motoradress", 1).toInt()).toLatin1().at(0)){

                    sendData(m_outputBuffer->takeAt(i));
                    (*m_converstionStatus)[0] = ConversationStatus::WaitingForReply;
                }

                else if(m_converstionStatus->at(1) == ConversationStatus::Ready && m_outputBuffer->at(i).at(1) == QString("%1").arg(m_settings->value("motorsettings/yaxis/motoradress", 2).toInt()).toLatin1().at(0)){

                    sendData(m_outputBuffer->takeAt(i));
                    (*m_converstionStatus)[1] = ConversationStatus::WaitingForReply;
                }

                else if(m_converstionStatus->at(2) == ConversationStatus::Ready && m_outputBuffer->at(i).at(1) == QString("%1").arg(m_settings->value("motorsettings/zaxis/motoradress", 3).toInt()).toLatin1().at(0)){

                    sendData(m_outputBuffer->takeAt(i));
                    (*m_converstionStatus)[2] = ConversationStatus::WaitingForReply;
                }

                else if(m_converstionStatus->at(3) == ConversationStatus::Ready && m_outputBuffer->at(i).at(1) == QString("%1").arg(m_settings->value("motorsettings/extruder/motoradress", 4).toInt()).toLatin1().at(0)){

                    sendData(m_outputBuffer->takeAt(i));
                    (*m_converstionStatus)[3] = ConversationStatus::WaitingForReply;
                }

                else if(m_converstionStatus->at(0) == ConversationStatus::Ready && m_converstionStatus->at(1) == ConversationStatus::Ready && m_converstionStatus->at(2) == ConversationStatus::Ready && m_converstionStatus->at(3) == ConversationStatus::Ready && m_outputBuffer->at(i).at(1) == QString("*").toLatin1().at(0)){

                    sendData(m_outputBuffer->takeAt(i));

                    for(int n = 0;n < m_converstionStatus->count();n++){

                        (*m_converstionStatus)[n] = ConversationStatus::WaitingForReply;
                    }
                }

                else{

                    return;
                }

            }
        }
    }
}

void SerialInterface::sendData(QByteArray data)
{

    //checks if the connection is open
    //exected if it is
    if(m_serialPort->isOpen() == true){

        //writes m_data to the port
        m_serialPort->write(data);
    }

    //executed if it isn't
    else{

        //sets the status to error
        *m_status = SerialInterface::Error;
        //emits that the status has changed
        emit statusChanged(*m_status);
        //emits that an error has occured
        emit error(QString("Not connected"));
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

void SerialInterface::initialise()
{

    //defining pointers

    m_serialPort = new QSerialPort(this);
    m_openMode = new QIODevice::OpenMode;
    m_status = new SerialInterface::Status;
    m_converstionStatus = new QList<SerialInterface::ConversationStatus>;
    m_inputBuffer = new QStringList;
    m_outputBuffer = new QList<QByteArray>;
    m_settings = new QSettings;

    //initialising pointers

    *m_status = SerialInterface::Disconnected;
    *m_openMode = QIODevice::ReadWrite;
    *m_inputBuffer = QStringList();

    for(int i = 0;i < 4;i++){

        m_converstionStatus->append(ConversationStatus::Ready);
    }

    //emits that the status has changed

    emit statusChanged(*m_status);

    //signals and slots

    QObject::connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(onReadReady()));
}
