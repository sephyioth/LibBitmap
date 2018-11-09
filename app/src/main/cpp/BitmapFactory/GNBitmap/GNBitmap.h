//
// Created by 凌志 on 2018/11/8.
//
/**   
*    
* 项目名称：LibBitmap      
* 类描述：   
* 创建人：genesis   
* 创建时间：2018/11/8 3:58 PM   
* 修改人：genesis  
* 修改时间：2018/11/8 3:58 PM   
* 修改备注：   
* @version    
*    
*/
#ifndef LIBBITMAP_GNBITMAP_H
#define LIBBITMAP_GNBITMAP_H

#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "memory.h"
#include <stdint.h>


class GNBitmap
{
public:
    int chennel;
    int width;
    int height;
    int flag;
    int stride;
    int type;
    void* bitmapData;

private:
    bool isCopyBitmap;

public :
    GNBitmap();

    GNBitmap(int w, int h, int format, int flag, int stride);

    ~GNBitmap();

public:

    GNBitmap* cloneBitmap();

    GNBitmap* createBitmap();

    GNBitmap* createBitmap(int w, int h, int format);

    int zeroBitmap();

    int invertBitmap();

    int recycle();

    int copyData(void* data, int type);

private:
    int getBitmapChannel();
};


#endif //LIBBITMAP_GNBITMAP_H
