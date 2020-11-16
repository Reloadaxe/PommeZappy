#include "Map.hh"

Map::Map(const unsigned int height, const unsigned int width) : _height(height), _width(width) {}

Map *Map::_map = nullptr;

Map *Map::Get(void)
{
    return _map == nullptr ? nullptr : _map;
}

Map *Map::Get(const unsigned int height, const unsigned int width)
{
    if (_map == nullptr) {
        _map = new Map(height, width);
    }
    return _map;
}

unsigned int Map::GetWidth(void) const
{
    return _width;
}

unsigned int Map::GetHeight(void) const
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

QString Map::GetPartContentAt(const unsigned int y, const unsigned int x) const
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

QJsonArray Map::GetPart(const Direction orientation, const unsigned int y, const unsigned int x) const
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
