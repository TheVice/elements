package com.yegorov.alexey.elements.api;

public class Elements
{
    static
    {
        System.loadLibrary("elements");
    }

    public static native void initializeAssets(Object manager);
    public static native void initializeAssetsAtCache(String path_to_cache);
}
