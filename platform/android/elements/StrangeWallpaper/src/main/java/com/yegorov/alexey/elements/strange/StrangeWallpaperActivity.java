package com.yegorov.alexey.elements.strange;

import android.app.Activity;
import android.os.Bundle;

import com.badlogic.gdx.GL2Test;
import com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView20;

public class StrangeWallpaperActivity extends Activity {

    private StrangeWallpaperView strangeWallpaperView;
    private com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView20 view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        if (GL2Test.checkGL20Support()) {

            view = new GLSurfaceView20(this);
            strangeWallpaperView = new StrangeWallpaperView(true, 5000, getAssets());
            view.setRenderer(strangeWallpaperView);
            setContentView(view);
        }
        else {

            throw new RuntimeException("OpenGL ES 2.0 do not support on this system");
        }
    }

    @Override
    protected void onPause() {

        super.onPause();
        view.onPause();
    }

    @Override
    protected void onResume() {

        super.onResume();
        view.onResume();
    }

    @Override
    protected void onDestroy() {

        super.onDestroy();
        strangeWallpaperView.onDestroy();
    }

}
