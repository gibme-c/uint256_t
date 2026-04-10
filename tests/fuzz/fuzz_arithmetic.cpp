#include "fuzz_helpers.h"

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    if (size < 64)
    {
        return 0;
    }

    uint256_t a = from_bytes_256(data);
    uint256_t b = from_bytes_256(data + 32);

    // Basic arithmetic (always safe)
    uint256_t sum = a + b;
    uint256_t diff = a - b;
    uint256_t prod = a * b;

    // Commutativity
    if (sum != b + a)
    {
        __builtin_trap();
    }
    if (prod != b * a)
    {
        __builtin_trap();
    }

    // a - a == 0
    if ((a - a) != uint256_0)
    {
        __builtin_trap();
    }

    // Identity
    if ((a + uint256_0) != a)
    {
        __builtin_trap();
    }
    if ((a * uint256_1) != a)
    {
        __builtin_trap();
    }

    // Division and modulo (only when divisor is non-zero)
    if (b)
    {
        uint256_t quot = a / b;
        uint256_t rem = a % b;

        // Division-remainder identity: (a / b) * b + (a % b) == a
        if (quot * b + rem != a)
        {
            __builtin_trap();
        }
    }

    if (a)
    {
        // Self-division
        if ((a / a) != uint256_1)
        {
            __builtin_trap();
        }
        if ((a % a) != uint256_0)
        {
            __builtin_trap();
        }
    }

    // Also test uint128_t with first 32 bytes
    {
        uint128_t a128 = from_bytes_128(data);
        uint128_t b128 = from_bytes_128(data + 16);

        if ((a128 + b128) != (b128 + a128))
        {
            __builtin_trap();
        }

        if (b128)
        {
            uint128_t q = a128 / b128;
            uint128_t r = a128 % b128;
            if (q * b128 + r != a128)
            {
                __builtin_trap();
            }
        }
    }

    (void)sum;
    (void)diff;

    return 0;
}
