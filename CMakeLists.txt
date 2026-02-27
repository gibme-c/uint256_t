cmake_minimum_required(VERSION 3.10...3.31)

project(uint256t VERSION 2.0.0 LANGUAGES CXX)

include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)

# Default to Release for single-config generators
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Mode: ${CMAKE_BUILD_TYPE}")

# ccache support
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Found ccache package... Activating...")
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

# Options
option(BUILD_TESTS "Build test executables" ON)
option(ENABLE_WERROR "Treat warnings as errors" OFF)
option(ENABLE_SANITIZERS "Enable ASAN + UBSAN (Debug builds)" OFF)


# --- Detect MinGW environment ---
# Only use CMake's built-in MINGW (set for GCC with MinGW). Clang on Windows can
# target either MinGW or MSVC ABI, and the linker varies (GNU ld vs lld-link) —
# applying the wrong linker flags breaks the build. We let Clang on Windows rely
# on the OS defaults for DEP/ASLR (enabled by default on modern Windows) rather
# than guessing the linker style.

# ---------------------------------------------------------------------------
# Hardening interface library — all flags live here
# ---------------------------------------------------------------------------
add_library(uint256t_hardening INTERFACE)

# Helper variables for generator expressions
set(_is_gcc "$<CXX_COMPILER_ID:GNU>")
set(_is_clang "$<CXX_COMPILER_ID:Clang>")
set(_is_appleclang "$<CXX_COMPILER_ID:AppleClang>")
set(_is_msvc "$<CXX_COMPILER_ID:MSVC>")
set(_is_gnu_like "$<OR:${_is_gcc},${_is_clang},${_is_appleclang}>")
set(_is_linux "$<PLATFORM_ID:Linux>")
set(_is_debug "$<CONFIG:Debug>")
set(_is_release "$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>,$<CONFIG:MinSizeRel>>")

# --- 1. Warnings (GCC/Clang) ---
target_compile_options(uint256t_hardening INTERFACE
    $<${_is_gnu_like}:
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wformat=2
        -Wformat-security
        -Wshadow
        -Wcast-align
        -Wdouble-promotion
        -Wnull-dereference
        -fno-strict-overflow
    >
)
# GCC-specific warnings
target_compile_options(uint256t_hardening INTERFACE
    $<${_is_gcc}:-Wstrict-aliasing=2>
)
# libstdc++ container assertions in Debug (bounds checks on operator[], etc.)
target_compile_options(uint256t_hardening INTERFACE
    $<$<AND:${_is_gcc},${_is_debug}>:-D_GLIBCXX_ASSERTIONS>
)

# --- 2. Warnings (MSVC) ---
target_compile_options(uint256t_hardening INTERFACE
    $<${_is_msvc}:
        /W4
        /permissive-
        /sdl
    >
)

# --- 3. -Werror / /WX (opt-in) ---
if(ENABLE_WERROR)
    target_compile_options(uint256t_hardening INTERFACE
        $<${_is_gnu_like}:-Werror>
        $<${_is_msvc}:/WX>
    )
endif()

# --- 4. Stack protection ---
# Probe -fstack-protector-strong: requires libssp or compiler-rt at link time.
# Clang+MinGW toolchains may lack libssp, so we verify with try_compile first.
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    set(CMAKE_REQUIRED_FLAGS "-fstack-protector-strong")
    check_cxx_source_compiles("int main() { char buf[64]; buf[0] = 0; return buf[0]; }" HAS_STACK_PROTECTOR_STRONG)
    unset(CMAKE_REQUIRED_FLAGS)
    if(HAS_STACK_PROTECTOR_STRONG)
        target_compile_options(uint256t_hardening INTERFACE
            $<${_is_gnu_like}:-fstack-protector-strong>
        )
    endif()
endif()
target_compile_options(uint256t_hardening INTERFACE
    $<${_is_msvc}:/GS>
)

# --- 5. FORTIFY_SOURCE (GCC/Clang, non-Windows) ---
# _FORTIFY_SOURCE is not reliably supported on MinGW
if(NOT WIN32)
    target_compile_options(uint256t_hardening INTERFACE
        $<$<AND:${_is_gnu_like},${_is_release}>:-U_FORTIFY_SOURCE>
        $<$<AND:${_is_gnu_like},${_is_release}>:-D_FORTIFY_SOURCE=2>
        $<$<AND:${_is_gnu_like},${_is_debug}>:-D_FORTIFY_SOURCE=1>
    )
endif()

# --- 6. Symbol visibility (GCC/Clang) — activates existing export macros ---
target_compile_options(uint256t_hardening INTERFACE
    $<${_is_gnu_like}:
        -fvisibility=hidden
        -fvisibility-inlines-hidden
    >
)

# --- 7. Control flow integrity ---
# Stack clash protection (Linux only — not supported on macOS/Apple Clang or Windows)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(uint256t_hardening INTERFACE
        $<$<OR:${_is_gcc},${_is_clang}>:-fstack-clash-protection>
    )
endif()
# Intel CET control flow integrity (x86_64 only, probe before using)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        check_cxx_compiler_flag("-fcf-protection=full" HAS_CF_PROTECTION)
        if(HAS_CF_PROTECTION)
            target_compile_options(uint256t_hardening INTERFACE
                $<$<OR:${_is_gcc},${_is_clang}>:-fcf-protection=full>
            )
        endif()
    endif()
endif()
# MSVC: control flow guard
target_compile_options(uint256t_hardening INTERFACE
    $<${_is_msvc}:/guard:cf>
)
# MSVC: Spectre mitigations (probe first)
if(MSVC)
    check_cxx_compiler_flag("/Qspectre" HAS_QSPECTRE)
    if(HAS_QSPECTRE)
        target_compile_options(uint256t_hardening INTERFACE /Qspectre)
    endif()
    # CET shadow stack compatibility
    check_cxx_compiler_flag("/guard:ehcont" HAS_GUARD_EHCONT)
    if(HAS_GUARD_EHCONT)
        target_compile_options(uint256t_hardening INTERFACE /guard:ehcont)
    endif()
endif()

# --- 8. Optimization flags ---
target_compile_options(uint256t_hardening INTERFACE
    $<$<AND:${_is_gnu_like},${_is_debug}>:-g3>
    $<$<AND:${_is_gnu_like},${_is_debug}>:-Og>
    $<$<AND:${_is_gnu_like},${_is_release}>:-O3>
    $<$<AND:${_is_msvc},${_is_release}>:/O2>
)

# --- 9. Sanitizers (opt-in) ---
if(ENABLE_SANITIZERS)
    target_compile_options(uint256t_hardening INTERFACE
        $<${_is_gnu_like}:-fsanitize=address,undefined>
        $<${_is_gnu_like}:-fno-omit-frame-pointer>
        $<${_is_gnu_like}:-fno-sanitize-recover=all>
        $<${_is_msvc}:/fsanitize=address>
    )
    target_link_options(uint256t_hardening INTERFACE
        $<${_is_gnu_like}:-fsanitize=address,undefined>
    )
endif()

# ---------------------------------------------------------------------------
# Library target
# ---------------------------------------------------------------------------
add_library(uint256t STATIC
    uint128_t.cpp
    uint256_t.cpp
)

# C++17 and PIC — set as target properties (not global) to avoid leaking to consumers
set_target_properties(uint256t PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    POSITION_INDEPENDENT_CODE ON
)

# For building uint256t itself — NOT system (you want to see your own warnings)
target_include_directories(uint256t PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# For consumers of uint256t — SYSTEM so they don't get our warnings
target_include_directories(uint256t SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(uint256t PRIVATE uint256t_hardening)

# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------
if(BUILD_TESTS)
    enable_testing()

    add_executable(uint256-tests tests/test_all.cpp)
    target_link_libraries(uint256-tests PRIVATE uint256t uint256t_hardening)
    target_include_directories(uint256-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)

    set_target_properties(uint256-tests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )

    # --- 10. Linker hardening (test executable only) ---
    # Linux (ELF)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set_property(TARGET uint256-tests APPEND_STRING PROPERTY LINK_FLAGS
            " -Wl,-z,relro,-z,now -Wl,-z,noexecstack")
    endif()
    # MinGW linker hardening (DEP + ASLR) — only for GCC+MinGW (known GNU ld)
    if(MINGW)
        set_property(TARGET uint256-tests APPEND_STRING PROPERTY LINK_FLAGS
            " -Wl,--nxcompat -Wl,--dynamicbase -Wl,--high-entropy-va")
    endif()
    # MSVC linker hardening
    if(MSVC)
        set_property(TARGET uint256-tests APPEND_STRING PROPERTY LINK_FLAGS
            " /DYNAMICBASE /NXCOMPAT /HIGHENTROPYVA /guard:cf")
        if(HAS_GUARD_EHCONT)
            set_property(TARGET uint256-tests APPEND_STRING PROPERTY LINK_FLAGS
                " /guard:ehcont /CETCOMPAT")
        endif()
    endif()

    add_test(NAME uint256-tests COMMAND uint256-tests)
endif()
