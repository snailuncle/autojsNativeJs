package com.jia.nativejs;
import java.lang.reflect.Field;
import java.lang.reflect.Method;

public class Main{
	
	static{
		System.loadLibrary("jni");
	}
	
	public native static Object init(ClassLoader loader);

}
