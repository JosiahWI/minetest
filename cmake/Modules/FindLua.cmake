# Look for Lua library to use
# This selects LuaJIT by default

option(ENABLE_LUAJIT "Enable LuaJIT support" TRUE)
set(USE_LUAJIT FALSE)
option(REQUIRE_LUAJIT "Require LuaJIT support" FALSE)
if(REQUIRE_LUAJIT)
	set(ENABLE_LUAJIT TRUE)
endif()
if(ENABLE_LUAJIT)
	find_package(LuaJIT)
	if(LUAJIT_FOUND)
		set(USE_LUAJIT TRUE)
		message (STATUS "Using LuaJIT provided by system.")
	elseif(REQUIRE_LUAJIT)
		message(FATAL_ERROR "LuaJIT not found whereas REQUIRE_LUAJIT=\"TRUE\" is used.\n"
			"To continue, either install LuaJIT or do not use REQUIRE_LUAJIT=\"TRUE\".")
	endif()
else()
	message (STATUS "LuaJIT detection disabled! (ENABLE_LUAJIT=0)")
endif()

if(NOT USE_LUAJIT)
	message(STATUS "LuaJIT not found, using bundled Lua.")
	set(LUA_LIBRARY lua)
        set(LUA_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/lib/lua/src)
	add_subdirectory(
          "${PROJECT_SOURCE_DIR}/lib/lua"
          "${PROJECT_BINARY_DIR}/lib/lua"
        )
endif()

if(NOT TARGET lua::lua)
  add_library(lua::lua INTERFACE IMPORTED)
  target_include_directories(lua::lua
    INTERFACE
      "${LUA_INCLUDE_DIR}"
  )

  target_link_libraries(lua::lua
    INTERFACE
      "${LUA_LIBRARY}"
  )
endif()
