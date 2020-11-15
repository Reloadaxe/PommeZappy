#ifndef _MAP_HH
#define _MAP_HH

#include <vector>
#include "Cell.hh"

class Map {
    public:
        Map(Map&) = delete;
        Map& operator=(Map&) = delete;
        unsigned int GetWidth(void);
        unsigned int GetHeight(void);
        Cell *GetCellAt(unsigned int y, unsigned int x);
        void Show(void);
        static Map *Get(void);
        static Map *Get(unsigned int height, unsigned int width);

    private:
        Map(void);
        Map(unsigned int height, unsigned int width);
        static Map *_map;
        unsigned int _height;
        unsigned int _width;
        std::vector<std::vector<Cell*>> _cells;
};

#endif
