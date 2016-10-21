package com.yegorov.alexey.elements.compass;

import android.app.Activity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.content.res.Configuration;
import android.os.Bundle;

import com.badlogic.gdx.GL2Test;
import com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView20;

public class MainActivity extends Activity {

    private SensorManager sensorManager;
    private CompassView compassView;
    private com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView20 view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        sensorManager = (SensorManager)getSystemService(Context.SENSOR_SERVICE);
        Sensor sensor = sensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION);

        if (sensor == null) {

            throw new RuntimeException("There is no orientation sensor");
        }

        if (GL2Test.checkGL20Support()) {

            final int startAngle = getStartAngle(getResources().getConfiguration().orientation);
            view = new GLSurfaceView20(this);
            compassView = new CompassView(startAngle, getAssets());
            view.setRenderer(compassView);
            sensorManager.registerListener(compassView, sensor, SensorManager.SENSOR_DELAY_UI);
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
        sensorManager.unregisterListener(compassView);
        compassView.onDestroy();
    }

    private static int getStartAngle(int orientation) {

        if (orientation == Configuration.ORIENTATION_PORTRAIT) {

            return 0;
        }
        else if (orientation == Configuration.ORIENTATION_LANDSCAPE) {

            return -270;
        }

        return 0;
    }

}
