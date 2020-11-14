#ifndef _PLAYER_HH
#define _PLAYER_HH

#include <iostream>
#include <QString>
#include <QJsonArray>
#include <QJsonValue>

class Player {
    public:
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;
        static Player *Get(void);
        const std::vector<const QString> *Think(const QJsonArray *map);

    private:
        Player(void);
        static Player *_player;
};

#endif