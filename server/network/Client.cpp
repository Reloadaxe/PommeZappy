#include "Client.h"

Client::Client()
{
}

Client::Client(QString client_id)
{
    this->client_id = client_id;
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

void Client::setClientId(QString client_id)
{
    this->client_id = client_id;
}

QString Client::getClientId() const
{
    return this->client_id;
}

void Client::setSocket(QTcpSocket* socket)
{
    this->socket = socket;
}

QTcpSocket* Client::getSocket() const
{
    return this->socket;
}

bool Client::isConnected() const
{
    if (this->socket != nullptr && this->socket->isValid())
        return (this->socket->state() == QTcpSocket::ConnectedState);
    else
        return false;
}
