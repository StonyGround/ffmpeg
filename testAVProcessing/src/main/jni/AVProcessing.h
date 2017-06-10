/* DO NOT EDIT THIS FILE - it is machine generated */
/* Header for class com_xiuxiu_util_AVProcessing */

#ifndef _Included_com_xiuxiu_util_AVProcessing
#define _Included_com_xiuxiu_util_AVProcessing
#include <jni.h>
#include <android/log.h>
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/opt.h"
#include "libavutil/imgutils.h"
#include "libavutil/mathematics.h"
#include "libswresample/swresample.h"
#include "libswscale/swscale.h"

#define RESULT_OK      0
#define RESULT_ERROR  -1

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    yuv2rgb
 * Signature: (I[III)V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_yuv2rgb
  (JNIEnv *, jclass, jint, jintArray, jint, jint);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    copyYUVData
 * Signature: (I[B[B[BI)V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_copyYUVData
  (JNIEnv *, jclass, jint, jbyteArray, jbyteArray, jbyteArray, jint);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    copyFrameData
 * Signature: (I[BI)V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_copyFrameData
  (JNIEnv *, jclass, jint, jbyteArray, jint);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    setRotateClipFunc
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_setRotateClipFunc
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    rotateClipYUV
 * Signature: ([B[BII)V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_rotateClipYUV
  (JNIEnv *, jclass, jbyteArray, jbyteArray, jint, jint, jboolean);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    initAudioEncode
 * Signature: (Ljava/lang/String;II)I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_initAudioEncode
  (JNIEnv *, jclass, jstring, jint, jint);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    uninitAudioEncode
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_uninitAudioEncode
  (JNIEnv *, jclass);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    encodeAudioFrame
 * Signature: ([BI)V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_encodeAudioFrame
  (JNIEnv *, jclass, jbyteArray, jint);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    mergeAudioFiles
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_mergeAudioFiles
  (JNIEnv *, jclass, jstring, jstring);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    muxAVFile
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;D)I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_muxAVFile
  (JNIEnv *, jclass, jstring, jstring, jstring, jdouble);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    extractAVFile
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;D)I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_extractAVFile
  (JNIEnv *, jclass, jstring, jstring, jstring, jdouble);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    mixAudioWithSong
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_mixAudioWithSong
  (JNIEnv *, jclass, jstring, jstring, jstring);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    mixAudioWithSong2
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;D)I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_mixAudioWithSong2
  (JNIEnv *, jclass, jstring, jstring, jstring, jdouble);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    getVideoFrameRate
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_getVideoFrameRate
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    initVideoEncode
 * Signature: (Ljava/lang/String;II)I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_initVideoEncode
  (JNIEnv *, jclass, jstring, jint, jint);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    uninitVideoEncode
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_uninitVideoEncode
  (JNIEnv *, jclass);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    encodeVideoFrames
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_encodeVideoFrames
  (JNIEnv *, jclass, jbyteArray);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    initVideoDecode
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_initVideoDecode
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    uninitVideoDecode
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_uninitVideoDecode
  (JNIEnv *, jclass);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    decodeVideo2Frame
 * Signature: ([B[B[BI)D
 */
JNIEXPORT jdouble JNICALL Java_com_xiuxiu_util_AVProcessing_decodeVideo2Frame
  (JNIEnv *, jclass, jbyteArray, jbyteArray, jbyteArray, jint);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    saveDataFrame
 * Signature: ([BI)I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_saveDataFrame
  (JNIEnv *, jclass, jbyteArray, jint);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    deleteDataFrame
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_deleteDataFrame
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    openFrameFile
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_openFrameFile
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    closeFrameFile
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_closeFrameFile
  (JNIEnv *, jclass);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    readFrameData
 * Signature: ([BI)I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_readFrameData
  (JNIEnv *, jclass, jbyteArray, jint);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    createBlurShaderProgram
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_createBlurShaderProgram
  (JNIEnv *, jclass);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    createLogoShaderProgram
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_createLogoShaderProgram
  (JNIEnv *, jclass);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    createCopyShaderProgram
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_createCopyShaderProgram
  (JNIEnv *, jclass);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    createMainShaderProgram
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_createMainShaderProgram
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    useShaderProgram
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_useShaderProgram
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    getShaderHandle
 * Signature: (Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_getShaderHandle
  (JNIEnv *, jclass, jstring, jint);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    deleteShaderProgram
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_deleteShaderProgram
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    initFBO
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_initFBO
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    bindFBO
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_bindFBO
  (JNIEnv *, jclass);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    useFBOTexture
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_useFBOTexture
  (JNIEnv *, jclass);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    deleteFBO
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_deleteFBO
  (JNIEnv *, jclass);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    deleteFile
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_deleteFile
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    deleteFiles
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_deleteFiles
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_xiuxiu_util_AVProcessing
 * Method:    copyFile
 * Signature: (Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_copyFile
  (JNIEnv *, jclass, jstring, jstring);

#ifdef __cplusplus
}
#endif
#endif
