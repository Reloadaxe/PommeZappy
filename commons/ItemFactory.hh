#ifndef _ITEM_FACTORY_HH
#define _ITEM_FACTORY_HH

#include <iostream>
#include "Item.hh"
#include "Deraumere.hh"
#include "Linemate.hh"
#include "Mendiane.hh"
#include "Sibur.hh"

class ItemFactory {
    public:
        static Item *MakeItem(const std::string name);
};

#endif