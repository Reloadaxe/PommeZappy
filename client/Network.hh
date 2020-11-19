#ifndef _NETWORK_HH
#define _NETWORK_HH

#include <QString>
#include <QTcpSocket>
#include <QDataStream>
#include <iostream>

class Network : public QObject {
    Q_OBJECT
public:
    static Network *Get(void);
    void Connect(const QString host, const quint16 port);
    void Send(const QString message);
    QString Read(void);

private slots:
    void sendError(QAbstractSocket::SocketError socketError);

private:
    Network();
    QTcpSocket _socket;
    static Network *_network;
};

#endif