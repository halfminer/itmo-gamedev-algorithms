project(itmo-gamedev-algorithms)

cmake_minimum_required(VERSION 3.20)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

#add_subdirectory(hammurabi)
add_subdirectory(dynamic_array)
add_subdirectory(quicksort)
add_subdirectory(tests)