#include "fuzz_helpers.h"

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    if (size < 65)
    {
        return 0;
    }

    uint256_t a = from_bytes_256(data);
    uint256_t b = from_bytes_256(data + 32);
    unsigned int shift = data[64] % 257; // 0-256 inclusive

    // Bitwise operations
    uint256_t and_result = a & b;
    uint256_t or_result = a | b;
    uint256_t xor_result = a ^ b;
    uint256_t not_result = ~a;

    // Self-XOR is zero
    if ((a ^ a) != uint256_0)
    {
        __builtin_trap();
    }

    // OR with zero is identity
    if ((a | uint256_0) != a)
    {
        __builtin_trap();
    }

    // AND with max is identity
    if ((a & uint256_max) != a)
    {
        __builtin_trap();
    }

    // Double negation is identity
    if (~(~a) != a)
    {
        __builtin_trap();
    }

    // XOR commutativity
    if (xor_result != (b ^ a))
    {
        __builtin_trap();
    }

    // AND commutativity
    if (and_result != (b & a))
    {
        __builtin_trap();
    }

    // OR commutativity
    if (or_result != (b | a))
    {
        __builtin_trap();
    }

    // De Morgan's law: ~(a & b) == (~a) | (~b)
    if (~and_result != (~a | ~b))
    {
        __builtin_trap();
    }

    // Shift operations
    uint256_t left_shifted = a << uint256_t(shift);
    uint256_t right_shifted = a >> uint256_t(shift);

    // Shift by 0 is identity
    if ((a << uint256_0) != a)
    {
        __builtin_trap();
    }
    if ((a >> uint256_0) != a)
    {
        __builtin_trap();
    }

    // Shift by 256 or more is zero
    if ((a << uint256_t(256)) != uint256_0)
    {
        __builtin_trap();
    }
    if ((a >> uint256_t(256)) != uint256_0)
    {
        __builtin_trap();
    }

    (void)left_shifted;
    (void)right_shifted;
    (void)not_result;

    return 0;
}
