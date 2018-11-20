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
#include "BitmapFactory/BitmapUtills/BitmapUtills.h"
#include "BitmapFactory/GNBitmapContast.h"

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
//    argb* data = static_cast<argb*>(bitmap->bitmapData);

//
//
//    for (int i = 0; i < bitmap->height * bitmap->width; ++i)
//    {
//        data[i].alpha = 0x8f;
//    }



    int length = 4;
    point2D* dstPoint = (point2D*) malloc(sizeof(point2D) * length);
    double x[4] = {0};
    double y[4] = {0};
    x[0] = bitmap->width * 0.05;
    x[1] = bitmap->width * 0.9;
    x[2] = bitmap->width * 0.2f;
    x[3] = bitmap->width * 0.8;
    y[0] = bitmap->height * 0.33;
    y[1] = bitmap->height * 0.25;
    y[2] = bitmap->height * 0.7f;
    y[3] = bitmap->height * 0.9f;
    for (int i = 0; i < length; ++i)
    {
        dstPoint[i].x = x[i];
        dstPoint[i].y = y[i];
    }
    IplImage* dst;
    gncvAffineTransfrom(bitmap, dst, dstPoint, length);
    bitmap->copyData(dst->imageData, ANDROID_BITMAP_FORMAT_RGBA_8888);
//    gnNoise(bitmap, k1, k2);
    AndroidBitmap_unlockPixels(env, bitmapIn);
    return 1;
}

