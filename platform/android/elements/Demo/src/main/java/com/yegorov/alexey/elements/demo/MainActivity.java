package com.yegorov.alexey.elements.demo;

import android.app.Activity;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;

import com.badlogic.gdx.GL2Test;
import com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView20;

public class MainActivity extends Activity {

    private DemoView demoView;
    private com.badlogic.gdx.backends.android.surfaceview.GLSurfaceView20 view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {

            throw new RuntimeException("Run-time check of permission not implemented. " +
                                       "Required READ_EXTERNAL_STORAGE and WRITE_EXTERNAL_STORAGE");
        }

        if (!Environment.MEDIA_MOUNTED.equals(Environment.getExternalStorageState())) {

            throw new RuntimeException("External storage is " + Environment.getExternalStorageState());
        }

        if (GL2Test.checkGL20Support()) {

            String path_to_apk = getPathToApk();
            //String path_to_cache = getCacheDir().getAbsolutePath();
            String path_to_cache = String.format("%s/%s/%s",
                    Environment.getExternalStorageDirectory().getAbsolutePath(),
                    getPackageName(),
                    getCacheDir().getName());

            view = new GLSurfaceView20(this);
            demoView = new DemoView(path_to_apk, path_to_cache);
            view.setRenderer(demoView);
            view.setOnTouchListener(demoView);
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
        demoView.onDestroy();
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
