find_package(Lua REQUIRED)

add_subdirectory(
  "${PROJECT_SOURCE_DIR}/lib/bitop"
  "${PROJECT_BINARY_DIR}/lib/bitop"
)

find_package(CURL REQUIRED)
find_package(Freetype REQUIRED)
find_package(GMP REQUIRED)
find_package(IrrlichtMt REQUIRED)
find_package(Json REQUIRED)
find_package(Ncursesw REQUIRED)
if(USE_SOUND)
  find_package(OpenAlTarget REQUIRED)
endif()
find_package(SQLite3 REQUIRED)
find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Zstd REQUIRED)

add_library(common OBJECT "")
add_library(minetest::common ALIAS common)

add_executable(minetest WIN32 "")

# Most subdirectories register additional source dependencies.
add_subdirectory(benchmark)
add_subdirectory(client)
add_subdirectory(content)
add_subdirectory(database)
add_subdirectory(gui)
add_subdirectory(irrlicht_changes)
add_subdirectory(mapgen)
add_subdirectory(network)
add_subdirectory(script)
add_subdirectory(server)
add_subdirectory(threading)
add_subdirectory(unittest)
add_subdirectory(util)

target_sources(common
  PRIVATE
    ban.cpp
    chat.cpp
    clientiface.cpp
    collision.cpp
    content_mapnode.cpp
    content_nodemeta.cpp
    convert_json.cpp
    craftdef.cpp
    debug.cpp
    defaultsettings.cpp
    emerge.cpp
    environment.cpp
    face_position_cache.cpp
    filesys.cpp
    gettext.cpp
    httpfetch.cpp
    hud.cpp
    inventory.cpp
    inventorymanager.cpp
    itemdef.cpp
    itemstackmetadata.cpp
    light.cpp
    log.cpp
    map.cpp
    map_settings_manager.cpp
    mapblock.cpp
    mapnode.cpp
    mapsector.cpp
    metadata.cpp
    modchannels.cpp
    nameidmapping.cpp
    nodedef.cpp
    nodemetadata.cpp
    nodetimer.cpp
    noise.cpp
    objdef.cpp
    object_properties.cpp
    particles.cpp
    pathfinder.cpp
    player.cpp
    porting.cpp
    profiler.cpp
    raycast.cpp
    reflowscan.cpp
    remoteplayer.cpp
    rollback.cpp
    rollback_interface.cpp
    serialization.cpp
    server.cpp
    serverenvironment.cpp
    serverlist.cpp
    settings.cpp
    staticobject.cpp
    terminal_chat_console.cpp
    texture_override.cpp
    tileanimation.cpp
    tool.cpp
    translation.cpp
    version.cpp
    voxel.cpp
    voxelalgorithms.cpp
)

target_include_directories(common
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/script"
    "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_libraries(common
  PRIVATE
    bitop::bitop
    $<$<BOOL:USE_CURL>:CURL::libcurl>
    GMP::GMP
    ncursesw::ncursesw
    Threads::Threads
    SQLite3::SQLite3
    ZLIB::ZLIB
    zstd::zstd
  PUBLIC
    IrrlichtMt::IrrlichtMt
    json::json
    lua::lua
)

target_compile_features(common
  PUBLIC
    cxx_std_14
)

target_sources(minetest
  PRIVATE
    main.cpp
)

target_include_directories(minetest
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_libraries(minetest
  PRIVATE
    Freetype::Freetype
    IrrlichtMt::IrrlichtMt
    $<$<BOOL:FALSE>:minetest::benchmarks>
    minetest::common
    $<$<BOOL:FALSE>:minetest::tests>
    $<$<BOOL:FALSE>:minetest::client_tests>
    $<$<BOOL:USE_SOUND>:OpenAl::OpenAl>
)

target_compile_features(minetest
  PRIVATE
    cxx_std_14
)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_config.h"
  NEWLINE_STYLE LF
)
