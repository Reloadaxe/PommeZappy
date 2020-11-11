#ifndef _PLAYER_HH
#define _PLAYER_HH

#include <SFML/Graphics.hpp>
#include <iostream>
#include "FontManager.hh"

class Player {
    public:
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;
        void showInformations(sf::RenderWindow *window, const unsigned int width, const unsigned int height, const unsigned int hudHeight);
        static Player *Get(void);

    private:
        Player(void);
        static Player *_player;
        unsigned int _energy;
        unsigned int _lifePoints;
        unsigned int _victoryPoints;
        unsigned int _orientation;
};

#endif