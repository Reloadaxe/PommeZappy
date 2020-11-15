#ifndef _PLAYER_HH
#define _PLAYER_HH

#include <algorithm>
#include "Map.hh"

enum Direction { North, East, South, West };
enum Command { left, right, fwd, rightfwd, leftfwd, jump, back, inspect, me };

class Player {
    public:
        Player(const unsigned int y, const unsigned int x);
        void AddLifePoint(void);
        void RemoveLifePoint(void);
        void AddVictoryPoint(void);
        void RemoveVictoryPoint(void);
        void ResetEnergy(void);
        void RemoveEnergy(void);
        bool CanMove(void) const;
        bool CanAttack(void) const;
        void Attack(void) const;
        void Move(void);
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
