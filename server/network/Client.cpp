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
}

Player* Client::getPlayer()
{
    return this->player;
}

void Client::setMap(Map* map)
{
    this->map = map;
}

Map* Client::getMap()
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

QString Client::getClientId()
{
    return this->client_id;
}

void Client::setCommand(QString command)
{
    this->move_command = command;
}

QString Client::getCommand()
{
    return this->move_command;
}

void Client::clearCommand()
{
    this->move_command = "";
}

QTcpSocket* Client::getSocket()
{
    return this->socket;
}

bool Client::isConnected()
{
    return (this->socket->state() == QTcpSocket::ConnectedState);
}
