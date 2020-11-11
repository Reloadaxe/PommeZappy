#include "Item.hh"

Item::Item(const char c) : _char(c) {}

const char Item::GetChar(void) const
{
    return _char;
}