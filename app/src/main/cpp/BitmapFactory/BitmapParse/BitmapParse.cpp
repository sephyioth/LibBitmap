//
// Created by 凌志 on 2018/11/8.
//
/**   
*    
* 项目名称：LibBitmap      
* 类描述：   
* 创建人：genesis   
* 创建时间：2018/11/8 3:52 PM   
* 修改人：genesis  
* 修改时间：2018/11/8 3:52 PM   
* 修改备注：   
* @version    
*    
*/
#include <android/bitmap.h>
#include "BitmapParse.h"
#include "stdio.h"


GNBitmap* praseBitmap(JNIEnv* env, jobject jobject1)
{
    if (jobject1 == NULL)
    {
        return NULL;
    }
    GNBitmap* bitmap           = new GNBitmap();
    AndroidBitmapInfo infoin;
    int               chensize = 0;
    int               ret      = 0;
    if ((ret = AndroidBitmap_getInfo(env, jobject1, &infoin)) < 0)
    {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return NULL;
    }
    bitmap->width  = infoin.width;
    bitmap->height = infoin.height;
    bitmap->stride = infoin.stride;
    bitmap->flag   = infoin.flags;
    bitmap->type   = infoin.format;

    if (infoin.format == ANDROID_BITMAP_FORMAT_RGBA_8888)
    {
        bitmap->chennel = 4;
        chensize = 4;
    } else if (infoin.format == ANDROID_BITMAP_FORMAT_A_8)
    {
        bitmap->chennel = 1;
        chensize = 1;
    } else if (infoin.format == ANDROID_BITMAP_FORMAT_RGB_565 ||
               infoin.format == ANDROID_BITMAP_FORMAT_RGBA_4444)
    {
        bitmap->chennel = 4;
        chensize = 2;
    }
    if ((ret       = AndroidBitmap_lockPixels(env, jobject1, &bitmap->bitmapData)) < 0)
    {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return NULL;
    }
    bitmap->image = cvCreateImageHeader(cvSize(bitmap->width, bitmap->height), IPL_DEPTH_8U,
                                        chensize);
    cvSetData(bitmap->image, bitmap->bitmapData, bitmap->width * chensize);
    return bitmap;
}


int freeBitmap(GNBitmap* bitmap)
{
    if (bitmap == NULL)
    {
        return -1;
    }
    bitmap->recycle();
    free(bitmap);
    return 1;
}