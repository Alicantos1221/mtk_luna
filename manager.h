#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QTimer>
#include <QDebug>

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = nullptr);
public slots:
    void dataOK();
signals:
    void writeData(QByteArray ba);
private:
    QTimer timer;
    void timeout();
    QByteArray answer;
    quint8 calculateLRC(const QByteArray &data);
};

#endif // MANAGER_H
