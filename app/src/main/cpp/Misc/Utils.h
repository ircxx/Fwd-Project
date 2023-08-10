#ifndef UTILS_H
#define UTILS_H
#include "../Hooking/dobby.h"
#include <jni.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include "Obfuscation/Obfuscate.h"
#include "JNIStuff.h"

typedef unsigned long DWORD;
static DWORD libBase;

DWORD findLibrary(const char *library);
DWORD getAbsoluteAddress(const char* libraryName, DWORD relativeAddr);
DWORD getRealOffset(DWORD offset);
bool isLibraryLoaded(const char *libraryName);
void hook(void *orig_fcn, void* new_fcn, void **orig_fcn_ptr);

DWORD findLibrary(const char *library)
{
    char filename[0xFF] = {0},
            buffer[1024] = {0};
    FILE *fp = NULL;
    DWORD address = 0;
    const char *selfmaps = OBFUSCATE("/proc/self/maps");
    sprintf(filename, OBFUSCATE("%s"), selfmaps);
    fp = fopen(filename, OBFUSCATE("rt"));
    if (fp == NULL)
    {
        perror(OBFUSCATE("fopen"));
        goto done;
    }

    while (fgets(buffer, sizeof(buffer), fp))
    {
        if (strstr(buffer, library))
        {
            address = (DWORD) strtoul(buffer, NULL, 16);
            goto done;
        }
    }

    done:

    if (fp)
    {
        fclose(fp);
    }

    return address;
}
DWORD getAbsoluteAddress(const char* libraryName, DWORD relativeAddr)
{
    if (libBase == 0)
        libBase = findLibrary(libraryName);
    if (libBase != 0)
        return (reinterpret_cast<DWORD>(libBase + relativeAddr));
    else
        return 0;
}
DWORD getRealOffset(DWORD offset)
{
    if (libBase == 0)
        libBase = findLibrary(OBFUSCATE("libil2cpp.so"));
    if (libBase != 0)
        return (reinterpret_cast<DWORD>(libBase + offset));
    else
        return 0;
}

bool isLibraryLoaded(const char *libraryName)
{
    char line[512] = {0};
    FILE *fp = fopen(OBFUSCATE("/proc/self/maps"), OBFUSCATE("rt"));
    if (fp != NULL)
    {
        while (fgets(line, sizeof(line), fp))
        {
            if (strstr(line, libraryName))
                return true;
        }
        fclose(fp);
    }
    return false;
}

uintptr_t string2Offset(const char *c)
{
    int base = 16;
    // See if this function catches all possibilities.
    // If it doesn't, the function would have to be amended
    // whenever you add a combination of architecture and
    // compiler that is not yet addressed.
    static_assert(sizeof(uintptr_t) == sizeof(unsigned long)
                  || sizeof(uintptr_t) == sizeof(unsigned long long),
                  "Please add string to handle conversion for this architecture.");

    // Now choose the correct function ...
    if (sizeof(uintptr_t) == sizeof(unsigned long))
    {
        return strtoul(c, nullptr, base);
    }

    // All other options exhausted, sizeof(uintptr_t) == sizeof(unsigned long long))
    return strtoull(c, nullptr, base);
}



static std::string getCacheDir(JNIEnv *_env)
{

    jobject this_obj = getGlobalContext(_env);
    jclass context_class = _env->FindClass("android/content/Context");
    jmethodID get_cache_dir_method = _env->GetMethodID(context_class, "getCacheDir", "()Ljava/io/File;");
    jobject cache_dir_obj = _env->CallObjectMethod(this_obj, get_cache_dir_method);
    jclass file_class = _env->FindClass("java/io/File");
    jmethodID get_absolute_path_method = _env->GetMethodID(file_class, "getAbsolutePath", "()Ljava/lang/String;");
    jstring cache_dir_path_obj = (jstring)_env->CallObjectMethod(cache_dir_obj, get_absolute_path_method);
    const char* cache_dir_path = _env->GetStringUTFChars(cache_dir_path_obj, nullptr);
    std::string result(cache_dir_path);
    _env->ReleaseStringUTFChars(cache_dir_path_obj, cache_dir_path);
    return result;
}

void hook(void *orig_fcn, void* new_fcn, void **orig_fcn_ptr)
{
    DobbyHook(orig_fcn, new_fcn, orig_fcn_ptr);
}
std::string readTextFile(std::string path)
{
    FILE    *textfile;
    char    *text;
    long    numbytes;
    textfile = fopen(path.c_str(), "r");
    if(textfile == NULL)
        return "ERROR";

    fseek(textfile, 0L, SEEK_END);
    numbytes = ftell(textfile);
    fseek(textfile, 0L, SEEK_SET);

    text = (char*)calloc(numbytes, sizeof(char));
    if(text == NULL)
        return "ERROR";

    fread(text, sizeof(char), numbytes, textfile);
    fclose(textfile);
    return text;
}
#endif
