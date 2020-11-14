#include "server.h"

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
    std::cout\
            << "Listening on " << host << ", port " << port << "\n"\
            << "Handling " << nb_players << " players\n"\
            << "On a map of width " << map_width << " and height " << map_height << "\n"\
            << "Cycling map every " << cycle_interval << " ms\n";

    // Initiating server
    std::vector<std::_Any_data> clients;
}
