//
// Created by ircxx on 7/8/2023.
//
#include "ESP.h"
#include "../Hack/Declarations.h"
#include "Unity/Screen.h"
#include "Logging.h"
#include "Obfuscation/Obfuscate.h"

LinePosition mLinePosition;
BoxType sBoxType;

void ESP::DrawESP() {

    ImGui::NewFrame();
    const auto flags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration |
                       ImGuiWindowFlags_NoInputs;

    ImGui::GetStyle().AntiAliasedFill = true;
    ImGui::GetStyle().AntiAliasedLines = true;


    ImGui::Begin(OBFUSCATE("overlay"), nullptr, flags);

    ImGui::SetWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(Unity::Screen::Width.get(), Unity::Screen::Height.get()),
                         ImGuiCond_Always);


    if (configManager->G_Config.SilentConfig.DrawFov) {
        ESP::Utils::DrawCircle(Unity::Screen::Width.get() / 2, Unity::Screen::Height.get() / 2,
                               configManager->G_Config.SilentConfig.Fov, false,
                               configManager->G_Config.ESPConfig.LineBoxColor);
    }

    for (Player *player: entityListManager->PlayerSet) {
        //ESP::Utils::DrawText(ImVec2(Unity::Screen::Width.get() / 2, Unity::Screen::Height.get() / 3), ImColor(255,255,255,255), std::to_string(entityListManager->PlayerSet.size()).c_str());

        if ((*(void **) ((long) player + 0x40)) != nullptr &&
            (*(void **) ((long) player + 0xA0)) != nullptr &&
            (*(void **) ((long) player + 0xA4)) != nullptr) {

            if (configManager->G_Config.SilentConfig.DrawLine) {
                if (ClosestEnemy != nullptr) {
                    Vector3 Head = ClosestEnemy->getPlayerData()->W2SHeadPosition;
                    if (Head.z < 1.f) continue;
                    ESP::Utils::DrawLine(
                            ImVec2(Unity::Screen::Width.get() / 2, Unity::Screen::Height.get() / 2),
                            ImVec2(Head.x, Unity::Screen::Height.get() - Head.y),
                            configManager->G_Config.ESPConfig.LineBoxColor);

                }
            }

            Vector3 Head = player->getPlayerData()->W2SHeadPosition;
            Vector3 Spine = player->getPlayerData()->W2SSpinePosition;
            Vector3 Hips = player->getPlayerData()->W2SHipsPosition;
            Vector3 LeftUpperArm = player->getPlayerData()->W2SLeftUpperArmPosition;
            Vector3 LeftLowerArm = player->getPlayerData()->W2SLeftLowerArmPosition;
            Vector3 RightUpperArm = player->getPlayerData()->W2SRightUpperArmPosition;
            Vector3 RightLowerArm = player->getPlayerData()->W2SRightLowerArmPosition;
            Vector3 LeftUpperLeg = player->getPlayerData()->W2SLeftUpperLegPosition;
            Vector3 LeftLowerLeg = player->getPlayerData()->W2SLeftLowerLegPosition;
            Vector3 RightUpperLeg = player->getPlayerData()->W2SRightUpperLegPosition;
            Vector3 RightLowerLeg = player->getPlayerData()->W2SRightLowerLegPosition;

            Vector3 HeadForBox = player->getPlayerData()->W2SHeadForBoxPosition;
            Vector3 ToeForBox = player->getPlayerData()->W2SToeForBoxPosition;
            if (Head.z < 1.f) continue;
            if (Spine.z < 1.f) continue;
            if (Hips.z < 1.f) continue;

            if (HeadForBox.z < 1.f) continue;
            if (ToeForBox.z < 1.f) continue;

            //if (LeftUpperArm.z < 1.f) continue;
            //if (LeftLowerArm.z < 1.f) continue;
            //if (RightUpperArm.z < 1.f) continue;
            //if (RightLowerArm.z < 1.f) continue;
            //if (LeftUpperLeg.z < 1.f) continue;
            //if (LeftLowerLeg.z < 1.f) continue;
            //if (RightUpperLeg.z < 1.f) continue;
            if (RightLowerLeg.z < 1.f) continue;

            float Height =
                    abs(HeadForBox.y - ToeForBox.y) * (1.0 / 1.0), Width =
                    Height * 0.60f;

            ImVec4 PlayerRect = ImVec4(HeadForBox.x - Width / 2.f,
                                       Unity::Screen::Height.get() - HeadForBox.y,
                                       Width, Height);

            //ImVec2 aaaa = ImGui::CalcTextSize(player->getPlayerData()->Name->c_str());
            //ESP::Utils::DrawText(ImVec2((PlayerRect.x + aaaa.x), (PlayerRect.y - (PlayerRect.w / 8))),
            //                     ImColor(255,255,255,255), player->getPlayerData()->Name->c_str());

            if (configManager->G_Config.ESPConfig.Line) {
                if (configManager->G_Config.ESPConfig.LinePosition.Current == mLinePosition.Up) {
                    ESP::Utils::DrawLine(
                            ImVec2(Unity::Screen::Width.get() / 2, 0),
                            ImVec2(HeadForBox.x, Unity::Screen::Height.get() - HeadForBox.y),
                            configManager->G_Config.ESPConfig.LineBoxColor);
                } else if (configManager->G_Config.ESPConfig.LinePosition.Current ==
                           mLinePosition.Center) {
                    ESP::Utils::DrawLine(
                            ImVec2(Unity::Screen::Width.get() / 2, Unity::Screen::Height.get() / 2),
                            ImVec2(ToeForBox.x, Unity::Screen::Height.get() - ToeForBox.y),
                            configManager->G_Config.ESPConfig.LineBoxColor);
                } else if (configManager->G_Config.ESPConfig.LinePosition.Current ==
                           mLinePosition.Down) {
                    ESP::Utils::DrawLine(
                            ImVec2(Unity::Screen::Width.get() / 2, Unity::Screen::Height.get()),
                            ImVec2(ToeForBox.x, Unity::Screen::Height.get() - ToeForBox.y),
                            configManager->G_Config.ESPConfig.LineBoxColor);
                }
            }

            if (configManager->G_Config.ESPConfig.Box) {
                if (configManager->G_Config.ESPConfig.mBoxType.Current == sBoxType.Normal) {
                    ESP::Utils::DrawBox(PlayerRect, configManager->G_Config.ESPConfig.LineBoxColor);

                } else if (configManager->G_Config.ESPConfig.mBoxType.Current == sBoxType.Outline) {
                    ESP::Utils::DrawBoxOutline(PlayerRect,
                                               configManager->G_Config.ESPConfig.LineBoxColor);

                }
            }

            if (configManager->G_Config.ESPConfig.Health) {
                ESP::Utils::DrawVerticalHealthBar(PlayerRect, 100, player->getPlayerData()->Health,
                                                  configManager->G_Config.ESPConfig.DrawHealthText);

            }

            if(configManager->G_Config.ESPConfig.Skeleton){

                //
                ESP::Utils::DrawLine(
                        ImVec2(Head.x, Unity::Screen::Height.get() - Head.y),
                        ImVec2(Spine.x, Unity::Screen::Height.get() - Spine.y),
                        configManager->G_Config.ESPConfig.SkeletonColor);

                // Columna Vertebral
                ESP::Utils::DrawLine(
                        ImVec2(Spine.x, Unity::Screen::Height.get() - Spine.y),
                        ImVec2(Hips.x, Unity::Screen::Height.get() - Hips.y),
                        configManager->G_Config.ESPConfig.SkeletonColor);

                // Parte Superior Brazo Izquierdo
                ESP::Utils::DrawLine(
                        ImVec2(Head.x, Unity::Screen::Height.get() - Head.y),
                        ImVec2(LeftUpperArm.x, Unity::Screen::Height.get() - LeftUpperArm.y),
                        configManager->G_Config.ESPConfig.SkeletonColor);
                // Parte Inferior Brazo Izquierdo
                ESP::Utils::DrawLine(
                        ImVec2(LeftUpperArm.x, Unity::Screen::Height.get() - LeftUpperArm.y),
                        ImVec2(LeftLowerArm.x, Unity::Screen::Height.get() - LeftLowerArm.y),
                        configManager->G_Config.ESPConfig.SkeletonColor);

                // Parte Superior Brazo Derecho
                ESP::Utils::DrawLine(
                        ImVec2(Head.x, Unity::Screen::Height.get() - Head.y),
                        ImVec2(RightUpperArm.x, Unity::Screen::Height.get() - RightUpperArm.y),
                        configManager->G_Config.ESPConfig.SkeletonColor);

                // Parte Inferior Brazo Derecho
                ESP::Utils::DrawLine(
                        ImVec2(RightUpperArm.x, Unity::Screen::Height.get() - RightUpperArm.y),
                        ImVec2(RightLowerArm.x, Unity::Screen::Height.get() - RightLowerArm.y),
                        configManager->G_Config.ESPConfig.SkeletonColor);

                // Cadera a parte superior Izquierda de la pierna
                ESP::Utils::DrawLine(
                        ImVec2(Hips.x, Unity::Screen::Height.get() - Hips.y),
                        ImVec2(LeftUpperLeg.x, Unity::Screen::Height.get() - LeftUpperLeg.y),
                        configManager->G_Config.ESPConfig.SkeletonColor);

                // parte superior Izquierda de la pierna a (parte baja Izquierda de la pierna)
                ESP::Utils::DrawLine(
                        ImVec2(LeftUpperLeg.x, Unity::Screen::Height.get() - LeftUpperLeg.y),
                        ImVec2(LeftLowerLeg.x, Unity::Screen::Height.get() - LeftLowerLeg.y),
                        configManager->G_Config.ESPConfig.SkeletonColor);

                // Cadera a parte superior Derecha de la pierna
                ESP::Utils::DrawLine(
                        ImVec2(Hips.x, Unity::Screen::Height.get() - Hips.y),
                        ImVec2(RightUpperLeg.x, Unity::Screen::Height.get() - RightUpperLeg.y),
                        configManager->G_Config.ESPConfig.SkeletonColor);

                // parte superior Derecha de la pierna a (parte baja Derecha de la pierna)
                ESP::Utils::DrawLine(
                        ImVec2(RightUpperLeg.x, Unity::Screen::Height.get() - RightUpperLeg.y),
                        ImVec2(RightLowerLeg.x, Unity::Screen::Height.get() - RightLowerLeg.y),
                        configManager->G_Config.ESPConfig.SkeletonColor);


            }
        }
    }

    ImGui::End();


}