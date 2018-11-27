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


#define  LOG_TAG    "libGenesisBitmap"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define  PI 3.141592653

#define BLUR_GAUSS_TYPE_WH            0X00
#define BLUR_GAUSS_TYPE_2D          0X01
#define BLUR_GAUSS_TYPE_STACKBLUR       0X02

#define BLUR_MEDIAN_TYPE_MEDIAN         0X00
#define BLUR_MEDIAN_TYPE_AVERAGE        0X02
#define EDGE_TYPE_SOBEL                 0x00
#define EDGE_TYPE_PREWITTE              0x01


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

typedef struct
{
    float x;
    float y;
} point2D;

enum BitmapType
{
    GNBITMAP_GRAY,
    GNBITMAP_ARGB,
    GNBITMAP_HSV
};


#endif //LIBBITMAP_GNBITMAPCONTAST_H