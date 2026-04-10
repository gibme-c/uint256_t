#include "fuzz_helpers.h"

#include <cstddef>
#include <cstdint>
#include <stdexcept>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    if (size < 48)
    {
        return 0;
    }

    uint256_t a256 = from_bytes_256(data);
    uint128_t b128 = from_bytes_128(data + 32);

    // Cross-type arithmetic
    uint256_t sum = a256 + b128;
    uint256_t diff = a256 - b128;
    uint256_t prod = a256 * b128;

    // Commutativity via free function: b128 + a256 == a256 + b128
    if ((b128 + a256) != sum)
    {
        __builtin_trap();
    }
    if ((b128 * a256) != prod)
    {
        __builtin_trap();
    }

    // Division and modulo
    if (b128)
    {
        uint256_t quot = a256 / b128;
        uint256_t rem = a256 % b128;

        // Division-remainder identity
        if (quot * uint256_t(b128) + rem != a256)
        {
            __builtin_trap();
        }
    }

    // Cross-type bitwise
    {
        uint256_t and_result = a256 & b128;
        uint256_t or_result = a256 | b128;
        uint256_t xor_result = a256 ^ b128;

        // Commutativity via free functions
        if ((b128 & a256) != and_result)
        {
            __builtin_trap();
        }
        if ((b128 | a256) != or_result)
        {
            __builtin_trap();
        }
        if ((b128 ^ a256) != xor_result)
        {
            __builtin_trap();
        }
    }

    // Cross-type comparison consistency
    {
        bool eq = (a256 == b128);
        bool neq = (a256 != b128);
        if (eq == neq)
        {
            __builtin_trap();
        }

        bool gt = (a256 > b128);
        bool lt = (a256 < b128);
        bool gte = (a256 >= b128);
        bool lte = (a256 <= b128);

        // Exactly one of: gt, lt, eq must be true
        int count = (gt ? 1 : 0) + (lt ? 1 : 0) + (eq ? 1 : 0);
        if (count != 1)
        {
            __builtin_trap();
        }

        // gte == (gt || eq)
        if (gte != (gt || eq))
        {
            __builtin_trap();
        }
        // lte == (lt || eq)
        if (lte != (lt || eq))
        {
            __builtin_trap();
        }
    }

    (void)diff;

    return 0;
}
