# uint256_t

An unsigned 256-bit integer type for C++. Works like the built-in `uintX_t` types, just bigger.

Both `uint256_t` and `uint128_t` are included.

MIT licensed. See [LICENSE](LICENSE) for details.

## Quick Start

Include the header and go:

```cpp
#include <iostream>
#include "uint256_t.h"

int main()
{
    uint256_t a = 1;
    uint256_t b = 2;
    std::cout << (a | b) << std::endl;

    uint256_t big("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    std::cout << big.str(10) << std::endl;

    return 0;
}
```

## Building

Requires a C++17 compiler. Tested with GCC 11+, Clang 14+, AppleClang, MSVC, and MinGW.

### CMake (recommended)

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j
```

This produces a static library (`uint256t`) and, by default, a test executable (`uint256-tests`).

### Direct compilation

```bash
g++ -std=c++17 main.cpp uint128_t.cpp uint256_t.cpp -o main
```

Or compile the `.cpp` files into object files / a library and link as usual.

## Running Tests

Tests use CTest. After building:

```bash
cd build
ctest -C Release --output-on-failure
```

To skip building tests:

```bash
cmake .. -DBUILD_TESTS=OFF
```

## What You Get

All the operators you'd expect on an integer type:

- **Arithmetic**: `+`, `-`, `*`, `/`, `%` (division by zero throws `std::domain_error`)
- **Bitwise**: `&`, `|`, `^`, `~`
- **Shifts**: `<<`, `>>`
- **Comparison**: `==`, `!=`, `<`, `>`, `<=`, `>=`
- **Increment/Decrement**: `++`, `--` (prefix and postfix)
- **Assignment**: `=`, `+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `|=`, `^=`, `<<=`, `>>=`
- **Stream output**: works with `std::cout` in oct, dec, and hex modes

Mixed operations with built-in integer types work naturally:

```cpp
uint256_t x = 42;
x += 10;
bool check = (x > 50);
```

### Construction

```cpp
uint256_t a;                          // default (uninitialized, like built-in types)
uint256_t b(42);                      // from any integer type
uint256_t c("0xdeadbeef");            // from hex string (with or without 0x prefix)
uint256_t d("12345", 10);             // from string in any base 2-36
uint256_t e(upper_128, lower_128);    // from two uint128_t halves
```

### Useful Helpers

```cpp
x.str(10)         // string in base 10 (bases 2-36 supported)
x.str(16, 64)     // hex string zero-padded to 64 characters
x.bits()           // number of significant bits (0 returns 0, 1 returns 1, 255 returns 8)
x.upper()          // upper 128 bits (as uint128_t)
x.lower()          // lower 128 bits (as uint128_t)
x.export_bits()    // big-endian byte vector (always 32 bytes for uint256_t)
x.export_bits_truncate()  // same, but leading zero bytes stripped
```

### Pre-defined Constants

```cpp
uint256_0    // 0
uint256_1    // 1
uint256_max  // 2^256 - 1
uint128_0    // 0
uint128_1    // 1
```

## Acknowledgements

With much help from Auston Sterling.

Thanks to Stefan Deigmuller for finding a bug in `operator*`.

Thanks to Francois Dessenne for convincing me to do a general rewrite of this class.

Thanks to John Skaller for making symbols visible when compiling as a shared library.

Originally by Jason Lee (calccrypto).
