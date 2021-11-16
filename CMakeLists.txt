cmake_minimum_required(VERSION 3.19.0)
project(spore VERSION 0.1.0)
include(FetchContent)

FetchContent_Declare(
  agt3d
  GIT_REPOSITORY https://github.com/akikoplays/agt3d.git
)
# set(FETCHCONTENT_FULLY_DISCONNECTED ON)
FetchContent_MakeAvailable(agt3d)

if (MSVC)
  add_compile_options(/W3 /WX)
  add_definitions(-DWINDOWS -DWINDOWS_LEAN_AND_MEAN)
else()
  add_compile_options(-W -Wall -pedantic 
    -Wno-unused-variable -Wno-deprecated-volatile -Wno-reorder-ctor -Wno-unused-parameter)
endif()

# find includes in the corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
if(MSVC)
  # in visual studio use CMakeSettings.json and set the 
  # "cmakeCommandArgs": " -DCMAKE_PREFIX_PATH=\"D:\\packages\\opencv_450\"" or whatever your local path is to opencv install folder
  #set(CMAKE_PREFIX_PATH "D:/packages/opencv_450/build")
else()
  # currently WIP - I need to switch to CMake presets available in 3.19 to be able to replicate vs code and vs cmake builds and support
  # user (local) configuration
  set(CMAKE_PREFIX_PATH "/Users/borisp/Qt/6.1.3/macos/")
endif()

find_package(OpenCV REQUIRED)

# Qt modules (https://doc.qt.io/qt-6/qtmodules.html) you're using in your application
message("Looking for Qt...")
find_package(Qt6 COMPONENTS Gui Widgets Quick Qml REQUIRED)
if (${Qt6_FOUND})
    message("Found Qt " ${Qt6_VERSION})
else()
    message("Couldn't find Qt")
endif()

#-------------------------------------------------------
# Sources
#-------------------------------------------------------

file(GLOB SRCS 
  *.cpp 
  *.h 
  ui/*.cpp
  ui/*.h
)
  
file (GLOB UI_SRCS
  ui/*.ui
  ui/*.qrc
)

add_executable(${PROJECT_NAME} 
  ${SRCS}
  ${UI_SRCS}
)

#-------------------------------------------------------
# Target Properties
#-------------------------------------------------------

target_precompile_headers(agt3d PRIVATE 
  "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h>"
)

set_target_properties(agt3d PROPERTIES CXX_STANDARD 20)

set_target_properties(${PROJECT_NAME} PROPERTIES
    QT_QML_MODULE_VERSION 1.0
    QT_QML_MODULE_URI AGT
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
  AUTOMOC TRUE
  AUTORCC TRUE
  AUTOUIC TRUE
)
qt6_qml_type_registration(${PROJECT_NAME})

target_link_libraries( ${PROJECT_NAME}
  PUBLIC
    ${OpenCV_LIBS}
    Qt6::Widgets
    Qt6::Quick
    Qt6::Qml
    Qt6::Gui
    agt3d
)
