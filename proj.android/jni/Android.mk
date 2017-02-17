LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)





LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Scenes/HelloWorldScene.cpp \
                   ../../Classes/Systems/Collision.cpp \
                   ../../Classes/Systems/CollisionNode.cpp \
                   ../../Classes/Scenes/GameOverScene.cpp \
                   ../../Classes/Systems/GameSystem.cpp \
                   ../../Classes/Objects/Obj3d.cpp \
                   ../../Classes/Objects/Player.cpp \
                   ../../Classes/Objects/Enemy.cpp \
                   ../../Classes/Camera/Satellite.cpp \
                   ../../Classes/Systems/ReadySetGo.cpp \
                   ../../Classes/Scenes/TitleScene.cpp \
                   ../../Classes/Scenes/LogoScene.cpp \
                   ../../Classes/Objects/Radar.cpp \
                   ../../Classes/Objects/Dot.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
