#include "serialPortManager.h"

SerialPortManager::SerialPortManager(SerialPortSettings settings, QObject *parent): QObject(parent),
    serialPort(new QSerialPort(this))
{
    connect(serialPort, &QSerialPort::readyRead, this, &SerialPortManager::handeReadyRead);
    connect(serialPort, &QSerialPort::errorOccurred, this, &SerialPortManager::handleError);
    serialPort->setBaudRate(settings.baudrate);
    serialPort->setDataBits(settings.databits);
    serialPort->setParity(settings.parity);
    serialPort->setStopBits(settings.stopBits);
    serialPort->setFlowControl(settings.flow);
}

SerialPortManager::~SerialPortManager()
{
    if (serialPort->isOpen()) {
            serialPort->close();
        }
        delete serialPort;
}

void SerialPortManager::setPortName(QString portName)
{
    serialPort->setPortName(portName);
}

void SerialPortManager::open()
{
    if (!serialPort->isOpen()) {
            if (!serialPort->open(QIODevice::ReadWrite)) {
                qWarning() << "Не удалось открыть порт" << serialPort->portName();
            }
        }
}

void SerialPortManager::close()
{
    if (serialPort->isOpen()) {
            serialPort->close();
        }
}

void SerialPortManager::writeData(QByteArray ba)
{
    if(serialPort->isOpen()){
        serialPort->write(ba);
        qDebug()<<"Sent data"<<ba.toHex();
    } else {
        qWarning()<<"Порт закрыт. Невозможно отправить данные.";
    }
}

void SerialPortManager::handeReadyRead()
{
    QByteArray ba = serialPort->readAll();
    emit readData(ba);
}

void SerialPortManager::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError) return;
        qWarning() << "Ошибка порта:" << serialPort->errorString();
}
