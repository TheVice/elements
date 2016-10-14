package com.yegorov.alexey.elements.fire;

import android.app.Activity;
import android.os.Bundle;

import com.badlogic.gdx.GL2Test;
import com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView20;

public class FireWallpaperActivity extends Activity {

    private FireWallpaperView fireWallpaperView;
    private com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView20 view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        if (GL2Test.checkGL20Support()) {

            view = new GLSurfaceView20(this);
            fireWallpaperView = new FireWallpaperView(true, 0, getAssets());
            view.setRenderer(fireWallpaperView);
            view.setOnTouchListener(fireWallpaperView);
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
        fireWallpaperView.onDestroy();
    }

}
