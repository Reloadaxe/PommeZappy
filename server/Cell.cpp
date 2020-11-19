#include "Cell.hh"

Cell::Cell(const unsigned int y, const unsigned int x) : _y(y), _x(x), _item(nullptr), _client(nullptr) {}

void Cell::SetItem(Item *item)
{
    _item = item;
}

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
    (void)_y; // util with graphisms
    (void)_x; // util with graphisms
    if (_client != nullptr) {
        std::cout << _client->getPlayer()->GetId();
        return;
    }
    if (_item != nullptr) {
        std::cout << _item->GetRepr();
        return;
    }
    std::cout << " ";
}
