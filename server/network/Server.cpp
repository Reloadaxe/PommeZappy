#include "Server.h"

Server* Server::instance = 0;

Server::Server(std::string listen_host, int listen_port, int max_clients, QObject *parent)
    : QTcpServer(parent)
{
    this->listen_host = QString::fromUtf8(listen_host.c_str());
    this->listen_port = listen_port;
    this->max_clients = max_clients;
}

Server* Server::getInstance(std::string listen_host, int listen_port, int max_clients)
{
    if (instance == 0)
        instance = new Server(listen_host, listen_port, max_clients, nullptr);
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
            || this->refuse_additional_clients) {
        socket_client->disconnect();
        qDebug() << "Refused client due to nb clients exceeded or game started "\
                 << socket_client->peerAddress().toString();
        return;
    }

    QString peer_name = QString::fromUtf8(get_uuid().c_str());
    Client client = Client(peer_name, socket_client);
    client.connected = true;
    qDebug() << "Client connected with address "\
             << socket_client->peerAddress().toString()\
             << " : ID " << peer_name << " was attributed";
    this->clients.insert(std::pair<QTcpSocket*, Client>(socket_client, client));

    connect(socket_client, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket_client, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

/**
 * @brief Server::readyRead
 * Handles incoming command
 */
void Server::readyRead()
{
    QTcpSocket *socket_client = (QTcpSocket*)sender();
    Client client = clients.find(socket_client)->second;

    if (client.getClientId() != NULL)
    {
        // Reading only first line
        QString line;
        QString command = "";
        bool first_line = true;
        // We need to go through this loop to make
        // sure we can answer.
        while(socket_client->canReadLine())
        {
            if (first_line) {
                line = QString::fromUtf8(socket_client->readLine()).trimmed();
                first_line = false;
            }
        }
        for (int c = 0; c < line.size(); c++)
            if (line[c] == '\n')
                break;
            else
                command += line[c];
        this->respondToCommand(&client, command);
        qDebug() << "Received command : " << command;
    } else {
        qDebug() << "ERROR: Can't find client associated with socket : " << socket_client->peerAddress().toString();
        return;
    }
}

/**
 * @brief Server::processCommand
 * Returns the value corresponding to the command and/or stacks it for the next game cycle
 *
 * "move" commands are pushed into the commands stack
 * "utilitarian" commands are not
 */
void Server::respondToCommand(Client* client, QString command)
{
    std::string response = get_response_ko(command.toStdString());
    std::string command_type = get_command_type(command.toStdString());
//    if (command_type.empty())
//        ; // TODO
//    else if(command_type == "move")
//        ; // TODO
//    else if(command_type == "utilitarian")
//        ; // TODO
    client->getSocket()->write(response.c_str());
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

std::vector<Client*> Server::getClients()
{
    std::vector<Client*> ptr_clients;
    std::map<QTcpSocket*, Client>::iterator it;
    for ( it = this->clients.begin(); it != this->clients.end(); it++ )
        ptr_clients.push_back(&it->second);
    return ptr_clients;
}
