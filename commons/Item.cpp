#include "Item.hh"

Item::Item(const char c) : _char(c) {}

Item::~Item() {}

char Item::GetChar(void)
{
    return _char;
}
