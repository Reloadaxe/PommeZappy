#ifndef _CELL_HH
#define _CELL_HH

#include "Item.hh"
#include "Client.h"

class Client;
class Item;
class Cell {
    public:
        Cell(const unsigned int y, const unsigned int x);
        void SetItem(Item *item);
        Item *GetItem(void) const;
        void RemoveItem(void);
        Client *GetClient(void) const;
        void RemoveClient(void);
        void SetClient(Client *client);
        unsigned int GetY(void) const;
        unsigned int GetX(void) const;
        void Show(void) const;

    private:
        const unsigned int _y;
        const unsigned int _x;
        Item *_item;
        Client *_client;
};

#endif
