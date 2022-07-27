add_subdirectory(common)
add_subdirectory(cpp_api)
add_subdirectory(lua_api)

target_sources(common
  PRIVATE
    scripting_server.cpp
)

target_sources(minetest
  PRIVATE
    scripting_client.cpp
    scripting_mainmenu.cpp
)
