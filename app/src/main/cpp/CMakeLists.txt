# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        native-lib                                 # 这个是jni编译生产的so库的名字，最后生成：libhello.so

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp)               # 要编译的c/c++文件列表 文件路径相对于cmake文件路径

#每多一个库文件 这里都要添加一段add_library(库名  SHARED  源文件)
add_library(jnidemo         SHARED      JNIDemo.cpp)
add_library(hello           SHARED      JNIHello.c)


#最终生成的.so库文件在这里：app/build/intermediates/cmake/debug/obj/
#如果把已经生成好的库文件拷贝到app/src/main/jniLibs目录下 在配置引用链接 可以直接使用 这种情况下不需要编译源文件

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

#find_library( lib):在NDK目录下搜索lib, 保存在变量val中。value后面使用的时候：${val}
find_library( # Sets the name of the path variable.
        log-lib                                   # 依赖的系统so库

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

#当a.so依赖b.so的时候 使用target_link_libraries(a.so  a.so)链接起来，结合find_library使用
target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib} )

target_link_libraries( jnidemo        ${log-lib} )  #设置要链接的库文件的名称


