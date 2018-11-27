package com.genesis.imagejni.imageLib;

import android.graphics.Bitmap;

/**
 * 项目名称：ImageTest
 * 类描述：
 * 创建人：genesis
 * 创建时间：2017/6/22 下午5:14
 * 修改人：genesis
 * 修改时间：2017/6/22 下午5:14
 * 修改备注：
 */
public class ImageImpl {
    public enum GaussType {
        GAUSSBLUR_WH(0x00), GAUSSBLUR_2D(0x01),BLUR_GAUSS_TYPE_STACKBLUR(0X02);

        private final int id;

        GaussType (int i) {
            id = i;
        }

        public int getId () {
            return id;
        }
    }

    public enum EdgeType {
        EDGE_TYPE_SOBEL(0x00), EDGE_TYPE_PREWITTE(0x01);

        EdgeType (int i) {
            id = i;
        }

        private final int id;

        public int getId () {
            return id;
        }
    }

    public enum MedianType {
        BLUR_MEDIAN_TYPE_MEDIAN(0x00), BLUR_MEDIAN_TYPE_AVERAGE(0x02);

        MedianType (int i) {
            id = i;
        }

        private final int id;

        public int getId () {
            return id;
        }

    }

    public static int noise (Bitmap bitmap, float k1, float k2) {
        return nNoise(bitmap, k1, k2);
    }


    public static int medianBlur (Bitmap bitmap, Bitmap mask, int blurW, int blurH, MedianType
            type) {
        return nMedianBlur(bitmap, mask, blurW, blurH, type.getId());
    }

    public static void gauss2Image (Bitmap bitmap1, Bitmap bitmap2, int radium) {
        nGauss2Blur(bitmap1, bitmap2, radium, GaussType.GAUSSBLUR_WH.getId());
    }


    public static void gauss2Image (Bitmap bitmap1, Bitmap bitmap2, int radium, GaussType type) {
        if (type == null) {
            type = GaussType.GAUSSBLUR_WH;
        }
        nGauss2Blur(bitmap1, bitmap2, radium, type.getId());
    }

    public static int sobelImage (Bitmap bitmapIn) {
        if (bitmapIn != null) {
            return nEdgeImage(bitmapIn, EdgeType.EDGE_TYPE_SOBEL.getId());
        } else {
            System.out.println("error input bitmap");
            return 0;
        }
    }

    public static int perwitteImage (Bitmap bitmapIn) {
        if (bitmapIn != null) {
            return nEdgeImage(bitmapIn, EdgeType.EDGE_TYPE_PREWITTE.getId());
        } else {
            System.out.println("error input bitmap");
            return 0;
        }
    }


    public static int friter (Bitmap bitmapIn) {
        assert bitmapIn == null : "error bitmap ";
        nFriter(bitmapIn, null, 0);
        return 1;
    }

    public static int mirror (Bitmap bitmapIn, float point) {
        assert bitmapIn == null : "error bitmap ";
        return nMmirror(bitmapIn, point);
    }

    public static int sharpening (Bitmap bitmapIn) {
        assert bitmapIn == null : "error bitmap ";
        return nSharpening(bitmapIn);
    }

    public static int[] histgramImage (Bitmap bitmap) {
        return nHistgramImage(bitmap);
    }

    /****内部接口函数****/
    private static native int nEdgeImage (Bitmap bitmapIn, int type);

    private static native int nSharpening (Bitmap bitmapIn);

    private static native int nPainting (Bitmap bitmapIn);

//    private static native int nPrewitteImage (Bitmap bitmapIn);

    private static native int nOstuImage (Bitmap bitmapIn);

    private static native int nHistgramAverage (Bitmap bitmapIn);

    private static native int[] nHistgramImage (Bitmap bitmap);

    private static native int nFriter (Bitmap bitmapIn, int[] parames, int type);

    private static native int nNoise (Bitmap bitmapIn, float k1, float k2);

    private static native int nMmirror (Bitmap bitmapIn, float point);

    private static native int nGauss2Blur (Bitmap bitmap, Bitmap mask, int radium, int type);

    private static native int nMedianBlur (Bitmap bitmap, Bitmap mask, int blurW, int blurH, int
            type);

    static {
        try {
            System.loadLibrary("gimage");
            System.loadLibrary("opencv_java3");

        } catch (Exception e) {
            System.out.println("LoadLib error");
        }
    }


}
