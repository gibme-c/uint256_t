cmake_minimum_required(VERSION 3.10...3.31)

if(DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: Debug, Release, RelWithDebInfo")
else()
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: Debug, Release, RelWithDebInfo")
endif()

message(STATUS "Mode: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CONFIGURATION_TYPES Debug RelWithDebInfo Release CACHE STRING INTERNAL)
set(ARCH native CACHE STRING  "CPU to build for: -march value or native")

message(STATUS "Building for target architecture: ${ARCH}")

set(LIB_MAJOR_VERSION "2")
set(LIB_MINOR_VERSION "0")
set(LIB_PATCH_VERSION "0")
set(LIB_VERSION_STRING "${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION}.${LIB_PATCH_VERSION}")

project(uint256t VERSION "${LIB_VERSION_STRING}" LANGUAGES CXX)

if(NOT MSVC)
    find_program(CCACHE_PROGRAM ccache)
    if(CCACHE_PROGRAM)
        message(STATUS "Found ccache package... Activating...")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
    endif()
endif()

## This section describes our general CMake setup options
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_SKIP_INSTALL_RULES OFF FORCE)
set(CMAKE_SKIP_PACKAGE_ALL_DEPENDENCY ON FORCE)
set(CMAKE_SUPPRESS_REGENERATION ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Enable c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## We only build static binaries -- this is left here for our dependencies
set(STATIC ON CACHE BOOL FORCE "Link libraries statically? Forced to ON")
add_definitions(-DSTATICLIB)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std:c++17 /DWIN32_LEAN_AND_MEAN /wd4267 /wd4804 /D_DLL")

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
    if("${ARCH}" STREQUAL "default")
        set(ARCH_FLAG "")
    else()
        set(ARCH_FLAG "-march=${ARCH}")
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wuninitialized")

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -Og")

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -O3")

    if(APPLE)
        if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
            # Need to build against libc++ instead of libstc++ on apple
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdinc++ -I/usr/local/opt/llvm/include/c++/v1 -nodefaultlibs -lc++ -lc++abi -lm -lc -lgcc -lgcc_eh")

            # Need these flags so gcc OSX works on the cryptopp ASM - https://groups.google.com/forum/#!topic/cryptopp-users/po8yO-vYaac
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCRYPTOPP_CLANG_INTEGRATED_ASSEMBLER=1")

        elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
            # Need to link against the llvm libc++ library, default is too old for std::filesystem
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -I/usr/local/opt/llvm/include/c++/v1")
        endif()
    endif()

    if(MINGW OR STATIC_LIBC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libstdc++")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
    endif()

    if(NOT APPLE)
        set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    endif()
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(UINT256T_SRC
    uint128_t.cpp
    uint256_t.cpp
)

add_library(uint256t STATIC ${UINT256T_SRC})
target_include_directories(uint256t PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

option(BUILD_TESTS "Build test executables" ON)
if(BUILD_TESTS)
    enable_testing()

    add_executable(uint256-tests tests/test_all.cpp)
    target_link_libraries(uint256-tests PRIVATE uint256t)
    target_include_directories(uint256-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    add_test(NAME uint256-tests COMMAND uint256-tests)
endif()
