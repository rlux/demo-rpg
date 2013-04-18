cmake_minimum_required(VERSION 2.6)

project(tmxrenderer)
set(target tmxrenderer)

IF(NOT MSVC)
	ADD_DEFINITIONS(-std=c++0x -Werror=return-type)
ENDIF(NOT MSVC)


find_package(Qt4 COMPONENTS QtCore REQUIRED)
include(${QT_USE_FILE})

include_directories("include" "../tmx/include")

FILE(GLOB_RECURSE headers "include" *.h *.hpp)

set(sources
  src/Renderer.cpp
)

add_library(${target} SHARED ${sources} ${headers})

target_link_libraries(${target} tmx ${QT_LIBRARIES})
