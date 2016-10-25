package com.yegorov.alexey.elements.character;

import android.app.Activity;
//import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
//import android.hardware.Sensor;
//import android.hardware.SensorManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;

import com.badlogic.gdx.GL2Test;
import com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView20;

public class CharacterWallpaperActivity extends Activity {

    //private SensorManager sensorManager;
    private CharacterWallpaperView characterWallpaperView;
    private com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView20 view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        /*sensorManager = (SensorManager)getSystemService(Context.SENSOR_SERVICE);
        Sensor sensor = sensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION);

        if (sensor == null) {

            throw new RuntimeException("There is no orientation sensor");
        }*/

        if (GL2Test.checkGL20Support()) {

            view = new GLSurfaceView20(this);

            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {

                characterWallpaperView = new CharacterWallpaperView(true, getAssets());
            }
            else {

                if (!Environment.MEDIA_MOUNTED.equals(Environment.getExternalStorageState())) {

                    throw new RuntimeException("External storage is " +
                                                Environment.getExternalStorageState());
                }

                String path_to_apk = getPathToApk();
                //String path_to_cache = getCacheDir().getAbsolutePath();
                String path_to_cache = String.format("%s/%s/%s",
                        Environment.getExternalStorageDirectory().getAbsolutePath(),
                        getPackageName(),
                        getCacheDir().getName());
                characterWallpaperView = new CharacterWallpaperView(true,
                                                                    path_to_apk,
                                                                    path_to_cache);
            }

            view.setRenderer(characterWallpaperView);
            /*sensorManager.registerListener(characterWallpaperView,
                                           sensor,
                                           SensorManager.SENSOR_DELAY_UI);*/
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

    public String getPathToApk() {

        PackageManager packageManager = getPackageManager();
        ApplicationInfo appInfo = null;

        try {

            appInfo = packageManager.getApplicationInfo(getPackageName(), 0);
        } catch (PackageManager.NameNotFoundException exc) {

            exc.printStackTrace();
            throw new RuntimeException("Unable to locate APK");
        }

        return appInfo.sourceDir;
    }

}
