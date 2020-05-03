## so中执行autojs脚本



## 加密方法作者: 

## 内个球 which_who@qq.com(1366505103) 

## 发布时间: 2020/05/02 23:08:50 



## 生成so教程

## 作者: 家
## qq群: 1019208967  webpack-autojs 



1. 用as创建一个新项目, 名字是TestSo

2. com.jia.testso.MainActivity , 与 MainActivity同级别, 新建一个Main.java

   ```java
   package com.jia.testso;
   
   import java.lang.reflect.Field;
   import java.lang.reflect.Method;
   
   public class Main{
   
       static{
           System.loadLibrary("jni");
       }
   
       public native static Object init(ClassLoader loader);
   
   }
   
   ```

3. 生成.class文件  buidl -> make project 

   F:\myGithub\TestSo\app\build\intermediates\javac\debug\classes\com\jia\testso\Main.class
   
4. 在app/src/main文件夹下新建一个jni文件夹

5. 打开Android Studio的终端，cd到这个目录app/src/main/jni

6. 输入命令,用javah命令生成生成c\c++头文件, 这个jni文件夹下生成一个.h文件

   javah -jni -classpath F:\myGithub\TestSo\app\build\intermediates\javac\debug\classes com.jia.testso.Main

   **请更改为自己的路径和包名**
   
7. 在jni目录下新建一个c/c++source file ,取名test.cpp 实现上面.h文件中的方法。

   ```cpp
   /*
    * Copyright (C) 2009 The Android Open Source Project
    *
    * Licensed under the Apache License, Version 2.0 (the "License");
    * you may not use this file except in compliance with the License.
    * You may obtain a copy of the License at
    *
    *      http://www.apache.org/licenses/LICENSE-2.0
    *
    * Unless required by applicable law or agreed to in writing, software
    * distributed under the License is distributed on an "AS IS" BASIS,
    * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    * See the License for the specific language governing permissions and
    * limitations under the License.
    *
    */
   #include <string.h>
   #include <jni.h>
   
   /* This is a trivial JNI example where we use a native method
    * to return a new VM String. See the corresponding Java source
    * file located at:
    *
    *   apps/samples/hello-jni/project/src/com/example/hellojni/HelloJni.java
    */
   extern "C"
   {
   	JNIEXPORT jobject JNICALL Java_com_jia_testso_Main_init(JNIEnv* env, jobject thiz, jobject loader)
   	{
   		jstring js = env->NewStringUTF("toastLog(\"String from JNI！\")");
   		
   		jclass ldclass = env->GetObjectClass(loader);
   		jmethodID ldmethod = env->GetMethodID(ldclass, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
   		
   		jclass cls0 = (jclass)env->CallObjectMethod(loader, ldmethod, env->NewStringUTF("com.stardust.autojs.script.ScriptSource"));
   		jclass cls1 = (jclass)env->CallObjectMethod(loader, ldmethod, env->NewStringUTF("com.stardust.autojs.script.StringScriptSource"));
   		jclass cls2 = (jclass)env->CallObjectMethod(loader, ldmethod, env->NewStringUTF("com.stardust.autojs.execution.ExecutionConfig"));
   		jclass cls  = (jclass)env->CallObjectMethod(loader, ldmethod, env->NewStringUTF("com.stardust.autojs.ScriptEngineService"));
   		
   		jmethodID ssmethod = env->GetMethodID(cls1, "<init>", "(Ljava/lang/String;)V");
   		jobject ssobj = env->NewObject(cls1, ssmethod, js);
   		
   		jmethodID defmethod = env->GetStaticMethodID(cls2, "getDefault", "()Lcom/stardust/autojs/execution/ExecutionConfig;");
   		jobject defobj = env->CallStaticObjectMethod(cls2, defmethod);
   		
   		jmethodID cbmethod = env->GetStaticMethodID(cls, "getInstance", "()Lcom/stardust/autojs/ScriptEngineService;");
   		jobject cbobj = env->CallStaticObjectMethod(cls, cbmethod);
   		
   		jmethodID exmethod = env->GetMethodID(cls, "execute", "(Lcom/stardust/autojs/script/ScriptSource;Lcom/stardust/autojs/execution/ExecutionConfig;)Lcom/stardust/autojs/execution/ScriptExecution;");
   		jobject exobj = env->CallObjectMethod(cbobj, exmethod, ssobj, defobj);
   		
   		return exobj;
   	}
   }
   
   ```

8. 在jni文件夹下新建Android.mk和Application.mk文件。

   Android.mk

   ```
      LOCAL_PATH := $(call my-dir)
      include $(CLEAR_VARS)
      LOCAL_MODULE := jni
      LOCAL_SRC_FILES := test.cpp
      include $(BUILD_SHARED_LIBRARY)
   ```

   Application.mk

   ```
      APP_PLATFORM := android-15
      APP_ALLOW_MISSING_DEPS=true
   ```

   

9. 设定ndk路径  project structure / SDK Location / Android NDK location

   C:\Users\jia\AppData\Local\Android\Sdk\ndk\21.0.6113669

10. 终端进入到jni目录，输入指令 ndk-build,就会生成相应的so文件。

    ```
    F:\myGithub\TestSo\app\src\libs\armeabi-v7a\libjni.so
    ```

    

11. 解压apk, 提取classes2.dex

    ```
    F:\myGithub\TestSo\app\build\outputs\apk\debug\app-debug.apk
    ```

12. 把libjni.so 和classes2.dex 复制到/sdcard/脚本

13. 用普通版autojs执行脚本

    ```js
    /*
     * @Author: 家
    ```
 * @QQ: 203118908
     * @bilibili: 晓宇小凡
     * @versioin: 1.0
     * @Date: 2020-05-02 23:15:47
     * @LastEditTime: 2020-05-03 16:23:35
     * @LastEditors: 家
     * @Description: so中执行autojs脚本
     * @FilePath: \autojsNativeJs\nativeJs\main.js
     * @学习格言: 即用即学, 即学即用
     * @加密方法是 内个球  which_who@qq.com(1366505103)  2020/05/02 23:08:50 制作完成
     */
    var ctx = context;
    var cwd = files.cwd();
    var dexpath=cwd+"/classes2.dex"
    var sopath=cwd+"/libjni.so"
    log('dexpath = '+dexpath)
    log('sopath = '+sopath)
    var jnipath=ctx.getDir("libs", android.app.Activity.MODE_PRIVATE);
    log('jnipath = '+jnipath)
    var dirpath=ctx.getDir("dex", android.app.Activity.MODE_PRIVATE).getAbsolutePath();
    log('dirpath = '+dirpath)
    copy(sopath, new java.io.File(jnipath, "libjni.so").getAbsolutePath());
    var dcl=new Packages.dalvik.system.DexClassLoader(dexpath, dirpath, jnipath, java.lang.ClassLoader.getSystemClassLoader());
    
    var cls=dcl.loadClass("com.jia.testso.Main")
    var api=cls.newInstance()
    api.init(ctx.getClass().getClassLoader());
    
    function copy(f, t){
    	var fip = new java.io.FileInputStream(f).getChannel();
    	var fop = new java.io.FileOutputStream(t).getChannel();
    	fip.transferTo(0, fip.size(), fop);
    	fip.close();fop.close();
    }
    
    ```
    
    ```
14. String from JNI！
















   ​	

   

   





   





































