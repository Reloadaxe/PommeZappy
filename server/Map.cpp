#include "Map.hh"

Map::Map(void) {}
Map::Map(unsigned int height, unsigned int width) : _height(height), _width(width) {}

Map *Map::_map = nullptr;

Map *Map::Get(void)
{
    if (_map == nullptr) {
        _map = new Map();
    }
    return _map;
}

Map *Map::Get(unsigned int height, unsigned int width)
{
    if (_map == nullptr) {
        _map = new Map(height, width);
    }
    return _map;
}

unsigned int Map::GetWidth(void)
{
    return _width;
}

unsigned int Map::GetHeight(void)
{
    return _height;
}

Cell *Map::GetCellAt(unsigned int y, unsigned int x)
{
    return _cells.at(y).at(x);
}

void Map::Show(void)
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
