#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <QtNetwork>
#include <vector>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

#include "Client.h"
#include "Player.hh"
#include "Map.hh"
#include "Cell.hh"

std::vector<Player*> get_init_players(Map* map, int nb_players);

void associate_players_to_clients(Map *map, std::vector<Player*> players, std::vector<Client*> clients);
void associate_map_to_clients(Map* map, std::vector<Client*> clients);

#endif // GAME_UTILS_H
