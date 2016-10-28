package com.yegorov.alexey.elements.character;

import android.hardware.Sensor;
import android.hardware.SensorEvent;

import com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView;
import com.yegorov.alexey.elements.api.Elements;
import com.yegorov.alexey.elements.api.Unzip;

import java.util.Vector;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class CharacterWallpaperView implements GLSurfaceView.Renderer,
                                    android.hardware.SensorEventListener {

    private Character character;
    private boolean isPreview;
    private final String DEFAULT_MODEL = "assets/models/R2-D2/R2-D2.dae";
    private Object assetManager;

    private String path_to_apk;
    private String path_to_cache;

    public CharacterWallpaperView(boolean preview,  Object manager) {

        isPreview = preview;
        assetManager = manager;
        this.path_to_apk = null;
        this.path_to_cache = null;
    }

    public CharacterWallpaperView(boolean preview, String path_to_apk, String path_to_cache) {

        isPreview = preview;
        assetManager = null;
        this.path_to_apk = path_to_apk;
        this.path_to_cache = path_to_cache;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        if (character != null) {

            character.close();
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

        character = new Character(isPreview);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

        character.startup(width, height);
        loadModel();
        character.rotation(0, 2 / (float) Math.sqrt(Math.PI), (float) Math.PI / 4);
    }

    @Override
    public void onDrawFrame(GL10 gl) {

        character.render();
    }

    private void loadModel() {

        character.model(DEFAULT_MODEL);
    }

    @Override
    public void onSensorChanged(final SensorEvent event) {

        /*queueEvent(new Runnable() {

            @Override
            public void run() {*/

                if (character != null && event.sensor.getType() == Sensor.TYPE_ORIENTATION) {

                    character.rotation((float)Math.toRadians(event.values[0]),
                                       (float)Math.toRadians(event.values[1]),
                                       (float)Math.toRadians(event.values[2]));
                }
            /*}
        });*/
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }

    public void onDestroy() {

        /*queueEvent(new Runnable() {

            @Override
            public void run() {*/

                if (character != null) {

                    character.close();
                }
            /*}
        });*/
    }

}
