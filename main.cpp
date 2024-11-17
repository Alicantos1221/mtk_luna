#include <QCoreApplication>
#include <QDebug>

#include "serialPortManager.h"
#include "packetDecoder.h"
#include "manager.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SerialPortSettings settings;
    settings.baudrate = QSerialPort::Baud19200;
    settings.databits = QSerialPort::Data8;
    settings.parity = QSerialPort::NoParity;
    settings.stopBits = QSerialPort::OneStop;
    settings.flow = QSerialPort::NoFlowControl;

    SerialPortManager serialPortManager(settings);
    PacketDecoder packetDecoder;
    Manager manager;

    // отправили полученное сообщение на расшифровку и визуализацию
    QObject::connect(&serialPortManager,&SerialPortManager::readData,&packetDecoder,&PacketDecoder::readData);
    // отправили сообщение манагеру, чтоб он сбросил таймер и отправил ответ
    QObject::connect(&packetDecoder,&PacketDecoder::dataOK,&manager,&Manager::dataOK);
    // манагер запулил ответ через сом порт
    QObject::connect(&manager,&Manager::writeData,&serialPortManager,&SerialPortManager::writeData);

    serialPortManager.setPortName();
    serialPortManager.open();

    return a.exec();
}
