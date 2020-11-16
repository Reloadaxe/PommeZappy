#include "Client.h"

Client::Client()
{
}

Client::Client(QString client_id, QTcpSocket *socket)
{
    this->client_id = client_id;
    this->socket = socket;
}

Client::Client(std::string client_id, QTcpSocket *socket)
{
    this->client_id = QString::fromUtf8(client_id.c_str());
    this->socket = socket;
}

Client::~Client()
{
    this->disconnect();
}

void Client::setPlayer(Player* player)
{
    this->player = player;
    player->SetClient(this);
}

Player* Client::getPlayer() const
{
    return this->player;
}

void Client::setMap(Map* map)
{
    this->map = map;
}

Map* Client::getMap() const
{
    return this->map;
}

void Client::disconnect()
{
    this->socket->disconnect();
}

void Client::setClientId(QString client_id)
{
    this->client_id = client_id;
}

QString Client::getClientId() const
{
    return this->client_id;
}

QTcpSocket* Client::getSocket() const
{
    return this->socket;
}

bool Client::isConnected() const
{
    return (this->socket->state() == QTcpSocket::ConnectedState);
}
