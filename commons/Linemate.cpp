#include "Linemate.hh"

Linemate::Linemate(void) : Item('L') {}

void Linemate::DoAction(Player *player) const {
    player->AddLifePoint();
}