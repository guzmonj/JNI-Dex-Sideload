void setPolicy(JNIEnv *env, jobject thiz) {
    jclass klass = env->FindClass("android/os/StrictMode$ThreadPolicy$Builder");
    jmethodID method = env->GetMethodID(klass, "<init>", "()V");
    jobject o1 = env->NewObject(klass, method);

    method = env->GetMethodID(klass, "permitAll", "()Landroid/os/StrictMode$ThreadPolicy$Builder;");
    jobject o2 = env->CallObjectMethod(o1, method);

    method = env->GetMethodID(klass, "build", "()Landroid/os/StrictMode$ThreadPolicy;");
    jobject o3 = env->CallObjectMethod(o2, method);

    klass = env->FindClass("android/os/StrictMode");
    method = env->GetStaticMethodID(klass, "setThreadPolicy","(Landroid/os/StrictMode$ThreadPolicy;)V");
    env->CallStaticVoidMethod(klass, method, o3);
	
    env->DeleteLocalRef(klass);
    env->DeleteLocalRef(o1);
    env->DeleteLocalRef(o2);
    env->DeleteLocalRef(o3);

}

void DEX(JNIEnv *env, jobject thiz, const char *dexLocation, const char *javaClass) {
    jclass klass = env->FindClass("android/content/ContextWrapper");
    jmethodID method = env->GetMethodID(klass, "getClassLoader", "()Ljava/lang/ClassLoader;");
    jobject o11 = env->CallObjectMethod(thiz, method);

    method = env->GetMethodID(klass, "getApplicationInfo","()Landroid/content/pm/ApplicationInfo;");
    jobject o12 = env->CallObjectMethod(thiz, method);
    klass = env->FindClass("android/content/pm/ApplicationInfo");
    jfieldID field = env->GetFieldID(klass, "nativeLibraryDir", "Ljava/lang/String;");
    jobject o13 = env->GetObjectField(o12, field);

    klass = env->FindClass("android/content/ContextWrapper");
    method = env->GetMethodID(klass, "getExternalCacheDir", "()Ljava/io/File;");
    jobject o14 = env->CallObjectMethod(thiz, method);

    klass = env->FindClass("dalvik/system/BaseDexClassLoader");
    method = env->GetMethodID(klass, "<init>","(Ljava/lang/String;Ljava/io/File;Ljava/lang/String;Ljava/lang/ClassLoader;)V");
    jobject o16 = env->NewObject(klass, method, env->NewStringUTF(dexLocation), o14, o13, o11);

    klass = env->FindClass("java/lang/ClassLoader");
    method = env->GetMethodID(klass, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
    jobject o17 = env->CallObjectMethod(o16, method, env->NewStringUTF(javaClass));

    klass = env->FindClass("java/lang/Class");
    method = env->GetMethodID(klass, "newInstance", "()Ljava/lang/Object;");
    jobject o18 = env->CallObjectMethod(o17, method);

    klass = env->FindClass("java/lang/Class");
    jobjectArray array = env->NewObjectArray(1, klass, 0);
    klass = env->FindClass("android/content/Context");
    env->SetObjectArrayElement(array, 0, klass);

    klass = env->FindClass("java/lang/Class");
    method = env->GetMethodID(klass, "getMethod","(Ljava/lang/String;[Ljava/lang/Class;)Ljava/lang/reflect/Method;");
    jobject met = env->CallObjectMethod(o17, method, env->NewStringUTF("Init"), array);

    klass = env->FindClass("java/lang/reflect/Method");
    method = env->GetMethodID(klass, "setAccessible", "(Z)V");
    env->CallVoidMethod(met, method, true);

    klass = env->FindClass("java/lang/Object");
    jobjectArray array2 = env->NewObjectArray(1, klass, 0);
    env->SetObjectArrayElement(array2, 0, thiz);

    klass = env->FindClass("java/lang/reflect/Method");
    method = env->GetMethodID(klass, "invoke","(Ljava/lang/Object;[Ljava/lang/Object;)Ljava/lang/Object;");
    env->CallObjectMethod(met, method, o18, array2);

    klass = env->FindClass("java/io/File");
    method = env->GetMethodID(klass, "<init>", "(Ljava/lang/String;)V");
    jobject o20 = env->NewObject(klass, method, env->NewStringUTF(dexLocation));

    method = env->GetMethodID(klass, "exists", "()Z");
    jboolean b = env->CallBooleanMethod(o20, method);
    if (b) {
        method = env->GetMethodID(klass, "delete", "()Z");
        env->CallBooleanMethod(o20, method);
    }
	
    env->DeleteLocalRef(o11);
    env->DeleteLocalRef(o12);
    env->DeleteLocalRef(o13);
    env->DeleteLocalRef(o14);
    env->DeleteLocalRef(o16);
    env->DeleteLocalRef(o17);
    env->DeleteLocalRef(o18);
    env->DeleteLocalRef(klass);
    env->DeleteLocalRef(array);
    env->DeleteLocalRef(array2);
    env->DeleteLocalRef(met);
    env->DeleteLocalRef(o20);
}
