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


JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nSobelImage(JNIEnv* env, jclass type, jobject bitmapIn)
{

    // TODO


    return 1;

}


JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nSharpening(JNIEnv* env, jclass type, jobject bitmapIn)
{

    // TODO

    return 1;

}


JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nPainting(JNIEnv* env, jclass type, jobject bitmapIn,
                                                       jobject bitmapOut)
{

    // TODO
    return 1;

}


JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nCannyImage(JNIEnv* env, jclass type, jobject bitmapIn)
{

    // TODO

    return 1;

}


JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nPrewitteImage(JNIEnv* env, jclass type,
                                                            jobject bitmapIn)
{

    // TODO
    return 1;

}


JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nOstuImage(JNIEnv* env, jclass type, jobject bitmapIn,
                                                        jobject bitmapOut)
{

    // TODO
    return 1;

}


JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nRenderPlasma(JNIEnv* env, jclass type,
                                                           jobject bitmapIn, jobject bitmapOut)
{

    // TODO
    return 1;

}


JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nHistgramAverage(JNIEnv* env, jclass type,
                                                              jobject bitmapIn, jobject bitmapOut)
{

    // TODO
    return 1;

}


JNIEXPORT jintArray JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nHistgramImage(JNIEnv* env, jclass type,
                                                            jobject bitmap)
{

    // TODO
    return NULL;

}


JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nFriter(JNIEnv* env, jclass type, jobject bitmapIn,
                                                     jobject bitmapOut)
{

    // TODO
    return 1;

}


JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nMmirror(JNIEnv* env, jclass type, jobject bitmapIn,
                                                       jfloat point)
{

    // TODO
    return 1;

}


JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nGaussBlur(JNIEnv* env, jclass type, jobject bitmap)
{

    // TODO
    return 1;

}