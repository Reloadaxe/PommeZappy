#ifndef _SIBUR_HH
#define _SIBUR_HH

#include "Item.hh"
#include "../server/network/Server.h"
#include "../server/network/Client.h"

class Sibur : public Item {
    public:
        Sibur(void);
        void DoAction(Player *player) const override;
};

#endif
