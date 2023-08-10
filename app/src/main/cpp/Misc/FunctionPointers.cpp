//
// Created by ircxx on 6/8/2023.
//
#include "FunctionPointers.h"

BNM::LoadClass Pointers::Component;
BNM::Method<void *> Pointers::Component_get_transform;

BNM::LoadClass Pointers::Transform;
BNM::Property<Vector3> Pointers::Transform_Position;
BNM::Method<Vector3> Pointers::Transform_GetForward;

BNM::LoadClass Pointers::Camera;
BNM::Method<Vector3> Pointers::Camera_WorldToScreenPoint;




BNM::LoadClass Pointers::PhotonPlayerClz;

BNM::LoadClass Pointers::LocalPlayer;
BNM::LoadClass Pointers::BulletManager;
BNM::LoadClass Pointers::Bullet;
//BNM::LoadClass GlovesController = LoadClass("", "GlovesController");
BNM::LoadClass Pointers::CameraManager;
BNM::Method<void *> Pointers::Camera_main;

BNM::LoadClass Pointers::PlayerClz;
BNM::Field<float> Pointers::Health;
BNM::Field<bool> Pointers::isMine;
BNM::Field<int> Pointers::Team;
BNM::Field<void *> Pointers::ThirdPersonBodyPartReferences;

void Pointers::LoadPointers() {
    Component = BNM::LoadClass(OBFUSCATES_BNM("UnityEngine"), OBFUSCATES_BNM("Component"));
    Component_get_transform = Component.GetMethodByName(OBFUSCATE_BNM("get_transform"), 0);

    Transform = BNM::LoadClass(OBFUSCATES_BNM("UnityEngine"), OBFUSCATES_BNM("Transform"));
    Transform_Position = Transform.GetPropertyByName(OBFUSCATES_BNM("position"));
    Transform_GetForward = Transform.GetMethodByName(OBFUSCATES_BNM("get_forward"), 0);


    Camera = BNM::LoadClass(OBFUSCATES_BNM("UnityEngine"), OBFUSCATES_BNM("Camera"));
    Camera_WorldToScreenPoint = Camera.GetMethodByName(OBFUSCATES_BNM("WorldToScreenPoint"), 1);


    PhotonPlayerClz = BNM::LoadClass(OBFUSCATES_BNM(""), OBFUSCATES_BNM("AILNOOHHLJL"));

    LocalPlayer = BNM::LoadClass(OBFUSCATES_BNM(""), OBFUSCATES_BNM("LocalPlayer"));

    BulletManager = BNM::LoadClass(OBFUSCATES_BNM(""), OBFUSCATES_BNM("BulletManager"));

    Bullet = BNM::LoadClass(OBFUSCATES_BNM(""), OBFUSCATES_BNM("Bullet"));

    CameraManager = BNM::LoadClass(OBFUSCATES_BNM(""), OBFUSCATES_BNM("CameraManager"));
    Camera_main = CameraManager.GetMethodByName(OBFUSCATES_BNM("get_MainCamera"), 0);

    PlayerClz = BNM::LoadClass(OBFUSCATES_BNM(""), OBFUSCATES_BNM("Player"));
    Health = PlayerClz.GetFieldByName(OBFUSCATES_BNM("KNFBIPGOEPP"));
    isMine = PlayerClz.GetFieldByName(OBFUSCATES_BNM("isMine"));
    Team = PlayerClz.GetFieldByName(OBFUSCATES_BNM("KOACJLIKJLC"));
    ThirdPersonBodyPartReferences = PlayerClz.GetFieldByName(OBFUSCATES_BNM("CJJLIGLBCHD"));


}
