#include "Map.hh"

Map::Map(void) {}
Map::Map(const unsigned int height, const unsigned int width), _height(height), _width(width) {}

Map *Map::_map = nullptr;

Map *Map::Get(void)
{
    if (_map == nullptr) {
        _map = new Map();
    }
    return _map;
}

Map *Map::Get(const unsigned int height, const unsigned int width)
{
    if (_map == nullptr) {
        _map = new Map(height, width);
    }
    return _map;
}

const unsigned int GetWidth(void) const
{
    return _width;
}

const unsigned int GetHeight(void) const
{
    return _height;
}

Cell *Map::GetCellAt(const unsigned int y, const unsigned int x) const
{
    return _cells.at(y).at(x);
}

void Map::Show(void) const
{
    for (std::vector<Cell*> cellsLine: _cells) {
        for (Cell *cell : cellsLine) {
            cell->Show();
        }
        // if (show in commandLine) {
        //     write('\n');
        // }
    }
}