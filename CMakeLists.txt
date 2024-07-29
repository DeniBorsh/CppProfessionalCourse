cmake_minimum_required(VERSION 3.10)

project(ip_filter)

set(CMAKE_CXX_STANDARD 17)

add_executable(ip_filter ip_filter.cpp)
add_executable(test_version test_version.cpp)



include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

target_link_libraries(test_version
    gtest
    gtest_main
)

add_custom_target(run_tests COMMAND test_version)

enable_testing()

add_test(test_version test_version)