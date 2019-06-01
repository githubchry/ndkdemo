//
// Created by a8512 on 2019/6/1.
//

#ifndef NDKDEMO_JNIDYNAMICREGISTERDEMO_H
#define NDKDEMO_JNIDYNAMICREGISTERDEMO_H
#include <jni.h>

//extern "C"表示让编译器将本代码作为C语言来编译，但是C语言是不支持重载的 所以函数不能同名


#ifdef __cplusplus
extern "C" {
#endif
/*
 * Method:    Sayhello
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Sayhello_a
        (JNIEnv *, jobject);

/*
 * Method:    Sayhello
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Sayhello_b
        (JNIEnv *, jobject, jstring);

/*
 * Method:    add
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL add
        (JNIEnv *, jobject, jint, jint);

/*
 * Method:    checkPwd
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL checkPwd
        (JNIEnv *, jobject, jstring);

/*
 * Method:    increaseArrayElse
 * Signature: ([I)[I
 */
JNIEXPORT jintArray JNICALL increaseArrayElse
        (JNIEnv *, jobject, jintArray);

/*
 * Class:     com_fsly_ndkdemo_JNIDemo
 * Method:    callbackSub
 * Signature: ()V
 */
JNIEXPORT void JNICALL callbackSub
        (JNIEnv *, jobject);

/*
 * Method:    callbackHelloFormJava
 * Signature: ()V
 */
JNIEXPORT void JNICALL callbackHelloFormJava
        (JNIEnv *, jobject);

/*
 * Method:    callbackPrintString
 * Signature: ()V
 */
JNIEXPORT void JNICALL callbackPrintString
        (JNIEnv *, jobject);

/*
 * Method:    callbackSayHello
 * Signature: ()V
 */
JNIEXPORT void JNICALL callbackSayHello
        (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif

#endif //NDKDEMO_JNIDYNAMICREGISTERDEMO_H
