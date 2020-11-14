#ifndef _NTW_SERVER_H
#define _NTW_SERVER_H

#include <map>
#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>

#include "Client.h"
#include "server_utils.h"

class Server : public QTcpServer {
    Q_OBJECT

public:
    static Server* getInstance(std::string listen_host, int listen_port, int max_clients, QObject *parent);
    void start(void);
    void refuseAdditionalClients(); // When game starts

protected:
    void incomingConnection(int socketDescriptor);

private slots:
    void readyRead();
    void disconnected();

private:
    static Server* instance;
    Server(std::string listen_host, int listen_port, int max_clients, QObject *parent = nullptr);

    std::map<QTcpSocket*, Client> clients;
    QString listen_host;
    int listen_port;
    int max_clients;
    bool refuse_additional_clients = false;
};

Server* Server::instance = 0;

#endif
