#include "Sibur.hh"

Sibur::Sibur(void) : Item('S') {}

void Sibur::DoAction(Player *player) const {
    Server *server = Server::getInstance();

    std::vector<Client*> clients = server->getClients();

    for (int i = 0; i < (int)clients.size(); i++) {
        Player *plr = clients[i]->getPlayer();
        if (plr->GetId() != player->GetId()) {
            plr->RemoveLifePoint();
        }
    }
}
