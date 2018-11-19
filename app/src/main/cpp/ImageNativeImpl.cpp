//
// Created by 凌志 on 2018/11/8.
//
/**   
*    
* 项目名称：ImageJNI      
* 类描述：   
* 创建人：genesis   
* 创建时间：2018/11/8 2:48 PM   
* 修改人：genesis  
* 修改时间：2018/11/8 2:48 PM   
* 修改备注：   
* @version    
*    
*/
#include "ImageNativeImpl.h"
#include "BitmapFactory/BitmapParse/BitmapParse.h"
#include "BitmapFactory/GNCore.h"
#include "opencv/highgui.h"
#include "opencv/cv.h"
#include "opencv2/core/core_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/core/types_c.h"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/core/hal/interface.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/types.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;


JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nEdgeImage(JNIEnv* env, jclass type_, jobject bitmapIn,
                                                        jint type)
{
    GNBitmap* bitmap = praseBitmap(env, bitmapIn);
    int ret = 0;
    if (bitmap != NULL)
    {
        LOGI("parse Suc");
    } else
    {
        LOGI("parse Failed");
    }
    if ((ret = AndroidBitmap_lockPixels(env, bitmapIn, &bitmap->bitmapData)) < 0)
    {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return ret;
    }
    gnDealEdge(bitmap, type);
    AndroidBitmap_unlockPixels(env, bitmapIn);
    return 1;
}


JNIEXPORT jint
JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nSharpening(JNIEnv* env, jclass type, jobject bitmapIn)
{


    return 1;

}


JNIEXPORT jint


JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nPainting(JNIEnv* env, jclass type, jobject bitmapIn,
                                                       jobject bitmapOut)
{

    // TODO
    return 1;

}


JNIEXPORT jint


JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nCannyImage(JNIEnv* env, jclass type, jobject bitmapIn)
{

    // TODO

    return 1;

}


JNIEXPORT jint


JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nPrewitteImage(JNIEnv* env, jclass type,
                                                            jobject bitmapIn)
{

    // TODO
    return 1;

}


JNIEXPORT jint


JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nOstuImage(JNIEnv* env, jclass type, jobject bitmapIn,
                                                        jobject bitmapOut)
{

    // TODO
    return 1;

}


JNIEXPORT jint


JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nRenderPlasma(JNIEnv* env, jclass type,
                                                           jobject bitmapIn, jobject bitmapOut)
{

    // TODO
    return 1;

}


JNIEXPORT jint


JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nHistgramAverage(JNIEnv* env, jclass type,
                                                              jobject bitmapIn, jobject bitmapOut)
{

    // TODO
    return 1;

}


JNIEXPORT jintArray


JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nHistgramImage(JNIEnv* env, jclass type,
                                                            jobject bitmap)
{

    // TODO
    return NULL;

}


JNIEXPORT jint
JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nFriter(JNIEnv* env, jclass type, jobject bitmapIn,
                                                     jintArray parames_,
                                                     jint btype)
{
    int* parames = NULL;
    int size;
    if (parames_ != NULL)
    {
        parames = env->GetIntArrayElements(parames_, NULL);
        size    = env->GetArrayLength(parames_);

    }
    GNBitmap* gbitmap1 = praseBitmap(env, bitmapIn);
    int ret = 0;
    if (gbitmap1 == NULL ||
        (ret = AndroidBitmap_lockPixels(env, bitmapIn, &gbitmap1->bitmapData)) < 0)
    {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return ret;
    }
    gnFilter(gbitmap1, parames, size);
    AndroidBitmap_unlockPixels(env, bitmapIn);
    return 1;

}


JNIEXPORT jint


JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nMmirror(JNIEnv* env, jclass type, jobject bitmapIn,
                                                      jfloat point)
{

    // TODO
    return 1;

}


JNIEXPORT jint


JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nGauss2Blur(JNIEnv* env, jclass type, jobject bitmap,
                                                         jobject mask, jint radium, jint gtype)
{
    GNBitmap* gbitmap1 = praseBitmap(env, bitmap);
    GNBitmap* gbitmap2 = praseBitmap(env, mask);
    int ret = 0;
    if (gbitmap1 == NULL ||
        (ret = AndroidBitmap_lockPixels(env, bitmap, &gbitmap1->bitmapData)) < 0)
    {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return ret;
    }
    if (gbitmap2 != NULL)
    {
        if ((ret = AndroidBitmap_lockPixels(env, mask, &gbitmap2->bitmapData)) < 0)
        {
            LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
            return ret;
        }
    }
    gnGaussBlur(gbitmap1, gbitmap2, radium, gtype);
    AndroidBitmap_unlockPixels(env, bitmap);
    AndroidBitmap_unlockPixels(env, mask);
    return 1;
}


JNIEXPORT jint


JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nMedianBlur(JNIEnv* env, jclass type, jobject bitmap,
                                                         jobject mask, jint blurW, jint blurH,
                                                         jint btype)
{
    GNBitmap* gbitmap1 = praseBitmap(env, bitmap);
    GNBitmap* gbitmap2 = praseBitmap(env, mask);
    int ret = 0;
    if (gbitmap1 == NULL ||
        (ret = AndroidBitmap_lockPixels(env, bitmap, &gbitmap1->bitmapData)) < 0)
    {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return ret;
    }
    if (gbitmap2 != NULL)
    {
        if ((ret = AndroidBitmap_lockPixels(env, mask, &gbitmap2->bitmapData)) < 0)
        {
            LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
            return ret;
        }
    }
    gnMedianBlur(gbitmap1, gbitmap2, blurW, blurH, btype);
    AndroidBitmap_unlockPixels(env, bitmap);
    AndroidBitmap_unlockPixels(env, mask);
    return 1;
}


JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nNoise(JNIEnv* env, jclass type, jobject bitmapIn,
                                                    jfloat k1, jfloat k2)
{
    // TODO
    GNBitmap* bitmap = praseBitmap(env, bitmapIn);
    int ret = 0;
    if (bitmap != NULL)
    {
        LOGI("parse Suc");
    } else
    {
        LOGI("parse Failed");
    }
    if ((ret = AndroidBitmap_lockPixels(env, bitmapIn, &bitmap->bitmapData)) < 0)
    {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return ret;
    }
//    gnNoise(bitmap, k1, k2);
//    Mat image(bitmap->height, bitmap->width, CV_8UC4, bitmap->bitmapData);

    LOGI("STEP1  CV START");
    IplImage* image = cvCreateImageHeader(cvSize(bitmap->width, bitmap->height), IPL_DEPTH_8U, 4);
    cvSetData(image, bitmap->bitmapData, 4 * bitmap->width);
    IplImage* out = cvCreateImage(cvSize(bitmap->width, bitmap->height), IPL_DEPTH_8U, 4);
    cvSmooth(image, out, CV_GAUSSIAN, 81, 81);
    LOGI("STEP1  CV END");

    LOGI("STEP2  BLUR_GAUSS_TYPE_WH START");
    gnGaussBlur(bitmap, NULL, 30, BLUR_GAUSS_TYPE_WH);
    LOGI("STEP2  BLUR_GAUSS_TYPE_WH END");


    LOGI("STEP3  BLUR_GAUSS_TYPE_WH START");
    gnGaussBlur(bitmap, NULL, 30, BLUR_GAUSS_TYPE_STACKBLUR);
    LOGI("STEP3  BLUR_GAUSS_TYPE_WH END");


    bitmap->copyData(out->imageData, ANDROID_BITMAP_FORMAT_RGBA_8888);
    //Please make attention about BGRA byte order
    //ARGB stored in java as int array becomes BGRA at native level

    AndroidBitmap_unlockPixels(env, bitmapIn);


    return 1;
}

