cmake_minimum_required(VERSION 3.5)

project(qvlctest LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wignored-attributes -fpermissive")
endif()

include("${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/vlc-3.0.12/vlc.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libvlcpp/libvlcpp.cmake")

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    qvlc.cpp
    qvlc.h
    res.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qvlctest
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(qvlctest SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(qvlctest
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(qvlctest PUBLIC ${VlcMasterIncludePath})
target_include_directories(qvlctest PUBLIC ${libvlcppIncludePath})

target_link_libraries(qvlctest PUBLIC ${libvlccore})
target_link_libraries(qvlctest PUBLIC ${libvlc})
target_link_libraries(qvlctest PUBLIC ${axvlc})
target_link_libraries(qvlctest PUBLIC ${npvlc})
target_link_libraries(qvlctest PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
