#include "../pch.h"
#include "load.h"
#include "../GlobalVars.h"
#include "Obfuscation/Obfuscate.h"

/**** Global Pointers ****/
void* UnityHandle = nullptr;
void* Il2cppHandle = nullptr;


int loadLibrary(JNIEnv* env, const char* a2, const char* libName, void** libHandle)
{
    void* pre_libHandle;
    const struct JNINativeInterface* functions;
    char* errorStr;
    char* dl_error_str;
    JavaVM *vm;
    char errbuff[1024];
    char pathToLibrary[2048];
    /**** Function Pointer ****/
    int (*OnLoad)(JavaVM * vm, int);

    if (!*libHandle)
    {
        if (env->GetJavaVM(&vm) <= -1)
        {
            functions = env->functions;
            errorStr = OBFUSCATE("Unable to retrieve Java VM");
            goto throwFatalError;
        }
        
        //__android_log_print(ANDROID_LOG_INFO, "libmain", "suck suck %s a2 %s", libName, a2);
        snprintf(pathToLibrary, 0x7FFu, OBFUSCATE("%s/%s"), a2, libName);
   
        pre_libHandle = dlopen(pathToLibrary, 1);
        if (!pre_libHandle)
        {
            pre_libHandle = dlopen(libName, 1);
            if (!pre_libHandle)
            {
                dl_error_str = dlerror();
                snprintf(errbuff, 0x400u, OBFUSCATE("Unable to load library: %s [%s]"), pathToLibrary, dl_error_str);
                functions = env->functions;
                errorStr = errbuff;
                goto throwFatalError;
            }
        }
        OnLoad = (int (*)(JavaVM *, int))dlsym(pre_libHandle, OBFUSCATE("JNI_OnLoad"));
        if (OnLoad && OnLoad(vm, 0) >= 65543)
        {
            functions = env->functions;
            errorStr = OBFUSCATE("Unsupported VM version");
        throwFatalError:
            functions->FatalError(env, errorStr);
            return 0;
        }
        *libHandle = pre_libHandle;
    }
    return 0;
}




jboolean load(JNIEnv* env, jobject obj, jstring str) {

    size_t str_lenght;
    void* UnityNativeLibraryPath_str = nullptr;
    const char* UTFchars;
    bool loaded;

    //if ((sub_1D64(a1, a2) & 4) == 0)
    //    return false;
    str_lenght = env->GetStringUTFLength(str) + 1;
    UnityNativeLibraryPath_str = malloc(str_lenght);
    UTFchars = env->GetStringUTFChars(str, 0);
    memcpy(UnityNativeLibraryPath_str, UTFchars, str_lenght);
    env->ReleaseStringUTFChars(str, UTFchars);
    loadLibrary(env, (const char *)UnityNativeLibraryPath_str, OBFUSCATE("libunity.so"), &UnityHandle);
    loadLibrary(env, (const char *)UnityNativeLibraryPath_str, OBFUSCATE("libil2cpp.so"), &Il2cppHandle);
    free(UnityNativeLibraryPath_str);
    loaded = (bool)UnityHandle;
    if (UnityHandle) {
        loaded = true;
    }
    return loaded;
}