#include "ItemFactory.hh"

Item *ItemFactory::MakeItem(const std::string name)
{
    if (name == "Deraumere")
        return new Deraumere();
    if (name == "Linemate")
        return new Linemate();
    if (name == "Mendiane")
        return new Mendiane();
    if (name == "Sibur")
        return new Sibur();
    return nullptr;
}