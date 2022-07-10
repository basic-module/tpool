include_directories(${PROJECT_SOURCE_DIR}/include)

set(src_list 
		tpool.cpp
		)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(tpool ${src_list})

