#ifndef _NTW_CLIENT_H
#define _NTW_CLIENT_H

#include <iostream>
#include <vector>
#include <QTcpSocket>

/**
 * @brief The Client class
 * Class used to manage Client socket connections from the Server.
 * NOT INTENTED TO BE USED BY THE "CLIENT" PART OF THE Zappy PROJECT !!
 */
class Client
{

public:
    Client();
    ~Client();
    Client(QString client_id, QTcpSocket *socket);
    Client(std::string client_id, QTcpSocket *socket);

    // Player* player; // Client points to player

    void disconnect();                      // Drops the socket connection
    // void setPlayer(Player* player);
    // Player* getPlayer();
    void setClientId(QString client_id);
    QString getClientId();
    QTcpSocket* getSocket();
    bool addCommand(QString command);       // TODO : Adds next command to play, returns success state
    QString readCommand();                  // Unstacks and returns the oldest command
    bool isConnected();

private:
    QTcpSocket *socket = nullptr;
    QString client_id = NULL;               // generated by the server

    QString move_command;                   // next move command to play
    long last_game_cycle = -1;
};

#endif
