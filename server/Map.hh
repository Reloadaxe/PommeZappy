#ifndef _MAP_HH
#define _MAP_HH

#include <vector>
#include <QJsonArray>
#include "Client.h"
#include "Cell.hh"
#include "game_enums.hh"

class Cell;
class Map {
    public:
        Map(Map&) = delete;
        Map& operator=(Map&) = delete;
        int GetWidth(void) const;
        int GetHeight(void) const;
        Cell *GetCellAt(const int y, const int x) const;
        std::vector<std::vector<Cell*>> GetCells(void) const;
        void Show(void) const;
        Cell *GetRandomAvailableCell(void) const;
        QString GetPartContentAt(const int y, const int x) const;
        QJsonArray GetPart(const Direction orientation, const int y, const int x) const;
        static Map *Get(void);
        static Map *Get(const int height, const int width);

    private:
        Map(const int height, const int width);
        static Map *_map;
        const int _height;
        const int _width;
        std::vector<std::vector<Cell*>> _cells;
};

#endif
