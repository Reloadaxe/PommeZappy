#ifndef _CELL_HH
#define _CELL_HH

#include "Item.hh"
#include "Player.hh"

class Cell {
    public:
        Cell(unsigned int y, unsigned int x);
        Item *GetItem(void);
        void RemoveItem(void);
        Player *GetPlayer(void);
        void RemovePlayer(void);
        void SetPlayer(Player *player);
        void Show(void);

    private:
        unsigned int _y;
        unsigned int _x;
        Item *_item;
        Player *_player;
};

#endif
