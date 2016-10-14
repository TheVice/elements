package com.yegorov.alexey.elements.liquid;

import android.app.Activity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.os.Bundle;

import com.badlogic.gdx.GL2Test;
import com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView20;

public class LiquidWallpaperActivity extends Activity {

    private SensorManager sensorManager;
    private LiquidWallpaperView liquidWallpaperView;
    private com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView20 view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        sensorManager = (SensorManager)getSystemService(Context.SENSOR_SERVICE);
        Sensor sensor = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);

        if (sensor == null) {

            throw new RuntimeException("There is no accelerometer sensor");
        }

        if (GL2Test.checkGL20Support()) {

            view = new GLSurfaceView20(this);
            liquidWallpaperView = new LiquidWallpaperView(true, 0, getAssets());
            view.setRenderer(liquidWallpaperView);
            view.setOnTouchListener(liquidWallpaperView);
			sensorManager.registerListener(liquidWallpaperView, sensor, SensorManager.SENSOR_DELAY_FASTEST);
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
        sensorManager.unregisterListener(liquidWallpaperView);
        liquidWallpaperView.onDestroy();
    }

}
