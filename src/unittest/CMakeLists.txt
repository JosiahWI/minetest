if(BUILD_UNITTESTS)
  add_library(tests OBJECT
    test.cpp
    test_address.cpp
    test_authdatabase.cpp
    test_activeobject.cpp
    test_areastore.cpp
    test_ban.cpp
    test_collision.cpp
    test_compression.cpp
    test_connection.cpp
    test_filepath.cpp
    test_gettext.cpp
    test_inventory.cpp
    test_irrptr.cpp
    test_lua.cpp
    test_map.cpp
    test_map_settings_manager.cpp
    test_mapnode.cpp
    test_modchannels.cpp
    test_modmetadatadatabase.cpp
    test_nodedef.cpp
    test_noderesolver.cpp
    test_noise.cpp
    test_objdef.cpp
    test_profiler.cpp
    test_random.cpp
    test_schematic.cpp
    test_serialization.cpp
    test_serveractiveobjectmgr.cpp
    test_server_shutdown_state.cpp
    test_settings.cpp
    test_socket.cpp
    test_servermodmanager.cpp
    test_threading.cpp
    test_utilities.cpp
    test_voxelarea.cpp
    test_voxelalgorithms.cpp
    test_voxelmanipulator.cpp
  )
  add_library(minetest::tests ALIAS tests)

  target_link_libraries(tests
    PRIVATE
      minetest::common
  )

  add_library(client_tests OBJECT
    test_clientactiveobjectmgr.cpp
    test_eventmanager.cpp
    test_gameui.cpp
    test_keycode.cpp
  )
  add_library(minetest::client_tests ALIAS client_tests)

  target_link_libraries(client_tests
    PRIVATE
      minetest::common
  )
endif()
