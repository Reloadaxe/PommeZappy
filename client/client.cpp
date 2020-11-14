#include <iostream>
#include <sstream>
#include <exception>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "Player.hh"

void ShowUsage(void)
{
    std::cerr << "Usage :\n./client --host HOST --port PORT\n\nParameters :\nHOST : text\nPORT : number" << std::endl;
    exit(1);
}

void connect(int argc, char *argv[])
{
    std::string host = "";
    int16_t port = 0;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--host") {
            if (i + 1 < argc) {
                i++;
                host = std::string(argv[i]);
            } else {
                ShowUsage();
            }
        } else if (std::string(argv[i]) == "--port") {
            if (i + 1 < argc) {
                i++;
                std::istringstream iss(argv[i]);
                iss >> port;
            } else {
                ShowUsage();
            }
        } else {
            ShowUsage();
        }
    }

    if (host == "" || port == 0) {
        ShowUsage();
    }
    // connect to server and get player Id
}

const QJsonObject JsonFromString(const QString string)
{
    QJsonDocument doc = QJsonDocument::fromJson(string.toUtf8());
    return doc.object();
}

int main(int argc, char *argv[])
{
    connect(argc, argv);

    // Player *player = Player::Get();

    // Connection *connection = Connection::Get();
    // while (true) {
        // connection->Send("me");
        // const QJsonObject me = JsonFromString(connection->Read()).take("me");
        // if (me.take("energy") == 0)
        //     continue;
        // connection->Send("map");
        // const QJsonArray *map = JsonFromString(connection->Read()).take("map");

        //const std::vector<const QString> *commands = player->Think(map);

        // for (const QString command: &commands) {
        //     connection->Send(command);
        // }
    // }

    return 0;
}
