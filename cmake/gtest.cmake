include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz 
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/googletest
)
FetchContent_MakeAvailable(googletest)
