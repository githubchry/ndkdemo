/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_fsly_ndkdemo_JNIDemo */

#ifndef _Included_com_fsly_ndkdemo_JNIDemo
#define _Included_com_fsly_ndkdemo_JNIDemo
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_fsly_ndkdemo_JNIDemo
 * Method:    Sayhello
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_fsly_ndkdemo_JNIDemo_Sayhello__
  (JNIEnv *, jobject);

/*
 * Class:     com_fsly_ndkdemo_JNIDemo
 * Method:    Sayhello
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_fsly_ndkdemo_JNIDemo_Sayhello__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_fsly_ndkdemo_JNIDemo
 * Method:    add
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_fsly_ndkdemo_JNIDemo_add
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     com_fsly_ndkdemo_JNIDemo
 * Method:    checkPwd
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_fsly_ndkdemo_JNIDemo_checkPwd
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_fsly_ndkdemo_JNIDemo
 * Method:    increaseArrayElse
 * Signature: ([I)[I
 */
JNIEXPORT jintArray JNICALL Java_com_fsly_ndkdemo_JNIDemo_increaseArrayElse
  (JNIEnv *, jobject, jintArray);

/*
 * Class:     com_fsly_ndkdemo_JNIDemo
 * Method:    callbackSub
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_fsly_ndkdemo_JNIDemo_callbackSub
  (JNIEnv *, jobject);

/*
 * Class:     com_fsly_ndkdemo_JNIDemo
 * Method:    callbackHelloFormJava
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_fsly_ndkdemo_JNIDemo_callbackHelloFormJava
  (JNIEnv *, jobject);

/*
 * Class:     com_fsly_ndkdemo_JNIDemo
 * Method:    callbackPrintString
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_fsly_ndkdemo_JNIDemo_callbackPrintString
  (JNIEnv *, jobject);

/*
 * Class:     com_fsly_ndkdemo_JNIDemo
 * Method:    callbackSayHello
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_fsly_ndkdemo_JNIDemo_callbackSayHello
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif