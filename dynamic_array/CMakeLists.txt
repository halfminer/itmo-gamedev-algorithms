enable_testing()

add_executable(
  dynamic_array
  Array.h
  ArrayTest.cpp
)

target_link_libraries(
  dynamic_array
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(dynamic_array)