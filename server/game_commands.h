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

typedef QString (*cmd_rgtr_func_ptr)(Client*);
typedef void (*cmd_prfm_func_ptr)(Client*);

cmd_rgtr_func_ptr get_rgtr_command_fnc(std::string command);
cmd_prfm_func_ptr get_prfm_command_fnc(std::string command);

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

void cmd_perform(Client* client);
void cmd_perform_left(Client* client);
void cmd_perform_right(Client* client);
void cmd_perform_fwd(Client* client);
void cmd_perform_leftfwd(Client* client);
void cmd_perform_rightfwd(Client* client);
void cmd_perform_jump(Client* client);
void cmd_perform_back(Client* client);
void cmd_perform_inspect(Client* client);

#endif // GAME_COMMANDS_H
