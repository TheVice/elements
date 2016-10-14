package com.yegorov.alexey.elements.liquid;

import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.view.MotionEvent;
import android.view.View;

import com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView;
import com.yegorov.alexey.elements.api.Elements;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class LiquidWallpaperView implements GLSurfaceView.Renderer,
                                            View.OnTouchListener,
                                            android.hardware.SensorEventListener {

    private Liquid liquid;
    private boolean isPreview;
    private int quality;
    private Object assetManager;
    private static final String DEFAULT_ASSET = "textures/background.png";

    public LiquidWallpaperView(boolean preview, int quality, Object manager) {

        isPreview = preview;
        this.quality = quality;
        assetManager = manager;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        if (liquid != null) {

            liquid.close();
        }

        Elements.initializeAssets(assetManager);
        liquid = new Liquid(isPreview);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

        liquid.startup(width, height, quality);
        loadBackground();
        loadColor();
    }

    @Override
    public void onDrawFrame(GL10 gl) {

        liquid.render();
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {

        if(liquid != null) {

            liquid.touch(event.getX(), event.getY(), event.getAction());
            return true;
        }
        
        return false;
    }

    @Override
    public void onSensorChanged(final SensorEvent event) {

        /*queueEvent(new Runnable() {

            @Override
            public void run() {*/

                if (liquid != null && event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {

                    liquid.acceleration(-event.values[0], -event.values[1], 0.0f);
                }
            /*}
        });*/
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }

    private void loadBackground() {

        liquid.background(DEFAULT_ASSET);
    }

    private void loadColor() {

        final int color = 0x55196271;

        liquid.color(Color.red(color) / 255.0f,
                Color.green(color) / 255.0f,
                Color.blue(color) / 255.0f,
                Color.alpha(color) / 255.0f);
    }

    public void onDestroy() {

        /*queueEvent(new Runnable() {

            @Override
            public void run() {*/

                if (liquid != null) {

                    liquid.close();
                }
            /*}
        });*/
    }

}
