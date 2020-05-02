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
	JNIEXPORT jobject JNICALL Java_com_jia_nativejs_Main_init(JNIEnv* env, jobject thiz, jobject loader)
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
