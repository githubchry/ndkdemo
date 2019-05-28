#include <jni.h>    //必要
/**
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
 */


/**
 * jstring      :返回值
 * JNIEnv *env  :里面有很多方法
 * jobject jobj :谁调用了这个方法就是谁的实例
 *
 * 两个参数是固定的,java调用的时候不需要写上去，系统会自动追加。这里的jobj就是JNI.this
 * @return
 */
jstring Java_com_fsly_ndkdemo_JNISayHello_Say(JNIEnv *env, jobject jobj)     //Java_全类名_方法名
{

    //jstring     (*NewString)(JNIEnv*, const jchar*, jsize);
    //jstring     (*NewStringUTF)(JNIEnv*, const char*);
    char* text = "new Hello!-- JNIHello.c, libhello.so";
    return (*env)->NewStringUTF(env, text);

}

/**
 * 编写完函数  需要修改CMakeLists.txt文件  编译so文件
 *
 * #每多一个库文件 这里都要添加一段add_library(库名\n  SHARED\n  源文件)
add_library( # Sets the name of the library.
             hello     # 这个是jni编译生产的so库的名字  最后生成：libhello.so

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             hello.c)                      # 要编译的c/c++文件列表 文件路径相对于cmake文件路径
*/