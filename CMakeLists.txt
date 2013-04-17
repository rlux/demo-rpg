cmake_minimum_required(VERSION 2.6)

project(demo-rpg)
set(target demo-rpg)

IF(NOT MSVC)
	ADD_DEFINITIONS(-std=c++0x -Werror=return-type)
ENDIF(NOT MSVC)


find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
include(${QT_USE_FILE})

include_directories("include" "lib/tmx/include")

FILE(GLOB_RECURSE headers "include" *.h *.hpp)

set(sources
	src/main.cpp
)

#QT4_WRAP_CPP(moc_sources ...)
#QT4_WRAP_UI(ui_headers ...)

add_subdirectory("lib")

add_executable(${target} ${sources} ${headers})

target_link_libraries(${target} tmx ${QT_LIBRARIES})


#copy data
add_custom_command(
  TARGET ${target} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
)