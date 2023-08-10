//
// Created by ircxx on 7/8/2023.
//

#ifndef IMGUIANDROID_CONFIGURATIONSTRUCT_H
#define IMGUIANDROID_CONFIGURATIONSTRUCT_H


struct LinePosition{
    int Up = 0;
    int Center = 1;
    int Down = 2;
    int Current = 0;
};

struct BoxType {
    int Normal = 0;
    int Outline = 1;
    int Current = 0;
};

struct Silent
{
    bool Enable, DrawLine, DrawFov = false;
    float Fov = 40.0f;
    int PositionBullet = 0;
};

struct ESPEnemy
{
    bool Enable = false;
    bool Line = false;  LinePosition LinePosition;
    bool Box = false; BoxType mBoxType;
    float LineBoxColor[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
    bool Health, DrawHealthText = false;
    bool Distance, Name = false; float NameDistanceColor[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
    bool Skeleton = false; float SkeletonColor[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
    bool Rainbow = false;
};


struct Chams
{
    float Color[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
    bool Rainbow = false;
    int OutlineWidth, WireframeWidth = 1;
    int CurrentChamsType = 0;
};
struct Gloves
{
    int CurrentGlovesType = 0;
};


struct GlobalConfiguration {
    ESPEnemy ESPConfig;
    Chams ChamsConfig;
    Gloves GlovesConfig;
    Silent SilentConfig;
    bool LoadOnStart = false;
};

#endif //IMGUIANDROID_CONFIGURATIONSTRUCT_H
