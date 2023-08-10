//
// Created by ircxx on 7/8/2023.
//

#ifndef IMGUIANDROID_CLOSESTENEMYMANAGER_H
#define IMGUIANDROID_CLOSESTENEMYMANAGER_H


#include "../Player/Player.h"

class ClosestEnemyManager {
private:
    float shortestDistance;
public:
    ClosestEnemyManager();
    float Fov;
    Player* GetClosestEnemy(Player*);

};


#endif //IMGUIANDROID_CLOSESTENEMYMANAGER_H
