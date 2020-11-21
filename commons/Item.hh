#ifndef _ITEM_HH
#define _ITEM_HH

#include "../server/Player.hh"

class Player;
class Item {
    public:
        Item(const char c);
        virtual ~Item();
        virtual void DoAction(Player *player) const = 0;
        char GetRepr(void) const;

    private:
        char _char;
};

#endif
