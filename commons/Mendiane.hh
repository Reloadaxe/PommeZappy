#ifndef _MENDIANE_HH
#define _MENDIANE_HH

#include "Item.hh"

class Mendiane : public Item {
    public:
        Mendiane(void);
        void DoAction(void) const override;
};

#endif
