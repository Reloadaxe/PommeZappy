#include "Server.h"
#include "ClientThread.h"
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

Server* Server::getInstance(std::string listen_host, int listen_port, int max_clients, QObject *parent)
{
    if (instance == 0)
        instance = new Server(listen_host, listen_port, max_clients, parent);
    return instance;
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
    std::cout << "Server started." << std::endl;
}

void Server::stop(void)
{
    std::cout << "Server stopped." << std::endl;
    close();
}

void Server::refuseAdditionalClients()
{
    this->refuse_additional_clients = true;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    if (static_cast<int>(this->clients.size()) >= max_clients
            || this->refuse_additional_clients) {
        QTcpSocket *socket_client = new QTcpSocket(0);
        socket_client->write("Refused connection due to nb clients exceeded or game started ");
        socket_client->disconnectFromHost();
        std::cout << "Server is full or game started <> "\
                 << socket_client->peerAddress().toString().toStdString() << std::endl;
        return;
    }

    ClientThread* thread = new ClientThread(socketDescriptor, this);
    connect(thread, &ClientThread::finished, thread, &ClientThread::deleteLater);
    thread->start();
}

std::vector<Client*> Server::getClients()
{
    return clients;
}

bool Server::areAllClientsDisconnected()
{
    bool all_clients_disconnected = true;
    for (size_t i = 0; i < clients.size(); i++) {
        //std::cout << "Client " << i << " is " << clients[i]->isConnected() << std::endl;
        if (clients[i]->isConnected())
            return false;
    }
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
    for (size_t i = 0; i < clients.size(); i++)
        clients[i]->getPlayer()->ResetEnergy();

    const std::vector<Cell *> availableCells = getAvailableCells(map);
    if ((int)availableCells.size() <= 0)
        return;
    unsigned int cellIndex = rand() % (int)availableCells.size();

    const std::string availableItems[4] = {"Deraumere", "Linemate", "Mendiane", "Sibur"};
    Item *item = ItemFactory::MakeItem(availableItems[rand() % 4]);

    availableCells.at(cellIndex)->SetItem(item);
}
