#include "game_utils.h"

std::vector<Player*> get_init_players(Map* map, int nb_players)
{
    std::vector<Player*> players;
    for (int i = 0; i < nb_players; i++)
    {
        Cell *cell = map->GetRandomAvailableCell();
        players.push_back(new Player(cell->GetY(), cell->GetX())); // TODO : Spawn players in appropriate map locations
    }
    return players;
}

void associate_players_to_clients(Map* map, std::vector<Player*> players, std::vector<Client*> clients)
{
    for(std::size_t i = 0; i < clients.size(); i++)
    {
        clients[i]->setPlayer(players[i]);
        std::cout << players[i]->GetY() << " " << players[i]->GetX() << std::endl;
        map->GetCellAt(players[i]->GetY(), players[i]->GetX())->SetClient(clients[i]);
    }
}

void associate_map_to_clients(Map* map, std::vector<Client*> clients)
{
    for(std::size_t i = 0; i < clients.size(); i++)
        clients[i]->setMap(map);
}
