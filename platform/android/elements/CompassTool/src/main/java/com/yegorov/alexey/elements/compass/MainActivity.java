package com.yegorov.alexey.elements.compass;

import android.app.Activity;
import android.content.Context;
//import android.hardware.Sensor;
//import android.hardware.SensorManager;
import android.content.res.Configuration;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.DisplayMetrics;
import android.view.WindowManager;

import com.yegorov.alexey.elements.api.Elements;

public class MainActivity extends Activity {

    //private SensorManager sensorManager;
    private CompassView compassView;
    private GLSurfaceView view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        /*sensorManager = (SensorManager)getSystemService(Context.SENSOR_SERVICE);
        Sensor sensor = sensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION);

        if (sensor == null) {

            throw new RuntimeException("There is no orientation sensor");
        }*/

        final int startAngle = getStartAngle(getResources().getConfiguration().orientation);
        view = new GLSurfaceView(this);

        Elements.initializeAssets(getAssets());
        Elements.initializePreferences(PreferenceManager.getDefaultSharedPreferences(getApplicationContext()));

        WindowManager wm = (WindowManager) getSystemService(Context.WINDOW_SERVICE);
        DisplayMetrics metrics = new DisplayMetrics();
        wm.getDefaultDisplay().getMetrics(metrics);

        Elements.initializeMetrics(metrics);

        compassView = new CompassView(startAngle, getAssets());

        view.setEGLContextClientVersion(2);
        view.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        view.setPreserveEGLContextOnPause(true);

        view.setRenderer(compassView);
        //sensorManager.registerListener(compassView, sensor, SensorManager.SENSOR_DELAY_UI);
        setContentView(view);
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
        //sensorManager.unregisterListener(compassView);
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
