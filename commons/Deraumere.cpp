#include "Deraumere.hh"

Deraumere::Deraumere(void) : Item('D') {}

void Deraumere::DoAction(Player *player) const {
    player->RemoveLifePoint();
}