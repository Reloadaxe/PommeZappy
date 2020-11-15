#include "game_commands.h"
#include "server_utils.h"

// cmd_register_* pour enregistrer la commande dans le joueur et
//                  retourner la réponse serveur en fonction de si
//                  la commande est réalisable.
// cmd_perform    pour effectuer lors du game cycle la commande enregistrée

std::map<std::string, cmd_rgtr_func_ptr> REGISTER_COMMANDS {
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

std::map<std::string, cmd_prfm_func_ptr> PERFORM_COMMANDS {
    {"left", &cmd_perform_left},
    {"right", &cmd_perform_right},
    {"fwd", &cmd_perform_fwd},
    {"leftfwd", &cmd_perform_leftfwd},
    {"rightfwd", &cmd_perform_rightfwd},
    {"jump", &cmd_perform_jump},
    {"back", &cmd_perform_back},
    {"inspect", &cmd_perform_inspect}
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

cmd_rgtr_func_ptr get_rgtr_command_fnc(std::string command)
{
    std::map<std::string, cmd_rgtr_func_ptr>::const_iterator pos = REGISTER_COMMANDS.find(command);
    if (pos == REGISTER_COMMANDS.end())
        return pos->second;
    return nullptr;
}

cmd_prfm_func_ptr get_prfm_command_fnc(std::string command)
{
    std::map<std::string, cmd_prfm_func_ptr>::const_iterator pos = PERFORM_COMMANDS.find(command);
    if (pos == PERFORM_COMMANDS.end())
        return pos->second;
    return nullptr;
}


/*
 * ===============
 * REGISTER COMMANDS
 * ===============
 */

/**
 * @brief cmd_register
 * Returns the value corresponding to the command and stores it in case of a "move" command.
 * @param client
 * @param command
 * @return
 */
QString cmd_register(Client* client, std::string command)
{
    cmd_rgtr_func_ptr command_fnc = get_rgtr_command_fnc(command);
    if (command_fnc != nullptr)
    {
        // Checking if command is a "move" one
        if (MOVE_COMMAND_NAMES.find(command) != MOVE_COMMAND_NAMES.end())
        {
            // If client has not already played for the next cycle,
            // store its command.
            if (client->getCommand().isEmpty())
            {
                client->setCommand(QString::fromUtf8(command.c_str()));
                return command_fnc(client);
            }
        } else {
            // Allow any non-move command
            return command_fnc(client);
        }
    }
    return QString::fromUtf8(get_response_ko(command).c_str());
}

QString cmd_register_left(Client* client)
{
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Return answer
    return "{}";
}

QString cmd_register_right(Client* client)
{
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Return answer
    return "{}";
}

QString cmd_register_fwd(Client* client)
{
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Return answer
    return "{}";
}

QString cmd_register_leftfwd(Client* client)
{
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Return answer
    return "{}";
}

QString cmd_register_rightfwd(Client* client)
{
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Return answer
    return "{}";
}

QString cmd_register_jump(Client* client)
{
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Return answer
    return "{}";
}

QString cmd_register_back(Client* client)
{
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Return answer
    return "{}";
}

QString cmd_register_inspect(Client* client)
{
    // Check if move is possible
    client->getMap();
    client->getPlayer();
    // Return answer
    return "{}";
}

QString cmd_register_map(Client* client)
{
    // Return "map" details
    client->getMap();
    return "{}";
}

QString cmd_register_me(Client* client)
{
    // Return "me" details
    client->getClientId();
    client->getPlayer();
    return "{}";
}


/*
 * ===============
 * PERFORM COMMANDS
 * ===============
 */

/**
 * @brief cmd_perform
 * Performs the player commands and update Map accordingly.
 * Reminder : Only move commands have been registered from here.
 * @param client
 */
void cmd_perform(Client* client)
{
    if (client->getCommand().isEmpty())
        return;
    // If function exist for this command, perform it
    cmd_prfm_func_ptr command_fnc = get_prfm_command_fnc(client->getCommand().toStdString());
    if (command_fnc != nullptr)
        return command_fnc(client);
}

void cmd_perform_left(Client* client)
{
    // If player move is possible, deal with
    // effects (energy, attack...).
    client->getMap();
    client->getPlayer();
}

void cmd_perform_right(Client* client)
{
    // If player move is possible, deal with
    // effects (energy, attack...).
    client->getMap();
    client->getPlayer();
}

void cmd_perform_fwd(Client* client)
{
    // If player move is possible, deal with
    // effects (energy, attack...).
    client->getMap();
    client->getPlayer();
}

void cmd_perform_leftfwd(Client* client)
{
    // If player move is possible, deal with
    // effects (energy, attack...).
    client->getMap();
    client->getPlayer();
}

void cmd_perform_rightfwd(Client* client)
{
    // If player move is possible, deal with
    // effects (energy, attack...).
    client->getMap();
    client->getPlayer();
}

void cmd_perform_jump(Client* client)
{
    // If player move is possible, deal with
    // effects (energy, attack...).
    client->getMap();
    client->getPlayer();
}

void cmd_perform_back(Client* client)
{
    // If player move is possible, deal with
    // effects (energy, attack...).
    client->getMap();
    client->getPlayer();
}

void cmd_perform_inspect(Client* client)
{
    // If player move is possible, deal with
    // effects (energy, attack...).
    client->getMap();
    client->getPlayer();
}
