add_library(GMP mini-gmp.c mini-gmp.h)
add_library(GMP::GMP ALIAS GMP)

target_include_directories(GMP PUBLIC "${CMAKE_CURRENT_LIST_DIR}/")
