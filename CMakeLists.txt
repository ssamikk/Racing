cmake_minimum_required(VERSION 3.5)

project(racing VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Quick QuickWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Quick QuickWidgets)


set(PROJECT_SOURCES
        src/main.cpp
        src/generalwindows.h
        src/generalwindows.cpp
        src/generalwindows.ui
        src/gamescene.h
        src/gamescene.cpp
        src/game.h
        src/game.cpp
        src/car.h
        src/car.cpp
        src/recource.qrc
        android/AndroidManifest.xml
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(racing
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(racing SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(racing
            ${PROJECT_SOURCES}
        )
    endif()
endif()

qt_add_qml_module(racing
    URI racing
    VERSION 1.0
    QML_FILES src/main.qml
)

set_property(TARGET racing APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)

set_target_properties(racing PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.samko.ru
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(racing
    PRIVATE Qt6::Quick)

target_link_libraries(racing PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_link_libraries(racing PRIVATE Qt${QT_VERSION_MAJOR}::QuickWidgets)

install(TARGETS racing
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(racing)
endif()

