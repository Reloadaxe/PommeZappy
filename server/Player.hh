#ifndef _PLAYER_HH
#define _PLAYER_HH

#include <algorithm>
#include "Map.hh"
#include "Id.hh"

const enum Direction { North, East, South, West };
const enum Command { left, right, fwd, rightfwd, leftfwd, jump, back, inspect, me };

class Player {
    public:
        Player(const unsigned int y, const unsigned int x);
        void AddLifePoint(void);
        void RemoveLifePoint(void);
        void AddVictoryPoint(void);
        void RemoveVictoryPoint(void);
        void ResetEnergy(void);
        void RemoveEnergy();
        const bool CanMove() const;
        const bool CanAttack() const;
        void Attack();
        void Move();
        bool DoCommand(const Command command);
        static void SetIds(const unsigned int size);

    private:
        static std::vector<bool> _ids;
        unsigned int _id;
        unsigned int _energy;
        unsigned int _lifePoints;
        unsigned int _victoryPoints;
        Direction _orientation;
        unsigned int _y;
        unsigned int _x;
};

#endif