#include "Item.hh"

Item::Item(const char c) : _char(c) {}

char Item::GetChar(void)
{
    return _char;
}
