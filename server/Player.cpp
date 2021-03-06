#include "Player.hh"

std::vector<bool> *Player::_ids = nullptr;

Player::Player(const int y, const int x) : _is_dead(false), _energy(2), _lifePoints(10), _victoryPoints(0), _orientation(zp_North), _y(y), _x(x), _client(nullptr)
{
    const std::vector<bool>::iterator it = std::find(_ids->begin(), _ids->end(), false);
    if (it != _ids->end())
    {
        const int index = std::distance(_ids->begin(), it);
        _id = index + 1;
        _ids->at(index) = true;
    }
    else
    {
        _id = 0;
    }
}

void Player::SetClient(Client *client)
{
    _client = client;
}

Client *Player::GetClient(void) const
{
    return _client;
}

int Player::GetLifePoints(void) const
{
    return _lifePoints;
}

void Player::SetIsDead(const bool isDead)
{
    _is_dead = isDead;
}

bool Player::GetIsDead(void)
{
    if (!_is_dead && _lifePoints < 0) {
        Map *map = Map::Get();
        map->GetCellAt(_y, _x)->RemoveClient();
        _is_dead = true;
    }
    return _is_dead;
}

int Player::GetId(void) const
{
    return _id;
}

int Player::GetY(void) const
{
    return _y;
}

int Player::GetX(void) const
{
    return _x;
}

void Player::SetIds(const unsigned int size)
{
    if (_ids == nullptr) {
        _ids = new std::vector<bool>;
        for (int i = 0; i < (int)size; i++)
            _ids->push_back(false);
    }
}

void Player::AddLifePoint(void)
{
    _lifePoints++;
}

void Player::RemoveLifePoint(void)
{
    _lifePoints--;
}

void Player::AddVictoryPoint(void)
{
    _victoryPoints++;
}

void Player::RemoveVictoryPoint(void)
{
    _victoryPoints--;
}

void Player::ResetEnergy(void)
{
    _energy = 2;
}

void Player::RemoveEnergy(void)
{
    _energy--;
}

bool Player::CanMove(const Map *map) const
{
    switch (_orientation)
    {
    case Direction::zp_North:
        return _y - 1 >= 0;
    case Direction::zp_East:
        return _x + 1 < map->GetWidth();
    case Direction::zp_South:
        return _y + 1 < map->GetHeight();
    case Direction::zp_West:
        return _x - 1 >= 0;
    }
    return false;
}

bool Player::CanAttack(const Map *map) const
{
    switch (_orientation)
    {
    case Direction::zp_North:
        return map->GetCellAt(_y - 1, _x)->GetClient() != nullptr;
    case Direction::zp_East:
        return map->GetCellAt(_y, _x + 1)->GetClient() != nullptr;
    case Direction::zp_South:
        return map->GetCellAt(_y + 1, _x)->GetClient() != nullptr;
    case Direction::zp_West:
        return map->GetCellAt(_y, _x - 1)->GetClient() != nullptr;
    }
    return false;
}

void Player::Attack(const Map *map) const
{
    Client *client;
    switch (_orientation)
    {
    case Direction::zp_North:
        client = map->GetCellAt(_y - 1, _x)->GetClient();
        break;
    case Direction::zp_East:
        client = map->GetCellAt(_y, _x + 1)->GetClient();
        break;
    case Direction::zp_South:
        client = map->GetCellAt(_y + 1, _x)->GetClient();
        break;
    case Direction::zp_West:
        client = map->GetCellAt(_y, _x - 1)->GetClient();
        break;
    }
    if (client != NULL)
        client->getPlayer()->RemoveLifePoint();
}

void Player::Move(const Map *map)
{
    map->GetCellAt(_y, _x)->RemoveClient();

    switch (_orientation)
    {
    case Direction::zp_North:
        _y--;
        break;
    case Direction::zp_East:
        _x++;
        break;
    case Direction::zp_South:
        _y++;
        break;
    case Direction::zp_West:
        _x--;
        break;
    }

    map->GetCellAt(_y, _x)->SetClient(GetClient());
    Item *item = map->GetCellAt(_y, _x)->GetItem();
    if (item != nullptr) {
        item->DoAction(this);
    }
}

bool Player::HasWon(void) const
{
    return _victoryPoints >= 10;
}

bool Player::CanJump(const Map *map) const
{
    switch (_orientation)
    {
    case Direction::zp_North:
        return _y - 3 > 0 && map->GetCellAt(_y - 3, _x)->GetClient() == nullptr;
    case Direction::zp_East:
        return _x + 3 < map->GetWidth() - 1 && map->GetCellAt(_y, _x + 3)->GetClient() == nullptr;
    case Direction::zp_South:
        return _y + 3 < map->GetHeight() - 1 && map->GetCellAt(_y + 3, _x)->GetClient() == nullptr;
    case Direction::zp_West:
        return _x - 3 > 0 && map->GetCellAt(_y, _x - 3)->GetClient() == nullptr;
    }
    return false;
}

bool Player::DoCommand(const Command command, const Map *map)
{
    switch (command) {
        case Command::zp_left:
            _orientation = (Direction)((int)_orientation > 0 ? (int)_orientation - 1 : 3);
            break;
        case Command::zp_right:
            _orientation = (Direction)(((unsigned int)_orientation + 1) % 4);
            break;
        case Command::zp_fwd:
            if (!CanMove(map))
                return false;
            if (CanAttack(map))
                Attack(map);
            else
                Move(map);
            break;
        case Command::zp_rightfwd:
            if (!DoCommand(Command::zp_right, map) || !DoCommand(Command::zp_fwd, map))
                return false;
            break;
        case Command::zp_leftfwd:
            if (!DoCommand(Command::zp_left, map) || DoCommand(Command::zp_fwd, map))
                return false;
            break;
        case Command::zp_jump:
            if (!CanJump(map))
                return false;
            for (unsigned int i = 0; i < 3; i++)
                Move(map);
            RemoveEnergy();
            break;
        case Command::zp_back:
            _orientation = (Direction)(((unsigned int)_orientation + 2) % 4);
            if (!DoCommand(Command::zp_fwd, map))
                return false;
            break;
    }
    RemoveEnergy();
    return true;
}

Direction Player::GetOrientation() const
{
    return _orientation;
}

QString Player::GetOrientationStr(const Direction orientation) const
{
    switch (orientation) {
        case Direction::zp_North:
            return "North";
        case Direction::zp_East:
            return "East";
        case Direction::zp_South:
            return "South";
        case Direction::zp_West:
            return "West";
    }
    return "";
}

QJsonObject Player::getInformations(const bool all) const
{
    QJsonObject informations;

    informations.insert("id", (int)_id);
    informations.insert("life", (int)_lifePoints);
    informations.insert("victory", (int)_victoryPoints);
    if (all) {
        informations.insert("energy", (int)_energy);
        informations.insert("orientation", GetOrientationStr(_orientation));
    }

    return informations;
}
