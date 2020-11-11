#include "Player.hh"

Player::Player(void) : _energy(2), _lifePoints(10), _victoryPoints(0), _orientation(0) {}

void drawText(sf::RenderWindow *window, const sf::Vector2f position, const std::string message)
{
    sf::Text text(message, *FontManager::GetDefaultFont(), FontManager::GetDefaultFontSize());

    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    sf::Rect<float> rect = text.getLocalBounds();
    text.setPosition(position.x - rect.width / 2, position.y - rect.height / 2);

    window->draw(text);
}

void Player::showInformations(sf::RenderWindow *window, const unsigned int width, const unsigned int height, const unsigned int hudHeight)
{
    (void)_orientation;
    drawText(window, sf::Vector2f(width / 6, height - hudHeight / 2),
             "ENERGY : " + std::to_string(_energy));
    
    drawText(window, sf::Vector2f(width / 2, height - hudHeight / 2),
             "LIFE POINTS : " + std::to_string(_lifePoints));

    drawText(window, sf::Vector2f(width * 5 / 6, height - hudHeight / 2),
             "VICTORY POINTS : " + std::to_string(_victoryPoints));
}

Player *Player::_player = nullptr;

Player *Player::Get(void)
{
    if (_player == nullptr)
        _player = new Player();
    return _player;
}