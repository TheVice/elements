package com.yegorov.alexey.elements.air;

import android.graphics.Color;
import android.view.MotionEvent;
import android.view.View;

import com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView;
import com.yegorov.alexey.elements.api.Elements;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class AirWallpaperView implements GLSurfaceView.Renderer,
                                         View.OnTouchListener {

    private Air air;
    private boolean isPreview;
    private int textureSize;
    private Object assetManager;


    public AirWallpaperView(boolean preview, int textureSize, Object manager) {

        isPreview = preview;
        this.textureSize = textureSize;
        assetManager = manager;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        if (air != null) {

            air.close();
        }

        Elements.initializeAssets(assetManager);
        air = new Air(isPreview);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

        air.startup(width, height, textureSize);
        loadColors();
    }

    @Override
    public void onDrawFrame(GL10 gl) {

        air.render();
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {

        if(air != null) {

            air.touch(event.getX(), event.getY(), event.getAction());
            return true;
        }
        
        return false;
    }

    private void loadColors() {

        final int colorSpeedDown = 0xFF0091EA;
        final int colorSpeedUp = 0xFFFF6F00;
        air.colors(Color.red(colorSpeedDown) / 255.0f,
                Color.green(colorSpeedDown) / 255.0f,
                Color.blue(colorSpeedDown) / 255.0f,
                Color.red(colorSpeedUp) / 255.0f,
                Color.green(colorSpeedUp) / 255.0f,
                Color.blue(colorSpeedUp) / 255.0f);
    }

    public void onDestroy() {

        /*queueEvent(new Runnable() {

            @Override
            public void run() {*/

                if (air != null) {

                    air.close();
                }
            /*}
        });*/
    }

}
