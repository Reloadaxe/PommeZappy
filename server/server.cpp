#include "server.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("zappy");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Zappy server help");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption map_height_option{
                QStringList() << "map-height",
                QCoreApplication::translate("main", "Height of the map (default to 5)"),
                QCoreApplication::translate("main", "map-height"),
                "5"
                };
    parser.addOption(map_height_option);

    QCommandLineOption map_width_option{
                QStringList() << "map-width",
                QCoreApplication::translate("main", "Width of the map (default to 5)"),
                QCoreApplication::translate("main", "map-width"),
                "5"
                };
    parser.addOption(map_width_option);

    QCommandLineOption host_option{
                QStringList() << "host",
                QCoreApplication::translate("main", "Listening host IP address (default to 127.0.0.1)"),
                QCoreApplication::translate("main", "host"),
                "127.0.0.1"
                };
    parser.addOption(host_option);

    QCommandLineOption port_option{
                QStringList() << "port",
                QCoreApplication::translate("main", "Listening port (default to 4242)"),
                QCoreApplication::translate("main", "port"),
                "4242"
                };
    parser.addOption(port_option);

    QCommandLineOption nb_players_option{
                QStringList() << "players",
                QCoreApplication::translate("main", "Number of players on the game (default de 4 players)"),
                QCoreApplication::translate("main", "players"),
                "4"
                };
    parser.addOption(nb_players_option);

    QCommandLineOption cycle_interval_option{
                QStringList() << "cycle",
                QCoreApplication::translate("main", "Determines the interval of a game cycle, in milliseconds (default to 500ms)"),
                QCoreApplication::translate("main", "cycle"),
                "500"
                };
    parser.addOption(cycle_interval_option);

    // Process the actual command line arguments given by the user
    parser.process(app);

    QString map_height_value = parser.value(map_height_option);
    QString map_width_value = parser.value(map_width_option);
    QString host_value = parser.value(host_option);
    QString port_value = parser.value(port_option);
    QString nb_players_value = parser.value(nb_players_option);
    QString cycle_interval_value = parser.value(cycle_interval_option);

    int map_height = convert_assert_str_int(map_height_value.toStdString(), "map_height", 2);
    int map_width = convert_assert_str_int(map_width_value.toStdString(), "map_width", 2);
    int port = convert_assert_str_int(port_value.toStdString(), "port", 1024, 100000);
    int nb_players = convert_assert_str_int(nb_players_value.toStdString(), "nb_players", 1, 1000);
    int cycle_interval = convert_assert_str_int(cycle_interval_value.toStdString(), "cycle", 1, 60000);
    std::string host = host_value.toStdString();
    assert_ip(host, "host");

    std::cout\
            << "Listening on " << host << ", port " << port << "\n"\
            << "Handling " << nb_players << " players\n"\
            << "On a map of width " << map_width << " and height " << map_height << "\n"\
            << "Cycling map every " << cycle_interval << " ms\n";
}
