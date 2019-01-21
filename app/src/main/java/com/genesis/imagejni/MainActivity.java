package com.genesis.imagejni;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ImageView;

import com.genesis.imagejni.imageLib.ImageImpl;

public class MainActivity extends AppCompatActivity {
    private Bitmap mBitmap;
    private int    mX, mY;
    private int       mCount   = 100;
    private ImageView mImageView;
    private Handler   mHandler = new Handler() {
        @Override
        public void handleMessage (Message msg) {
            super.handleMessage(msg);
            Bitmap bitmap = (Bitmap) msg.obj;
            if (bitmap != null) mImageView.setImageBitmap(bitmap);
        }
    };

    @Override
    protected void onCreate (Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);// 隐藏标题
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,

                WindowManager.LayoutParams.FLAG_FULLSCREEN);// 设置全屏

//        setContentView(new MySurfaceView(this));
        setContentView(R.layout.activity_main);
        mImageView = (ImageView) findViewById(R.id.imageView);
        mBitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.bmp_src);
        mImageView.setImageBitmap(mBitmap);
        mImageView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch (View v, MotionEvent event) {
                int x = (int) (event.getX() );
                int y = (int) (event.getY() - v.getPivotY());
                Log.i("genesis test", "x :" + v.getScaleX() + "y :" +  v.getScaleY());
                mBitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.bmp_src);
                int radium = mBitmap.getWidth() > mBitmap.getHeight() ? mBitmap.getWidth()
                                                                      : mBitmap.getHeight();
                ImageImpl.shadowEffect(mBitmap, x, y, radium / 2, 100);
                mImageView.setImageBitmap(mBitmap);
                return false;
            }
        });

//        Bitmap bitmap2 = BitmapFactory.decodeResource(getResources(), R.mipmap.bmp_boe);
////        bitmap2 = Bitmap.createScaledBitmap(bitmap2, bitmap.getWidth(), bitmap.getHeight(),
// true);
////        ImageImpl.(bitmap);
////        ImageImpl.noise(bitmap, 1, 1);
//        mX = mBitmap.getWidth();
//        mY = mBitmap.getHeight();
//        mImageView = (ImageView) findViewById(R.id.imageView);
//        new Thread(new Runnable() {
//            @Override
//            public void run () {
//
//                while (true) {
//                    double[] x = new double[4];
//                    double[] y = new double[4];
//                    Bitmap bitmap = Bitmap.createBitmap(mBitmap);
//                    x[0] = mBitmap.getWidth() * 0.0;
//                    x[1] = mX;
//                    x[2] = 0;
//                    x[3] = mBitmap.getWidth();
//                    y[0] = 0;
//                    y[1] = mY;
//                    y[2] = mBitmap.getHeight();
//                    y[3] = mBitmap.getHeight();
//                    int[][] local = new int[2][4];
//                    for (int i = 0; i < 4; i++) {
//                        local[0][i] = (int) x[i];
//                        local[1][i] = (int) y[i];
//                    }
//                    ImageImpl.warpPerspective(bitmap, local);
//                    Message msg = new Message();
//                    msg.what = 0;
//                    msg.obj = mBitmap;
//                    mHandler.sendMessage(msg);
//
//                    try {
//                        Thread.sleep(10);
//                    } catch (InterruptedException e) {
//                        e.printStackTrace();
//                    }
//                }
//
//            }
//        }).start();
    }

    private void logic () {
        if (mCount < 50) {
            mCount = 100;
        }
        mCount--;
        mX = mBitmap.getWidth() - mCount * 2;
        mY = mCount;

    }

}
