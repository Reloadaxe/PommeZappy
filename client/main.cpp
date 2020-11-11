#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <time.h>
#include "Player.hh"
#include "Map.hh"
#include "Connection.hh"

void Quit(sf::RenderWindow *window)
{
    // TODO close connection to server
    window->close();
}

void ShowUsage(void)
{
    std::cerr << "Usage :\n./client --host HOST --port PORT\n\nParameters :\nHOST : text\nPORT : number" << std::endl;
}

int main(int argc, char *argv[])
{
    std::string host = "";
    int16_t port = 0;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--host") {
            if (i + 1 < argc) {
                i++;
                host = std::string(argv[i]);
            } else {
                ShowUsage();
                return 1;
            }
        } else if (std::string(argv[i]) == "--port") {
            if (i + 1 < argc) {
                i++;
                std::istringstream iss(argv[i]);
                iss >> port;
            } else {
                ShowUsage();
                return 1;
            }
        } else {
            ShowUsage();
            return 1;
        }
    }

    if (host == "" || port == 0) {
        ShowUsage();
        return 1;
    }

    const unsigned int width = sf::VideoMode::getDesktopMode().width;
    const unsigned int height = sf::VideoMode::getDesktopMode().height;
    // const unsigned int hudHeight = height / 6;
    // const unsigned int cellNumberX = 10;
    // const unsigned int cellNumberY = 10;

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(width, height), "Zappy", sf::Style::Fullscreen);

    Player *player = Player::Get();

    Connection *connection = new Connection(host, port);

    while (window->isOpen())
    {
        // Event management
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Quit(window);
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    Quit(window);
            }
        }

        connection->Send("map");
        const std::string map = connection->Read();

        const std::string command = player->Think(map);

        connection->Send(command);
        const std::string success = connection->Read();

        std::cout << success << std::endl;

        // Map show
        // window->clear();
        // showMap(window, cellNumberX, cellNumberY, width / cellNumberX, (height - hudHeight) / cellNumberY);
        // player->showInformations(window, width, height, hudHeight);
        // window->display();
    }

    return 0;
}