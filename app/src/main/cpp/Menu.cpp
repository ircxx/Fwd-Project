//
// Created by ircxx on 7/8/2023.
//
#include "Menu.h"
#include "Hack/Configuration/ConfigManager.h"
#include "Hack/Declarations.h"
#include "Unity/Screen.h"
#include "ImGui/imgui.h"
#include "Obfuscation/Obfuscate.h"

static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
struct
{
    int C_Menu = 0;
    int ShootMenu = 1;
    int VisualsMenu = 2;
    int SkinChanger = 3;
    int ConfigMenu = 4;
}MenuPage;

void DoStyle() {
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(255, 0, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0, 0, 0, 0));
}

void EndDoStyle() {
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
}
const char* ChamsTypes[] = {"None", "Color", "Wireframe", "Glow", "Shading", "Outline" };
const char* LinePositions[] = {OBFUSCATE("Up"), OBFUSCATE("Center"), OBFUSCATE("Down")};
const char* BoxTypes[] = {OBFUSCATE("Normal"), OBFUSCATE("Outline")};
const char* SilentPositions[] = {OBFUSCATE("Head"), OBFUSCATE("Hip")};
const char* GlovesTypes[] = {OBFUSCATE("None"), OBFUSCATE("Forest"), OBFUSCATE("Hex"), OBFUSCATE("Snake"), OBFUSCATE("Maze"), OBFUSCATE("Disco"), OBFUSCATE("Joker"), OBFUSCATE("Hazard" ), OBFUSCATE("Gore"), OBFUSCATE("Crosshairs" ), OBFUSCATE("KazamGlove"), OBFUSCATE("Ramses"), OBFUSCATE("Infected"), OBFUSCATE("Quadratic"), OBFUSCATE("Leopard"), OBFUSCATE("Mechanism"), OBFUSCATE("Blaze"), OBFUSCATE("Boss"), OBFUSCATE("Desert"), OBFUSCATE("Hornet"), OBFUSCATE("Prince"), OBFUSCATE("Luxus"), OBFUSCATE("Retro"), OBFUSCATE("Haunted"), OBFUSCATE("Witch"), OBFUSCATE("Scarecrow"), OBFUSCATE("Skeleton"), OBFUSCATE("Spider"), OBFUSCATE("Zombie"), OBFUSCATE("Ghost"), OBFUSCATE("Pumpkin"), OBFUSCATE("Tiger"), OBFUSCATE("Node"), OBFUSCATE("Volcanic"), OBFUSCATE("Goth"), OBFUSCATE("Nuclear"), OBFUSCATE("Bamboo"), OBFUSCATE("Nexus"), OBFUSCATE("Disco2"), OBFUSCATE("Waves"), OBFUSCATE("Brazil"), OBFUSCATE("Season1"), OBFUSCATE("Season2"), OBFUSCATE("Loyalty"), OBFUSCATE("Season3"), OBFUSCATE("BattleOfGlory"), OBFUSCATE("Hitman"), OBFUSCATE("Overpowered"), OBFUSCATE("Cosmos"), OBFUSCATE("GoldSnake"), OBFUSCATE("Feather"), OBFUSCATE("NineLives"), OBFUSCATE("Danger")};

//LinePosition sLinePosition;
//BoxType mBoxType;
void Menu::DrawMenu() {
    {
        ImGuiStyle& style = ImGui::GetStyle();

        style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

        ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(ImColor(0, 0, 0)));
        ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(ImColor(0, 0, 0)));
        ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(ImColor(0, 0, 0)));

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // making no spacing to widgets


        ImGui::Begin(OBFUSCATE("BlacKWelL [ircxx]"), NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize);

        ImGui::SetWindowSize(ImVec2(Unity::Screen::Width.get() /2.3, Unity::Screen::Height.get() / 2.5));

        ImGui::PopStyleVar(); // end

        style.WindowMenuButtonPosition = -1; // Hide Arrow Button of Window Menu
        style.WindowRounding = 12; // Round Borders

        ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(255, 0, 0))); // separator red

        ImGui::Separator(); // making separator

        ImGui::PopStyleColor();

        DoStyle();
        ImGui::BeginChild(OBFUSCATE(" "), ImVec2(ImGui::GetWindowWidth() / 4, ImGui::GetWindowSize().y), true); // begin a child window

        /*if (ImGui::TreeNode("Main"))
        {

            if (ImGui::Button("Player")) Menu.C_Menu = Menu.PlayerMenu;

            if (ImGui::Button("Weapon")) Menu.C_Menu = Menu.WeaponMenu;

            if (ImGui::Button("Knife")) Menu.C_Menu = Menu.KnifeMenu;

            if (ImGui::Button("Gloves")) Menu.C_Menu = Menu.GlovesMenu;

            ImGui::TreePop();

        }

        if (ImGui::TreeNode("Visual"))
        {

            if (ImGui::Button("ESP")) Menu.C_Menu = Menu.EspMenu;

            if (ImGui::Button("Chams")) Menu.C_Menu = Menu.ChamsMenu;

            ImGui::TreePop();

        }

        if (ImGui::TreeNode("Misc"))
        {

            if (ImGui::Button("Config")) Menu.C_Menu = Menu.ConfigMenu;

            ImGui::TreePop();

        }*/

        if (ImGui::Selectable(OBFUSCATE("Shoot"))) MenuPage.C_Menu = MenuPage.ShootMenu;
        //ImGui::SetCursorScreenPos(ImVec2(combo_pos.x + style.FramePadding.x, combo_pos.y + style.FramePadding.y));
        //float h = ImGui::GetTextLineHeightWithSpacing() ;
        //ImGui::Image(my_texture, ImVec2(h, h));
        //ImGui::SameLine();

        if (ImGui::Selectable(OBFUSCATE("Visuals"))) MenuPage.C_Menu = MenuPage.VisualsMenu;
        if (ImGui::Selectable(OBFUSCATE("Skins"))) MenuPage.C_Menu = MenuPage.SkinChanger;
        //if (ImGui::Selectable("Chams")) Menu.C_Menu = Menu.ChamsMenu;
        if (ImGui::Selectable(OBFUSCATE("Config"))) MenuPage.C_Menu = MenuPage.ConfigMenu;

        ImGui::EndChild();

        ImGui::SameLine();

        //
        ImGui::BeginChild(OBFUSCATE("  "), ImVec2(ImGui::GetContentRegionAvail().x - 5.0f/* - (ImGui::GetWindowWidth() / 4 )) / 2*/  , ImGui::GetWindowSize().y - 30.0f), true);

        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(ImColor(108,111,111, 130)));
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(ImColor(108, 111, 111, 130)));
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(ImColor(0,0,0)));
        ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(ImColor(199, 46, 46)));


        //const char* ComboChamsPreview = ChamsTypes[configManager->G_Config.ChamsConfig.CurrentChamsType];


        //int i = SizeContents.x;
        switch (MenuPage.C_Menu)
        {
            case 1:
                //ImGui::CheckboxX("Aimbot", &G_Config.PlayerConfig.Aim);
                //ImGui::Checkbox("Aim per fire", &configManager->G_Config.SilentConfigPlayerConfig.Aim);
                ImGui::Checkbox(OBFUSCATE("Enable"), &(configManager->G_Config.SilentConfig.Enable));
                //ImGui::Combo()
                ImGui::Combo(OBFUSCATE("Shot to"),
                             &configManager->G_Config.SilentConfig.PositionBullet,
                             SilentPositions, IM_ARRAYSIZE(SilentPositions));

                ImGui::SliderFloat(OBFUSCATE("Fov"), &(configManager->G_Config.SilentConfig.Fov), 0, 360);
                ImGui::Checkbox(OBFUSCATE("Draw Line"), &(configManager->G_Config.SilentConfig.DrawLine));
                ImGui::Checkbox(OBFUSCATE("Draw Fov"), &(configManager->G_Config.SilentConfig.DrawFov));

                //ImGui::SliderInt("Gloves", &(configManager->G_Config.SilentConfig.Gloves), 0, 52);


                break;

            case 2:
                //if(ImGui::BeginMainMenuBar()){
                    //if(ImGui::BeginMenu("ESP")) {
                        //ImGui::Text("Esps");
                        //ImGui::Separator();
                        ImGui::Checkbox(OBFUSCATE("Esp Line"), &(configManager->G_Config.ESPConfig.Line));
                        ImGui::SameLine();
                        ImGui::Combo(OBFUSCATE("Line Position"),
                                     &configManager->G_Config.ESPConfig.LinePosition.Current,
                                     LinePositions, IM_ARRAYSIZE(LinePositions));

                        ImGui::Checkbox(OBFUSCATE("Esp Box"), &configManager->G_Config.ESPConfig.Box);
                        ImGui::SameLine();
                        ImGui::Combo(OBFUSCATE("Box Type"),
                                     &configManager->G_Config.ESPConfig.mBoxType.Current,
                                     BoxTypes, IM_ARRAYSIZE(BoxTypes));
                        ImGui::ColorEdit3(OBFUSCATE("Color"), configManager->G_Config.ESPConfig.LineBoxColor,
                                          ImGuiColorEditFlags_NoInputs |
                                          ImGuiColorEditFlags_NoBorder);


                        ImGui::Checkbox(OBFUSCATE("Esp Health"), &configManager->G_Config.ESPConfig.Health);
                        ImGui::SameLine();
                        ImGui::Checkbox(OBFUSCATE("Draw Text"),
                                        &configManager->G_Config.ESPConfig.DrawHealthText);


                       /* ImGui::Checkbox(OBFUSCATE("Esp Distance"),
                                        &configManager->G_Config.ESPConfig.Distance);
                        ImGui::SameLine();
                        ImGui::Checkbox(OBFUSCATE("Esp Name"), &configManager->G_Config.ESPConfig.Name);

                        ImGui::ColorEdit3(OBFUSCATE("Color "),
                                          configManager->G_Config.ESPConfig.NameDistanceColor,
                                          ImGuiColorEditFlags_NoInputs |
                                          ImGuiColorEditFlags_NoBorder);*/

                        ImGui::Checkbox(OBFUSCATE("Esp Skeleton"),
                                        &configManager->G_Config.ESPConfig.Skeleton);
                        //ImGui::SameLine();
                        ImGui::ColorEdit3(OBFUSCATE("Color   "),
                                          configManager->G_Config.ESPConfig.SkeletonColor,
                                          ImGuiColorEditFlags_NoInputs |
                                          ImGuiColorEditFlags_NoBorder);
                        //ImGui::EndMenu();
                    //}

                    //if(ImGui::BeginMenu("Chams")) {
                        //ImGui::Text("Chams");
                        //ImGui::Separator();

                       /* ImGui::Combo("Chams Type",
                                     &configManager->G_Config.ChamsConfig.CurrentChamsType,
                                     ChamsTypes, IM_ARRAYSIZE(ChamsTypes));

                        ImGui::ColorEdit3("Color    ", configManager->G_Config.ChamsConfig.Color,
                                          ImGuiColorEditFlags_NoInputs |
                                          ImGuiColorEditFlags_NoBorder);
                        ImGui::SameLine(ImGui::GetWindowWidth() - 170);
                        ImGui::Checkbox("Rainbow", &configManager->G_Config.ChamsConfig.Rainbow);

                        ImGui::PushItemWidth(140.0f);
                        ImGui::SliderInt("Outline Width",
                                         &configManager->G_Config.ChamsConfig.OutlineWidth, 0, 10);

                        ImGui::SliderInt("Wireframe Width",
                                         &configManager->G_Config.ChamsConfig.WireframeWidth, 0,
                                         10);
                        ImGui::PopItemWidth();*/
                       // ImGui::EndMenu();
                   // }

                    //ImGui::EndMainMenuBar();
                //}

                break;


            case 3:
                ImGui::Combo(OBFUSCATE("Gloves"),
                             &configManager->G_Config.GlovesConfig.CurrentGlovesType,
                             GlovesTypes, IM_ARRAYSIZE(GlovesTypes));

                break;
            case 4:

                //ImGui::CheckboxX("Save Config", &Config.save);
                if (ImGui::Button(OBFUSCATE("Save Config"))) {
                    configManager->WriteConfiguration();
                    //ImGuiToast Save(ImGuiToastType_Success, 2000);
                    //Save.set_title2("Sucess");
                    //Save.set_content("Configuration Saved Sucessfully");
                    //ImGui::InsertNotification(Save);
                }

                if (ImGui::Button(OBFUSCATE("Load Config"))) {
                    configManager->ReadConfiguration();
                    //ImGuiToast Load(ImGuiToastType_Success, 2000);
                    //Load.set_title2("Sucess");
                    //Load.set_content("Configuration Loaded Sucessfully");
                    //ImGui::InsertNotification(Load);
                }

                //ImGui::CheckboxX("Load Config On Start", &G_Config.loadOnStart);

                break;

        }


        ImGui::PopStyleColor(4);

        ImGui::EndChild();

        ImGui::SameLine();
        EndDoStyle();
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f); // Round borders
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f)); // Background color
        ImGui::PopStyleVar(1); // Don't forget to Pop()
        ImGui::PopStyleColor(1);



        ImGui::End();
        ImGui::PopStyleColor(3);
    }
}
