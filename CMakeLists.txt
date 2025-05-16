cmake_minimum_required(VERSION 3.10)
project(BloomFilterProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include_directories(
    src
    src/BloomFilter
    src/Hash
    src/HTTP_Methods
    src/Server_Client
)

# Gather all source files
file(GLOB_RECURSE PROJECT_SOURCES
    src/BloomFilter/*.cpp
    src/Hash/*.cpp
    src/HTTP_Methods/*.cpp
    src/Server_Client/*.cpp
)

add_executable(bloomserver src/Main/main.cpp ${PROJECT_SOURCES})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(TestBloomFilter
    src/Tests/TestBloomFilter.cpp
    ${PROJECT_SOURCES}
)
target_link_libraries(TestBloomFilter gtest gtest_main pthread)
add_test(NAME TestBloomFilter COMMAND TestBloomFilter)

add_executable(TestHashFunctions
    src/Tests/TestHashFunctions.cpp
    ${PROJECT_SOURCES}
)
target_link_libraries(TestHashFunctions gtest gtest_main pthread)
add_test(NAME TestHashFunctions COMMAND TestHashFunctions)

add_executable(TestHTTPMethods
    src/Tests/TestHTTPMethods.cpp
    ${PROJECT_SOURCES}
)
target_link_libraries(TestHTTPMethods gtest gtest_main pthread)
add_test(NAME TestHTTPMethods COMMAND TestHTTPMethods)
