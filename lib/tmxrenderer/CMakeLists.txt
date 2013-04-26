cmake_minimum_required(VERSION 2.6)

project(tmxrenderer)
set(target tmxrenderer)

IF(NOT MSVC)
	ADD_DEFINITIONS(-std=c++0x -Werror=return-type)
ENDIF(NOT MSVC)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core REQUIRED)

include_directories("include" "../tmx/include")

FILE(GLOB_RECURSE headers "include" *.h *.hpp)

set(sources
  src/Renderer.cpp
)

add_library(${target} SHARED ${sources} ${headers})

target_link_libraries(${target} tmx)
qt5_use_modules(${target} Widgets)