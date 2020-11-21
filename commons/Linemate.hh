#ifndef _LINEMATE_HH
#define _LINEMATE_HH

#include "Item.hh"

class Linemate : public Item {
    public:
        Linemate(void);
        void DoAction(Player *player) const override;
};

#endif
