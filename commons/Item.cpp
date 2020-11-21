#include "Item.hh"

Item::Item(const char c) : _char(c) {}

Item::~Item() {}

char Item::GetRepr(void) const
{
    return _char;
}
