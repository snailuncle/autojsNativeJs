## so中执行autojs脚本



## 加密方法作者: 

## 内个球 which_who@qq.com(1366505103) 

## 发布时间: 2020/05/02 23:08:50 



## 生成so教程

## 作者: 家





```java
package com.jia.generateso;
```

2. MainActivity同级, 新建一个MyJni.java文件

   ```java
   package com.jia.generateso;
   
   public class MyJni {
   
       static {
           System.loadLibrary("MyJni");
       }
   
       public native static String getString();
   }
   
   
   ```

3. 生成.class文件

   buidl -> make project 

   class文件路径: F:\myGithub\GenerateSo\app\build\intermediates\javac\debug\classes\com\jia\generateso\MyJni.class

4. 在app/src/main文件夹下新建一个jni文件夹

5. 打开Android Studio的终端，cd到这个目录app/src/main/jni

6. 输入命令,用javah命令生成生成c\c++头文件, 这个jni文件夹下生成一个.h文件

   ### 请更改为自己的路径和包名

   

   `javah -jni -classpath F:\myGithub\NativeJs\app\build\intermediates\javac\debug\classes com.jia.nativejs.jni`

   

   ```
   javah -jni -classpath F:\myGithub\GenerateSo\app\build\intermediates\javac\debug\classes com.jia.generateso.MyJni
   ```

7. 在jni目录下新建一个c/c++source file ,取名test.c 实现上面.h文件中的方法。

   test.c

   ```c
   #include "jni.h"
   #include "com_jia_generateso_MyJni.h"
   
   JNIEXPORT jstring JNICALL Java_com_jia_generateso_MyJni_getString
     (JNIEnv *env, jclass jz){
   
     return (*env)->NewStringUTF(env,"this is the first time for me to use jni");
   
     }
   
   ```

8. 在jni文件夹下新建Android.mk和Application.mk文件。

   ### c版本

   

   Android.mk

   ```
   LOCAL_PATH := $(call my-dir)
   include $(CLEAR_VARS)
   LOCAL_MODULE := MyJni
   LOCAL_SRC_FILES := Test.c
   include $(BUILD_SHARED_LIBRARY)
   
   ```

   Application.mk

   ```
   APP_ABI := all
   ```

   

   ### c++版本

   

   Android.mk

   ```
   LOCAL_PATH := $(call my-dir)
   include $(CLEAR_VARS)
   LOCAL_MODULE := MyJni
   LOCAL_SRC_FILES := Test.cpp
   include $(BUILD_SHARED_LIBRARY)
   
   ```

   Application.mk

   ```
   APP_PLATFORM := android-15
   APP_ALLOW_MISSING_DEPS=true
   
   ```

   



9. 设定ndk路径   project structure / SDK Location / Android NDK location

10. 终端进入到jni目录，输入指令 ndk-build,就会生成相应的so文件。

11. 提取app中的classes2.dex

12. 提取armeabi-v7a下的libMyJni.so文件

13. 执行js脚本

   ```
    let dexFilepath = files.path("./classes2.dex");
    let soFilepath = files.path("/sdcard/libMyJni.so");
    
    log('复制so文件到lib文件夹 开始')
    // if (!files.exists(runtime.files.join(runtime.libraryDir, "libMyJni.so"))) {
      files.copy(soFilepath, runtime.files.join(runtime.libraryDir, "libMyJni.so"));
      log('复制so文件到lib文件夹 结束')
    // }
    runtime.loadDex(dexFilepath);
    
    importClass(com.jia.generateso.MyJni);
    let r = MyJni.getString();
    console.log(r);
    
   ```


​    