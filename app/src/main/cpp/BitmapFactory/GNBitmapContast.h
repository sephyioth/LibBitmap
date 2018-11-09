//
// Created by 凌志 on 2018/11/8.
//
/**   
*    
* 项目名称：LibBitmap      
* 类描述：   
* 创建人：genesis   
* 创建时间：2018/11/8 3:44 PM   
* 修改人：genesis  
* 修改时间：2018/11/8 3:44 PM   
* 修改备注：   
* @version    
*    
*/
#ifndef LIBBITMAP_GNBITMAPCONTAST_H
#define LIBBITMAP_GNBITMAPCONTAST_H

#include <android/log.h>
#include <android/bitmap.h>
#include "stdio.h"
#include "malloc.h"


#define  LOG_TAG    "libGenesisBitmap"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define  PI 3.141592653


typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
} argb;

typedef struct
{
    float H;
    float S;
    float V;

} hsv;

typedef struct
{
    uint8_t value;
} gray;

enum BitmapType
{
    GNBITMAP_GRAY,
    GNBITMAP_ARGB,
    GNBITMAP_HSV
};


#endif //LIBBITMAP_GNBITMAPCONTAST_H