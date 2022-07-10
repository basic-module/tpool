include(gtest)

set(test_list main.cpp test_tpool.cpp)

add_executable(test_tpool ${test_list})

include_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include
		${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include
		${PROJECT_SOURCE_DIR}/include
	)

target_link_directories(test_tpool PRIVATE
		${CMAKE_BINARY_DIR}/lib
	)

target_link_libraries(test_tpool PRIVATE
		gtest
		gmock
		tpool		
	)

add_test(NAME test_tpool COMMAND test_tpool)
