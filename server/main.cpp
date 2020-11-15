#include <chrono>
#include <string>
#include <iostream>

#include "main.h"
#include "Server.h"
#include "Map.hh"
#include "game_utils.h"

void clear_screen()
{
    int clear = 50;
    do {
        std::cout << std::endl;
        clear -= 1;
    } while (clear !=0);
}

uint64_t timeSinceEpochMillisec()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("zappy");
    QCoreApplication::setApplicationVersion("0.1");

    // Parsing and asserting CLI arguments
    QCommandLineParser parser;
    std::map<std::string, std::string> options = init_parser(&parser, &app);
    int map_height = convert_assert_str_int(options.find("map_height")->second, "map_height", 2);
    int map_width = convert_assert_str_int(options.find("map_width")->second, "map_width", 2);
    int port = convert_assert_str_int(options.find("port")->second, "port", 1024, 100000);
    int nb_players = convert_assert_str_int(options.find("nb_players")->second, "nb_players", 1, 1000);
    int cycle_interval = convert_assert_str_int(options.find("cycle_interval")->second, "cycle", 1, 60000);
    std::string host = options.find("host")->second;
    assert_ip(host, "host");

    // Printing summary
    std::cout
        << "Server will listen on " << host << ", port " << port << "\n"
        << "Handling " << nb_players << " players\n"
        << "On a map of width " << map_width << " and height " << map_height << "\n"
        << "Cycling map every " << cycle_interval << " ms\n"
        << std::endl;

    // Initializing game elements
    Map *map = Map::Get(map_height, map_width);
    std::vector<Player*> players = get_init_players(map, nb_players);
    long current_game_cycle = 0;
    uint64_t last_cycle_time = 0;

    // Initializing server
    Server *server = Server::getInstance(host, port, nb_players);
    std::cout << "Starting server..." << std::endl;
    server->start();
    std::cout << "Waiting for " << nb_players << " players to join..." << std::endl;
    while (static_cast<int>(server->getClients().size()) < nb_players);
    server->refuseAdditionalClients();
    std::cout << "Perfect, " << nb_players << " joined !" << std::endl;
    std::cout << "Initializating game players..." << std::endl;
    associate_players_to_clients(players, server->getClients());
    associate_map_to_clients(map, server->getClients());
    std::cout << "Starting the game..." << std::endl;

    // Periodically checking if :
    // - all players are disconnected (DONE)
    // - all players are dead (TODO)
    // - one player is left alive (TODO)
    while (server->areAllClientsDisconnected() == false)
    {
        uint64_t current_time = timeSinceEpochMillisec();
        if (current_time - last_cycle_time >= (ulong)cycle_interval)
        {
            clear_screen();
            server->performGameCycle(map);
            map->Show();
            current_game_cycle += 1;
            last_cycle_time = current_time;
            std::cout << "Currently running game cycle " << current_game_cycle << "..." << std::endl;
        }
    }

    // TODO : Game ended, displaying leaderboard
    std::cout << "Thank you for playing, game ended!" << std::endl;
    server->stop();
}
