#ifndef _PLAYER_HH
#define _PLAYER_HH

#include <algorithm>
#include <QJsonObject>
#include "Map.hh"
#include "Client.h"
#include "game_enums.hh"

class Map;
class Client;
class Player {
    public:
        Player(const unsigned int y, const unsigned int x);
        Direction GetOrientation() const;
        QString GetOrientationStr(const Direction orientation) const;
        void SetClient(Client *client);
        Client *GetClient(void) const;
        unsigned int GetId(void) const;
        unsigned int GetY(void) const;
        unsigned int GetX(void) const;
        void AddLifePoint(void);
        void RemoveLifePoint(void);
        void AddVictoryPoint(void);
        void RemoveVictoryPoint(void);
        void ResetEnergy(void);
        void RemoveEnergy(void);
        bool CanMove(const Map *map) const;
        bool CanAttack(const Map *map) const;
        bool CanJump(const Map *map) const;
        void Attack(const Map *map) const;
        void Move(const Map *map);
        bool DoCommand(const Command command, const Map *map);
        QJsonObject getInformations(const int id, const bool all=true) const;
        static void SetIds(const unsigned int size);

    private:
        static std::vector<bool> *_ids;
        unsigned int _id;
        unsigned int _energy;
        unsigned int _lifePoints;
        unsigned int _victoryPoints;
        Direction _orientation;
        unsigned int _y;
        unsigned int _x;
        Client *_client;
};

#endif
