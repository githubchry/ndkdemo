package com.fsly.ndkdemo;

/**
 * Created by a8512 on 2017/9/9.
 */

public class JNISayHello {

    {
        System.loadLibrary("hello");
        /**
         * 加载库文件
         * 两种情况
         * 1.对应CMakeList文件里面根据.c文件编译出来的库文件
         * 2.已经写编译好了的.so文件
         *
         * 这里说一下第二种情况：如何直接使用已经编译好了的库文件
         * 1.在app/src/main目录下新建名为"jniLibs"的目录
         * 2.拷贝.so文件到jniLib目录下(app/build/intermediates/cmake/debug/obj下的文件夹就是编译出来的库文件，可以将需要用到的平台的库文件拷贝过去)
         *      jniLibs目录结构应该是这样的
         *      jniLibs ->arm64-v8a
         *                  ->.so
         *              ->armeabi
         *                  ->.so
         *              ->armeabi-v8a
         *                  ->.so
         *              ->x86
         *                  ->.so
         *              -> ...
         *                  ->...
         * 3.在保证java的JNI类能与.so对应上的情况下，rebuild
         *
         * 注意，这里有个优先级 app/src/main/jniLibs > app/build/intermediates/cmake/debug/obj
         * 程序会先从jniLibs目录寻找,so文件加载，如果找不到在去obj目录加载
         * 所以，此中.c文件和CMakeList.txt的更改不会影响到代码的运行
         */

    }

    /**
     * 定义native方法
     * 调用C代码相应的方法
     * @return "hello"
     */
    public native String Say();
}
