package com.genesis.imagejni;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Build;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

import com.genesis.imagejni.imageLib.ImageImpl;

/**
 * 项目名称：GaussBlue
 * 类描述：
 * 创建人：genesis
 * 创建时间：2018/10/25 5:52 PM
 * 修改人：genesis
 * 修改时间：2018/10/25 5:52 PM
 * 修改备注：
 */
public class MySurfaceView extends SurfaceView implements SurfaceHolder.Callback, View
        .OnTouchListener, Runnable {

    private SurfaceHolder mHolder;
    private Canvas        mCanvas;
    private boolean       mIsDrawing;
    private Bitmap        mBitmap;
    private int           mX, mY;
    private int mCount = 100;

    //构造方法
    public MySurfaceView (Context context) {
        super(context);
        initView();
    }


    public MySurfaceView (Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public MySurfaceView (Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    private void initView () {
        mHolder = getHolder();
        mHolder.addCallback(this);
        setFocusable(true);
        setFocusableInTouchMode(true);
        this.setKeepScreenOn(true);
    }

    @Override
    public void surfaceCreated (SurfaceHolder holder) {
        mIsDrawing = true;
        mBitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.bmp_source);
        mX = mBitmap.getWidth() - 1;
        mY = mBitmap.getHeight() - 1;
        new Thread(this).start();
    }

    @Override
    public void surfaceChanged (SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed (SurfaceHolder holder) {
        mIsDrawing = false;

    }

    @Override
    public void run () {
        while (mIsDrawing) {
            logic();
            draw();
            //通过线程休眠以控制刷新速度
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

    }

    private boolean isAdd = false;

    private void logic () {
        Log.i("Genesis", "cout" + mCount);
        if (mCount < 70) {
            mCount = 70;
            isAdd = true;
        } else if (mCount > 100) {
            mCount = 100;
            isAdd = false;
        }
        if (isAdd) {
            mCount++;
        } else {
            mCount--;
        }
        int value = mCount * 2;
        mX = mBitmap.getWidth() - value - 1;
        mY = mCount;
    }

    private void draw () {
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.bmp_source);
        try {
            mCanvas = mHolder.lockCanvas();
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
//                mCanvas = mHolder.lockHardwareCanvas();
            }
            mCanvas.drawColor(Color.GREEN);
            Paint paint = new Paint();
            double[] x = new double[4];
            double[] y = new double[4];
            x[0] = 0;
            x[1] = mX;
            x[2] = 0;
            x[3] = mBitmap.getWidth() - 1;
            y[0] = 0;
            y[1] = mY;
            y[2] = mBitmap.getHeight() - 1;
            y[3] = mBitmap.getHeight() - 1;
            int[][] local = new int[2][4];
            for (int i = 0; i < 4; i++) {
                local[0][i] = (int) x[i];
                local[1][i] = (int) y[i];
            }
            ImageImpl.warpPerspective(bitmap, local);
            mCanvas.drawBitmap(bitmap, 0, 0, paint);
            mCanvas.save();
        } catch (Exception e) {

        } finally {
            if (mCanvas != null) {
                mHolder.unlockCanvasAndPost(mCanvas);
            }
        }
        bitmap.recycle();

    }

    @Override
    public boolean onTouch (View view, MotionEvent motionEvent) {
        return false;
    }
}
