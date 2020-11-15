#ifndef _NTW_SERVER_H
#define _NTW_SERVER_H

#include <map>
#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>

#include "Client.h"

class Server : public QTcpServer {
    Q_OBJECT

public:
    static Server* getInstance(std::string listen_host, int listen_port, int max_clients);
    void start(void);
    void stop(void);
    void refuseAdditionalClients(); // When game starts
    void respondToCommand(Client* client, QString command);
    bool areAllClientsDisconnected();
    void performGameCycle(Map* map);

    std::vector<Client*> getClients();

protected:
    void incomingConnection(qintptr socketDescriptor);

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

#endif
