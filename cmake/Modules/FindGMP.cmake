# Find script for GMP
# Provides imported target GMP::GMP

option(ENABLE_SYSTEM_GMP "Use GMP from system" TRUE)

set(USE_SYSTEM_GMP ${ENABLE_SYSTEM_GMP})

if(ENABLE_SYSTEM_GMP)
	find_path(GMP_INCLUDE_DIR NAMES gmp.h)
	find_library(GMP_LIBRARY NAMES gmp)
	if(GMP_INCLUDE_DIR AND GMP_LIBRARY)
		message(STATUS "Using GMP provided by system.")
		mark_as_advanced(GMP_INCLUDE_DIR GMP_LIBRARY)
	else()
		message (STATUS "Detecting GMP from system failed.")
		set(USE_SYSTEM_GMP FALSE)
	endif()
else()
	message(STATUS
		"Detecting GMP from system disabled! (ENABLE_SYSTEM_GMP=0)")
endif()

if(USE_SYSTEM_GMP)
	# GMP library has been found in system. Make imported target.
	add_library(GMP::GMP INTERFACE IMPORTED)
	target_include_directories(GMP::GMP INTERFACE "${GMP_INCLUDE_DIR}")
	target_link_libraries(GMP::GMP INTERFACE "${GMP_LIBRARY}")
else()
	message(STATUS "Using bundled mini-gmp library.")
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/gmp")
endif()
