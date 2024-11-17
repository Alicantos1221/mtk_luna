#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>

//устанавливать в этом классе настройки порта нельзя - этот класс же у нас универсальный
struct SerialPortSettings{
    QSerialPort::BaudRate baudrate;
    QSerialPort::DataBits databits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flow;
};

class SerialPortManager : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortManager(SerialPortSettings settings,QObject *parent = nullptr);
    ~SerialPortManager();
    void setPortName(QString portName = "/dev/ttyS0");
    void open();
    void close();

public slots:
    void writeData(QByteArray ba);

private slots:
    void handeReadyRead();
    void handleError(QSerialPort::SerialPortError error);
signals:
    void readData(QByteArray ba);

private:
    QSerialPort *serialPort;
};

#endif // SERIALPORTMANAGER_H
