# 设置CMake版本
cmake_minimum_required(VERSION 3.15)
# 打开编译数据库生成
Set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(tpool VERSION 0.1 LANGUAGES CXX)

# Build the library with C++20 standard support, independent from other including
# software which may use a different CXX_STANDARD or CMAKE_CXX_STANDARD.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
option(BUILD_SHARED_LIBS "Build tpool as a shared library." ON)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

add_subdirectory(src)

if (test)
	enable_testing()
	add_subdirectory(test)
endif()

