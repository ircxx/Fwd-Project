LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)
LOCAL_MODULE := libcurl
LOCAL_SRC_FILES := libs/armeabi-v7a/libcurl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libssl
LOCAL_SRC_FILES := libs/armeabi-v7a/libssl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libcrypto
LOCAL_SRC_FILES := libs/armeabi-v7a/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)
include $(CLEAR_VARS)

include $(CLEAR_VARS)

LOCAL_MODULE := libdobby

LOCAL_SRC_FILES := libs/armeabi-v7a/libdobby.a

include $(PREBUILT_STATIC_LIBRARY)
include $(CLEAR_VARS)

# Here is the name of your lib.
# When you change the lib name, change also on System.loadLibrary("") under OnCreate method on StaticActivity.java
# Both must have same name
LOCAL_MODULE    := ircxx

# Code optimization
LOCAL_CFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS += -fno-rtti -fno-exceptions -fpermissive
LOCAL_CPPFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror -s -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fms-extensions -frtti -fno-exceptions -fpermissive
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all, -llog
LOCAL_ARM_MODE := arm
LOCAL_CPP_FEATURES += exceptions

LOCAL_STATIC_LIBRARIES := libdobby libcurl libssl libcrypto

LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/ImGui


# Here you add the cpp file
LOCAL_SRC_FILES :=  native-lib.cpp\
                    Menu.cpp\
                    Hack/EntityListManager/EntityListManager.cpp\
                    Hack/Player/Player.cpp\
                    Hack/Configuration/ConfigManager.cpp\
                    Hack/ClosestEnemyManager/ClosestEnemyManager.cpp\
                    Unity/Screen.cpp\
                    Misc/FunctionPointers.cpp\
                    Misc/ESPUtils.cpp\
                    Misc/ESP.cpp\
	                Memory/KittyMemory.cpp \
	                Memory/MemoryPatch.cpp \
                   	Memory/MemoryBackup.cpp \
                    	Memory/KittyUtils.cpp \
             		ImGui/imgui.cpp \
             		ImGui/imgui_impl_android.cpp \
             		ImGui/imgui_impl_opengl3.cpp \
             		ImGui/imgui_tables.cpp \
             		ImGui/imgui_widgets.cpp \
             		ImGui/imgui_demo.cpp \
            	 	ImGui/imgui_draw.cpp \
             		ByNameModding/bnm.cpp \
        		Obfuscation/instr.cpp \
                        Crypt/AES.cpp \
                        Crypt/base64.cpp \
                        JSON/JSON.cpp \


LOCAL_LDLIBS := -llog -landroid  -lEGL -lGLESv2 -lGLESv3 -lz -fno-asm

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := main
# Code optimization
LOCAL_CFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS += -fno-rtti -fno-exceptions -fpermissive
LOCAL_CPPFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror -s -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fno-exceptions -fpermissive
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all, -llog
LOCAL_ARM_MODE := arm
LOCAL_CPP_FEATURES += exceptions

LOCAL_STATIC_LIBRARIES := libcurl libssl libcrypto
LOCAL_C_INCLUDES += $(LOCAL_PATH)
# Here you add the cpp file
LOCAL_SRC_FILES := libMain.cpp \
                   load/load.cpp\
                   unload/unload.cpp\
                   Crypt/AES.cpp \
                   Crypt/base64.cpp \
                   JSON/JSON.cpp \


LOCAL_LDLIBS := -llog -landroid -lz -fno-asm

include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)