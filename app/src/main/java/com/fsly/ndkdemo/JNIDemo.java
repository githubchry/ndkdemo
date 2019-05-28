package com.fsly.ndkdemo;

import android.util.Log;

/**
 * Created by a8512 on 2017/9/9.
 * 作用:java调用对用C代码的桥梁
 * 这个“JNI”类名可能会误导人，其实叫阿猫阿狗都可以
 *
 * C代码编写：两种方式
 * 1.不需要头文件  直接新建.c文件
 * 2.使用javah命令生成对应的头文件，里面会包括已经转化好了的对应C函数名
 *
 * 推荐使用第二种方式使用javah命令生成.h文件
 * 这种方式也有多种方法，这里使用AS自带终端实现
 * 1.点击下方Terminal,输入命令 cd app\src\main\java,进入对应的JNI类目录
 * 2.执行命令：javah 全类名（右键类名copy refrrence可以拷贝全类名），可以忽略的错误: 编码GBK的不可映射字符
 * 3.可以看到app\src\main\java目录下会多出一个.h文件,把它拖到cpp目录就可以
 * 4.在cpp目录根据这个.h文件新建/编写对应的.c/.cpp代码
 */

public class JNIDemo {

    {
        //System.loadLibrary("hello");    //这里对应的是CMakeList文件里面的名字
        System.loadLibrary("jnidemo");    //这里对应的是CMakeList文件里面的名字
    }

    /**
     * 定义native方法
     * 调用C代码相应的方法
     * @return "hello"
     */
    public native String Sayhello();

    /**
     * 从java传入字符串，C语言拼接返回
     * @param s
     * @return s+"add I form C"
     */
    public native String Sayhello(String s);

    /**
     * 从java传入两个int，C语言做加法运算后返回
     * @param a
     * @param b
     * @return a+b
     */
    public native int add(int a, int b);

    /**
     * 检查java传入的密码是否正确
     * @param pwd
     * @return 正确返回200 错误返回400
     */
    public native int checkPwd(String pwd);

    /**
     * C代码给java传入的整型数组每个元素都加上10
     * @param intArray
     * @return
     */
    public native int[] increaseArrayElse(int[] intArray);



    /**
     * 以上是java调用C的demo
     * -------------------------------------------------------------------------
     * 下面是C调用java的demo
     */

    //下面4个demo：当执行这些native方法的时候，通知C调用java相应的方法
    public native void callbackSub();
    public native void callbackHelloFormJava();
    public native void callbackPrintString();
    public native void callbackSayHello();

    private static final String TAG = "JNIDemo";

    public int sub(int x, int y){
        Log.e(TAG,"sub("+x+","+y+")");
        return x-y;
    }

    public void helloFormJava(){
        Log.e(TAG,"helloFormJava()");
    }

    public void printString(String s){
        Log.e(TAG,"C传过来text:"+s);
    }

    public static void sayHello(String s){
        Log.e(TAG,"这是java中的JNIDemo类里面的sayHello(String s)方法.此时被C调用了:"+s);
    }
}
