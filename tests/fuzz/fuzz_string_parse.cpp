#include "fuzz_helpers.h"

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    if (size < 2)
    {
        return 0;
    }

    // First byte selects the base
    static const uint8_t bases[] = {2, 8, 10, 16, 36};
    uint8_t base = bases[data[0] % 5];

    // Remaining bytes form the string input
    std::string input(reinterpret_cast<const char *>(data + 1), size - 1);

    // Test uint256_t string constructor with base
    try
    {
        uint256_t val(input, base);
        // Roundtrip: value back to string and re-parse should match
        std::string s = val.str(base);
        uint256_t roundtrip(s, base);
        if (val != roundtrip)
        {
            __builtin_trap();
        }
    }
    catch (const std::invalid_argument &)
    {
        // Expected for invalid digit strings
    }
    catch (const std::exception &)
    {
        // Other expected exceptions
    }

    // Test uint256_t hex string constructor (auto-detect)
    try
    {
        uint256_t val(input);
        (void)val;
    }
    catch (const std::exception &)
    {
    }

    // Test uint128_t hex string constructor
    try
    {
        uint128_t val(input);
        (void)val;
    }
    catch (const std::exception &)
    {
    }

    return 0;
}
