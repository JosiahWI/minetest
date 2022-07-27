add_library(jsoncpp STATIC jsoncpp.cpp)
add_library(jsoncpp::jsoncpp ALIAS jsoncpp)

target_compile_features(jsoncpp
  PUBLIC
    cxx_std_11
)
