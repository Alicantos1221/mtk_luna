#include "manager.h"
Manager::Manager(QObject *parent)
    : QObject{parent}
{
    QObject::connect(&timer,&QTimer::timeout,this,&Manager::timeout);
    timer.start(500);
    quint8 address = 0x01;
    answer.append(address);

    quint8 command = 0x05;
    answer.append(command);

    quint8 status = 0x00;
    answer.append(status);

    quint8 lrc = calculateLRC(answer);
    answer.append(lrc);
}

void Manager::dataOK()
{
    timer.stop();
    emit writeData(answer);
    timer.start(500);
}

quint8 Manager::calculateLRC(const QByteArray &data){
    quint8 lrc = 0;
    for(int i=0; i < data.size()-1;++i){
        lrc+=static_cast<quint8>(data[i]);
    }
    return static_cast<quint8>(0x100 -lrc);
}

void Manager::timeout()
{
    qDebug()<<"Ничего не приходит";
}
