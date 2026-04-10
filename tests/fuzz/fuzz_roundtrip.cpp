#include "fuzz_helpers.h"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    if (size < 32)
    {
        return 0;
    }

    uint256_t original = from_bytes_256(data);

    // Roundtrip through decimal string
    {
        std::string dec = original.str(10);
        uint256_t parsed(dec, 10);
        if (parsed != original)
        {
            __builtin_trap();
        }
    }

    // Roundtrip through hex string
    {
        std::string hex = original.str(16);
        uint256_t parsed(hex, 16);
        if (parsed != original)
        {
            __builtin_trap();
        }
    }

    // Roundtrip through binary string
    {
        std::string bin = original.str(2);
        uint256_t parsed(bin, 2);
        if (parsed != original)
        {
            __builtin_trap();
        }
    }

    // Roundtrip through export_bits
    {
        std::vector<uint8_t> bits = original.export_bits();
        if (bits.size() != 32)
        {
            __builtin_trap();
        }

        // Reconstruct from exported bytes
        uint256_t reconstructed = from_bytes_256(bits.data());
        if (reconstructed != original)
        {
            __builtin_trap();
        }
    }

    // export_bits_truncate consistency: prepending zeros should match export_bits
    {
        std::vector<uint8_t> full = original.export_bits();
        std::vector<uint8_t> truncated = original.export_bits_truncate();

        // truncated should be a suffix of full (after stripping leading zeros)
        if (truncated.size() > full.size())
        {
            __builtin_trap();
        }

        size_t offset = full.size() - truncated.size();
        for (size_t i = 0; i < offset; i++)
        {
            if (full[i] != 0x00)
            {
                __builtin_trap();
            }
        }
        for (size_t i = 0; i < truncated.size(); i++)
        {
            if (full[offset + i] != truncated[i])
            {
                __builtin_trap();
            }
        }
    }

    // uint128_t roundtrip
    {
        uint128_t val128 = from_bytes_128(data);
        std::string dec128 = val128.str(10);

        // Roundtrip through uint256_t string parsing (uint128_t has no base string ctor)
        uint256_t via256(dec128, 10);
        if (via256.upper() != uint128_0)
        {
            // Value too large for uint128_t — skip
        }
        else
        {
            // Lower 128 bits should match
            if (via256.lower() != val128)
            {
                __builtin_trap();
            }
        }
    }

    return 0;
}
