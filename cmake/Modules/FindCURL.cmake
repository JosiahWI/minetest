mark_as_advanced(CURL_LIBRARY CURL_INCLUDE_DIR)

find_library(CURL_LIBRARY NAMES curl libcurl)
find_path(CURL_INCLUDE_DIR NAMES curl/curl.h)

if(WIN32)
	# If VCPKG_APPLOCAL_DEPS is ON, dll's are automatically handled by VCPKG
	if(NOT VCPKG_APPLOCAL_DEPS)
		find_file(CURL_DLL NAMES libcurl-4.dll libcurl.dll
			DOC "Path to the cURL DLL (for installation)")
		mark_as_advanced(CURL_DLL)
	endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CURL DEFAULT_MSG CURL_LIBRARY CURL_INCLUDE_DIR)

if(CURL_FOUND AND NOT TARGET CURL::libcurl)
  add_library(CURL::libcurl INTERFACE IMPORTED)
  target_include_directories(CURL::libcurl
    INTERFACE
      "${CURL_INCLUDE_DIR}"
  )

  target_link_libraries(CURL::libcurl
    INTERFACE
      "${CURL_LIBRARY}"
  )
endif()
