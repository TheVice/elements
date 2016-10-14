package com.yegorov.alexey.elements.fire;

import android.graphics.Color;
import android.view.MotionEvent;
import android.view.View;

import com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView;
import com.yegorov.alexey.elements.api.Elements;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class FireWallpaperView implements GLSurfaceView.Renderer,
                                          View.OnTouchListener {

    private Fire fire;
    private boolean isPreview;
    private int quality;
    private Object assetManager;
    private static final String DEFAULT_ASSET = "textures/background.png";

    public FireWallpaperView(boolean preview, int quality, Object manager) {

        isPreview = preview;
        this.quality = quality;
        assetManager = manager;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        if (fire != null) {

            fire.close();
        }

        Elements.initializeAssets(assetManager);
        fire = new Fire(isPreview);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

        fire.startup(width, height, quality);
        loadBackground();
        loadColors();
    }

    @Override
    public void onDrawFrame(GL10 gl) {

        fire.render();
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {

        if(fire != null) {

            fire.touch(event.getX(), event.getY(), event.getAction());
            return true;
        }
        
        return false;
    }

    private void loadBackground() {

        fire.background(DEFAULT_ASSET);
    }

    private void loadColors() {

        final int colorHot = 0xff1980ff;
        fire.colorHot(Color.red(colorHot) / 255.0f,
                Color.green(colorHot) / 255.0f,
                Color.blue(colorHot) / 255.0f);

        final int colorCold = 0xffff8019;
        fire.colorCold(Color.red(colorCold) / 255.0f,
                Color.green(colorCold) / 255.0f,
                Color.blue(colorCold) / 255.0f);
    }

    public void onDestroy() {

        /*queueEvent(new Runnable() {

            @Override
            public void run() {*/

                if (fire != null) {

                    fire.close();
                }
            /*}
        });*/
    }

}
