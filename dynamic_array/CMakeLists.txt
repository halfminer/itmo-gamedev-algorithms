project(dynamic_array)

set(DYNAMIC_ARRAY_SRC Array.h)

add_library(dynamic_array ${DYNAMIC_ARRAY_SRC})

set_target_properties(dynamic_array PROPERTIES LINKER_LANGUAGE CXX)