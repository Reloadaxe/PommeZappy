#include "Cell.hh"

Cell::Cell(const unsigned int y, const unsigned int x) : _y(y), _x(x), _item(nullptr), _player(nullptr) {}

Item *Cell::GetItem(void) const
{
    return _item;
}

void Cell::RemoveItem(void)
{
    delete _item;
    _item = nullptr;
}

Player *Cell::GetPlayer(void) const
{
    return _player;
}

void Cell::RemovePlayer(void)
{
    _player = nullptr;
}

void Cell::SetPlayer(Player *player)
{
    _player = player;
}

void Cell::Show(void) const
{
    (void)_y;
    (void)_x;
    if (_item == nullptr) {
        // if (commandLine) write(empty cell char)
        // else DoNothing;
        return;
    }
    // if (commandLine) write(item->GetChar())
    // else showItem();
}
