#include "Mendiane.hh"

Mendiane::Mendiane(void) : Item('M') {}

void Mendiane::DoAction(Player *player) const {
    player->AddVictoryPoint();
}