# Find script for GMP
# Provides imported target GMP::GMP

option(ENABLE_SYSTEM_GMP "Use GMP from system" TRUE)

set(USE_SYSTEM_GMP ${ENABLE_SYSTEM_GMP})

if(ENABLE_SYSTEM_GMP)
	find_path(GMP_INCLUDE_DIR NAMES gmp.h)
	find_library(GMP_LIBRARY NAMES gmp)
	if(NOT GMP_INCLUDE_DIR OR NOT GMP_LIBRARY)
		message (STATUS "Detecting GMP from system failed.")
		set(USE_SYSTEM_GMP FALSE)
	endif()
else()
	message(STATUS
		"Detecting GMP from system disabled! (ENABLE_SYSTEM_GMP=0)")
endif()

if(NOT USE_SYSTEM_GMP)
	# Failed to find system GMP, so set vars for bundled mini-gmp.
	set(GMP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/gmp"
		CACHE INTERNAL "GMP include directory.")
	set(GMP_LIBRARY "bundled mini-gmp" CACHE INTERNAL "GMP library.")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GMP
	REQUIRED_VARS GMP_INCLUDE_DIR GMP_LIBRARY
)

mark_as_advanced(GMP_FOUND GMP_INCLUDE_DIR GMP_LIBRARY)

if(ENABLE_SYSTEM_GMP AND GMP_FOUND)
	# GMP library has been found in system. Make imported target.
	message(STATUS "Using GMP provided by system.")
	add_library(GMP::GMP INTERFACE IMPORTED)
	target_include_directories(GMP::GMP INTERFACE "${GMP_INCLUDE_DIR}")
	target_link_libraries(GMP::GMP INTERFACE "${GMP_LIBRARY}")
else()
	message(STATUS "Using bundled mini-gmp library.")
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/gmp")
endif()
