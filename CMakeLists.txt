cmake_minimum_required(VERSION 2.8.8)

project(demo-rpg)
set(target demo-rpg)

cmake_policy(SET CMP0009 NEW)

IF(NOT MSVC)
	ADD_DEFINITIONS(-std=c++0x -Werror=return-type)
ENDIF(NOT MSVC)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core REQUIRED)

include_directories("include" "lib/tmx/include" "lib/tmxrenderer/include" )

FILE(GLOB_RECURSE headers "include" *.h *.hpp)

set(sources
	src/main.cpp
	src/MainWindow.cpp
	src/Map.cpp
	src/Game.cpp
	src/GameState.cpp
	src/GameLoader.cpp
	src/GameWidget.cpp
	src/GameRenderer.cpp
	src/AnimatedObject.cpp
	src/Engine.cpp
	src/Player.cpp
	src/NPC.cpp
	src/NPCFactory.cpp
	src/Animation.cpp
	src/EventTrigger.cpp
	src/MapEvent.cpp
)

add_subdirectory("lib")

add_executable(${target} ${sources}  ${headers})

target_link_libraries(${target} tmx tmxrenderer)
qt5_use_modules(${target} Widgets Xml)

#copy data
add_custom_command(
  TARGET ${target} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
)