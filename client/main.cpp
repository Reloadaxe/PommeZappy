#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "Player.hh"
#include "Map.hh"

int main(void)
{
    
    const unsigned int width = sf::VideoMode::getDesktopMode().width;
    const unsigned int height = sf::VideoMode::getDesktopMode().height;
    const unsigned int hudHeight = height / 6;
    const unsigned int cellNumberX = 10;
    const unsigned int cellNumberY = 10;

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(width, height), "Zappy", sf::Style::Fullscreen);

    Player *player = Player::Get();

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window->close();
            }
        }
        window->clear();

        showMap(window, cellNumberX, cellNumberY, width / cellNumberX, (height - hudHeight) / cellNumberY);
        player->showInformations(window, width, height, hudHeight);

        window->display();
    }

    return 0;
}