void Method (JNIEnv *env, jobject thiz) { 
    setPolicy(thiz);
    DEX(thiz, "/storage/emulated/0/Android/data/com.company.application/cache/handler.dex", "com.company.activity.Example");
}
