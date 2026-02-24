cmake_minimum_required(VERSION 3.10...3.31)

project(uint256t VERSION 2.0.0 LANGUAGES CXX)

# Default to Release for single-config generators
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Mode: ${CMAKE_BUILD_TYPE}")

# C++17 required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ccache support
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Found ccache package... Activating...")
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

# Compiler-specific flags
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
    set(ARCH native CACHE STRING "CPU to build for: -march value or 'default' for none")
    if(NOT "${ARCH}" STREQUAL "default")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=${ARCH}")
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuninitialized")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -Og")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -O3")

endif()

# Library
add_library(uint256t STATIC
    uint128_t.cpp
    uint256_t.cpp
)
target_include_directories(uint256t PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Tests
option(BUILD_TESTS "Build test executables" ON)
if(BUILD_TESTS)
    enable_testing()

    add_executable(uint256-tests tests/test_all.cpp)
    target_link_libraries(uint256-tests PRIVATE uint256t)
    target_include_directories(uint256-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    add_test(NAME uint256-tests COMMAND uint256-tests)
endif()
