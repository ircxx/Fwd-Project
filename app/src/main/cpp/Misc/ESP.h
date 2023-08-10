#ifndef ImGuiAndroid_ESP
#define ImGuiAndroid_ESP

#include "../ImGui/imgui_internal.h"

namespace ESP {
    namespace Utils {
        void DrawLine(ImVec2 start, ImVec2 end, float color[4]);
        void DrawBox(ImVec4 rect, float color[4]);
        void DrawBoxOutline(ImVec4 rect, float color[4]);
        void DrawVerticalHealthBar(ImVec4 rect, int MaxHP, float c_HP, bool DrawText);
        void DrawCircle(float X, float Y, float radius, bool filled, float color[4]);
        void DrawText(ImVec2 position, ImVec4 color, const char *text);
        ImColor Float2Color(float color[4]);
    }
    void DrawESP();
}

#endif ImGuiAndroid_ESP