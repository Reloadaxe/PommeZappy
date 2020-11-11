#include "Map.hh"

void showMap(sf::RenderWindow *window, const unsigned int cellsNumberX, const unsigned int cellsNumberY,
             const unsigned int cellWidth, const unsigned int cellHeight)
{
    for (unsigned int y = 0; y < cellsNumberY; y++) {
        for (unsigned int x = 0; x < cellsNumberX; x++) {
            sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));

            cell.setFillColor(sf::Color::Green);
            cell.setOutlineColor(sf::Color::Black);
            cell.setOutlineThickness(5);
            cell.setPosition(cellWidth * x, cellHeight * y);

            window->draw(cell);
        }
    }
}