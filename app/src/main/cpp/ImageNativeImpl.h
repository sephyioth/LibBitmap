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
#ifndef IMAGEJNI_IMAGENATIVEIMPL_H
#define IMAGEJNI_IMAGENATIVEIMPL_H

#include <jni.h>
#include <string>


extern "C"
{

JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nSobelImage(JNIEnv* env, jclass type,
                                                         jobject bitmapIn);

JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nSharpening(JNIEnv* env, jclass type,
                                                         jobject bitmapIn);

JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nPainting(JNIEnv* env, jclass type, jobject bitmapIn);

JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nCannyImage(JNIEnv* env, jclass type,
                                                         jobject bitmapIn);

JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nPrewitteImage(JNIEnv* env, jclass type,
                                                            jobject bitmapIn);

JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nOstuImage(JNIEnv* env, jclass type, jobject bitmapIn);

JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nRenderPlasma(JNIEnv* env, jclass type,
                                                           jobject bitmapIn);

JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nHistgramAverage(JNIEnv* env, jclass type,
                                                              jobject bitmapIn);

JNIEXPORT jintArray JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nHistgramImage(JNIEnv* env, jclass type,
                                                            jobject bitmap);

JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nFriter(JNIEnv* env, jclass type, jobject bitmapIn);

JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nMmirror(JNIEnv* env, jclass type, jobject bitmapIn,
                                                      jfloat point);

JNIEXPORT jint JNICALL
Java_com_genesis_imagejni_imageLib_ImageImpl_nGauss2Blur(JNIEnv* env, jclass type, jobject bitmap,
                                                         jobject mask, jint radium);

};

#endif //IMAGEJNI_IMAGENATIVEIMPL_H
