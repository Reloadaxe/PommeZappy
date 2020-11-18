#include "Map.hh"

Map::Map(const int height, const int width) : _height(height), _width(width) {}

Map *Map::_map = nullptr;

Map *Map::Get(void)
{
    return _map == nullptr ? nullptr : _map;
}

Map *Map::Get(const int height, const int width)
{
    if (_map == nullptr) {
        _map = new Map(height, width);
    }
    return _map;
}

int Map::GetWidth(void) const
{
    return _width;
}

int Map::GetHeight(void) const
{
    return _height;
}

Cell *Map::GetCellAt(const int y, const int x) const
{
    return _cells.at(y).at(x);
}

std::vector<std::vector<Cell*>> Map::GetCells(void) const
{
    return _cells;
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

QString Map::GetPartContentAt(const int y, const int x) const
{
    if (y < 0 || y >= _height || x < 0 || x >= _width) {
        return "";
    }
    Cell *cell = GetCellAt(y, x);
    const Item *item = cell->GetItem();
    if (item != nullptr) {
        return (QChar)item->GetRepr();
    }
    const Client *client = cell->GetClient();
    if (client != nullptr) {
        return std::to_string(client->getPlayer()->GetId()).c_str();
    }
    return " ";
}

QJsonArray Map::GetPart(const Direction orientation, const int y, const int x) const
{
    QJsonArray part;

    switch (orientation) {
        case North:
            part.append(GetPartContentAt(y - 1, x - 1));
            part.append(GetPartContentAt(y - 1, x));
            part.append(GetPartContentAt(y - 1, x + 1));
            part.append(GetPartContentAt(y - 2, x));
            break;
        case East:
            part.append(GetPartContentAt(y - 1, x + 1));
            part.append(GetPartContentAt(y, x + 1));
            part.append(GetPartContentAt(y + 1, x + 1));
            part.append(GetPartContentAt(y, x + 2));
            break;
        case South:
            part.append(GetPartContentAt(y + 1, x + 1));
            part.append(GetPartContentAt(y + 1, x));
            part.append(GetPartContentAt(y + 1, x - 1));
            part.append(GetPartContentAt(y + 2, x));
            break;
        case West:
            part.append(GetPartContentAt(y + 1, x - 1));
            part.append(GetPartContentAt(y, x - 1));
            part.append(GetPartContentAt(y - 1, x - 1));
            part.append(GetPartContentAt(y, x - 2));
            break;
    }

    return part;
}
