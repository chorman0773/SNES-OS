#ifndef __JNINatives_hpp_2018_05_23_13_34
#define __JNINatives_hpp_2018_05_23_13_34

#include "jni/jni.h"

#define JNICALL extern "C"

JNICALL void Java_java_lang_Object_registerNatives(JNIENV*, jclass);
JNICALL void Java_java_lang_invoke_MethodHandle_registerNatives(JNIENV*,jclass);
JNICALL void Java_java_lang_invoke_VarHandle_registerNatives(JNIENV*,jclass);
JNICALL void Java_java_lang_invoke_MethodHandles_registerNatives(JNIENV*,jclass);
JNICALL void Java_java_lang_invoke_MethodHanldes_Lookup_registerNatives(JNIENV*,jclass);
JNICALL void Java_java_lang_ref_WeakReference_registerNatives(JNIENV*,jclass);
JNICALL void Java_java_lang_ref_SoftReference_registerNatives(JNIENV*,jclass);
JNICALL void Java_java_lang_reflect_Proxy_registerNatives(JNIENV*,jclass);





#endif
