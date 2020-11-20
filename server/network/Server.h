#ifndef _NTW_SERVER_H
#define _NTW_SERVER_H

#include <map>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <QTcpServer>
#include <QTcpSocket>

#include "Cell.hh"
#include "Client.h"
#include "Item.hh"
#include "ItemFactory.hh"

class Server : public QTcpServer {
    Q_OBJECT

public:
    static Server* getInstance(std::string listen_host, int listen_port, int max_clients);
    static Server* getInstance(std::string listen_host, int listen_port, int max_clients, QObject *parent);
    static Server* getInstance(void);
    void refuseAdditionalClients(); // When game starts
    void respondToCommand(Client* client, QString command);
    bool areAllClientsDisconnected();
    void performGameCycle(Map* map);

    std::vector<Client*> getClients();

public slots:
    void start(void);
    void stop(void);

protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;

private:
    static Server* instance;
    Server(std::string listen_host, int listen_port, int max_clients, QObject *parent = nullptr);

    std::vector<Client*> clients;
    QString listen_host;
    int listen_port;
    int max_clients;
    bool refuse_additional_clients = false;

signals:
    void error(QTcpSocket::SocketError socketError);
};

#endif
