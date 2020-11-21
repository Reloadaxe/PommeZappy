#include "Player.hh"

Player::Player(void) {}

Player *Player::_player = nullptr;

Player *Player::Get(void)
{
    if (_player == nullptr)
        _player = new Player();
    return _player;
}

std::vector<QString> *Player::Think(QJsonArray *map, const bool jumped)
{
    QString items = "D 1LMS";
    unsigned int maxWeight = 0;
    unsigned int cell = 0;
    for (int i = 0; i < map->size(); i++) {
        QString value = map->at(i).toString();
        int weight = value == "" ? 1 : items.indexOf(value);
        if (weight == -1)
            weight = 2;
        if (weight > (int)maxWeight) {
            maxWeight = weight;
            cell = i;
        }
    }

    std::vector<QString> *commands = new std::vector<QString>();

    if (maxWeight == 0) { 
        commands->push_back(jumped ? "right" : "jump");
        return commands;
    }
    
    switch (cell) {
        case 0:
            commands->push_back("leftfwd");
            break;
        case 1:
            commands->push_back("fwd");
            break;
        case 2:
            commands->push_back("rightfwd");
            break;
        case 3:
            commands->push_back("fwd");
            commands->push_back("fwd");
            break;
    }
    
    return commands;
}
