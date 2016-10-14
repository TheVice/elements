package com.yegorov.alexey.elements.api;

public class ElementsCompass {

	static {

		System.loadLibrary("elements");
	}

	public static native int create(Object manager);
	public static native boolean startup(int id, int width, int height);
	public static native boolean destroy(int id);
	public static native boolean render(int id);
	public static native boolean rotation(int id, float omega);
}
