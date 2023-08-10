#include <EGL/egl.h> // need to make a common.h that contains all these headers cuz this is nasty
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <fstream>
#include <sstream>
#include "nlohmann/json.hpp"
#include "Misc/Logging.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_android.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Obfuscation/Obfuscate.h"
#include <stdio.h>
#include <android/native_window_jni.h>
#include <jni.h>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <dlfcn.h>
#include "Misc/JNIStuff.h"
#include "Misc/FileWrapper.h"
#include "Misc/Utils.h"
//#include "ByNameModding/BNM.hpp"
#include "Obfuscation/Custom_Obfuscate.h"
#include "Unity/Unity.h"
#include "Misc/FunctionPointers.h"
#include "Hooking/Hooks.h"
#include "Misc/ImGuiStuff.h"
#include "Menu.h"
#include "Hooking/JNIHooks.h"
#include "Unity/Screen.h"
#include "Unity/Input.h"
#include "Hack/EntityListManager/EntityListManager.h"
#include "Hack/Player/Player.h"
#include "Hack/Declarations.h"
#include "Misc/ESP.h"

EntityListManager *entityListManager;

ConfigManager* configManager;
ClosestEnemyManager* closestEnemyManager;


void DrawImGui() {
    if (init && Unity::Screen::is_done) {
        ImGuiIO &io = ImGui::GetIO();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplAndroid_NewFrame(Unity::Screen::Width.get(), Unity::Screen::Height.get());
        ESP::DrawESP();
        Menu::DrawMenu();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGui::EndFrame();

    }
}


EGLBoolean (*old_eglSwapBuffers)(...);
EGLBoolean new_eglSwapBuffers(EGLDisplay _display, EGLSurface _surface) {
    SetupImGui();
    DrawImGui();
    return old_eglSwapBuffers(_display, _surface);
}
bool emulator = true;
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void * reserved)
{
    jvm = vm;
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if(!emulator){
        UnityPlayer_cls = env->FindClass(OBFUSCATE("com/unity3d/player/UnityPlayer"));
        UnityPlayer_CurrentActivity_fid = env->GetStaticFieldID(UnityPlayer_cls,
                                                                OBFUSCATE("currentActivity"),
                                                                OBFUSCATE("Landroid/app/Activity;"));
        hook((void *) env->functions->RegisterNatives, (void *) hook_RegisterNatives,
             (void **) &old_RegisterNatives);
    }

    configManager = new ConfigManager(getCacheDir(env));

    return JNI_VERSION_1_6;
}

static void *handle;
bool mlovinit(){
    handle = NULL;
    handle = dlopen(OBFUSCATE("libGLESv2.so"), RTLD_LAZY);
    if(!handle){
        //LOGE(OBFUSCATE("Cannot open library: %s"), dlerror());
        return false;
    }
    return true;
}


Player* ClosestEnemy;
Player *LocalPlayer;

Vector3 delta;

void (*SilentAim)(void *inst, Player *damager, Vector3 origin, Vector3 direction, int type, Vector3 visualOrigin);
void _SilentAim(void *inst, Player *damager, Vector3 origin,  Vector3 direction, int type, Vector3 visualOrigin) {
    if (damager == LocalPlayer) {
        if (ClosestEnemy != nullptr && configManager->G_Config.SilentConfig.Enable) {
            if(configManager->G_Config.SilentConfig.PositionBullet == 0) {
                delta.x = ClosestEnemy->getPlayerData()->HeadPosition.x - origin.x;
                delta.y = ClosestEnemy->getPlayerData()->HeadPosition.y - origin.y;
                delta.z = ClosestEnemy->getPlayerData()->HeadPosition.z - origin.z;
            }else if(configManager->G_Config.SilentConfig.PositionBullet == 1){
                delta.x = ClosestEnemy->getPlayerData()->SpinePosition.x - origin.x;
                delta.y = ClosestEnemy->getPlayerData()->SpinePosition.y - origin.y;
                delta.z = ClosestEnemy->getPlayerData()->SpinePosition.z - origin.z;
            }
            SilentAim(inst, damager, origin, delta, type, visualOrigin);
        } else {
            SilentAim(inst, damager, origin, direction, type, visualOrigin);
        }
    } else {
        SilentAim(inst, damager, origin, direction, type, visualOrigin);
    }
}




void (*old_PlayerUpdate)(Player *instance);
void PlayerUpdate(Player *instance) {
    if (IsUnityObjectAlive(instance)) {
        if (Pointers::isMine[(void *)instance]()) {
            LocalPlayer = instance;
            LocalPlayer->Update(Pointers::Team[(void *)instance]());
        } else if(LocalPlayer != nullptr && (Pointers::Team[(void *)instance]() != LocalPlayer->getPlayerData()->Team)) {
            entityListManager->Add((Player *) instance);
            instance->Update(LocalPlayer->getPlayerData()->Team);
            ClosestEnemy = closestEnemyManager->GetClosestEnemy(LocalPlayer);
            entityListManager->Manage();
        }
    }
    old_PlayerUpdate(instance);
}



void (*old_GetGloveCamo)(void *inst, int CamoType);
void GetGloveCamo(void *inst, int CamoType) {
    old_GetGloveCamo(inst, configManager->G_Config.GlovesConfig.CurrentGlovesType);
}

void (*old_GetGlovesMaterial)(void *inst, int CamoType, void *Material);
void GetGlovesMaterial(void *inst, int CamoType, void *Material) {

    old_GetGlovesMaterial(inst, configManager->G_Config.GlovesConfig.CurrentGlovesType, Material);
}

void (*old_FirstPersonHandsTextureUpdate)(void *inst);
void FirstPersonHandsTextureUpdate(void *inst) {
//	private GlovesController.GloveCamo KMJKJJAACKG; // 0x24

    //LOGI("old_FirstPersonHandsTextureUpdate Type");
    *(bool *)((long) inst + 0x1C) = true;
    *(int *)((long) inst + 18) = 32;
    old_FirstPersonHandsTextureUpdate(inst);
}


void (*old_MatchRestarted)(void *inst);
void MatchRestarted(void *inst) {
    entityListManager->RemoveAll();
    old_MatchRestarted(inst);
}

void (*old_MatchCompleted)(void *inst, int idk);
void MatchCompleted(void *inst, int idk) {
    entityListManager->RemoveAll();
    old_MatchCompleted(inst, idk);
}

void (*old_MatchOnLeftRoom)(void *inst);
void MatchOnLeftRoom(void *inst) {
    entityListManager->RemoveAll();
    old_MatchOnLeftRoom(inst);
}


void (*old_MatchOnDestroy)(void *inst);
void MatchOnDestroy(void *inst) {
    entityListManager->RemoveAll();
    old_MatchOnDestroy(inst);
}


void (*old_PlayerOnDestroy)(Player *player);
void PlayerOnDestroy(Player *player) {
    entityListManager->RemoveGivenPlayer(player);
    old_PlayerOnDestroy(player);
}


void *hack_thread(void *)
{
    using namespace BNM;
    do {
        sleep(1);
    } while (!Il2cppLoaded() && mlovinit());
    AttachIl2Cpp(); // this is required when you use bynamemodding functions

    entityListManager = new EntityListManager();
    closestEnemyManager = new ClosestEnemyManager();

    auto addr = (uintptr_t)dlsym(RTLD_NEXT, OBFUSCATE("eglSwapBuffers"));
    HOOK(addr, new_eglSwapBuffers, old_eglSwapBuffers);

    Unity::Screen::Setup();
    if(emulator){
        Unity::Input::Setup();
    }
    Pointers::LoadPointers();
    //Player::Setup();
    BNM::LoadClass MatchManager = BNM::LoadClass(OBFUSCATES_BNM(""), OBFUSCATES_BNM("MatchManager"));

    BNM::LoadClass GlovesController = BNM::LoadClass(OBFUSCATES_BNM(""), OBFUSCATES_BNM("GlovesController"));
    HOOK(MatchManager.GetMethodByName(OBFUSCATES_BNM("MatchRestarted"), 0).GetOffset(), MatchRestarted, old_MatchRestarted);
    HOOK(MatchManager.GetMethodByName(OBFUSCATES_BNM("MatchCompleted"), 1).GetOffset(), MatchCompleted, old_MatchCompleted);
    HOOK(MatchManager.GetMethodByName(OBFUSCATES_BNM("OnLeftRoom"), 0).GetOffset(), MatchOnLeftRoom, old_MatchOnLeftRoom);
    HOOK(MatchManager.GetMethodByName(OBFUSCATES_BNM("OnDestroy"), 0).GetOffset(), MatchOnDestroy, old_MatchOnDestroy);


    HOOK(GlovesController.GetMethodByName(OBFUSCATES_BNM("GetGloveCamo"), 1).GetOffset(), GetGloveCamo, old_GetGloveCamo);
    HOOK(GlovesController.GetMethodByName(OBFUSCATES_BNM("GetGlovesMaterial"), 2).GetOffset(), GetGlovesMaterial, old_GetGlovesMaterial);

    HOOK(Pointers::BulletManager.GetMethodByName(OBFUSCATES_BNM("FireBullet"), 5).GetOffset(), _SilentAim, SilentAim);
    HOOK(Pointers::PlayerClz.GetMethodByName(OBFUSCATES_BNM("Update"), 0).GetOffset(), PlayerUpdate, old_PlayerUpdate);
    HOOK(Pointers::PlayerClz.GetMethodByName(OBFUSCATES_BNM("OnDestroy"), 0).GetOffset(), PlayerOnDestroy, old_PlayerOnDestroy);

    DetachIl2Cpp(); // remember to detach when you are done using bynamemodding functions
    return NULL;
}
__attribute__((constructor))
void lib_main()
{
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}
