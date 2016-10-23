package com.yegorov.alexey.elements.character;

import android.hardware.Sensor;
import android.hardware.SensorEvent;

import com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView;
import com.yegorov.alexey.elements.api.Elements;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class CharacterWallpaperView implements GLSurfaceView.Renderer,
                                    android.hardware.SensorEventListener {

    private Character character;
    private boolean isPreview;
    private final String DEFAULT_MODEL = "assets/models/R2-D2/R2-D2.dae";
    private Object assetManager;


    public CharacterWallpaperView(boolean preview,  Object manager) {

        isPreview = preview;
        assetManager = manager;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        if (character != null) {

            character.close();
        }

        Elements.initializeAssets(assetManager);
        character = new Character(isPreview);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

        character.startup(width, height);
        loadModel();
        character.rotation(2 / (float) Math.sqrt(Math.PI), (float) Math.PI / 4, 0);
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
