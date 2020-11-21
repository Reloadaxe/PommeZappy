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
        Player(const int y, const int x);
        Direction GetOrientation() const;
        QString GetOrientationStr(const Direction orientation) const;
        void SetClient(Client *client);
        Client *GetClient(void) const;
        int GetId(void) const;
        int GetY(void) const;
        int GetX(void) const;
        int GetLifePoints(void) const;
        void SetIsDead(const bool isDead);
        bool GetIsDead(void);
        void AddLifePoint(void);
        void RemoveLifePoint(void);
        void AddVictoryPoint(void);
        void RemoveVictoryPoint(void);
        bool HasWon(void) const;
        void ResetEnergy(void);
        void RemoveEnergy(void);
        bool CanMove(const Map *map) const;
        bool CanAttack(const Map *map) const;
        bool CanJump(const Map *map) const;
        void Attack(const Map *map) const;
        void Move(const Map *map);
        bool DoCommand(const Command command, const Map *map);
        QJsonObject getInformations(const bool all) const;
        static void SetIds(const unsigned int size);

    private:
        static std::vector<bool> *_ids;
        bool _is_dead;
        unsigned int _id;
        unsigned int _energy;
        int _lifePoints;
        unsigned int _victoryPoints;
        Direction _orientation;
        int _y;
        int _x;
        Client *_client;
};

#endif
