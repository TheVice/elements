package com.yegorov.alexey.elements.compass;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class CompassView implements GLSurfaceView.Renderer,
                                    android.hardware.SensorEventListener {

    private Compass compass;
    private final int startAngle;
    private Object assetManager;

    public CompassView(int startAngle, Object manager) {

        this.startAngle = startAngle;
        assetManager = manager;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        if (compass != null) {

            compass.close();
        }

        compass = new Compass(assetManager);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

        compass.startup(width, height);
        compass.rotation(startAngle);
    }

    @Override
    public void onDrawFrame(GL10 gl) {

        compass.render();
    }

    @Override
    public void onSensorChanged(final SensorEvent event) {

        /*queueEvent(new Runnable() {

            @Override
            public void run() {*/

                if (compass != null && event.sensor.getType() == Sensor.TYPE_ORIENTATION) {

                    compass.rotation(startAngle + event.values[0]);
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

                if (compass != null) {

                    compass.close();
                }
            /*}
        });*/
    }

}
