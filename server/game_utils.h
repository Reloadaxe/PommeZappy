#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <QtNetwork>
#include <vector>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

std::string get_command_type(std::string command);
std::string get_response_ko(std::string command);

bool are_players_dead();

#endif // GAME_UTILS_H
