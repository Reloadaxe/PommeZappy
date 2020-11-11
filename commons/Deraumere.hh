#ifndef _DERAUMERE_HH
#define _DERAUMERE_HH

#include "Item.hh"

class Deraumere : public Item {
    public:
        Deraumere(void);
        void DoAction(void) const override;
}

#endif