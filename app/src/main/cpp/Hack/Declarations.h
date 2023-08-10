//
// Created by ircxx on 7/8/2023.
//

#ifndef IMGUIANDROID_DECLARATIONS_H
#define IMGUIANDROID_DECLARATIONS_H

#include "Configuration/ConfigManager.h"
#include "EntityListManager/EntityListManager.h"
#include "ClosestEnemyManager/ClosestEnemyManager.h"

extern EntityListManager *entityListManager;
extern ConfigManager* configManager;
extern ClosestEnemyManager* closestEnemyManager;
extern Player* ClosestEnemy;
extern Player *LocalPlayer;;
#endif //IMGUIANDROID_DECLARATIONS_H
