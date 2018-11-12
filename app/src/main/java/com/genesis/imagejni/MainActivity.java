package com.genesis.imagejni;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

import com.genesis.imagejni.imageLib.ImageImpl;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate (Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.bmp_source);
        Bitmap bitmap2 = BitmapFactory.decodeResource(getResources(), R.mipmap.bmp_boe);
        bitmap2 = Bitmap.createScaledBitmap(bitmap2, bitmap.getWidth(), bitmap.getHeight(), true);

        ImageImpl.medianBlur(bitmap, bitmap2, 10, 10, ImageImpl.MedianType.BLUR_MEDIAN_TYPE_MEDIAN);
        ImageView imageView = (ImageView) findViewById(R.id.imageView);
        imageView.setImageBitmap(bitmap);
    }
}
