#include <jni.h>
#include <string>
#include <android/log.h>

#define TAG "native-lib"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE,  TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,     TAG, __VA_ARGS__)   //警告
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,    TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,     TAG, __VA_ARGS__)   //绿色
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,    TAG, __VA_ARGS__)   //红色
/*
.externalNativeBuild    —> cmake 编译好的文件, 显示支持的各种硬件等信息 存放 .so 文件等Cmake相关文件
src/main/cpp            —> 众所周知 JNI Folder 。C 语言程序的逻辑部分, native-lib.cpp 文件名可自行修改
CMakeLists.txt          —> CMake 脚本配置的文件, 具体可查阅 CMake官网的资料
*/
extern "C"  //暴露给外部使用。 确保所有Java需要调用的C方法都放在extern “C”中，这样CMake才会帮我们正确编译。
JNIEXPORT jstring JNICALL
//用C/C++所写的源代码中的方法名称必须是全路径的方法名,然后以Java开头,分割使用下划线.
Java_com_fsly_ndkdemo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++, hello world!";
    return env->NewStringUTF(hello.c_str());
}
