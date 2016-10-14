package com.yegorov.alexey.elements.strange;

import android.graphics.Color;

import com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView;
import com.yegorov.alexey.elements.api.Elements;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class StrangeWallpaperView implements GLSurfaceView.Renderer {

    private Strange strange;
    private boolean isPreview;
    private int quality;
    private Object assetManager;

    public StrangeWallpaperView(boolean preview, int quality, Object manager) {

        isPreview = preview;
        this.quality = quality;
        assetManager = manager;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        if (strange != null) {

            strange.close();
        }

        Elements.initializeAssets(assetManager);
        strange = new Strange(isPreview);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

        strange.startup(width, height, quality);
        loadColors();
    }

    @Override
    public void onDrawFrame(GL10 gl) {

        strange.render();
    }

    private void loadColors() {

        final int colorBackground = 0xff202020;
        strange.colorBackground(Color.red(colorBackground) / 255.0f,
                Color.green(colorBackground) / 255.0f,
                Color.blue(colorBackground) / 255.0f);

        final int gradient1 = 0xff747474;
        final int gradient2 = 0xfff9f517;

        strange.colorGradient(Color.red(gradient1) / 255.0f,
                Color.green(gradient1) / 255.0f,
                Color.blue(gradient1) / 255.0f,
                Color.red(gradient2) / 255.0f,
                Color.green(gradient2) / 255.0f,
                Color.blue(gradient2) / 255.0f);
    }

    public void onDestroy() {

        /*queueEvent(new Runnable() {

            @Override
            public void run() {*/

                if (strange != null) {

                    strange.close();
                }
            /*}
        });*/
    }

}
