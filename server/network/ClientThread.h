#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <iostream>
#include <vector>
#include <QTcpSocket>
#include <QThread>
#include "Client.h"

class ClientThread : public QThread
{
    Q_OBJECT

public:
    ClientThread(int socketDescriptor, QObject *parent);

    void run() override;
    void respondToCommand(Client* client, QString command);

public slots:
    void disconnected();

signals:
    void error(QTcpSocket::SocketError socketError);
    void canBePushed();

private:
    int socketDescriptor;
    Client* client;
    QTcpSocket* socket;
};

#endif // CLIENTTHREAD_H
