package com.yegorov.alexey.elements.demo;

import android.view.MotionEvent;
import android.view.View;

import com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView;
import com.yegorov.alexey.elements.api.Elements;
import com.yegorov.alexey.elements.api.Unzip;

import java.util.Vector;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class DemoView implements GLSurfaceView.Renderer,
                                 View.OnTouchListener {

    private Demo demo;
    private Object assetManager;

    private String path_to_apk;
    private String path_to_cache;

    public DemoView(Object manager) {

        assetManager = manager;
        this.path_to_apk = null;
        this.path_to_cache = null;
    }

    public DemoView(String path_to_apk, String path_to_cache) {

        assetManager = null;
        this.path_to_apk = path_to_apk;
        this.path_to_cache = path_to_cache;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        if (demo != null) {

            demo.close();
        }

        if (assetManager != null) {

            Elements.initializeAssets(assetManager);
        }
        else {

            Unzip apkZip = new Unzip(path_to_apk);
            Vector<String> files = apkZip.listFiles();

            for (String file : files) {

                if (0 == file.indexOf("assets/")) {

                    String destination = path_to_cache + file.substring("assets".length());
                    apkZip.extractFile(file, destination);
                }
            }

            apkZip.close();

            Elements.initializeAssetsAtCache(path_to_cache);
        }

        demo = new Demo();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

        demo.startup(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {

        demo.render();
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {

        if(demo != null) {

            demo.touch(event.getX(), event.getY(), event.getAction(), event.getPointerCount());
            return true;
        }
        
        return false;
    }

    public void onDestroy() {

        /*queueEvent(new Runnable() {

            @Override
            public void run() {*/

                if (demo != null) {

                    demo.close();
                }
            /*}
        });*/
    }

}
