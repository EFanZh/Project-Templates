cmake_minimum_required(VERSION 3.12)
project(example)

include(FetchContent)
include(GoogleTest)

# Add Google Test dependency.

# https://cmake.org/cmake/help/latest/module/FetchContent.html

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.10.0
    GIT_SHALLOW ON
    GIT_PROGRESS ON
)

FetchContent_GetProperties(googletest)

if (MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

# Global compile options.

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_INCLUDE_SYSTEM_FLAG_CXX "/external:I ")

    string(REPLACE "/W3" "/W4" CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

    add_compile_options("/WX" "/experimental:external" "/external:W0")
else()
    add_compile_options("-Wall" "-Wextra" "-Wpedantic" "-Wconversion" "-Werror")
endif()

# Configure library.

add_library(example src/example/example.cpp)
target_include_directories(example PUBLIC include)

# Configure test.

enable_testing()

add_executable(example_test tests/example/example_test.cpp)
target_link_libraries(example_test PRIVATE example gtest_main)

gtest_discover_tests(example_test)
