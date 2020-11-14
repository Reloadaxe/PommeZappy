#include "game_utils.h"

std::vector<std::string> MOVE_COMMANDS{
    "left",
    "right",
    "fwd",
    "leftfwd",
    "rightfwd",
    "jump",
    "back",
    "inspect"
};

std::vector<std::string> UTILITARIAN_COMMANDS{
    "map",
    "me"
};

// TODO: pointeur sur fonction pour les commandes

/**
 * @brief get_command_type
 * Returns "move" or "utilitarian". Utilitarian commands don't require
 * any player energy verification in order to be returned by the server.
 * @param command
 * @return
 */
std::string get_command_type(std::string command)
{
    if (command.empty() || command.size() == 0)
        return "";
    if (std::find(MOVE_COMMANDS.begin(), MOVE_COMMANDS.end(), command) != MOVE_COMMANDS.end())
        return "move";
    if (std::find(UTILITARIAN_COMMANDS.begin(), UTILITARIAN_COMMANDS.end(), command) != UTILITARIAN_COMMANDS.end())
        return "utilitarian";
    return "";
}

std::string get_response_ko(std::string command)
{
    std::ostringstream stream;
    stream << "{\"" << command << "\": \"KO\"}";
    return stream.str();
}
