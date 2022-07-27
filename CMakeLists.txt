cmake_minimum_required(VERSION 3.16..3.18)

project(minetest
  VERSION 5.6.0
  DESCRIPTION "An open source voxel game engine"
  HOMEPAGE_URL "https://www.minetest.net"
  LANGUAGES C CXX
)

option(USE_CURL "Whether to use the Curl library." ON)
option(USE_LEVELDB "" OFF)
option(USE_POSTGRESQL "" OFF)
option(USE_PROMETHEUS "" OFF)
option(USE_SOUND "Whether to use sound." ON)
option(USE_SPATIAL "Whether to use libspatial." OFF)
option(USE_REDIS "" OFF)

add_compile_options(
  "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wshadow;-Wnon-virtual-dtor;-pedantic>"
  "$<$<CXX_COMPILER_ID:Clang>:-Weverything>"
  "$<$<CXX_COMPILER_ID:MSVC>:/permissive;/W4;/w14640>"
)

set(CMAKE_MODULE_PATH
  "${CMAKE_MODULE_PATH}"
  "${PROJECT_SOURCE_DIR}/cmake/Modules"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

set(ICON_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(PROJECT_NAME_CAPITALIZED "Minetest")
set(SHAREDIR ".")

add_subdirectory(src)
