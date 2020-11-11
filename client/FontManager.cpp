#include "FontManager.hh"

sf::Font *FontManager::_defaultFont;

sf::Font *FontManager::GetDefaultFont(void)
{
    if (_defaultFont == nullptr) {
        _defaultFont = new sf::Font();
        if (!_defaultFont->loadFromFile("Assets/arial.ttf"))
            std::cerr << "Unable to load font" << std::endl;
    }

    return _defaultFont;
}

unsigned int FontManager::_defaultFontSize = 40;

unsigned int FontManager::GetDefaultFontSize(void)
{
    return _defaultFontSize;
}