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
#ifndef LIBBITMAP_BITMAPPARSE_H
#define LIBBITMAP_BITMAPPARSE_H

#include "../GNBitmapContast.h"
#include "../GNBitmap/GNBitmap.h"
#include "jni.h"

GNBitmap* praseBitmap(JNIEnv *env,jobject jobject1);

int freeBitmap(GNBitmap* bitmap);


#endif //LIBBITMAP_BITMAPPARSE_H
