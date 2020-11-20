#include "ClientThread.h"
#include "game_commands.h"

ClientThread::ClientThread(int socketDescriptor, Client* client, QObject *parent)
: QThread(parent), socketDescriptor(socketDescriptor), client(client)
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

    this->socket = &client_socket;
    client->setSocket(&client_socket);
    std::cout << "Client connected with address "\
             << client_socket.peerAddress().toString().toStdString()\
             << " : ID " << client->getClientId().toStdString() << " was attributed" << std::endl;
    connect(&client_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

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
            std::cout << "Received command : " << command.toStdString() << std::endl;
            this->respondToCommand(client, command);
        }
    }
}

void ClientThread::disconnected()
{
    std::cout << "Client disconnected : " << client->getClientId().toStdString() << std::endl;
}

void ClientThread::respondToCommand(Client* client, QString command)
{
    std::string response = cmd_perform(client, command.toStdString()).toStdString();
    std::cout << "Responding : " << response << std::endl;
    client->getSocket()->write(response.c_str());
}
