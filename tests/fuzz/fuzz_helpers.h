#ifndef FUZZ_HELPERS_H
#define FUZZ_HELPERS_H

#include "uint256_t.h"

#include <cstddef>
#include <cstdint>

static inline uint64_t bytes_to_u64(const uint8_t *p)
{
    uint64_t v = 0;
    for (int i = 0; i < 8; i++)
    {
        v = (v << 8) | p[i];
    }
    return v;
}

static inline uint128_t from_bytes_128(const uint8_t *p)
{
    return uint128_t(bytes_to_u64(p), bytes_to_u64(p + 8));
}

static inline uint256_t from_bytes_256(const uint8_t *p)
{
    return uint256_t(from_bytes_128(p), from_bytes_128(p + 16));
}

#endif // FUZZ_HELPERS_H
