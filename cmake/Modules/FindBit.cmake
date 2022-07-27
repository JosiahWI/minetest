# FindBit.cmake
#
# Finds the bundled bitop library
#
# This will define the following variables
#
#    bit_FOUND
#    bit_INCLUDE_DIRS
#
# and the folloming imported targets
#
#    bit::bit
#
# Copyright: Josiah VanderZee <josiah_vanderzee@mediacombb.net>

find_path(Bit_INCLUDE_DIR
  NAMES bit.h
  HINTS "${PROJECT_SOURCE_DIR}/lib/bitop"
)

mark_as_advanced(Bit_FOUND Bit_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Bit
  REQUIRED_VARS Bit_INCLUDE_DIR
)

if(Bit_FOUND AND NOT TARGET bit::bit)
  add_library(bit::bit INTERFACE IMPORTED)
  target_include_directories(bit::bit
    INTERFACE
      "${bit_INCLUDE_DIR}"
  )
endif()
