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

cmd_func_ptr get_rgtr_command_fnc(std::string command);

QString cmd_perform(Client* client, std::string command);
QString cmd_perform_left(Client* client);
QString cmd_perform_right(Client* client);
QString cmd_perform_fwd(Client* client);
QString cmd_perform_leftfwd(Client* client);
QString cmd_perform_rightfwd(Client* client);
QString cmd_perform_jump(Client* client);
QString cmd_perform_back(Client* client);
QString cmd_perform_inspect(Client* client);
QString cmd_perform_map(Client* client);
QString cmd_perform_me(Client* client);

#endif // GAME_COMMANDS_H
