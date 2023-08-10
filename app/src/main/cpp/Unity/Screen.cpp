//
// Created by ircxx on 7/8/2023.
//
#include "Screen.h"

BNM::LoadClass Unity::Screen::Screen;
BNM::Property<int> Unity::Screen::Height;
BNM::Property<int> Unity::Screen::Width;
bool Unity::Screen::is_done = false;


void Unity::Screen::Setup() {
    Screen = BNM::LoadClass(OBFUSCATES_BNM("UnityEngine"), OBFUSCATES_BNM("Screen"));
    Height = Screen.GetPropertyByName(OBFUSCATES_BNM("height"));
    Width = Screen.GetPropertyByName(OBFUSCATES_BNM("width"));
    is_done = true;
}