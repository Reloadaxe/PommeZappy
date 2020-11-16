#ifndef _MAP_HH
#define _MAP_HH

#include <vector>
#include <QJsonArray>
#include "Cell.hh"
#include "game_enums.hh"

class Cell;
class Map {
    public:
        Map(Map&) = delete;
        Map& operator=(Map&) = delete;
        unsigned int GetWidth(void) const;
        unsigned int GetHeight(void) const;
        Cell *GetCellAt(const unsigned int y, const unsigned int x) const;
        void Show(void) const;
        QString GetPartContentAt(const unsigned int y, const unsigned int x) const;
        QJsonArray GetPart(const Direction orientation, const unsigned int y, const unsigned int x) const;
        static Map *Get(void);
        static Map *Get(const unsigned int height, const unsigned int width);

    private:
        Map(const unsigned int height, const unsigned int width);
        static Map *_map;
        const unsigned int _height;
        const unsigned int _width;
        std::vector<std::vector<Cell*>> _cells;
};

#endif
