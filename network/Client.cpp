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

void Client::setClientId(QString client_id)
{
    this->client_id = client_id;
}

QString Client::getClientId()
{
    return this->client_id;
}

QString readCommand()
{
    QString command = this->commands_stack;
}
