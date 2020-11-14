#include "Server.h"

Server::Server(std::string listen_host, int listen_port, int max_clients, QObject *parent)
    : QTcpServer(parent)
{
    this->listen_host = QString::fromUtf8(listen_host.c_str());
    this->listen_port = listen_port;
    this->max_clients = max_clients;
}

Server* Server::getInstance(std::string listen_host, int listen_port, int max_clients, QObject *parent)
{
    if (instance == 0)
        instance = new Server(listen_host, listen_port, max_clients, parent);
    return instance;
}

void Server::start(void)
{
    QHostAddress address;
    address.setAddress(this->listen_host);
    listen(address, (qint16)this->listen_port);
}

void Server::refuseAdditionalClients()
{
    this->refuse_additional_clients = true;
}

void Server::incomingConnection(int socketDescriptor)
{
    QTcpSocket *socket_client = new QTcpSocket(this);
    socket_client->setSocketDescriptor(socketDescriptor);

    if (static_cast<int>(this->clients.size()) >= max_clients
            || this->refuse_additional_clients)
        socket_client->disconnect();

    QString peer_name = QString::fromUtf8(get_uuid().c_str());
    Client client = Client(peer_name, socket_client);
    client.connected = true;
    qDebug() << "Client connected with address "\
             << socket_client->peerAddress().toString()\
             << " : ID " << peer_name << " was attributed";
    this->clients.insert(std::pair<QTcpSocket*, Client>(socket_client, client));

    // UI->addMessage("New client from: "+client->peerAddress().toString());

    connect(socket_client, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket_client, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

// On incoming command
void Server::readyRead()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    while(client->canReadLine())
    {
        QString line = QString::fromUtf8(client->readLine()).trimmed();
        //qDebug() << "Read line:" << line;
        // add command to client stack !
    }
}

void Server::disconnected()
{
    QTcpSocket *socket_client = (QTcpSocket*)sender();
    Client client = clients.find(socket_client)->second;

    if (client.getClientId() == NULL)
    {
        qDebug() << "ERROR: Can't find client : " << socket_client->peerAddress().toString();
        return;
    }
    qDebug() << "Client disconnected : " << socket_client->peerAddress().toString();

    client.connected = false;
    clients.erase(socket_client);
}
