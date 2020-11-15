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
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Make the player move on map
    // Return answer
    return "{}";
}

QString cmd_perform_right(Client* client)
{
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Return answer
    return "{}";
}

QString cmd_perform_fwd(Client* client)
{
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Return answer
    return "{}";
}

QString cmd_perform_leftfwd(Client* client)
{
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Return answer
    return "{}";
}

QString cmd_perform_rightfwd(Client* client)
{
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Return answer
    return "{}";
}

QString cmd_perform_jump(Client* client)
{
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Return answer
    return "{}";
}

QString cmd_perform_back(Client* client)
{
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Return answer
    return "{}";
}

QString cmd_perform_inspect(Client* client)
{
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Return answer
    return "{}";
}

QString cmd_perform_map(Client* client)
{
    // Return "map" details
    client->getMap();
    return "{}";
}

QString cmd_perform_me(Client* client)
{
    // Return "me" details
    client->getClientId();
    client->getPlayer();
    return "{}";
}
