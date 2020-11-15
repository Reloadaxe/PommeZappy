#ifndef GAME_COMMANDS_H
#define GAME_COMMANDS_H

#include <QtNetwork>
#include <vector>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

#include "Client.h"
#include "Player.hh"
#include "Map.hh"

typedef QString (*cmd_func_ptr)(Client*);

cmd_func_ptr get_command_fnc(std::string command);

QString cmd_register(Client* client, std::string command);
QString cmd_register_left(Client* client);
QString cmd_register_right(Client* client);
QString cmd_register_fwd(Client* client);
QString cmd_register_leftfwd(Client* client);
QString cmd_register_rightfwd(Client* client);
QString cmd_register_jump(Client* client);
QString cmd_register_back(Client* client);
QString cmd_register_inspect(Client* client);
QString cmd_register_map(Client* client);
QString cmd_register_me(Client* client);

QString cmd_perform(Client* client);

#endif // GAME_COMMANDS_H
