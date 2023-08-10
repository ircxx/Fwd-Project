//
// Created by ircxx on 6/8/2023.
//

#ifndef IMGUIANDROID_PLAYER_H
#define IMGUIANDROID_PLAYER_H

#include "../../ByNameModding/BNM.hpp"


struct BodyParts{
    uintptr_t head = 0xC;
    uintptr_t spine = 0x10;
    uintptr_t hips = 0x14;
    uintptr_t leftUpperArm = 0x18;
    uintptr_t leftLowerArm = 0x1C;
    uintptr_t rightUpperArm = 0x20;
    uintptr_t rightLowerArm = 0x24;
    uintptr_t leftUpperLeg = 0x28;
    uintptr_t leftLowerLeg = 0x2C;
    uintptr_t rightUpperLeg = 0x30;
    uintptr_t rightLowerLeg = 0x34;
};

struct PlayerData{
    int Health;
    int Team;
    int LocalTeam;
    BNM::MONO_STRUCTS::monoString *Name;
    void *ThirdPersonBody;

    BNM::UNITY_STRUCTS::Vector3 HeadPosition;
    BNM::UNITY_STRUCTS::Vector3 SpinePosition;
    BNM::UNITY_STRUCTS::Vector3 HipsPosition;
    BNM::UNITY_STRUCTS::Vector3 LeftUpperArmPosition;
    BNM::UNITY_STRUCTS::Vector3 LeftLowerArmPosition;
    BNM::UNITY_STRUCTS::Vector3 RightUpperArmPosition;
    BNM::UNITY_STRUCTS::Vector3 RightLowerArmPosition;
    BNM::UNITY_STRUCTS::Vector3 LeftUpperLegPosition;
    BNM::UNITY_STRUCTS::Vector3 LeftLowerLegPosition;
    BNM::UNITY_STRUCTS::Vector3 RightUpperLegPosition;
    BNM::UNITY_STRUCTS::Vector3 RightLowerLegPosition;


    //BNM::UNITY_STRUCTS::Vector3 ToePosition;

    BNM::UNITY_STRUCTS::Vector3 W2SHeadPosition;
    BNM::UNITY_STRUCTS::Vector3 W2SSpinePosition;
    BNM::UNITY_STRUCTS::Vector3 W2SHipsPosition;
    BNM::UNITY_STRUCTS::Vector3 W2SLeftUpperArmPosition;
    BNM::UNITY_STRUCTS::Vector3 W2SLeftLowerArmPosition;
    BNM::UNITY_STRUCTS::Vector3 W2SRightUpperArmPosition;
    BNM::UNITY_STRUCTS::Vector3 W2SRightLowerArmPosition;
    BNM::UNITY_STRUCTS::Vector3 W2SLeftUpperLegPosition;
    BNM::UNITY_STRUCTS::Vector3 W2SLeftLowerLegPosition;
    BNM::UNITY_STRUCTS::Vector3 W2SRightUpperLegPosition;
    BNM::UNITY_STRUCTS::Vector3 W2SRightLowerLegPosition;

    // For box
    BNM::UNITY_STRUCTS::Vector3 W2SHeadForBoxPosition;
    BNM::UNITY_STRUCTS::Vector3 W2SToeForBoxPosition;

    BNM::UNITY_STRUCTS::Vector3 ForwardDirection;
};

class Player {
public:
    PlayerData* getPlayerData();
    void Update(int LocalTeam);
};


#endif //IMGUIANDROID_PLAYER_H
