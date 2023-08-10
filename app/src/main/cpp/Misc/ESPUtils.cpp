//
// Created by ircxx on 7/8/2023.
//
#include <algorithm>
#include <string>
#include "ESP.h"

ImColor ESP::Utils::Float2Color(float color[4]){
    return ImColor(color[0],color[1],color[2],color[3]);

}

void ESP::Utils::DrawLine(ImVec2 start, ImVec2 end, float color[4]) {
    auto background = ImGui::GetBackgroundDrawList();
    if(background) {
        background->AddLine(start, end, ESP::Utils::Float2Color(color));
    }
}

void ESP::Utils::DrawBox(ImVec4 rect, float color[4]) {
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(rect.x, rect.y), ImVec2( (rect.x ) + (rect.z ), (rect.y) + (rect.w) ),
                                            ESP::Utils::Float2Color(color));
}
void ESP::Utils::DrawBoxOutline(ImVec4 rect, float color[4]) {
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(rect.x + 1, rect.y + 1), ImVec2( (rect.x + 1) + (rect.z - 2), (rect.y + 1) + (rect.w - 2) ), ImColor( 0, 0, 0, 255 ) );
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(rect.x - 1, rect.y - 1), ImVec2( (rect.x - 1) + (rect.z + 2), (rect.y - 1) + (rect.w + 2) ), ImColor( 0, 0, 0, 255 ) );
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(rect.x, rect.y), ImVec2( (rect.x ) + (rect.z ), (rect.y) + (rect.w) ),
                                            ESP::Utils::Float2Color(color));

}

void ESP::Utils::DrawVerticalHealthBar(ImVec4 rect, int MaxHP, float c_HP, bool DrawText) {
    float health = std::clamp((int) c_HP, 0, MaxHP);

    int h = (int) c_HP;
    std::string hpp = std::to_string(h) + " hp";

    int x = rect.x - 2;//+ PlayerRect.w + 2;

    int y = rect.y;
    ImVec2 hpsize = ImGui::CalcTextSize(hpp.c_str());

    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x - 5, y + rect.w),
                                                  ImColor(0, 0, 0, 255));

    ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(
            ImVec2(x - 1, y + rect.w - (rect.w * (health / MaxHP))),
            ImVec2(x - 4, y + rect.w),
            ImGui::GetColorU32(ImVec4(0.f, 1.f, 0.f, 1.000f)),
            ImGui::GetColorU32(ImVec4(1.f, 1.0f, 0.f, 1.000f)),
            ImGui::GetColorU32(ImVec4(1.f, 0.400f, 0.f, 1.000f)),
            ImGui::GetColorU32(ImVec4(1.f, 0.f, 0.f, 1.000f)));

    ImColor hp = ImColor(0, 255, 0, 255);
    if (h > ((MaxHP / 2) + (MaxHP / 4))) {
        hp = ImColor(0, 255, 0, 255);
    } else if (h > ((MaxHP / 2))) {
        hp = ImColor(255, 255, 0, 255);
    } else if (h > ((MaxHP / 2) - (MaxHP / 4))) {
        hp = ImColor(255, 165, 0, 255);
    } else if (h < ((MaxHP / 4))) {
        hp = ImColor(255, 0, 0, 255);
    }

    if (DrawText) {
        ImGui::GetBackgroundDrawList()->AddText(
                ImVec2((rect.x - hpsize.x) - 10, (rect.y + (rect.w / 8))),
                hp, hpp.c_str());
    }
}



void ESP::Utils::DrawCircle(float X, float Y, float radius, bool filled, float color[4]) {
    auto background = ImGui::GetBackgroundDrawList();
    if (background) {
        if (filled) {
            background->AddCircleFilled(ImVec2(X, Y), radius,
                                        ESP::Utils::Float2Color(color));
        } else {
            background->AddCircle(ImVec2(X, Y), radius,
                                  ESP::Utils::Float2Color(color));
        }
    }
}

void ESP::Utils::DrawText(ImVec2 position, ImVec4 color, const char *text) {
    auto background = ImGui::GetBackgroundDrawList();
    if (background) {
        background->AddText(NULL, 25.0f, position,
                            ImColor(color.x, color.y, color.z, color.w), text);
    }
}

