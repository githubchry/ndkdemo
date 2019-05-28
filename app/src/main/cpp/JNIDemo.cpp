//
// Created by a8512 on 2017/9/9.
//

#include "com_fsly_ndkdemo_JNIDemo.h"
#include <string.h>
#include <android/log.h>

#define TAG "JNIDemo-cpp"
//打印log还要在CMakeList.txt加上target_link_libraries( jnidemo        ${log-lib} )设置要链接的库文件的名称
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE,  TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,     TAG, __VA_ARGS__)   //警告
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,    TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,     TAG, __VA_ARGS__)   //绿色
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,    TAG, __VA_ARGS__)   //红色
/**
 *
 * .c/.cpp函数JNIEnv调用区别
 * char* text = "Hello Wolrd.";
 * return (*env)->NewStringUTF(env, text);   //C就用这种方式
 * return env->NewStringUTF(text);           //C++用这种格式


 * JNIEXPORT和JNICALL 可留可不留
 *
 *  对应类型    可查看jni.h文件
 * Java类型       JNI别名       本地类型
 * boolean      jboolean    unsigned char
 * byte         jbyte       signed char
 * char         jchar       unsigned short
 * short        jshort      short
 * int          jint        int
 * long         jlong       long long
 * float        jfloat      float
 * double       jdouble     double
 *
 *
 * 编写完函数  需要修改CMakeLists.txt文件  编译so文件
 * #添加一行   add_library(库名  库的类型 源文件)
 * 库名：      是jni编译生产的so库的名字，在工程的全局域内必须是唯一的  如填hello最后生成：libhello.so
 * 类型：      STATIC静态 | SHARED动态 | MODULE
 * 源文件:     要编译的c/c++文件列表 文件路径相对于cmake文件路径
*/




/**
 * 重载模板1
 * JNIEnv *env  :里面有很多方法
 * jobject job  :谁调用了这个方法就是谁的实例
 * @return      "Hello!I am form C."
 */
 jstring Java_com_fsly_ndkdemo_JNIDemo_Sayhello__
        (JNIEnv *env, jobject job){

    char* text = "Hello!I am form C.";
    return env->NewStringUTF(text);
    //return (*env)->NewStringUTF(env, text);   //如果是用C语言格式就用这种方式
    //return env->NewStringUTF(text);           //C++用这种格式
}

/**
 * 重载模板2
 * JNIEnv *env  :里面有很多方法
 * jobject job :谁调用了这个方法就是谁的实例
 * jstring str  :java传入的字符串
 * @return      :str+"--Hello!I am form C."
 */
jstring Java_com_fsly_ndkdemo_JNIDemo_Sayhello__Ljava_lang_String_2
        (JNIEnv *env, jobject job, jstring str){

    const char* fromJava = env->GetStringUTFChars(str, 0);  //jstring转const char *  也可以在网上找jstring转char *
    const char* fromC = " -- Hello!I am form C.";

    char result[512];
    strcpy(result, fromJava);
    strcat(result, fromC);
    return env->NewStringUTF(result);
}

/**
 * jint         :返回值
 * JNIEnv *env  :里面有很多方法
 * jobject jobj :谁调用了这个方法就是谁的实例
 *jint a, jint b:两个参数
 *
 * 两个参数是固定的,java调用的时候不需要写上去，系统会自动追加。这里的jobj就是JNI.this
 * @return
 */
jint Java_com_fsly_ndkdemo_JNIDemo_add
        (JNIEnv *env, jobject jobj, jint a, jint b) {
    int sum = a + b;
    //由于java和C对应的int类型写法一样  可以直接返回
    return sum;
}

/**
 * 假设服务器的密码是"000000"
 */
JNIEXPORT jint JNICALL Java_com_fsly_ndkdemo_JNIDemo_checkPwd
        (JNIEnv *env, jobject job, jstring str){
    const char* origin = "000000";
    const char* fromJava = env->GetStringUTFChars(str, 0);  //jstring转const char *  也可以在网上找jstring转char *
    int ret = strcmp(origin, fromJava);
    LOGD("ret:%d\n",ret);
    if (ret == 0){
        return 200;     //密码正确
    } else{
        return 400;
    }
}

/**
 * 给jintArr的每个元素加上10  这个函数可以改成不返回数组，因为函数里面直接更改了传入的数组
 * JNIEnv *env      :里面有很多方法
 * jobject job      :谁调用了这个方法就是谁的实例
 *jintArray jintArr :入参是一个int数组
 * @return 返回一个int数组
 *
 * 看了下啥是 jintArray ，发现就是一个空结构体，继承自 jarray ，现在的你一脸懵逼。你是不是以为会传进来一个 jint 的数组？
 *
 * Naive 。
 *
 * 实际上，这个传进来的破玩意只是一个指向 JVM 里那块数组对应的内存的指针，类似 ID 一样的存在，
 * 你可以通过它获取数组的元素、设置数组的元素、获取数组的长度，但它本身和数组无关。也就是说，光有这个指针，是啥都干不了的。
 *
 * 所以我们需要用到那个 JNIEnv 指针，用它获取那个数组，并对 JVM 中对应的数组的元素进行赋值。
 */
JNIEXPORT jintArray JNICALL Java_com_fsly_ndkdemo_JNIDemo_increaseArrayElse
        (JNIEnv *env, jobject job, jintArray jarr){
    //1.得到数组长度
    int size = env->GetArrayLength(jarr);

    //2.得到数组元素
    jint* intArr =  env->GetIntArrayElements(jarr,JNI_FALSE);

    //3.遍历数组，加上10
    for (int i = 0; i < size; ++i) {
        //*(intArr+i) += 10;
        intArr[i] += 10;
    }
    /**
     * 下面这个语句必须要，不然java端不能获取到修改后的新数据,
     * 忘记调用ReleaseIntArrayElements会导致在一段较长的时间内固定数组，
     * 或者无法回收用于存储该数组的不可移动副本的内存。
     *
     */
    env->ReleaseIntArrayElements(jarr,intArr,JNI_OK);
    /**
     * 上面这句把 intArr 被操作之后的值赋回去。
     * JNI_OK 表示把 intArr 复制到 JVM 去，并释放 intArr 这个数组。
     * 还有两个可以传进去的值：
     * JNI_COMMIT 表示复制，但不释放。
     * JNI_ABORT 不复制，但释放资源。
     */

    //4.返回数组
    return jarr;
}



/**
 * 以上是java调用C的demo
 * -------------------------------------------------------------------------
 * 下面是C调用java的demo
 */


/**
 * C回调java方法的核心思想：反射
 * 调用java中JNIDemo类中的public int sub(int x, int y)的方法
 * 调用一个方法首先得到这个类的实例，要得到这个类的实例就要得到字节码
 *
 * 如何获得一个方法的签名？
 * 1.命令行窗口中，进入应用的classes/debug目录(cd app\build\intermediates\classes\debug)
 * 2.执行命令：javap -s 全类名 显示所有方法的签名信息
 * 执行命令之前需要rebuild一下
 *
 * GetStaticMethodID    获取静态方法
 * GetMethodID          获取普通方法
 *
 * CallIntMethod    返回一个int
 * CallVoidMethod   没有返回值
 */
JNIEXPORT void JNICALL Java_com_fsly_ndkdemo_JNIDemo_callbackSub
        (JNIEnv *env, jobject job){
    //1.得到字节码
    //jclass FindClass(const char* name)
    jclass jclazz = env->FindClass("com/fsly/ndkdemo/JNIDemo");

    //2.得到方法
    //jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    //最后一个参数是方法签名 通过javap -s 全类名获得
    jmethodID jmethodID = env->GetMethodID(jclazz, "sub", "(II)I");

    //3.实例化该类
    jobject jobject = env->AllocObject(jclazz);

    //4.调用方法
    //jint        (*CallIntMethod)(JNIEnv*, jobject, jmethodID, ...);
    int value = env->CallIntMethod(job, jmethodID, 2019, 1234);
    //printf("value:%d\n",value);     //这样是无法查看的
    LOGD("value:%d\n",value);
    //至此，成功调用了该java方法

}

JNIEXPORT void JNICALL Java_com_fsly_ndkdemo_JNIDemo_callbackHelloFormJava
        (JNIEnv *env, jobject job){

    jclass jclazz = env->FindClass("com/fsly/ndkdemo/JNIDemo");

    jmethodID jmethodID = env->GetMethodID(jclazz, "helloFormJava", "()V");

    jobject jobject = env->AllocObject(jclazz);

    env->CallVoidMethod(job, jmethodID);
}

JNIEXPORT void JNICALL Java_com_fsly_ndkdemo_JNIDemo_callbackPrintString
        (JNIEnv *env, jobject job){

    jclass jclazz = env->FindClass("com/fsly/ndkdemo/JNIDemo");

    jmethodID jmethodID = env->GetMethodID(jclazz, "printString", "(Ljava/lang/String;)V");

    jobject jobject = env->AllocObject(jclazz);

    char* text = "Hello!I am form C.";
    env->CallVoidMethod(job, jmethodID, env->NewStringUTF(text));
}

JNIEXPORT void JNICALL Java_com_fsly_ndkdemo_JNIDemo_callbackSayHello
        (JNIEnv *env, jobject job){

    jclass jclazz = env->FindClass("com/fsly/ndkdemo/JNIDemo");

    jmethodID jmethodID = env->GetStaticMethodID(jclazz, "sayHello", "(Ljava/lang/String;)V");

    jobject jobject = env->AllocObject(jclazz);

    char* text = "Hello!I am form C.";
    // void CallStaticVoidMethod(jclass clazz, jmethodID methodID, ...)
    env->CallStaticVoidMethod(jclazz, jmethodID, env->NewStringUTF(text));
}


