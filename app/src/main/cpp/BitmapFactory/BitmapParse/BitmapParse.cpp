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
    GNBitmap* bitmap = new GNBitmap();
    AndroidBitmapInfo infoin;
    void* pixelsin;
    int ret = 0;
    if ((ret = AndroidBitmap_getInfo(env, jobject1, &infoin)) < 0)
    {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return NULL;
    }
    bitmap->width   = infoin.width;
    bitmap->height  = infoin.height;
    bitmap->stride  = infoin.stride;
    bitmap->flag    = infoin.flags;
    bitmap->chennel = infoin.format;

    if ((ret = AndroidBitmap_lockPixels(env, jobject1, &bitmap->bitmapData)) < 0)
    {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return NULL;
    }
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