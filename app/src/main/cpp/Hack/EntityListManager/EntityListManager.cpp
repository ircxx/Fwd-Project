//
// Created by ircxx on 6/8/2023.
//

#include "EntityListManager.h"
#include "Hack/Declarations.h"
//#include "Hack/Player/Player.h"

class Player;
void EntityListManager::Add(Player *player) {
    if(player != nullptr)
    PlayerSet.insert(player);
}

void EntityListManager::Manage() {
    for(Player *Player : PlayerSet) {
        if ((Player->getPlayerData()->Team == LocalPlayer->getPlayerData()->LocalTeam) ||
            !BNM::IsUnityObjectAlive(Player) || Player->getPlayerData()->ThirdPersonBody == nullptr || Player->getPlayerData()->Health == 0) {
            EntityListManager::RemoveGivenPlayer(Player);
        }
    }

}

void EntityListManager::RemoveAll() {
    PlayerSet.clear();
}

void EntityListManager::RemoveGivenPlayer(Player *player) {
    PlayerSet.erase(player);
}