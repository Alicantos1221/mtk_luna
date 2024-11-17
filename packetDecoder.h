#ifndef PACKETDECODER_H
#define PACKETDECODER_H

#include <QObject>
#include <QDebug>

const double ANGLE_SCALE_FACTOR = 360.0 / 32768.0;
const quint16 SIGN_BIT_MASK = 0x8000;
const double ANGLE_CORRECTION = 360.0;

struct Packet{
    bool isTestmode;
    bool isAlphaReliable;
    bool isBetaReliable;
    double alphaG;
    double alphaBUO;
    double deltaAlphaG;
    double psi0;
    double betaGG;
    double deltaBetaGG;
    bool isLrcValid;
};

class PacketDecoder : public QObject
{
    Q_OBJECT
public:
    explicit PacketDecoder(QObject *parent = nullptr);
public slots:
    void readData(QByteArray ba);
signals:
    void dataOK();
private:
    Packet packet;
};


#endif // PACKETDECODER_H
