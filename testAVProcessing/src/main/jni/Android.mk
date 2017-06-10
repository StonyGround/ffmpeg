LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := ffmpeg
LOCAL_SRC_FILES := prebuilt/libffmpeg.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := AVProcessing
LOCAL_SRC_FILES := EncodeAudio.c       \
                   EncodeVideo.c       \
                   MuxAVFile.c         \
                   MixAudioWithSong.c  \
                   MixAudioWithSong2.c \
                   YUVConvert.c        \
                   ShaderManager.c     \
                   ExtractAVFile.c     \
                   DecodeVideo2Frame.c \
                   Util.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_LDLIBS := -llog -ljnigraphics -lz -landroid -lGLESv2
LOCAL_SHARED_LIBRARIES := ffmpeg

include $(BUILD_SHARED_LIBRARY)