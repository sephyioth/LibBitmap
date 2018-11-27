
cmake_minimum_required(VERSION 3.4.1)

include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/include)

add_library(libopencv_java3 SHARED IMPORTED)
set_target_properties(libopencv_java3 PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/src/main/jniLibs/native/${ANDROID_ABI}/libopencv_java3.so)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

file(GLOB source_files "src/main/cpp/*.cpp" "src/main/cpp/*.H" "src/main/cpp/*.c"
        "src/main/cpp/BitmapFactory/*.H"
        "src/main/cpp/BitmapFactory/*.cpp"
        "src/main/cpp/BitmapFactory/BitmapParse/*.H"
        "src/main/cpp/BitmapFactory/BitmapParse/*.cpp"
        "src/main/cpp/BitmapFactory/BitmapUtills/*.cpp"
        "src/main/cpp/BitmapFactory/BitmapUtills/*.h"
        "src/main/cpp/BitmapFactory/BitmapUtills/Matrix.h"
        "src/main/cpp/BitmapFactory/BitmapUtills/Matrix.cpp"
        "src/main/cpp/BitmapFactory/GNBitmap/*.cpp"
        "src/main/cpp/BitmapFactory/GNBitmap/*.h"
        "src/main/cpp/BitmapFactory/Blur/*.cpp"
        "src/main/cpp/BitmapFactory/Blur/*.h"
        "src/main/cpp/BitmapFactory/Conversion/*.cpp"
        "src/main/cpp/BitmapFactory/Conversion/*.h"
        "src/main/cpp/BitmapFactory/BitmapFilter/*.cpp"
        "src/main/cpp/BitmapFactory/BitmapFilter/*.h"
        "src/main/cpp/CL/*.hpp"
        "src/main/cpp/CL/*.h"
        "src/main/cpp/ImageNativeImpl.cpp"
        )

add_library( # Sets the name of the library.
        gimage

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${source_files})


# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        gimage
        -ljnigraphics
        libopencv_java3
        log
        ${log-lib})