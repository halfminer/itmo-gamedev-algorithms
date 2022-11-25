set(QUICKSORT_SRC QuickSort.h)

add_library(quicksort SHARED ${QUICKSORT_SRC})

set_target_properties(quicksort PROPERTIES LINKER_LANGUAGE CXX)