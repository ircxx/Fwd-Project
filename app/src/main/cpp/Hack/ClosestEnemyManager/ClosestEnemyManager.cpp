//
// Created by ircxx on 7/8/2023.
//

#include "ClosestEnemyManager.h"
#include "../Declarations.h"
#include "../../Misc/FunctionPointers.h"
#include "Misc/Logging.h"

class Player;

ClosestEnemyManager::ClosestEnemyManager() {
    shortestDistance = 99999999.0f;
}

Player *ClosestEnemyManager::GetClosestEnemy(Player *LocalPlayer) {

    if (!LocalPlayer) {
        return nullptr;
    }
    shortestDistance = 99999999.0f;;
    float maxAngle = configManager->G_Config.SilentConfig.Fov;

    Player *closestEnemy = nullptr;
    void *Camera = Pointers::Camera_main();
    if (Camera != nullptr) {
        for (Player *Player: entityListManager->PlayerSet) {
            if (Player != nullptr) {
                if (Player->getPlayerData()->Health > 0) {//
                    Vector3 targetDir = Vector3::Normalize(
                            Player->getPlayerData()->HeadPosition -
                            Pointers::Transform_Position[Pointers::Component_get_transform[(void *)LocalPlayer]()]());
                    float angle =
                            Vector3::Angle(targetDir,
                                           LocalPlayer->getPlayerData()->ForwardDirection) * 360;

                    if (angle <= maxAngle) {
                        if (angle < shortestDistance) {
                            shortestDistance = angle;
                            closestEnemy = Player;
                        }
                    }
                }
            }
        }
    }
    return closestEnemy;
}

