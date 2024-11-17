#include "packetDecoder.h"
#include <QDateTime>

PacketDecoder::PacketDecoder(QObject *parent)
    : QObject{parent} {}

void PacketDecoder::readData(QByteArray ba)
{
        // Значение угла
        if (ba.size() >= 2) {
            quint16 rawValue = static_cast<quint16>(ba[0] | (ba[1] << 8));
            packet.alphaG = rawValue * ANGLE_SCALE_FACTOR;
            if (rawValue & SIGN_BIT_MASK) {
                packet.alphaG -= ANGLE_CORRECTION;
            }
        }
 //читаем в packet
    // расшифровываем, и если всё в поряде выдаем сигнал managery
    emit dataOK();

    // Логи для расшифрованных данных
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");

    // Вывод расшифрованного сообщения
        qDebug() << timestamp << ": Packet received.";
        qDebug() << timestamp << ": Режим работы: " << (packet.isTestmode ? "Тестовый" : "Рабочий");
        qDebug() << timestamp << ": Надежность угла альфа: " << (packet.isAlphaReliable ? "Надежен" : "Не надежен");
        qDebug() << timestamp << ": Надежность угла бета: " << (packet.isBetaReliable ? "Надежен" : "Не надежен");
        qDebug() << timestamp << ": Угол альфа (G): " << packet.alphaG;
        qDebug() << timestamp << ": Угол альфа (BUO): " << packet.alphaBUO;
        qDebug() << timestamp << ": Изменение угла альфа (дельта G): " << packet.deltaAlphaG;
        qDebug() << timestamp << ": Пси0: " << packet.psi0;
        qDebug() << timestamp << ": Угол бета (GG): " << packet.betaGG;
        qDebug() << timestamp << ": Изменение угла бета (дельта GG): " << packet.deltaBetaGG;
        qDebug() << timestamp << ": Контрольная сумма LRC: " << (packet.isLrcValid ? "Корректна" : "Некорректна");
}
