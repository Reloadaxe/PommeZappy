#ifndef _MAP_HH
#define _MAP_HH

#include <vector>
#include "Cell.hh"

class Map {
    public:
        Map(const Map&) = delete;
        Map& operator=(const Map&) = delete;
        const unsigned int GetWidth(void) const;
        const unsigned int GetHeight(void) const;
        Cell *GetCellAt(const unsigned int y, const unsigned int x) const;
        void Show(void) const;
        static Map *Get(void);
        static Map *Get(const unsigned int height, const unsigned int width);

    private:
        Map(void);
        Map(const unsigned int height, const unsigned int width);
        static Map *_map;
        const unsigned int _height;
        const unsigned int _width;
        std::vector<std::vector<Cell*>> _cells;
};

#endif