//
// Created by ircxx on 6/8/2023.
//

#include "Player.h"
//#include "../../Misc/FunctionPointers.h"
//#include "../../ByNameModding/BNM.hpp"
#include "../../Misc/FunctionPointers.h"
#include "Misc/Logging.h"
#include <unordered_map>



std::unordered_map<Player *, PlayerData> PlayerDataMap;
BodyParts mBodyParts;
Vector3 GetPlayerLocationByTransform(void *player) {
    if(BNM::IsUnityObjectAlive(player)) {
        Vector3 location(0, 0, 0);
        location = Pointers::Transform_Position[player]();
        return location;
    }
}

PlayerData* getPlayerDatawithOrig(Player* player){
    if(PlayerDataMap.find(player) == PlayerDataMap.end())
        PlayerDataMap[player] = PlayerData();

    return &(PlayerDataMap[player]);
}

PlayerData* Player::getPlayerData() {
    return getPlayerDatawithOrig(this);
}

void InitBodyPositions(Player *player){
    player->getPlayerData()->HeadPosition = GetPlayerLocationByTransform(
            *(void **) ((long) player->getPlayerData()->ThirdPersonBody + mBodyParts.head));

    player->getPlayerData()->SpinePosition = GetPlayerLocationByTransform(
            *(void **) ((long) player->getPlayerData()->ThirdPersonBody + mBodyParts.spine));

    player->getPlayerData()->HipsPosition = GetPlayerLocationByTransform(
            *(void **) ((long) player->getPlayerData()->ThirdPersonBody + mBodyParts.hips));

    player->getPlayerData()->LeftUpperArmPosition = GetPlayerLocationByTransform(
            *(void **) ((long) player->getPlayerData()->ThirdPersonBody + mBodyParts.leftUpperArm));

    player->getPlayerData()->LeftLowerArmPosition = GetPlayerLocationByTransform(
            *(void **) ((long) player->getPlayerData()->ThirdPersonBody + mBodyParts.leftLowerArm));

    player->getPlayerData()->RightUpperArmPosition = GetPlayerLocationByTransform(
            *(void **) ((long) player->getPlayerData()->ThirdPersonBody + mBodyParts.rightUpperArm));

    player->getPlayerData()->RightLowerArmPosition = GetPlayerLocationByTransform(
            *(void **) ((long) player->getPlayerData()->ThirdPersonBody + mBodyParts.rightLowerArm));

    player->getPlayerData()->LeftUpperLegPosition = GetPlayerLocationByTransform(
            *(void **) ((long) player->getPlayerData()->ThirdPersonBody + mBodyParts.leftUpperLeg));

    player->getPlayerData()->LeftLowerLegPosition = GetPlayerLocationByTransform(
            *(void **) ((long) player->getPlayerData()->ThirdPersonBody + mBodyParts.leftLowerLeg));

    player->getPlayerData()->RightUpperLegPosition = GetPlayerLocationByTransform(
            *(void **) ((long) player->getPlayerData()->ThirdPersonBody + mBodyParts.rightUpperLeg));

    player->getPlayerData()->RightLowerLegPosition = GetPlayerLocationByTransform(
            *(void **) ((long) player->getPlayerData()->ThirdPersonBody + mBodyParts.rightLowerLeg));

    //

}
void InitBodyW2SPositions(Player *player){
    player->getPlayerData()->W2SHeadPosition = Pointers::Camera_WorldToScreenPoint[Pointers::Camera_main()](
            player->getPlayerData()->HeadPosition);

    player->getPlayerData()->W2SSpinePosition = Pointers::Camera_WorldToScreenPoint[Pointers::Camera_main()](
            player->getPlayerData()->SpinePosition);

    player->getPlayerData()->W2SHipsPosition = Pointers::Camera_WorldToScreenPoint[Pointers::Camera_main()](
            player->getPlayerData()->HipsPosition);

    player->getPlayerData()->W2SLeftUpperArmPosition = Pointers::Camera_WorldToScreenPoint[Pointers::Camera_main()](
            player->getPlayerData()->LeftUpperArmPosition);

    player->getPlayerData()->W2SLeftLowerArmPosition = Pointers::Camera_WorldToScreenPoint[Pointers::Camera_main()](
            player->getPlayerData()->LeftLowerArmPosition);

    player->getPlayerData()->W2SRightUpperArmPosition = Pointers::Camera_WorldToScreenPoint[Pointers::Camera_main()](
            player->getPlayerData()->RightUpperArmPosition);

    player->getPlayerData()->W2SRightLowerArmPosition = Pointers::Camera_WorldToScreenPoint[Pointers::Camera_main()](
            player->getPlayerData()->RightLowerArmPosition);

    player->getPlayerData()->W2SLeftUpperLegPosition = Pointers::Camera_WorldToScreenPoint[Pointers::Camera_main()](
            player->getPlayerData()->LeftUpperLegPosition);

    player->getPlayerData()->W2SLeftLowerLegPosition = Pointers::Camera_WorldToScreenPoint[Pointers::Camera_main()](
            player->getPlayerData()->LeftLowerLegPosition);

    player->getPlayerData()->W2SRightUpperLegPosition = Pointers::Camera_WorldToScreenPoint[Pointers::Camera_main()](
            player->getPlayerData()->RightUpperLegPosition);

    player->getPlayerData()->W2SRightLowerLegPosition = Pointers::Camera_WorldToScreenPoint[Pointers::Camera_main()](
            player->getPlayerData()->RightLowerLegPosition);


    // For Box

    player->getPlayerData()->RightLowerLegPosition.y -= 0.50f;
    //player->getPlayerData()->HeadPosition.y += 0.30f;
    Vector3 HforBox = player->getPlayerData()->HeadPosition;
    HforBox.y += 0.30f;
    player->getPlayerData()->W2SHeadForBoxPosition = Pointers::Camera_WorldToScreenPoint[Pointers::Camera_main()](
            HforBox);

    player->getPlayerData()->W2SToeForBoxPosition = Pointers::Camera_WorldToScreenPoint[Pointers::Camera_main()](
            player->getPlayerData()->RightLowerLegPosition);


}
void Player::Update(int LocalTeam) {
    if(this->getPlayerData() == nullptr)
        return;

    this->getPlayerData()->Health = Pointers::Health[(void *)this]();
    this->getPlayerData()->Team = Pointers::Team[(void *)this]();
    this->getPlayerData()->LocalTeam = LocalTeam;
    this->getPlayerData()->Name = *(BNM::MONO_STRUCTS::monoString **)((long) this + 0x17C);

    this->getPlayerData()->ThirdPersonBody = Pointers::ThirdPersonBodyPartReferences[(void *)this]();
    if(this->getPlayerData()->ThirdPersonBody != nullptr) {
        InitBodyPositions(this);
        InitBodyW2SPositions(this);
    }
    this->getPlayerData()->ForwardDirection = Pointers::Transform_GetForward[Pointers::Component_get_transform[Pointers::Camera_main()]()]();

    //LOGI("%f %f %f", this->getPlayerData()->Position.x, this->getPlayerData()->Position.y, this->getPlayerData()->Position.z);
}

