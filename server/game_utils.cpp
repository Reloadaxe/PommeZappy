#include "game_utils.h"

std::vector<Player*> get_init_players(Map* map, int nb_players)
{
    map->GetWidth(); // To remove once following TODO is done (avoiding -Wunused)
    std::vector<Player*> players(nb_players);
    for (int i = 0; i < nb_players; i++)
    {
        players.push_back(new Player(0, 0)); // TODO : Spawn players in appropriate map locations
    }
    return players;
}

void associate_players_to_clients(std::vector<Player*> players, std::vector<Client*> clients)
{
    for(std::size_t i = 0; i < clients.size(); i++)
        clients[i]->setPlayer(players[i]);
}

void associate_map_to_clients(Map* map, std::vector<Client*> clients)
{
    for(std::size_t i = 0; i < clients.size(); i++)
        clients[i]->setMap(map);
}
