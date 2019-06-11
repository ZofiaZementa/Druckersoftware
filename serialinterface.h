#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QSettings>

class SerialInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QIODevice::OpenMode openMode READ openMode WRITE setOpenMode)
    Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged)
    Q_PROPERTY(qint32 baudRate READ baudRate WRITE setBaudRate NOTIFY baudRateChanged)

public:
    explicit SerialInterface(QObject *parent = nullptr);
    ~SerialInterface();

    enum Status{Connected, Disconnected, Error};

    bool setBaudRate(qint32 baudRate);
    bool setPortName(QString portName);
    QString readData();
    QStringList availablePortNames();
    QStringList standardBaudRates();
    QIODevice::OpenMode openMode();
    void setOpenMode(QIODevice::OpenMode mode);
    QString portName();
    qint32 baudRate();
    Status status();

signals:

    void error(QString errorMessage);
    void dataReceived(QByteArray data);
    void statusChanged(SerialInterface::Status status);
    void portNameChanged(QString portName);
    void baudRateChanged(qint32 baudRate);

public slots:

    void initialise();
    bool connect();
    bool connect(QIODevice::OpenMode mode);
    void disconnect();
    void send(QByteArray data);
    bool reconnect();
    bool reconnect(QIODevice::OpenMode mode);

private slots:

    void onReadReady();
    void onBytesWritten();

private:

    void sendData(QByteArray data);

    QSerialPort *m_serialPort;
    Status *m_status;
    QIODevice::OpenMode *m_openMode;
    QSettings *m_settings;

};

#endif // SERIALINTERFACE_H
