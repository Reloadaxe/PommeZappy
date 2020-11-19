#include "Server.h"
#include "server_utils.h"
#include "game_commands.h"

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

Server* Server::getInstance(void)
{
    return instance;
}

void Server::start(void)
{
    QHostAddress address;
    address.setAddress(this->listen_host);
    listen(address, (qint16)this->listen_port);
}

void Server::stop(void)
{
    close();
}

void Server::refuseAdditionalClients()
{
    this->refuse_additional_clients = true;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket_client = new QTcpSocket(this);
    socket_client->setSocketDescriptor(socketDescriptor);

    if (static_cast<int>(this->clients.size()) >= max_clients
            || this->refuse_additional_clients) {
        socket_client->disconnect();
        qDebug() << "Refused connection due to nb clients exceeded or game started "\
                 << socket_client->peerAddress().toString();
        return;
    }

    QString peer_name = QString::fromUtf8(get_uuid().c_str());
    Client client = Client(peer_name, socket_client);
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
    std::cout << "reading" << std::endl;
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

bool Server::areAllClientsDisconnected()
{
    bool all_clients_disconnected = true;
    std::map<QTcpSocket*, Client>::iterator it;
    for ( it = this->clients.begin(); it != this->clients.end(); it++ )
        if (it->second.isConnected())
            return false;
    return all_clients_disconnected;
}

void Server::respondToCommand(Client* client, QString command)
{
    client->getSocket()->write(
        cmd_perform(client, command.toStdString()).toStdString().c_str()
    );
}

std::vector<Cell *> getAvailableCells(const Map *map)
{
    std::vector<Cell *> availableCells;

    for (std::vector<Cell *> cellsLine : map->GetCells())
        for (Cell *cell : cellsLine)
            if (cell->GetClient() == nullptr && cell->GetItem() == nullptr)
                availableCells.push_back(cell);

    return availableCells;
}

/**
 * @brief performGameCycle
 * This function is called each cycle to reinitialize the energy
 * of players to 2.
 */
void Server::performGameCycle(Map* map)
{
    srand(time(NULL));
    std::map<QTcpSocket*, Client>::iterator it;
    for (it = this->clients.begin(); it != this->clients.end(); it++)
        it->second.getPlayer()->ResetEnergy();

    const std::vector<Cell *> availableCells = getAvailableCells(map);
    if ((int)availableCells.size() <= 0)
        return;
    unsigned int cellIndex = rand() % (int)availableCells.size();

    const std::string availableItems[4] = {"Deraumere", "Linemate", "Mendiane", "Sibur"};
    Item *item = ItemFactory::MakeItem(availableItems[rand() % 4]);

    availableCells.at(cellIndex)->SetItem(item);
}
