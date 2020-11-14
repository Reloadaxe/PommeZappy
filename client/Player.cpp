#include "Player.hh"

Player::Player(void) {}

Player *Player::_player = nullptr;

Player *Player::Get(void)
{
    if (_player == nullptr)
        _player = new Player();
    return _player;
}

const std::vector<const QString> *Player::Think(const QJsonArray *map)
{
    const QString items = "D 1LMS";
    unsigned int maxWeight = 0;
    unsigned int cell = 0;
    for (int i = 0; i < map->size(); i++) {
        const QString value = map->at(i).toString();
        int weight = value == "" ? 1 : items.indexOf(value);
        if (weight == -1)
            weight = 2;
        if (weight > (int)maxWeight) {
            maxWeight = weight;
            cell = i;
        }
    }

    std::vector<const QString> *commands = new std::vector<const QString>();

    if (maxWeight == 0)
        commands->push_back("jump");
    
    switch (cell) {
        case 0:
            commands->push_back("leftfwd");
            break;
        case 1:
            commands->push_back("front");
            break;
        case 2:
            commands->push_back("rightfwd");
            break;
        case 3:
            commands->push_back("front");
            commands->push_back("front");
            break;
    }
    
    return commands;
}