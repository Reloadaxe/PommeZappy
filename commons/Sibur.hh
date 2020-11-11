#ifndef _SIBUR_HH
#define _SIBUR_HH

#include "Item.hh"

class Sibur : public Item {
    public:
        Sibur(void);
        void DoAction(void) const override;
}

#endif