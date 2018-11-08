package com.genesis.imagejni.imageLib;

import android.graphics.Bitmap;
import android.util.Log;

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


    public static Bitmap sobelImage (Bitmap bitmapIn) {
        if (bitmapIn != null) {
            Bitmap gary = Bitmap.createBitmap(bitmapIn.getWidth(), bitmapIn.getHeight(), Bitmap
                    .Config.ALPHA_8);
            Bitmap bitmapOut = Bitmap.createBitmap(bitmapIn.getWidth(), bitmapIn.getHeight(),
                    Bitmap.Config.ALPHA_8);
//            nRenderPlasma(bitmapIn, gary);
//            nSobelImage(gary, bitmapOut);
            gary.recycle();
            return bitmapOut;
        } else {
            System.out.println("error input bitmap");
            return null;
        }
    }

    public static Bitmap cannyImage (Bitmap bitmapIn) {
        if (bitmapIn != null) {
            Bitmap bitmapOut = Bitmap.createBitmap(bitmapIn.getWidth(), bitmapIn.getHeight(),
                    Bitmap.Config.ALPHA_8);
//            nCannyImage(bitmapIn, bitmapOut);
            return bitmapOut;
        } else {
            System.out.println("error input bitmap");
            return null;
        }
    }

    public static Bitmap prewitteImage (Bitmap bitmapIn) {
        if (bitmapIn != null) {
            Bitmap gary = Bitmap.createBitmap(bitmapIn.getWidth(), bitmapIn.getHeight(), Bitmap
                    .Config.ALPHA_8);
            Bitmap bitmapOut = Bitmap.createBitmap(bitmapIn.getWidth(), bitmapIn.getHeight(),
                    Bitmap.Config.ALPHA_8);
//            nRenderPlasma(bitmapIn, gary);
//            nPrewitteImage(gary, bitmapOut);
            gary.recycle();
            return bitmapOut;
        } else {
            System.out.println("error input bitmap");
            return null;
        }
    }

    public static Bitmap ostuImage (Bitmap bitmapIn) {
        if (bitmapIn != null) {
            Bitmap gary = Bitmap.createBitmap(bitmapIn.getWidth(), bitmapIn.getHeight(), Bitmap
                    .Config.ALPHA_8);
            Bitmap bitmapOut = Bitmap.createBitmap(bitmapIn.getWidth(), bitmapIn.getHeight(),
                    Bitmap.Config.ALPHA_8);
//            nRenderPlasma(bitmapIn, gary);
//            nOstuImage(gary, bitmapOut);
            gary.recycle();
            return bitmapOut;
        } else {
            System.out.println("error input bitmap");
            return null;
        }
    }

    public static Bitmap renderPlasma (Bitmap bitmapIn) {
        if (bitmapIn != null) {
            Log.i("genesis", "width =" + bitmapIn.getWidth() + "  height " + bitmapIn.getHeight());
            Bitmap bitmapOut = Bitmap.createBitmap(bitmapIn.getWidth(), bitmapIn.getHeight(),
                    Bitmap.Config.ALPHA_8);
//            nRenderPlasma(bitmapIn, bitmapOut);
            return bitmapOut;
        } else {
            System.out.println("error input bitmap");
            return null;
        }
    }

    public static Bitmap histgramAverage (Bitmap bitmapIn) {
        if (bitmapIn != null) {
            Bitmap bitmapOut = Bitmap.createBitmap(bitmapIn.getWidth(), bitmapIn.getHeight(),
                    Bitmap.Config.ARGB_8888);
//            nHistgramAverage(bitmapIn, bitmapOut);
            return bitmapOut;
        } else {
            System.out.println("error input bitmap");
            return null;
        }
    }

    public static Bitmap friter (Bitmap bitmapIn) {
        assert bitmapIn == null : "error bitmap ";
        Bitmap bitmapOut = Bitmap.createBitmap(bitmapIn.getWidth(), bitmapIn.getHeight(), Bitmap
                .Config.ARGB_8888);
//        nFriter(bitmapIn, bitmapOut);
        return bitmapOut;
    }

    public static Bitmap mirror (Bitmap bitmapIn) {
        assert bitmapIn == null : "error bitmap ";
        Bitmap bitmapOut = Bitmap.createBitmap(bitmapIn.getWidth(), bitmapIn.getHeight(), Bitmap
                .Config.ARGB_8888);
//        nMmirror(bitmapIn, bitmapOut, 0.5f);
        return bitmapOut;
    }

    public static Bitmap sharpening (Bitmap bitmapIn) {
        assert bitmapIn == null : "error bitmap ";
        Bitmap bitmapOut = Bitmap.createBitmap(bitmapIn.getWidth(), bitmapIn.getHeight(), Bitmap
                .Config.ARGB_8888);
//        nSharpening(bitmapIn, bitmapOut);
        return bitmapOut;
    }

    public static Bitmap gaussBlur (Bitmap bitmap) {
        assert bitmap == null : "error bitmap ";
        Bitmap bitmapOut = Bitmap.createBitmap(bitmap);
        nGaussBlur(bitmapOut);
        return bitmapOut;
    }

    public static int[] histgramImage (Bitmap bitmap) {
        return nHistgramImage(bitmap);
    }

    /****内部接口函数****/
    private static native int nSobelImage (Bitmap bitmapIn);

    private static native int nSharpening (Bitmap bitmapIn);

    private static native int nPainting (Bitmap bitmapIn);

    private static native int nCannyImage (Bitmap bitmapIn);

    private static native int nPrewitteImage (Bitmap bitmapIn);

    private static native int nOstuImage (Bitmap bitmapIn);

    private static native int nRenderPlasma (Bitmap bitmapIn);

    private static native int nHistgramAverage (Bitmap bitmapIn);

    private static native int[] nHistgramImage (Bitmap bitmap);

    private static native int nFriter (Bitmap bitmapIn);

    private static native int nMmirror (Bitmap bitmapIn, float point);

    private static native int nGaussBlur (Bitmap bitmap);

    static {
        try {
            System.loadLibrary("gimage");
        } catch (Exception e) {
            System.out.println("LoadLib error");
        }
    }


}
