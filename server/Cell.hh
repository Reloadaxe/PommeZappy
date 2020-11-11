#ifndef _CELL_HH
#define _CELL_HH

#include "Item.hh"
#include "Player.hh"

class Cell {
    public:
        Cell(const unsigned int y, const unsigned int x);
        Item *GetItem(void) const;
        void RemoveItem(void);
        Player *GetPlayer(void) const;
        void RemovePlayer(void);
        void SetPlayer(Player *player);
        void Show(void);

    private:
        const unsigned int _y;
        const unsigned int _x;
        Item *_item;
        Player *_player;
};

#endif