#include "parser_service.h"

std::map<std::string, std::string> init_parser(QCommandLineParser* parser, QCoreApplication *app) {
    parser->setApplicationDescription("Zappy server help");
    parser->addHelpOption();
    parser->addVersionOption();

    QCommandLineOption map_height_option{
                QStringList() << "map-height",
                QCoreApplication::translate("main", "Height of the map (default to 5)"),
                QCoreApplication::translate("main", "map-height"),
                "5"
                };
    parser->addOption(map_height_option);

    QCommandLineOption map_width_option{
                QStringList() << "map-width",
                QCoreApplication::translate("main", "Width of the map (default to 5)"),
                QCoreApplication::translate("main", "map-width"),
                "5"
                };
    parser->addOption(map_width_option);

    QCommandLineOption host_option{
                QStringList() << "host",
                QCoreApplication::translate("main", "Listening host IP address (default to 127.0.0.1)"),
                QCoreApplication::translate("main", "host"),
                "127.0.0.1"
                };
    parser->addOption(host_option);

    QCommandLineOption port_option{
                QStringList() << "port",
                QCoreApplication::translate("main", "Listening port (default to 4242)"),
                QCoreApplication::translate("main", "port"),
                "4242"
                };
    parser->addOption(port_option);

    QCommandLineOption nb_players_option{
                QStringList() << "players",
                QCoreApplication::translate("main", "Number of players on the game (default de 4 players)"),
                QCoreApplication::translate("main", "players"),
                "4"
                };
    parser->addOption(nb_players_option);

    QCommandLineOption cycle_interval_option{
                QStringList() << "cycle",
                QCoreApplication::translate("main", "Determines the interval of a game cycle, in milliseconds (default to 500ms)"),
                QCoreApplication::translate("main", "cycle"),
                "500"
                };
    parser->addOption(cycle_interval_option);

    // Process the actual command line arguments given by the user
    parser->process(*app);

    return std::map<std::string, std::string> {
        { "map_height", parser->value(map_height_option).toStdString()},
        { "map_width", parser->value(map_width_option).toStdString()},
        { "host", parser->value(host_option).toStdString()},
        { "port", parser->value(port_option).toStdString()},
        { "nb_players", parser->value(nb_players_option).toStdString()},
        { "cycle_interval", parser->value(cycle_interval_option).toStdString()}
     };
}
