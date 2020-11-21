#include <iostream>
#include <sstream>
#include <exception>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "Player.hh"
#include "Network.hh"

void ShowUsage(void)
{
    std::cerr << "Usage :\n./client --host HOST --port PORT\n\nParameters :\nHOST : text\nPORT : number" << std::endl;
    exit(1);
}

void connect(int argc, char *argv[])
{
    QString host = "";
    int16_t port = 0;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--host") {
            if (i + 1 < argc) {
                i++;
                host = argv[i];
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
    Network *network = Network::Get();
    network->Connect(host, port);
}

QJsonObject JsonFromString(const QString string)
{
    QJsonDocument doc = QJsonDocument::fromJson(string.toUtf8());
    return doc.object();
}

int main(int argc, char *argv[])
{
    connect(argc, argv);

    Player *player = Player::Get();

    Network *network = Network::Get();
    network->Read();
    while (true) {
        network->Send("me");
        QJsonObject me = JsonFromString(network->Read()).value("me").toObject();
        if (me.value("energy").toInt() == 0)
            continue;
        network->Send("map");
        QJsonArray map = JsonFromString(network->Read()).value("map").toArray();

        std::vector<QString> *commands = player->Think(&map);

        for (QString command: *commands) {
            network->Send(command);
        }
    }

    return 0;
}
