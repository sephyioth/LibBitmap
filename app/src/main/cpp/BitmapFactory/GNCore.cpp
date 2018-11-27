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
#include "BitmapFilter/Filter.h"
#include "../CL/cl.h"
#include "../CL/cl_platform.h"
#include "../aopencl.h"
#include "Conversion/ConversionTransForm.h"

#define  KERNEL_SRC "\n" \



int gpuTask()
{
    initFns();
    /*宿主机变量*/
    cl_uint        numPlatforms; //the NO. of platforms
    cl_platform_id platform = NULL; //the chosen platform
    cl_int         status;
    cl_platform_id* platforms;
    cl_uint numDevices = 0;
    cl_device_id* devices;
    cl_context       context;
    cl_command_queue commandQueue;
    cl_program       program;
    cl_kernel        kernel;
    //size_t global;
    cl_mem           a1, a2, a3;

    /*Step1: Getting platforms and choose an available one.*/
    status = clGetPlatformIDs(0, NULL, &numPlatforms);

    /*For clarity, choose the first available platform. */
    if (numPlatforms > 0)
    {
        platforms = (cl_platform_id*) malloc(
                numPlatforms * sizeof(cl_platform_id));
        status    = clGetPlatformIDs(numPlatforms, platforms, NULL);
        platform  = platforms[0];
        free(platforms);
    }

    /*Step 2:Query the platform and choose the first GPU device if has one.Otherwise use the CPU as device.*/
    status  = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
//	if (numDevices == 0) //no GPU available.
//			{
//		printf("No GPU device available.\n");
//		printf("Choose CPU as default device.\n");
//		status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 0, NULL,
//				&numDevices);
//		devices = (cl_device_id*) malloc(numDevices * sizeof(cl_device_id));
//		status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, numDevices,
//				devices, NULL);
//	} else {
//		devices = (cl_device_id*) malloc(numDevices * sizeof(cl_device_id));
//		status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, numDevices,
//				devices, NULL);
//	}
    devices = (cl_device_id*) malloc(numDevices * sizeof(cl_device_id));
    status  = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, numDevices, devices,
                             NULL);

    /*Step 3: Create context.*/
    context = clCreateContext(NULL, 1, devices, NULL, NULL, &status);

    /*Step 4: Creating command queue associate with the context.*/
    commandQueue = clCreateCommandQueue(context, devices[0], 0, &status);

    /*Step 5: Create program object */
    const char* source = KERNEL_SRC;
    size_t sourceSize[] = {strlen(source)};
    program = clCreateProgramWithSource(context, 1, &source, sourceSize,
                                        &status);

    /*Step 6: Build program. */
    status = clBuildProgram(program, 1, devices, NULL, NULL, NULL);


    /*Step 8: Create kernel object */
    kernel = clCreateKernel(program, "Sobel", &status);

    // set the argument list for the kernel command
    status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &a1);
    status = clSetKernelArg(kernel, 1, sizeof(cl_mem), &a2);
    status = clSetKernelArg(kernel, 2, sizeof(cl_mem), &a3);


}


int gnDealEdge(GNBitmap* bitmap, int type)
{
    uint8_t* data                      = transColorsA8(bitmap);
    if (data == NULL)
    {
        return -1;
    }
    double* pointx, * pointy;
    double          gxSobelModel[9]    = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    double          gySobelModel[9]    = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    double          gxPrewitteModel[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    double          gyPrewitteModel[9] = {1, 1, 1, 0, 0, 0, -1, -1, -1};
    if (type == EDGE_TYPE_SOBEL)
    {
        pointx = gxSobelModel;
        pointy = gySobelModel;
    } else
    {
        pointx = gxPrewitteModel;
        pointy = gyPrewitteModel;
    }
    int w = bitmap->width;
    int h = bitmap->height;
    uint8_t* tempX = (uint8_t*) malloc(sizeof(uint8_t) * w * h);
    uint8_t* tempY = (uint8_t*) malloc(sizeof(uint8_t) * w * h);
    convolution(data, pointx, tempX, w, h, 3, 3);
    convolution(data, pointy, tempY, w, h, 3, 3);
    average(tempX, tempY, data, w, h);
    bitmap->copyData(data, ANDROID_BITMAP_FORMAT_A_8);
    free(tempX);
    free(tempY);
    return 1;
}


int gnGaussBlur(GNBitmap* gbitmap1, GNBitmap* gbitmap2, int radium, int type)
{
    LOGI("gnGaussBlur");
    uint8_t* mask  = NULL;
    argb   * dst   = NULL;
    if (gbitmap2 != NULL && (gbitmap1->width == gbitmap2->width &&
                             gbitmap1->height == gbitmap2->height))
    {
        uint8_t* data = transColorsA8(gbitmap2);
        if (data != NULL)
        {
            LOGI("gnGaussBlur data is null  (%d, %d)", gbitmap1->width, gbitmap1->height);
            inRangeS(data, mask, gbitmap2->width, gbitmap2->height, 0xff, 0x40);
        }
    }
    argb   * argb1 = (argb*) gbitmap1->bitmapData;
    gaussBlur(argb1, dst, gbitmap1->width, gbitmap1->height, radium, type, mask);
    gbitmap1->copyData(dst, ANDROID_BITMAP_FORMAT_RGBA_8888);
    free(dst);
    free(mask);
    return 1;
}


int gnMedianBlur(GNBitmap* src, GNBitmap* mask, jint blurw, jint blurh, jint btype)
{

    LOGI("gnMedianBlur");
    uint8_t* gmask = NULL;
    argb   * dst   = NULL;
    if (mask != NULL && (src->width == mask->width &&
                         src->height == mask->height))
    {
        uint8_t* data = transColorsA8(mask);
        if (data != NULL)
        {
            LOGI("gnGaussBlur data is null  (%d, %d)", src->width, src->height);
            inRangeS(data, gmask, mask->width, mask->height, 0xff, 0x40);
        }
    }
    argb   * argb1 = (argb*) src->bitmapData;
    gnMedianBlur(argb1, dst, src->width, src->height, blurw, blurh, btype, gmask);
    src->copyData(dst, ANDROID_BITMAP_FORMAT_RGBA_8888);
    free(dst);
    free(gmask);
    return 1;
}


int gnFilter(GNBitmap* src, int* parames, int size)
{
    argb* dst   = NULL;
    argb* argb1 = (argb*) src->bitmapData;
    oldPaint(argb1, dst, src->width, src->height, 8, 20);
    src->copyData(dst, ANDROID_BITMAP_FORMAT_RGBA_8888);
    free(dst);
    return 1;
}


int gnNoise(GNBitmap* src, float k1, float k2)
{
    k1 = k1 < 0 ? 0 : k1;
    k2 = k2 < 0 ? 0 : k2;
    argb* dst   = NULL;
    argb* argb1 = (argb*) src->bitmapData;
    noise(argb1, dst, src->width, src->height, k1, k2);
    src->copyData(dst, ANDROID_BITMAP_FORMAT_RGBA_8888);
    free(dst);
    return 1;
}


int gncvAffineTransfrom(GNBitmap* src, IplImage*&dst, point2D* points, int length)
{
    cvnAffineTransfrom(src->image, dst, points, length);
    return 1;
}



int gncvWarpPerspective(GNBitmap* src, IplImage*&dst, point2D* points, int length)
{
    cvnWarpPerspective(src->image, dst, points, length);
    return 1;
}

