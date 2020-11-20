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
    ClientThread(int socketDescriptor, Client* client, QObject *parent);

    void run() override;
    void respondToCommand(Client* client, QString command);

private slots:
    void disconnected();

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    Client* client;
    QTcpSocket* socket;
};

#endif // CLIENTTHREAD_H
