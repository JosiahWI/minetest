if(BUILD_BENCHMARKS)
  add_library(benchmarks OBJECT
    benchmark.cpp
    benchmark_serialize.cpp
  )
  add_library(minetest::benchmarks ALIAS benchmarks)

  target_link_libraries(benchmarks
    PRIVATE
      minetest::common
  )
endif()
