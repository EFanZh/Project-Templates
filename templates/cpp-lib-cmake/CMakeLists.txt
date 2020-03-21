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

if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

# Compile options.

if(MSVC)
    set(CMAKE_INCLUDE_SYSTEM_FLAG_C "/external:I")
    set(CMAKE_INCLUDE_SYSTEM_FLAG_CXX "/external:I")
endif()

function(set_compile_options TARGET)
    set_target_properties(${TARGET}
                          PROPERTIES CXX_EXTENSIONS OFF
                                     CXX_STANDARD 20
                                     CXX_STANDARD_REQUIRED ON)

    if(MSVC)
        target_compile_options(${TARGET} PRIVATE "/Wall" "/WX" "/experimental:external" "/external:W0")
    else()
        target_compile_options(${TARGET} PRIVATE "-Wall" "-Wextra" "-Wpedantic" "-Wconversion" "-Werror")
    endif()
endfunction()

# Configure library.

add_library(example src/example/example.cpp)
set_compile_options(example)
target_include_directories(example PUBLIC include)

# Configure test.

enable_testing()

add_executable(example_tests tests/example/example_tests.cpp)
set_compile_options(example_tests)
target_link_libraries(example_tests PRIVATE example gtest_main)

gtest_discover_tests(example_tests)
