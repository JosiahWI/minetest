find_package(OpenAL REQUIRED)
find_package(Vorbis REQUIRED)

if(NOT TARGET OpenAl::OpenAL)
  add_library(OpenAl::OpenAl INTERFACE IMPORTED)
  target_include_directories(OpenAl::OpenAl
    INTERFACE
      "${OPENAL_INCLUDE_DIR}"
  )

  target_link_libraries(OpenAl::OpenAl
    INTERFACE
      "${OPENAL_LIBRARY}"
      vorbis::vorbis
  )
endif()
