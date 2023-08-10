#ifndef IMGUIANDROID_SCREEN_H
#define IMGUIANDROID_SCREEN_H

#include "../ByNameModding/BNM.hpp"

using namespace BNM::UNITY_STRUCTS;
using namespace BNM::MONO_STRUCTS;
using namespace BNM;

namespace Unity
{
    namespace Screen
    {
        extern BNM::LoadClass Screen;
        extern BNM::Property<int> Height;
        extern BNM::Property<int> Width;
        extern bool is_done;

        void Setup();
    }
}

#endif IMGUIANDROID_SCREEN_H