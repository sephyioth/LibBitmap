package com.genesis.imagejni;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.genesis.imagejni.imageLib.ImageImpl;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    Bitmap effectBitmap;
    ImageView originalImageView;
    ImageView effectImageView;
    Button mSobel;

    @Override
    protected void onCreate (Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        mSobel = findViewById(R.id.sobel);
        mSobel.setOnClickListener(this);

        Bitmap originalBitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.bmp_source);
        effectBitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.bmp_source);
        effectBitmap = Bitmap.createScaledBitmap(effectBitmap, effectBitmap.getWidth(), effectBitmap.getHeight(), true);
        effectImageView = (ImageView) findViewById(R.id.effect_imageView);
        originalImageView = (ImageView) findViewById(R.id.original_imageView);
        originalImageView.setImageBitmap(originalBitmap);
    }

    @Override
    public void onClick(View v) {
        Log.d("onclick",v.toString());
        switch (v.getId()) {
            case R.id.sobel:
                ImageImpl.gauss2Image(effectBitmap, null, 30);
                effectImageView.setImageBitmap(effectBitmap);
                break;
        }
    }


}
