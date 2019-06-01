package com.fsly.ndkdemo;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.TextView;

import static java.lang.String.valueOf;


/*
 * NDK开发流程
 * 1.在java里面写native代码
 * 2.写C代码 - 生成头文件
 * 3.配置动态链接库的名称
 * 4.加载动态链接库
 * 5.使用
 * */
public class MainActivity extends AppCompatActivity {
    private JNIDemo jniDemo;
    private JNIDynamicRegisterDemo jniDynamicRegisterDemo;
    private JNISayHello jniSayHello;

    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        jniSayHello = new JNISayHello();
        String text0 = jniSayHello.Say();
        Log.e(TAG, text0);

        Log.e(TAG, "==========================================================================================");
        //==========================================================================================
        jniDemo = new JNIDemo();
        String text1 = jniDemo.Sayhello();
        Log.e(TAG, text1);

        String text2 = jniDemo.Sayhello("Hello!I am from java!");
        Log.e(TAG, text2);

        int code = jniDemo.checkPwd("000000");       //正确：000000
        Log.e(TAG, valueOf(code));

        int sum = jniDemo.add(5,7);
        Log.e(TAG, valueOf(sum));

        int array1[] = {1,2,3,4,5};
        int array2[] = jniDemo.increaseArrayElse(array1);     //C里面也改了array1本身 传过去的是地址，改的地址上的数据 所以打印出来都变了
        for(int i = 0;i<5;i++){
            Log.e(TAG, "array1["+i+"]="+valueOf(array1[i])+", array2["+i+"]="+valueOf(array2[i]));
        }

        /**
         * 以上是java调用C的demo
         * -------------------------------------------------------------------------
         * 下面是C调用java的demo
         */

        Log.e(TAG, "------------------------------------------------------------------------------------------");
        jniDemo.callbackSub();
        jniDemo.callbackHelloFormJava();
        jniDemo.callbackPrintString();
        jniDemo.callbackSayHello();

        //==========================================================================================

        Log.e(TAG, "==========================================================================================");
        //==========================================================================================
        jniDynamicRegisterDemo = new JNIDynamicRegisterDemo();
        String text11 = jniDynamicRegisterDemo.Sayhello();
        Log.e(TAG, text11);

        String text22 = jniDynamicRegisterDemo.Sayhello("Hello!I am from java!");
        Log.e(TAG, text22);

        int code1 = jniDynamicRegisterDemo.checkPwd("123455");       //正确：000000
        Log.e(TAG, valueOf(code1));

        int sum1 = jniDynamicRegisterDemo.add(5,7);
        Log.e(TAG, valueOf(sum1));

        int array3[] = {1,2,3,4,5};
        int array4[] = jniDynamicRegisterDemo.increaseArrayElse(array3);     //C里面也改了array1本身 传过去的是地址，改的地址上的数据 所以打印出来都变了
        for(int i = 0;i<5;i++){
            Log.e(TAG, "array3["+i+"]="+valueOf(array3[i])+", array3["+i+"]="+valueOf(array4[i]));
        }

        /**
         * 以上是java调用C的demo
         * -------------------------------------------------------------------------
         * 下面是C调用java的demo
         */
        Log.e(TAG, "------------------------------------------------------------------------------------------");

        jniDynamicRegisterDemo.callbackSub();
        jniDynamicRegisterDemo.callbackHelloFormJava();
        jniDynamicRegisterDemo.callbackPrintString();
        jniDynamicRegisterDemo.callbackSayHello();

        Log.e(TAG, "==========================================================================================");
        //==========================================================================================
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    // Used to load the 'native-lib' library on application startup.
    static {
        //此处的form库的名称需要和CMakeLists.txt中配置的相同
        System.loadLibrary("native-lib");
    }
}
