package com.yegorov.alexey.elements.character;

import android.app.Activity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.os.Bundle;
import dalvik.system.VMRuntime;

import com.badlogic.gdx.GL2Test;
import com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView20;

public class CharacterWallpaperActivity extends Activity {

    //private SensorManager sensorManager;
    private CharacterWallpaperView characterWallpaperView;
    private com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView20 view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        VMRuntime.getRuntime().setMinimumHeapSize(12 * 1024 * 1024);

        super.onCreate(savedInstanceState);

        /*sensorManager = (SensorManager)getSystemService(Context.SENSOR_SERVICE);
        Sensor sensor = sensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION);

        if (sensor == null) {

            throw new RuntimeException("There is no orientation sensor");
        }*/

        if (GL2Test.checkGL20Support()) {

            view = new GLSurfaceView20(this);
            characterWallpaperView = new CharacterWallpaperView(true, getAssets());
            view.setRenderer(characterWallpaperView);
            //sensorManager.registerListener(characterWallpaperView, sensor, SensorManager.SENSOR_DELAY_UI);
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
        //sensorManager.unregisterListener(characterWallpaperView);
        characterWallpaperView.onDestroy();
    }

}
