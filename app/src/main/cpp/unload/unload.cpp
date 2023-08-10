#include "../pch.h"
#include "unload.h"
#include "../GlobalVars.h"
#include "Obfuscation/Obfuscate.h"

/**** Local Pointers ****/

void* m_UnityHandle = nullptr;
void* m_Il2cppHandle = nullptr;

/**** Functions Pointers ****/

void (*Il2cppUnload)(JavaVM*, int); 
void (*UnityUnload)(JavaVM*, int);

/****Java VM***/
JavaVM* vm;

jboolean unload(JNIEnv* env) {
    

    m_UnityHandle = UnityHandle;
    if (UnityHandle)
    {
        UnityHandle = 0;
        if (env->GetJavaVM(&vm) <= -1)
        {
            env->FatalError(OBFUSCATE("Unable to retrieve Java VM"));
        }
        else
        {
            UnityUnload = (void (*)(JavaVM*, int))dlsym(m_UnityHandle, OBFUSCATE("JNI_OnUnload"));
            if (UnityUnload)
                UnityUnload(vm, 0);
            dlclose(m_UnityHandle);
        }
    }

    m_Il2cppHandle = Il2cppHandle;
    if (Il2cppHandle)
    {
        Il2cppHandle = 0;
        if (env->GetJavaVM(&vm) <= -1)
        {
            env->FatalError(OBFUSCATE("Unable to retrieve Java VM"));
        }
        else
        {
            Il2cppUnload = (void (*)(JavaVM*, int))dlsym(m_Il2cppHandle, OBFUSCATE("JNI_OnUnload"));
            if (Il2cppUnload)
                Il2cppUnload(vm, 0);
            dlclose(m_Il2cppHandle);
        }
    }

	return true;
}