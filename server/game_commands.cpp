#include "game_commands.h"
#include "server_utils.h"

// cmd_register_* pour enregistrer la commande dans le joueur et
//                  retourner la réponse serveur en fonction de si
//                  la commande est réalisable.
// cmd_perform    pour effectuer lors du game cycle la commande enregistrée

std::map<std::string, cmd_func_ptr> COMMANDS {
    {"left", &cmd_register_left},
    {"right", &cmd_register_right},
    {"fwd", &cmd_register_fwd},
    {"leftfwd", &cmd_register_leftfwd},
    {"rightfwd", &cmd_register_rightfwd},
    {"jump", &cmd_register_jump},
    {"back", &cmd_register_back},
    {"inspect", &cmd_register_inspect},
    {"map", &cmd_register_map},
    {"me", &cmd_register_me}
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

cmd_func_ptr get_command_fnc(std::string command)
{
    std::map<std::string, cmd_func_ptr>::const_iterator pos = COMMANDS.find(command);
    if (pos == COMMANDS.end())
        return pos->second;
    return nullptr;
}


/**
 * @brief cmd_register
 * Returns the value corresponding to the command and stores it in case of a "move" command.
 * @param client
 * @param command
 * @return
 */
QString cmd_register(Client* client, std::string command)
{
    // Check if player already has already played for this cycle
    if (client->getCommand().isEmpty())
    {
        if (MOVE_COMMAND_NAMES.find(command) != MOVE_COMMAND_NAMES.end())
            client->setCommand(QString::fromUtf8(command.c_str()));
        cmd_func_ptr command_fnc = get_command_fnc(command);
        // If function exist for this command, return its result
        if (command_fnc != nullptr)
            return command_fnc(client);
    }
    return QString::fromUtf8(get_response_ko(command).c_str());
}

QString cmd_register_left(Client* client)
{
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Register command

    // Return answer
    return "";
}

QString cmd_register_right(Client* client)
{
    client->getMap();
    client->getPlayer();
    return "";
}

QString cmd_register_fwd(Client* client)
{
    client->getMap();
    client->getPlayer();
    return "";
}

QString cmd_register_leftfwd(Client* client)
{
    client->getMap();
    client->getPlayer();
    return "";
}

QString cmd_register_rightfwd(Client* client)
{
    client->getMap();
    client->getPlayer();
    return "";
}

QString cmd_register_jump(Client* client)
{
    client->getMap();
    client->getPlayer();
    return "";
}

QString cmd_register_back(Client* client)
{
    client->getMap();
    client->getPlayer();
    return "";
}

QString cmd_register_inspect(Client* client)
{
    client->getMap();
    client->getPlayer();
    return "";
}

QString cmd_register_map(Client* client)
{
    client->getMap();
    client->getPlayer();
    return "";
}

QString cmd_register_me(Client* client)
{
    client->getMap();
    client->getPlayer();
    return "";
}


QString cmd_perform(Client* client)
{

    // Deal with effects (energy, attack
    client->getMap();
    client->getPlayer();
    return "";
}


