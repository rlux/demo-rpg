cmake_minimum_required(VERSION 2.6)

project(tmx)
set(target tmx)

IF(NOT MSVC)
	ADD_DEFINITIONS(-std=c++0x -Werror=return-type)
ENDIF(NOT MSVC)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core REQUIRED)
find_package(ZLIB REQUIRED)

include_directories("include")

FILE(GLOB_RECURSE headers "include" *.h *.hpp)

set(sources
	src/Loader.cpp
	src/XmlHandler.cpp
	src/Format.cpp
	src/Builder.cpp
	src/Base.cpp
	src/Layer.cpp
	src/ImageLayer.cpp
	src/TileLayer.cpp
  src/Data.cpp
	src/ObjectLayer.cpp
	src/Cell.cpp
	src/Tile.cpp
	src/TileMapper.cpp
	src/Map.cpp
	src/Tileset.cpp
	src/Image.cpp
	src/Object.cpp
)

add_library(${target} SHARED ${sources} ${headers})

target_link_libraries(${target} ${ZLIB_LIBRARIES})
qt5_use_modules(${target} Widgets Xml)
