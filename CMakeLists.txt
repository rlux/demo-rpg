cmake_minimum_required(VERSION 2.6)

project(demo-rpg)
set(target demo-rpg)

IF(NOT MSVC)
	ADD_DEFINITIONS(-std=c++0x -Werror=return-type)
ENDIF(NOT MSVC)


find_package(Qt4 COMPONENTS QtCore QtGui QtXml REQUIRED)
include(${QT_USE_FILE})

include_directories("include" "lib/tmx/include" "lib/tmxrenderer/include" )

FILE(GLOB_RECURSE headers "include" *.h *.hpp)

set(sources
	src/main.cpp
	src/MainWindow.cpp
	src/Game.cpp
	src/GameLoader.cpp
	src/GameWidget.cpp
	src/GameRenderer.cpp
	src/AnimatedObject.cpp
	src/Engine.cpp
	src/Player.cpp
	src/NPC.cpp
	src/Animation.cpp
)

QT4_WRAP_CPP(moc_sources
  include/GameWidget.h
)
#QT4_WRAP_UI(ui_headers ...)

add_subdirectory("lib")

add_executable(${target} ${sources} ${moc_sources} ${headers})

target_link_libraries(${target} tmx tmxrenderer ${QT_LIBRARIES})


#copy data
add_custom_command(
  TARGET ${target} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
)