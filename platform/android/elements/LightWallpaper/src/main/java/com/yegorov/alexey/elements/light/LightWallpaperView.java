package com.yegorov.alexey.elements.light;

import android.graphics.Color;
import android.view.MotionEvent;
import android.view.View;

import com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView;
import com.yegorov.alexey.elements.api.Elements;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class LightWallpaperView implements GLSurfaceView.Renderer,
                                          View.OnTouchListener {

    private Light light;
    private boolean isPreview;
    private int quality;
    private Object assetManager;
    private static final String DEFAULT_ASSET = "textures/background.png";

    public LightWallpaperView(boolean preview, int quality, Object manager) {

        isPreview = preview;
        this.quality = quality;
        assetManager = manager;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        if (light != null) {

            light.close();
        }

        Elements.initializeAssets(assetManager);
        light = new Light(isPreview);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

        light.startup(width, height, quality);
        loadSurfaceBackground();
        loadSurfaceColor();
    }

    @Override
    public void onDrawFrame(GL10 gl) {

        light.render();
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {

        if(light != null) {

            light.surfaceTouch(event.getX(), event.getY(), event.getAction());
            return true;
        }
        
        return false;
    }

    private void loadSurfaceBackground() {

        light.background(DEFAULT_ASSET);
    }

    private void loadSurfaceColor() {

        final int color = 0xFFFFFFFF;

        light.color(Color.red(color) / 255.0f,
                Color.green(color) / 255.0f,
                Color.blue(color) / 255.0f);
    }

    public void onDestroy() {

        /*queueEvent(new Runnable() {

            @Override
            public void run() {*/

                if (light != null) {

                    light.close();
                }
            /*}
        });*/
    }

}
