//
// Created by ircxx on 6/8/2023.
//

#ifndef IMGUIANDROID_ENTITYLISTMANAGER_H
#define IMGUIANDROID_ENTITYLISTMANAGER_H


#include <unordered_set>
#include "Hack/Player/Player.h"

//class Player;
class EntityListManager {
public:
    std::unordered_set<Player *> PlayerSet;
    void Add(Player *);
    void Manage();
    void RemoveGivenPlayer(Player *);
    void RemoveAll();
};


#endif //IMGUIANDROID_ENTITYLISTMANAGER_H
