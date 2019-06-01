package com.fsly.ndkdemo;

import android.util.Log;

//java代码内容跟JNIDemo一致，在C层使用动态注册的方法实现
//参考 https://www.luoxudong.com/360.html

public class JNIDynamicRegisterDemo {
    {
        System.loadLibrary("dynamic");    //这里对应的是CMakeList文件里面的名字
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
