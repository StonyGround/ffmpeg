LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := avcodec
LOCAL_SRC_FILES := prebuilt/libavcodec-57.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avdevice
LOCAL_SRC_FILES := prebuilt/libavdevice-57.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avfilter
LOCAL_SRC_FILES := prebuilt/libavfilter-6.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avformat
LOCAL_SRC_FILES := prebuilt/libavformat-57.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avutil
LOCAL_SRC_FILES := prebuilt/libavutil-55.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := swresample
LOCAL_SRC_FILES := prebuilt/libswresample-2.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := swscale
LOCAL_SRC_FILES := prebuilt/libswscale-4.so
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
LOCAL_SHARED_LIBRARIES := avcodec avformat avutil swresample swscale
include $(BUILD_SHARED_LIBRARY)