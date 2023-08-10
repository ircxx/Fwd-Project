//
// Created by letha on 9/4/2021.
// Updated by Tomie on 3/27/2023
//

#ifndef IMGUIANDROID_FUNCTIONPOINTERS_H
#define IMGUIANDROID_FUNCTIONPOINTERS_H
#include "ByNameModding/BNM.hpp"
using namespace BNM::UNITY_STRUCTS;

namespace Pointers {

    extern BNM::LoadClass Component;
    extern BNM::Method<void *> Component_get_transform;

    extern BNM::LoadClass Transform;
    extern BNM::Property<Vector3> Transform_Position;
    extern BNM::Method<Vector3> Transform_GetForward;
    extern BNM::LoadClass Camera;
    extern BNM::Method<Vector3> Camera_WorldToScreenPoint;
    //extern BNM::Property<Vector3> Camera_Main;


    extern BNM::LoadClass PhotonPlayerClz;
    extern BNM::Method<Vector3> PhotonPlayer_getNickName;

    extern BNM::LoadClass LocalPlayer;
    extern BNM::LoadClass BulletManager;
    extern BNM::LoadClass Bullet;
    //BNM::LoadClass GlovesController = LoadClass("", "GlovesController");
    extern BNM::LoadClass CameraManager;
    extern BNM::Method<void *> Camera_main;

    extern BNM::LoadClass PlayerClz;
    extern BNM::Field<float> Health;
    extern BNM::Field<bool> isMine;
    extern BNM::Field<int> Team;
    extern BNM::Field<void *> ThirdPersonBodyPartReferences;


    void LoadPointers();
        /*GameObject = BNM::LoadClass("UnityEngine", "GameObject");
        GameObject_Transform = GameObject.GetPropertyByName("transform");

        Transform = BNM::LoadClass("UnityEngine", "Transform");
        Transform_Position = Transform.GetPropertyByName("position");

        Camera = BNM::LoadClass("UnityEngine", "Camera");
        Camera_WorldToScreenPoint = Camera.GetMethodByName("WorldToScreenPoint", 1);
        Camera_Main = Camera.GetPropertyByName("main");


        LocalPlayer = BNM::LoadClass("", "LocalPlayer");
        BulletManager = BNM::LoadClass("", "BulletManager");
        Bullet = BNM::LoadClass("", "Bullet");
        CameraManager = BNM::LoadClass("", "CameraManager");*/

}
#endif IMGUIANDROID_FUNCTIONPOINTERS_H
