//
// Created by 凌志 on 2018/11/8.
//
/**   
*    
* 项目名称：LibBitmap      
* 类描述：   
* 创建人：genesis   
* 创建时间：2018/11/8 5:53 PM   
* 修改人：genesis  
* 修改时间：2018/11/8 5:53 PM   
* 修改备注：   
* @version    
*    
*/
#include "GNCore.h"
#include "android/bitmap.h"
#include "BitmapUtills/BitmapUtills.h"
#include "Blur/Blur.h"


int gnSobel(GNBitmap* bitmap)
{
    uint8_t* data = transColorsA8(bitmap);
    if (data == NULL)
    {
        return -1;
    }
    double gxModel[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    double gyModel[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    int    w          = bitmap->width;
    int    h          = bitmap->height;
    uint8_t* tempX = (uint8_t*) malloc(sizeof(uint8_t) * w * h);
    uint8_t* tempY = (uint8_t*) malloc(sizeof(uint8_t) * w * h);
    convolution(data, gxModel, tempX, w, h, 3, 3);
    convolution(data, gyModel, tempY, w, h, 3, 3);
    average(tempX, tempY, data, w, h);
    bitmap->copyData(data, ANDROID_BITMAP_FORMAT_A_8);
    free(tempX);
    free(tempY);
    return 1;
}


int gnGaussBlur(GNBitmap* gbitmap1, GNBitmap* gbitmap2, int radium)
{
    LOGI("gnGaussBlur");
    uint8_t* data = transColorsA8(gbitmap2);
    if (data == NULL || gbitmap1->width != gbitmap2->width || gbitmap1->height != gbitmap2->height)
    {
        return -1;
    }
    LOGI("gnGaussBlur (%d, %d), b2(%d,%d)", gbitmap1->width, gbitmap1->height, gbitmap2->width,
         gbitmap2->height);

    uint8_t* mask = NULL;
    inRangeS(data, mask, gbitmap2->width, gbitmap2->height, 0xff, 0x40);
    argb* argb1 = (argb*) gbitmap1->bitmapData;
    gaussblur2d(argb1, gbitmap1->width, gbitmap1->height, radium, mask);
    free(mask);
    return 1;
}