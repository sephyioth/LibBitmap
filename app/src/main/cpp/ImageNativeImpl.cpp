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
    gnNoise(bitmap, k1, k2);
    AndroidBitmap_unlockPixels(env, bitmapIn);
    return 1;
}


JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nWarpPerspective(JNIEnv* env, jclass type_,
                                                              jobject bitmap, jobjectArray local,
                                                              jint type)
{
    GNBitmap* gbitmap = praseBitmap(env, bitmap);
    int ret = 0;
    if (gbitmap != NULL)
    {
        LOGI("parse Suc");
    } else
    {
        LOGI("parse Failed");
    }
    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &gbitmap->bitmapData)) < 0)
    {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return ret;
    }
    int rows = env->GetArrayLength(local);
    point2D* dstPoint = (point2D*) malloc(sizeof(point2D) * 4);
    memset(dstPoint, 0, sizeof(point2D) * 4);
    jintArray array = static_cast<jintArray>(env->GetObjectArrayElement(local, 0));
    int       cols  = env->GetArrayLength(array);
    jint* ddatax = env->GetIntArrayElements(array, NULL);
    array = static_cast<jintArray>(env->GetObjectArrayElement(local, 1));
    cols  = env->GetArrayLength(array);
    jint* ddatay = env->GetIntArrayElements(array, NULL);
    for (int j = 0; j < cols && j < 4; ++j)
    {
        dstPoint[j].x = (float) ddatax[j];
        dstPoint[j].y = (float) ddatay[j];
    }
#ifdef GNDEBUG
    for (int i = 0; i < 4; ++i)
    {
        LOGI("(%f, %f)", dstPoint[i].x, dstPoint[i].y);
    }
#endif
    gnnativeWarpPerspective(gbitmap, dstPoint, rows);
    AndroidBitmap_unlockPixels(env, bitmap);
    return 1;
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nShadowEffect(JNIEnv* env, jclass type, jobject bitmap,
                                                           jint x, jint y, jint radium, jint ktype)
{
    GNBitmap* gbitmap = praseBitmap(env, bitmap);
    assert(gbitmap != NULL);
    gnShadowEffect(gbitmap, x, y, radium, ktype);
    AndroidBitmap_unlockPixels(env, bitmap);
    return 1;
}


JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nBitmapLightAverage(JNIEnv* env, jclass type,
                                                                 jobject bitmap, jint x, jint y,
                                                                 jint width, jint height,
                                                                 jint filter)
{
    LOGI("jni light average start ");
    int               ret = -1;
    AndroidBitmapInfo infoin;
    if (bitmap == NULL)
    {
        return ret;
    }
    if ((ret = AndroidBitmap_getInfo(env, bitmap, &infoin)) < 0)
    {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return NULL;
    }
    int  chennel = 0;
    int  w       = infoin.width;
    int  h       = infoin.height;
    long dataAdd = 0;
    if (infoin.format == ANDROID_BITMAP_FORMAT_RGBA_8888)
    {
        chennel = 4;
    } else if (infoin.format == ANDROID_BITMAP_FORMAT_A_8)
    {
        chennel = 1;
    } else if (infoin.format == ANDROID_BITMAP_FORMAT_RGB_565 ||
               infoin.format == ANDROID_BITMAP_FORMAT_RGBA_4444)
    {
        chennel = 2;
    }
    void* bitmapData = malloc(sizeof(uint8_t) * w * h * chennel);
    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &bitmapData)) < 0)
    {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return NULL;
    }
    int ex = x + width < 0 ? 0 : x + width;
    ex = ex > w ? w : ex;
    int ey = y + height < 0 ? 0 : y + height;
    ex = ex > h ? h : ey;
    int count = 0;
    if (infoin.format == ANDROID_BITMAP_FORMAT_RGBA_8888)
    {
        argb* argb1 = (argb*) bitmapData;
        for (int i = x; i < ex; i += filter)
        {
            for (int j = y; j < ey; ++j)
            {
                argb temp = argb1[i * width + j];
                dataAdd += 0.299 * temp.red + 0.587 * temp.green + 0.114 * temp.blue;
                count++;
            }
        }
        count      = count > 0 ? count : 1;
        ret        = dataAdd / count;
    } else if (infoin.format == ANDROID_BITMAP_FORMAT_A_8)
    {
        uint8_t* data = (uint8_t*) bitmapData;
        for (int i = 0; i < ex; i += filter)
        {
            for (int j = 0; j < ey; ++j)
            {
                filter += data[i * width + j];
                count++;
            }
        }
        count      = count > 0 ? count : 1;
        ret        = dataAdd / count;
    } else
    {
        LOGE("Not support Android RGB565 AND rgb444");
    }
    LOGI("average light %d ,will return ", ret);
    free(bitmapData);
    AndroidBitmap_unlockPixels(env, bitmap);
    return ret;
}