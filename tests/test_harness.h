#ifndef TEST_HARNESS_H
#define TEST_HARNESS_H

#include <cstdint>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include "uint256_t.h"

static int _tests_run = 0;
static int _tests_passed = 0;

#define CHECK(expr)                                                                                                    \
    do                                                                                                                 \
    {                                                                                                                  \
        _tests_run++;                                                                                                  \
        if (expr)                                                                                                      \
        {                                                                                                              \
            _tests_passed++;                                                                                           \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            std::cerr << "FAIL: " << #expr << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl;                 \
        }                                                                                                              \
    } while (0)

#define CHECK_EQ(a, b)                                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        _tests_run++;                                                                                                  \
        if ((a) == (b))                                                                                                \
        {                                                                                                              \
            _tests_passed++;                                                                                           \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            std::cerr << "FAIL: " << #a << " == " << #b << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl;    \
        }                                                                                                              \
    } while (0)

#define CHECK_THROW(expr, exception_type)                                                                              \
    do                                                                                                                 \
    {                                                                                                                  \
        _tests_run++;                                                                                                  \
        bool caught = false;                                                                                           \
        try                                                                                                            \
        {                                                                                                              \
            (void)(expr);                                                                                              \
        }                                                                                                              \
        catch (const exception_type &)                                                                                 \
        {                                                                                                              \
            caught = true;                                                                                             \
        }                                                                                                              \
        catch (...)                                                                                                    \
        {                                                                                                              \
        }                                                                                                              \
        if (caught)                                                                                                    \
        {                                                                                                              \
            _tests_passed++;                                                                                           \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            std::cerr << "FAIL (no throw): " << #expr << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl;      \
        }                                                                                                              \
    } while (0)

#define TEST_RESULTS(name)                                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        std::cout << name << ": " << _tests_passed << "/" << _tests_run << " passed" << std::endl;                     \
        return (_tests_passed == _tests_run) ? 0 : 1;                                                                 \
    } while (0)

#endif // TEST_HARNESS_H
