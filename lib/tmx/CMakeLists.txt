cmake_minimum_required(VERSION 2.6)

project(tmx)
set(target tmx)

IF(NOT MSVC)
	ADD_DEFINITIONS(-std=c++0x -Werror=return-type)
ENDIF(NOT MSVC)


find_package(Qt4 COMPONENTS QtCore QtXml REQUIRED)
include(${QT_USE_FILE})

include_directories("include")

FILE(GLOB_RECURSE headers "include" *.h *.hpp)

set(sources
	src/Parser.cpp
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

target_link_libraries(${target} ${QT_LIBRARIES})
