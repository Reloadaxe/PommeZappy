#ifndef _FONT_MANAGER_HH
#define _FONT_MANAGER_HH

#include <SFML/Graphics/Font.hpp>
#include <iostream>

class FontManager {
    public:
        static sf::Font *GetDefaultFont(void);
        static unsigned int GetDefaultFontSize(void);

    private:
        static sf::Font *_defaultFont;
        static unsigned int _defaultFontSize;
};

#endif