#include "Player.hh"

Player::Player(const unsigned int y, const unsigned int x) : _energy(2), _lifePoints(10), _victoryPoints(0), _orientation(North), _y(y), _x(x)
{
    std::vector<bool>::iterator it = std::find(_ids.begin(), _ids.end(), false);
    if (it != _ids.end()) {
        int index = std::distance(_ids.begin(), it);
        _id = _ids.at(index);
        _ids.at(index) = true;
    } else {
        _id = -1;
    }
}

void Player::SetIds(const unsigned int size)
{
    std::fill(_ids.begin(), _ids.begin() + size, false);
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

void Player::RemoveEnergy()
{
    _energy--;
}

const bool Player::CanMove() const
{
    const Map *map = Map::Get();
    switch(_orientation) {
        case North:
            if (_y > 0) {
                return true;
            }
            return false;
        case East:
            if (_x < map->GetWidth() - 1) {
                return true;
            }
            return false;
        case South:
            if (_y < map->GetHeight() - 1) {
                return true;
            }
            return false;
        case West:
            if (_x > 0) {
                return true;
            }
            return false;
    }
}

const bool Player::CanAttack() const
{
    const Map *map = Map::Get();
    switch(_orientation) {
        case North:
            if (map->GetCellAt(_y - 1, _x)->GetPlayer() != nullptr) {
                return true;
            }
            return false;
        case East:
            if (map->GetCellAt(_y, _x + 1)->GetPlayer() != nullptr) {
                return true;
            }
            return false;
        case South:
            if (map->GetCellAt(_y + 1, _x)->GetPlayer() != nullptr) {
                return true;
            }
            return false;
        case West:
            if (map->GetCellAt(_y, _x - 1)->GetPlayer() != nullptr) {
                return true;
            }
            return false;
    }
}

void Player::Attack()
{
    const Map *map = Map::Get();
    Player *player;
    switch(_orientation) {
        case North:
            player = map->GetCellAt(_y - 1, _x)->GetPlayer();
            break;
        case East:
            player = map->GetCellAt(_y, _x + 1)->GetPlayer();
            break;
        case South:
            player = map->GetCellAt(_y + 1, _x)->GetPlayer();
            break;
        case West:
            player = map->GetCellAt(_y, _x - 1)->GetPlayer();
            break;
    }
    player->RemoveLifePoint();
}

void Player::Move()
{
    Map *map = Map::Get();
    map->GetCellAt(_y, _x)->RemovePlayer();

    switch(_orientation) {
        case North:
            _y--;
            break;
        case East:
            _x++;
            break;
        case South:
            _y++;
            break;
        case West:
            _x--;
            break;
    }

    map->GetCellAt(_y, _x)->SetPlayer(this);
}

bool Player::DoCommand(const Command command)
{
    switch(command) {
        case left:
            _orientation = (Direction)((int)_orientation > 0 ? (int)_orientation - 1 : 3);
            return true;
        case right:
            _orientation = (Direction)(((unsigned int)_orientation + 1) % 4);
            break;
        case fwd:
            if (!CanMove()) {
                return false;
            }
            if (CanAttack()) {
                Attack();
            } else {
                Move();
            }
            return true;
        case rightfwd:
            if (!DoCommand(right) || !DoCommand(fwd)) {
                return false;
            }
            return true;
        case leftfwd:
            if (!DoCommand(left) || DoCommand(fwd)) {
                return false;
            }
            return true;
        case jump:
            for (unsigned int i = 0; i < 3; i++) {
                if (!CanMove()) {
                    return false;
                }
                Move();
            }
            RemoveEnergy();
            return true;
        case back:
            break;
        case inspect:
            break;
        case me:
            break;
    }
    if (command != me) {
        RemoveEnergy();
    }
}