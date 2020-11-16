#include "game_commands.h"
#include "server_utils.h"

std::map<std::string, cmd_func_ptr> REGISTER_COMMANDS {
    {"left", &cmd_perform_left},
    {"right", &cmd_perform_right},
    {"fwd", &cmd_perform_fwd},
    {"leftfwd", &cmd_perform_leftfwd},
    {"rightfwd", &cmd_perform_rightfwd},
    {"jump", &cmd_perform_jump},
    {"back", &cmd_perform_back},
    {"inspect", &cmd_perform_inspect},
    {"map", &cmd_perform_map},
    {"me", &cmd_perform_me}
};

std::set<std::string> MOVE_COMMAND_NAMES {
    "left",
    "right",
    "fwd",
    "leftwd",
    "rightfwd",
    "jump",
    "back",
    "inspect"
};

cmd_func_ptr get_rgtr_command_fnc(std::string command)
{
    std::map<std::string, cmd_func_ptr>::const_iterator pos = REGISTER_COMMANDS.find(command);
    if (pos == REGISTER_COMMANDS.end())
        return pos->second;
    return nullptr;
}


/*
 * ===============
 * REGISTER COMMANDS
 * ===============
 */

/**
 * @brief cmd_perform
 * Performs the command sent by the client if it has the necessary power.
 * @param client
 * @param command
 * @return
 */
QString cmd_perform(Client* client, std::string command)
{
    cmd_func_ptr command_fnc = get_rgtr_command_fnc(command);
    if (command_fnc != nullptr)
        return command_fnc(client);
    return QString::fromUtf8(get_response_ko(command).c_str());
}

QString cmd_perform_left(Client* client)
{
    const bool success = client->getPlayer()->DoCommand(Command::left, client->getMap());
    QJsonObject j;

    j.insert("left", success ? "OK" : "KO");
    QJsonDocument doc(j);

    return doc.toJson(QJsonDocument::Compact);
}

QString cmd_perform_right(Client* client)
{
    const bool success = client->getPlayer()->DoCommand(Command::right, client->getMap());
    QJsonObject j;

    j.insert("right", success ? "OK" : "KO");
    QJsonDocument doc(j);

    return doc.toJson(QJsonDocument::Compact);
}

QString cmd_perform_fwd(Client* client)
{
    const bool success = client->getPlayer()->DoCommand(Command::fwd, client->getMap());
    QJsonObject j;

    j.insert("fwd", success ? "OK" : "KO");
    QJsonDocument doc(j);

    return doc.toJson(QJsonDocument::Compact);
}

QString cmd_perform_leftfwd(Client* client)
{
    const bool success = client->getPlayer()->DoCommand(Command::leftfwd, client->getMap());
    QJsonObject j;

    j.insert("leftfwd", success ? "OK" : "KO");
    QJsonDocument doc(j);

    return doc.toJson(QJsonDocument::Compact);
}

QString cmd_perform_rightfwd(Client* client)
{
    const bool success = client->getPlayer()->DoCommand(Command::rightfwd, client->getMap());
    QJsonObject j;

    j.insert("rightfwd", success ? "OK" : "KO");
    QJsonDocument doc(j);

    return doc.toJson(QJsonDocument::Compact);
}

QString cmd_perform_jump(Client* client)
{
    const bool success = client->getPlayer()->DoCommand(Command::jump, client->getMap());
    QJsonObject j;

    j.insert("jump", success ? "OK" : "KO");
    QJsonDocument doc(j);

    return doc.toJson(QJsonDocument::Compact);
}

QString cmd_perform_back(Client* client)
{
    const bool success = client->getPlayer()->DoCommand(Command::back, client->getMap());
    QJsonObject j;

    j.insert("back", success ? "OK" : "KO");
    QJsonDocument doc(j);

    return doc.toJson(QJsonDocument::Compact);
}

QString cmd_perform_inspect(Client* client)
{
    std::vector<Client*> clients = Server::getInstance()->getClients();
    QJsonObject j;

    QJsonArray playersInformations;
    for (Client *client : clients) {
        const Player *player = client->getPlayer();
        playersInformations.append(player->getInformations(player->GetId(), false));
    }

    j.insert("inspect", playersInformations);
    QJsonDocument doc(j);

    client->getPlayer()->RemoveEnergy();

    return doc.toJson(QJsonDocument::Compact);
}

QString cmd_perform_map(Client* client)
{
    const Player *player = client->getPlayer();
    QJsonArray mapPart = client->getMap()->GetPart(player->GetOrientation(), player->GetY(), player->GetX());
    QJsonObject j;

    j.insert("map", mapPart);
    QJsonDocument doc(j);

    return doc.toJson(QJsonDocument::Compact);
}

QString cmd_perform_me(Client* client)
{
    const Player *player = client->getPlayer();
    QJsonObject j;

    j.insert("me", player->getInformations(player->GetId()));
    QJsonDocument doc(j);

    return doc.toJson(QJsonDocument::Compact);
}
