# https://cmake.org/cmake/help/latest/policy/CMP0092.html
cmake_minimum_required(VERSION 3.15)
project(example)

# Global configuration.

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(STANDALONE_PROJECT ON)
else()
    set(STANDALONE_PROJECT OFF)
endif()

# Compile options.

if(MSVC)
    set(CMAKE_INCLUDE_SYSTEM_FLAG_C "/external:I")
    set(CMAKE_INCLUDE_SYSTEM_FLAG_CXX "/external:I")

    add_compile_options("/experimental:external" "/external:W0")
endif()

function(set_compile_options TARGET)
    set_target_properties("${TARGET}"
                          PROPERTIES CXX_EXTENSIONS OFF
                                     CXX_STANDARD_REQUIRED ON)

    if(MSVC)
        target_compile_options(
            "${TARGET}"
            PRIVATE
            "/W4"
            "/we4287" # 'operator': unsigned/negative constant mismatch
            "/we4365" # 'action': conversion from 'type_1' to 'type_2', signed/unsigned mismatch
            "/we4388" # signed/unsigned mismatch
            "/we4826" # Conversion from 'type1' to 'type2' is sign-extended. This may cause unexpected runtime behavior.
            "/WX"
        )
    else()
        target_compile_options("${TARGET}" PRIVATE "-Wall" "-Wextra" "-Wpedantic" "-Wconversion" "-Werror")
    endif()
endfunction()

# Configure library.

add_library(example src/example/example.cpp)
target_compile_features(example PUBLIC cxx_std_17)
set_compile_options(example)

if(STANDALONE_PROJECT)
    target_include_directories(example PUBLIC include)
else()
    target_include_directories(example SYSTEM PUBLIC include)
endif()

# Configure test.

# See https://github.com/microsoft/GSL/blob/master/CMakeLists.txt.

if(STANDALONE_PROJECT)
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

    enable_testing()

    add_executable(example_tests tests/example/example_tests.cpp)
    set_compile_options(example_tests)
    target_link_libraries(example_tests PRIVATE example gtest_main)

    gtest_discover_tests(example_tests)
endif()
