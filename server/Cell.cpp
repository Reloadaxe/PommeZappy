#include "Cell.hh"

Cell::Cell(const unsigned int y, const unsigned int x) : _y(y), _x(x), _item(nullptr), _client(nullptr) {}

Item *Cell::GetItem(void) const
{
    return _item;
}

void Cell::RemoveItem(void)
{
    delete _item;
    _item = nullptr;
}

Client *Cell::GetClient(void) const
{
    return _client;
}

void Cell::RemoveClient(void)
{
    _client = nullptr;
}

void Cell::SetClient(Client *client)
{
    _client = client;
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
