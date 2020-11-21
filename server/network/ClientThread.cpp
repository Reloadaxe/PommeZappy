#include "ClientThread.h"
#include "server_utils.h"
#include "game_commands.h"

ClientThread::ClientThread(int socketDescriptor, QObject *parent)
: QThread(parent), socketDescriptor(socketDescriptor)
{

}

/**
 * @brief Server::run
 * Handles client potential incoming command
 */
void ClientThread::run()
{
    QTcpSocket client_socket;
    if (!client_socket.setSocketDescriptor(socketDescriptor)) {
        emit error(client_socket.error());
        return;
    }

    client_socket.waitForConnected();

    Server* server = Server::getInstance();
    QString peer_name = QString::fromUtf8(get_uuid().c_str());
    client = new Client(peer_name);

    this->socket = &client_socket;
    client->setSocket(&client_socket);
    server->clients.push_back(client);
    std::cout << "Client connected with address "\
             << client_socket.peerAddress().toString().toStdString()\
             << " : ID " << client->getClientId().toStdString() << " was attributed" << std::endl;
    connect(&client_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    while(game_started == nullptr || *game_started == false)
    {
        client_socket.waitForReadyRead(1);
        if (client_socket.state() == QTcpSocket::UnconnectedState)
            return;
    }
    if (client_socket.state() == QTcpSocket::UnconnectedState)
        return;
    client_socket.write("go\n");
    client_socket.waitForBytesWritten();
    std::cout << "Sent 'go' to "
              << client->getClientId().toStdString()
              << std::endl;

    while(true)
    {
        client_socket.waitForReadyRead();
        // Reading only first line
        QString line;
        QString command = "";
        bool first_line = true;
        // We need to go through this loop to make
        // sure we can answer.
        while(client_socket.canReadLine())
        {
            if (first_line) {
                line = QString::fromUtf8(client_socket.readLine()).trimmed();
                first_line = false;
                break;
            }
        }
        for (int c = 0; c < line.size(); c++)
            if (line[c] == '\n')
                break;
            else
                command += line[c];
        if (command.size() > 0) {
            //std::cout << "Received command : " << command.toStdString() << std::endl;
            this->respondToCommand(client, command);
        }
    }
}

void ClientThread::disconnected()
{
    client->setSocket(nullptr);
    if (client->getPlayer() != nullptr)
        client->getPlayer()->SetIsDead(true);
    std::cout << "Client disconnected : " << client->getClientId().toStdString() << std::endl;
}

void ClientThread::respondToCommand(Client* client, QString command)
{
    std::string response = cmd_perform(client, command.toStdString()).toStdString();
    //std::cout << "Responding : " << response << std::endl;
    client->getSocket()->write((response + "\n").c_str());
    client->getSocket()->waitForBytesWritten();
}
