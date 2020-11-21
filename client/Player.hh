#ifndef _PLAYER_HH
#define _PLAYER_HH

#include <iostream>
#include <vector>
#include <QString>
#include <QJsonArray>
#include <QJsonValue>

class Player {
    public:
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;
        static Player *Get(void);
        std::vector<QString> *Think(QJsonArray *map, const bool jumped, const int turned);

    private:
        Player(void);
        static Player *_player;
};

#endif
