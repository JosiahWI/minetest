if(NOT TARGET lua::lua)
  message(FATAL_ERROR "Lua must be included before bitop.")
endif()

add_library(bitop STATIC bit.c)
add_library(bitop::bitop ALIAS bitop)

target_include_directories(bitop
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(bitop
  PUBLIC
    lua::lua
)
