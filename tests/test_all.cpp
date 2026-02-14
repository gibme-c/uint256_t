#include "test_harness.h"
#include <map>

// ============================================================================
// test_constructor
// ============================================================================
void test_constructor()
{
    // Constructor, standard
    {
        uint256_t value(0x0123456789abcdefULL);
        const uint256_t original = value;
        CHECK_EQ(uint256_t(), 0);
        CHECK_EQ(value, original);
        CHECK_EQ(uint256_t(std::move(value)), original);
        CHECK_EQ(value, 0x0123456789abcdefULL);
    }

    // Constructor, string
    {
        CHECK_EQ(uint256_t("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"), uint256_max);
        CHECK_EQ(uint256_t("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"), uint256_max);
        CHECK_EQ(uint256_t("0x0"), 0);
        CHECK_EQ(uint256_t("0"), 0);
        CHECK_EQ(uint256_t("0x0123456789abcdef"), 0x0123456789abcdefULL);
    }

    // Constructor, base_string
    {
        CHECK_EQ(uint256_t("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff", 16), uint256_max);
        CHECK_EQ(uint256_t("115792089237316195423570985008687907853269984665640564039457584007913129639935", 10), uint256_max);
        CHECK_EQ(uint256_t("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111", 2), uint256_max);
        CHECK_EQ(uint256_t("0", 10), 0);
        CHECK_EQ(uint256_t("0123456789abcdef", 16), 0x0123456789abcdefULL);
        CHECK_EQ(uint256_t("755", 8), 0x01ed);
        CHECK_EQ(uint256_t("31415926", 10), 0x01df5e76ULL);
    }

    // Constructor, one
    {
        CHECK_EQ(uint256_t(true).upper(),  false);
        CHECK_EQ(uint256_t(true).lower(),   true);
        CHECK_EQ(uint256_t(false).upper(), false);
        CHECK_EQ(uint256_t(false).lower(), false);
        CHECK_EQ(uint256_t((uint8_t)  0x01ULL).upper(),               0ULL);
        CHECK_EQ(uint256_t((uint16_t) 0x0123ULL).upper(),             0ULL);
        CHECK_EQ(uint256_t((uint32_t) 0x01234567ULL).upper(),         0ULL);
        CHECK_EQ(uint256_t((uint64_t) 0x0123456789abcdefULL).upper(), 0ULL);
        CHECK_EQ(uint256_t((uint8_t)  0x01ULL).lower(),               (uint8_t)  0x01ULL);
        CHECK_EQ(uint256_t((uint16_t) 0x0123ULL).lower(),             (uint16_t) 0x0123ULL);
        CHECK_EQ(uint256_t((uint32_t) 0x01234567ULL).lower(),         (uint32_t) 0x01234567ULL);
        CHECK_EQ(uint256_t((uint64_t) 0x0123456789abcdefULL).lower(), (uint64_t) 0x0123456789abcdefULL);
    }

    // Constructor, two
    {
        for(uint8_t hi = 0; hi < 2; hi++){
            for(uint8_t lo = 0; lo < 2; lo++){
                const uint256_t val(hi, lo);
                CHECK_EQ(val.upper(), hi);
                CHECK_EQ(val.lower(), lo);
            }
        }
        CHECK_EQ(uint256_t((uint8_t)  0x01ULL,               (uint8_t)  0x01ULL).upper(),               (uint8_t)  0x01ULL);
        CHECK_EQ(uint256_t((uint16_t) 0x0123ULL,             (uint16_t) 0x0123ULL).upper(),             (uint16_t) 0x0123ULL);
        CHECK_EQ(uint256_t((uint32_t) 0x01234567ULL,         (uint32_t) 0x01234567ULL).upper(),         (uint32_t) 0x01234567ULL);
        CHECK_EQ(uint256_t((uint64_t) 0x0123456789abcdefULL, (uint64_t) 0x0123456789abcdefULL).upper(), (uint64_t) 0x0123456789abcdefULL);
        CHECK_EQ(uint256_t((uint8_t)  0x01ULL,               (uint8_t)  0x01ULL).lower(),               (uint8_t)  0x01ULL);
        CHECK_EQ(uint256_t((uint16_t) 0x0123ULL,             (uint16_t) 0x0123ULL).lower(),             (uint16_t) 0x0123ULL);
        CHECK_EQ(uint256_t((uint32_t) 0x01234567ULL,         (uint32_t) 0x01234567ULL).lower(),         (uint32_t) 0x01234567ULL);
        CHECK_EQ(uint256_t((uint64_t) 0x0123456789abcdefULL, (uint64_t) 0x0123456789abcdefULL).lower(), (uint64_t) 0x0123456789abcdefULL);
    }

    // Constructor, four
    {
        for(uint8_t hi_hi = 0; hi_hi < 2; hi_hi++){
            for(uint8_t hi_lo = 0; hi_lo < 2; hi_lo++){
                for(uint8_t lo_hi = 0; lo_hi < 2; lo_hi++){
                    for(uint8_t lo_lo = 0; lo_lo < 2; lo_lo++){
                        const uint256_t val(hi_hi, hi_lo, lo_hi, lo_lo);
                        CHECK_EQ(val.upper().upper(), hi_hi);
                        CHECK_EQ(val.upper().lower(), hi_lo);
                        CHECK_EQ(val.lower().upper(), lo_hi);
                        CHECK_EQ(val.lower().lower(), lo_lo);
                    }
                }
            }
        }
    }
}

// ============================================================================
// test_assignment
// ============================================================================
void test_assignment()
{
    const uint256_t t_1   = true;
    const uint256_t f_1   = false;
    const uint256_t u8_1  = 0x01;
    const uint256_t u16_1 = 0x0123;
    const uint256_t u32_1 = 0x01234567;
    const uint256_t u64_1 = 0x0123456789abcdef;

    uint256_t t_2   = 0;
    uint256_t f_2   = 0;
    uint256_t u8_2  = 0;
    uint256_t u16_2 = 0;
    uint256_t u32_2 = 0;
    uint256_t u64_2 = 0;

    t_2 = t_1;
    f_2 = f_1;
    u8_2 = u8_1;
    u16_2 = u16_1;
    u32_2 = u32_1;
    u64_2 = u64_1;

    CHECK_EQ(t_1, t_2);
    CHECK_EQ(f_1, f_2);
    CHECK_EQ(u8_1, u8_2);
    CHECK_EQ(u16_1, u16_2);
    CHECK_EQ(u32_1, u32_2);
    CHECK_EQ(u64_1, u64_2);
}

// ============================================================================
// test_typecast
// ============================================================================
void test_typecast()
{
    const uint256_t val(0xaaaaaaaaaaaaaaaaULL, 0xaaaaaaaaaaaaaaaaULL);

    CHECK_EQ(static_cast <bool>     (uint256_t(true)),          true);
    CHECK_EQ(static_cast <bool>     (uint256_t(false)),         false);
    CHECK_EQ(static_cast <uint8_t>  (val),           (uint8_t)  0xaaULL);
    CHECK_EQ(static_cast <uint16_t> (val),           (uint16_t) 0xaaaaULL);
    CHECK_EQ(static_cast <uint32_t> (val),           (uint32_t) 0xaaaaaaaaULL);
    CHECK_EQ(static_cast <uint64_t> (val),           (uint64_t) 0xaaaaaaaaaaaaaaaaULL);
}

// ============================================================================
// test_accessors
// ============================================================================
void test_accessors()
{
    // Accessor, bits
    {
        uint256_t value = 1;
        for(uint32_t i = 0; i < 127; i++){
            CHECK_EQ(value.bits(), i + 1);
            value <<= 1;
        }

        CHECK_EQ(uint256_t(0).bits(), 0);
    }

    // Accessor, data
    {
        const uint256_t value(0xfedcba9876543210ULL, 0x0123456789abcdefULL, 0xfedcba9876543210ULL, 0x0123456789abcdefULL);
        CHECK_EQ(value.upper().upper(), 0xfedcba9876543210ULL);
        CHECK_EQ(value.upper().lower(), 0x0123456789abcdefULL);
        CHECK_EQ(value.lower().upper(), 0xfedcba9876543210ULL);
        CHECK_EQ(value.lower().lower(), 0x0123456789abcdefULL);
    }
}

// ============================================================================
// test_and
// ============================================================================
void test_and()
{
    // BitWise and
    {
        uint256_t t  ((bool)     true);
        uint256_t f  ((bool)     false);
        uint256_t u8 ((uint8_t)  0xaaULL);
        uint256_t u16((uint16_t) 0xaaaaULL);
        uint256_t u32((uint32_t) 0xaaaaaaaaULL);
        uint256_t u64((uint64_t) 0xaaaaaaaaaaaaaaaaULL);

        const uint256_t val(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL);

        CHECK_EQ(t   &  val, uint256_t(0));
        CHECK_EQ(f   &  val, uint256_t(0));
        CHECK_EQ(u8  &  val, uint256_t(0xa0ULL));
        CHECK_EQ(u16 &  val, uint256_t(0xa0a0ULL));
        CHECK_EQ(u32 &  val, uint256_t(0xa0a0a0a0ULL));
        CHECK_EQ(u64 &  val, uint256_t(0xa0a0a0a0a0a0a0a0ULL));

        CHECK_EQ(t   &= val, uint256_t(0x0ULL));
        CHECK_EQ(f   &= val, uint256_t(0x0ULL));
        CHECK_EQ(u8  &= val, uint256_t(0xa0ULL));
        CHECK_EQ(u16 &= val, uint256_t(0xa0a0ULL));
        CHECK_EQ(u32 &= val, uint256_t(0xa0a0a0a0ULL));
        CHECK_EQ(u64 &= val, uint256_t(0xa0a0a0a0a0a0a0a0ULL));
    }

    // External and
    {
        bool     t   = true;
        bool     f   = false;
        uint8_t  u8  = 0xaaULL;
        uint16_t u16 = 0xaaaaULL;
        uint32_t u32 = 0xaaaaaaaaULL;
        uint64_t u64 = 0xaaaaaaaaaaaaaaaaULL;

        const uint256_t val(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL);

        CHECK_EQ(t   &  val, uint256_t(0x0ULL));
        CHECK_EQ(f   &  val, uint256_t(0x0ULL));
        CHECK_EQ(u8  &  val, uint256_t(0xa0ULL));
        CHECK_EQ(u16 &  val, uint256_t(0xa0a0ULL));
        CHECK_EQ(u32 &  val, uint256_t(0xa0a0a0a0ULL));
        CHECK_EQ(u64 &  val, uint256_t(0xa0a0a0a0a0a0a0a0ULL));

        CHECK_EQ(t   &= val, false);
        CHECK_EQ(f   &= val, false);
        CHECK_EQ(u8  &= val, (uint8_t)  0xa0ULL);
        CHECK_EQ(u16 &= val, (uint16_t) 0xa0a0ULL);
        CHECK_EQ(u32 &= val, (uint32_t) 0xa0a0a0a0ULL);
        CHECK_EQ(u64 &= val, (uint64_t) 0xa0a0a0a0a0a0a0a0ULL);

        // zero
        CHECK_EQ(uint256_t() & val, 0);
    }
}

// ============================================================================
// test_or
// ============================================================================
void test_or()
{
    // BitWise or
    {
        uint256_t t  ((bool)     true);
        uint256_t f  ((bool)     false);
        uint256_t u8 ((uint8_t)  0xaaULL);
        uint256_t u16((uint16_t) 0xaaaaULL);
        uint256_t u32((uint32_t) 0xaaaaaaaaULL);
        uint256_t u64((uint64_t) 0xaaaaaaaaaaaaaaaaULL);

        const uint256_t val(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL);

        CHECK_EQ(t   |  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f1ULL));
        CHECK_EQ(f   |  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL));
        CHECK_EQ(u8  |  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0faULL));
        CHECK_EQ(u16 |  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0fafaULL));
        CHECK_EQ(u32 |  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0fafafafaULL));
        CHECK_EQ(u64 |  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xfafafafafafafafaULL));

        CHECK_EQ(t   |= val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f1ULL));
        CHECK_EQ(f   |= val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL));
        CHECK_EQ(u8  |= val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0faULL));
        CHECK_EQ(u16 |= val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0fafaULL));
        CHECK_EQ(u32 |= val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0fafafafaULL));
        CHECK_EQ(u64 |= val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xfafafafafafafafaULL));

        // zero
        CHECK_EQ(uint256_t() | val, val);
    }

    // External or
    {
        bool     t   = true;
        bool     f   = false;
        uint8_t  u8  = 0xaa;
        uint16_t u16 = 0xaaaa;
        uint32_t u32 = 0xaaaaaaaaULL;
        uint64_t u64 = 0xaaaaaaaaaaaaaaaaULL;

        const uint256_t val(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL);

        CHECK_EQ(t   |  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f1ULL));
        CHECK_EQ(f   |  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL));
        CHECK_EQ(u8  |  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0faULL));
        CHECK_EQ(u16 |  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0fafaULL));
        CHECK_EQ(u32 |  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0fafafafaULL));
        CHECK_EQ(u64 |  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xfafafafafafafafaULL));

        CHECK_EQ(t   |= val, true);
        CHECK_EQ(f   |= val, true);
        CHECK_EQ(u8  |= val, (uint8_t)  0xfaULL);
        CHECK_EQ(u16 |= val, (uint16_t) 0xfafaULL);
        CHECK_EQ(u32 |= val, (uint32_t) 0xfafafafaULL);
        CHECK_EQ(u64 |= val, (uint64_t) 0xfafafafafafafafaULL);

        // zero
        CHECK_EQ(uint256_t() | val, val);
    }
}

// ============================================================================
// test_xor
// ============================================================================
void test_xor()
{
    // BitWise xor
    {
        uint256_t t  ((bool)     true);
        uint256_t f  ((bool)     false);
        uint256_t u8 ((uint8_t)  0xaaULL);
        uint256_t u16((uint16_t) 0xaaaaULL);
        uint256_t u32((uint32_t) 0xaaaaaaaaULL);
        uint256_t u64((uint64_t) 0xaaaaaaaaaaaaaaaa);

        const uint256_t val(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL);

        CHECK_EQ(t   ^  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f1ULL));
        CHECK_EQ(f   ^  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL));
        CHECK_EQ(u8  ^  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f05aULL));
        CHECK_EQ(u16 ^  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f05a5aULL));
        CHECK_EQ(u32 ^  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f05a5a5a5aULL));
        CHECK_EQ(u64 ^  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0x5a5a5a5a5a5a5a5aULL));

        CHECK_EQ(t   ^= val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f1ULL));
        CHECK_EQ(f   ^= val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL));
        CHECK_EQ(u8  ^= val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f05aULL));
        CHECK_EQ(u16 ^= val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f05a5aULL));
        CHECK_EQ(u32 ^= val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f05a5a5a5aULL));
        CHECK_EQ(u64 ^= val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0x5a5a5a5a5a5a5a5aULL));

        // zero
        CHECK_EQ(uint256_t() ^ val, val);
    }

    // External xor
    {
        bool     t   = true;
        bool     f   = false;
        uint8_t  u8  = 0xaaULL;
        uint16_t u16 = 0xaaaaULL;
        uint32_t u32 = 0xaaaaaaaaULL;
        uint64_t u64 = 0xaaaaaaaaaaaaaaaaULL;

        const uint256_t val(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL);

        CHECK_EQ(t   ^  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f1ULL));
        CHECK_EQ(f   ^  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL));
        CHECK_EQ(u8  ^  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f05aULL));
        CHECK_EQ(u16 ^  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f05a5aULL));
        CHECK_EQ(u32 ^  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f05a5a5a5aULL));
        CHECK_EQ(u64 ^  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0x5a5a5a5a5a5a5a5aULL));

        CHECK_EQ(t   ^= val, true);
        CHECK_EQ(f   ^= val, true);
        CHECK_EQ(u8  ^= val, (uint8_t)  0x5aULL);
        CHECK_EQ(u16 ^= val, (uint16_t) 0x5a5aULL);
        CHECK_EQ(u32 ^= val, (uint32_t) 0x5a5a5a5aULL);
        CHECK_EQ(u64 ^= val, (uint64_t) 0x5a5a5a5a5a5a5a5aULL);

        // zero
        CHECK_EQ(uint256_t() ^ val, val);
    }
}

// ============================================================================
// test_invert
// ============================================================================
void test_invert()
{
    for(uint8_t hi_hi = 0; hi_hi < 2; hi_hi++){
        for(uint8_t hi_lo = 0; hi_lo < 2; hi_lo++){
            for(uint8_t lo_hi = 0; lo_hi < 2; lo_hi++){
                for(uint8_t lo_lo = 0; lo_lo < 2; lo_lo++){
                    const uint256_t val = ~uint256_t(hi_hi?0xffffffffffffffffULL:0x0000000000000000ULL,
                                                     hi_lo?0xffffffffffffffffULL:0x0000000000000000ULL,
                                                     lo_hi?0xffffffffffffffffULL:0x0000000000000000ULL,
                                                     lo_lo?0xffffffffffffffffULL:0x0000000000000000ULL);

                    CHECK_EQ(val.upper().upper(), hi_hi?0x0000000000000000ULL:0xffffffffffffffffULL);
                    CHECK_EQ(val.upper().lower(), hi_lo?0x0000000000000000ULL:0xffffffffffffffffULL);
                    CHECK_EQ(val.lower().upper(), lo_hi?0x0000000000000000ULL:0xffffffffffffffffULL);
                    CHECK_EQ(val.lower().lower(), lo_lo?0x0000000000000000ULL:0xffffffffffffffffULL);
                }
            }
        }
    }
}

// ============================================================================
// test_leftshift
// ============================================================================
void test_leftshift()
{
    // BitShift left
    {
        // operator<<
        uint256_t val(0x1);
        uint64_t exp_val = 1;
        for(uint8_t i = 0; i < 64; i++){
            CHECK_EQ(val << i, exp_val << i);
        }

        uint256_t zero(0);
        for(uint8_t i = 0; i < 64; i++){
            CHECK_EQ(zero << i, 0);
        }

        // operator<<=
        for(uint8_t i = 0; i < 63; i++){
            CHECK_EQ(val  <<= 1, exp_val <<= 1);
        }

        for(uint8_t i = 0; i < 63; i++){
            CHECK_EQ(zero <<= 1, 0);
        }
    }

    // External shift_left
    {
        bool      t    = true;
        bool      f    = false;
        uint8_t   u8   = 0xffULL;
        uint16_t  u16  = 0xffffULL;
        uint32_t  u32  = 0xffffffffULL;
        uint64_t  u64  = 0xffffffffffffffffULL;
        uint128_t u128  (0xffffffffffffffffULL, 0xffffffffffffffffULL);

        const uint256_t zero(0);
        const uint256_t one(1);

        CHECK_EQ(t    << zero, t);
        CHECK_EQ(f    << zero, f);
        CHECK_EQ(u8   << zero, u8);
        CHECK_EQ(u16  << zero, u16);
        CHECK_EQ(u32  << zero, u32);
        CHECK_EQ(u64  << zero, u64);
        CHECK_EQ(u128 << zero, u128);

        CHECK_EQ(t    <<= zero, t);
        CHECK_EQ(f    <<= zero, f);
        CHECK_EQ(u8   <<= zero, u8);
        CHECK_EQ(u16  <<= zero, u16);
        CHECK_EQ(u32  <<= zero, u32);
        CHECK_EQ(u64  <<= zero, u64);
        CHECK_EQ(u128 <<= zero, u128);

        CHECK_EQ(t    << one, uint256_t(t)    << 1);
        CHECK_EQ(f    << one, uint256_t(f)    << 1);
        CHECK_EQ(u8   << one, uint256_t(u8)   << 1);
        CHECK_EQ(u16  << one, uint256_t(u16)  << 1);
        CHECK_EQ(u32  << one, uint256_t(u32)  << 1);
        CHECK_EQ(u64  << one, uint256_t(u64)  << 1);
        CHECK_EQ(u128 << one, uint256_t(u128) << 1);

        CHECK_EQ(t    <<= one, true);
        CHECK_EQ(f    <<= one, false);
        CHECK_EQ(u8   <<= one, (uint8_t)  0xfeULL);
        CHECK_EQ(u16  <<= one, (uint16_t) 0xfffeULL);
        CHECK_EQ(u32  <<= one, (uint32_t) 0xfffffffeULL);
        CHECK_EQ(u64  <<= one, (uint64_t) 0xfffffffffffffffeULL);
        CHECK_EQ(u128 <<= one, uint128_t (0xffffffffffffffffULL, 0xfffffffffffffffeULL));

        CHECK_EQ(u8   << uint256_t(7),   uint256_t(0x7f00ULL));
        CHECK_EQ(u16  << uint256_t(15),  uint256_t(0x7fff0000ULL));
        CHECK_EQ(u32  << uint256_t(31),  uint256_t(0x7fffffff00000000ULL));
        CHECK_EQ(u64  << uint256_t(63),  uint256_t(0x0000000000000000ULL, 0x0000000000000000ULL, 0x7fffffffffffffffULL, 0x0000000000000000ULL));
        CHECK_EQ(u128 << uint256_t(127), uint256_t(0x7fffffffffffffffULL, 0xffffffffffffffffULL, 0x0000000000000000ULL, 0x0000000000000000ULL));

        CHECK_EQ(u8   <<= uint256_t(7),   (uint8_t)   0);
        CHECK_EQ(u16  <<= uint256_t(15),  (uint16_t)  0);
        CHECK_EQ(u32  <<= uint256_t(31),  (uint32_t)  0);
        CHECK_EQ(u64  <<= uint256_t(63),  (uint64_t)  0);
        CHECK_EQ(u128 <<= uint256_t(127), (uint128_t) 0);
    }
}

// ============================================================================
// test_rightshift
// ============================================================================
void test_rightshift()
{
    // BitShift right
    {
        // operator>>
        uint256_t val(0xffffffffffffffffULL);
        uint64_t exp = 0xffffffffffffffffULL;
        for(uint8_t i = 0; i < 64; i++){
            CHECK_EQ(val >> i, exp >> i);
        }

        uint256_t zero(0);
        for(uint8_t i = 0; i < 64; i++){
            CHECK_EQ(zero >> i, 0);
        }

        // operator>>=
        for(uint8_t i = 0; i < 64; i++){
            CHECK_EQ(val >>= 1, exp >>= 1);
        }

        for(uint8_t i = 0; i < 64; i++){
            CHECK_EQ(zero >>= 1, 0);
        }
    }

    // External shift_right
    {
        bool     t   = true;
        bool     f   = false;
        uint8_t  u8  = 0xffULL;
        uint16_t u16 = 0xffffULL;
        uint32_t u32 = 0xffffffffULL;
        uint64_t u64 = 0xffffffffffffffffULL;

        const uint256_t zero(0);
        const uint256_t one(1);

        CHECK_EQ(t   >> zero, one);
        CHECK_EQ(f   >> zero, zero);
        CHECK_EQ(u8  >> zero, u8);
        CHECK_EQ(u16 >> zero, u16);
        CHECK_EQ(u32 >> zero, u32);
        CHECK_EQ(u64 >> zero, u64);

        CHECK_EQ(t   >>= zero, t);
        CHECK_EQ(f   >>= zero, f);
        CHECK_EQ(u8  >>= zero, u8);
        CHECK_EQ(u16 >>= zero, u16);
        CHECK_EQ(u32 >>= zero, u32);
        CHECK_EQ(u64 >>= zero, u64);

        CHECK_EQ(t   >> one, uint256_t(t)   >> 1);
        CHECK_EQ(f   >> one, uint256_t(f)   >> 1);
        CHECK_EQ(u8  >> one, uint256_t(u8)  >> 1);
        CHECK_EQ(u16 >> one, uint256_t(u16) >> 1);
        CHECK_EQ(u32 >> one, uint256_t(u32) >> 1);
        CHECK_EQ(u64 >> one, uint256_t(u64) >> 1);

        CHECK_EQ(t   >>= one, false);
        CHECK_EQ(f   >>= one, false);
        CHECK_EQ(u8  >>= one, (uint8_t)  0x7fULL);
        CHECK_EQ(u16 >>= one, (uint16_t) 0x7fffULL);
        CHECK_EQ(u32 >>= one, (uint32_t) 0x7fffffffULL);
        CHECK_EQ(u64 >>= one, (uint64_t) 0x7fffffffffffffffULL);

        CHECK_EQ(u8  >> uint256_t(7),  zero);
        CHECK_EQ(u16 >> uint256_t(15), zero);
        CHECK_EQ(u32 >> uint256_t(31), zero);
        CHECK_EQ(u64 >> uint256_t(63), zero);

        CHECK_EQ(u8  >>= uint256_t(7),  (uint8_t)  0);
        CHECK_EQ(u16 >>= uint256_t(15), (uint16_t) 0);
        CHECK_EQ(u32 >>= uint256_t(31), (uint32_t) 0);
        CHECK_EQ(u64 >>= uint256_t(63), (uint64_t) 0);
    }
}

// ============================================================================
// test_logical
// ============================================================================
void test_logical()
{
    // Logical, and
    {
        const uint256_t A(0xffffffff);
        const uint256_t B(0x00000000);

        CHECK_EQ(A && A, true);
        CHECK_EQ(A && B, false);
    }

    // Logical, or
    {
        const uint256_t A(0xffffffff);
        const uint256_t B(0x00000000);

        CHECK_EQ(A || A, true);
        CHECK_EQ(A || B, true);
    }

    // Logical, not
    {
        CHECK_EQ(!uint256_t(0xffffffff), 0);
    }
}

// ============================================================================
// test_gt
// ============================================================================
#define unsigned_compare_gt(Z)                                         \
do                                                                     \
{                                                                      \
    static_assert(std::is_unsigned <Z>::value, "Type must be signed"); \
                                                                       \
    const Z small = std::numeric_limits <Z>::min();                    \
    const Z big   = std::numeric_limits <Z>::max();                    \
                                                                       \
    const uint256_t int_small(small);                                  \
    const uint256_t int_big(big);                                      \
                                                                       \
    CHECK_EQ(small > int_small, false);                                \
    CHECK_EQ(small > int_big,   false);                                \
                                                                       \
    CHECK_EQ(big > int_small,   true);                                 \
    CHECK_EQ(big > int_big,     false);                                \
}                                                                      \
while (0)

#define signed_compare_gt(Z)                                           \
do                                                                     \
{                                                                      \
    static_assert(std::is_signed <Z>::value, "Type must be signed");   \
                                                                       \
    const Z small =  1;                                                \
    const Z big = std::numeric_limits <Z>::max();                      \
                                                                       \
    const uint256_t int_small(small);                                  \
    const uint256_t int_big(big);                                      \
                                                                       \
    CHECK_EQ(small > int_small, false);                                \
    CHECK_EQ(small > int_big,   false);                                \
                                                                       \
    CHECK_EQ(big > int_small,   true);                                 \
    CHECK_EQ(big > int_big,     false);                                \
}                                                                      \
while (0)

void test_gt()
{
    // Comparison greater_than
    {
        const uint256_t big  (0xffffffffffffffffULL, 0xffffffffffffffffULL);
        const uint256_t small(0x0000000000000000ULL, 0x0000000000000000ULL);

        CHECK_EQ(small > small,     false);
        CHECK_EQ(small > big,       false);

        CHECK_EQ(big > small,        true);
        CHECK_EQ(big > big,         false);
    }

    // External greater_than
    {
        unsigned_compare_gt(bool);
        unsigned_compare_gt(uint8_t);
        unsigned_compare_gt(uint16_t);
        unsigned_compare_gt(uint32_t);
        unsigned_compare_gt(uint64_t);
        signed_compare_gt(int8_t);
        signed_compare_gt(int16_t);
        signed_compare_gt(int32_t);
        signed_compare_gt(int64_t);
    }
}

#undef unsigned_compare_gt
#undef signed_compare_gt

// ============================================================================
// test_gte
// ============================================================================
#define unsigned_compare_gte(Z)                                        \
do                                                                     \
{                                                                      \
    static_assert(std::is_unsigned <Z>::value, "Type must be signed"); \
                                                                       \
    const Z small = std::numeric_limits <Z>::min();                    \
    const Z big   = std::numeric_limits <Z>::max();                    \
                                                                       \
    const uint256_t int_small(small);                                  \
    const uint256_t int_big(big);                                      \
                                                                       \
    CHECK_EQ(small >= int_small, true);                                \
    CHECK_EQ(small >= int_big,   false);                               \
                                                                       \
    CHECK_EQ(big >= int_small,   true);                                \
    CHECK_EQ(big >= int_big,     true);                                \
}                                                                      \
while (0)

#define signed_compare_gte(Z)                                          \
do                                                                     \
{                                                                      \
    static_assert(std::is_signed <Z>::value, "Type must be signed");   \
                                                                       \
    const Z small =  1;                                                \
    const Z big = std::numeric_limits <Z>::max();                      \
                                                                       \
    const uint256_t int_small(small);                                  \
    const uint256_t int_big(big);                                      \
                                                                       \
    CHECK_EQ(small >= int_small, true) ;                               \
    CHECK_EQ(small >= int_big,   false);                               \
                                                                       \
    CHECK_EQ(big >= int_small,   true);                                \
    CHECK_EQ(big >= int_big,     true);                                \
}                                                                      \
while (0)

void test_gte()
{
    // Comparison greater_than_or_equals
    {
        const uint256_t big  (0xffffffffffffffffULL, 0xffffffffffffffffULL);
        const uint256_t small(0x0000000000000000ULL, 0x0000000000000000ULL);

        CHECK_EQ(small >= small,  true);
        CHECK_EQ(small >= big,   false);

        CHECK_EQ(big >= small,    true);
        CHECK_EQ(big >= big,      true);
    }

    // External greater_than_or_equals
    {
        unsigned_compare_gte(bool);
        unsigned_compare_gte(uint8_t);
        unsigned_compare_gte(uint16_t);
        unsigned_compare_gte(uint32_t);
        unsigned_compare_gte(uint64_t);
        signed_compare_gte(int8_t);
        signed_compare_gte(int16_t);
        signed_compare_gte(int32_t);
        signed_compare_gte(int64_t);
    }
}

#undef unsigned_compare_gte
#undef signed_compare_gte

// ============================================================================
// test_lt
// ============================================================================
#define unsigned_compare_lt(Z)                                            \
do                                                                        \
{                                                                         \
    static_assert(std::is_unsigned <Z>::value, "Type must be signed");    \
                                                                          \
    const Z small = std::numeric_limits <Z>::min();                       \
    const Z big   = std::numeric_limits <Z>::max();                       \
                                                                          \
    const uint256_t int_small(small);                                     \
    const uint256_t int_big(big);                                         \
                                                                          \
    CHECK_EQ(small < int_small, false);                                   \
    CHECK_EQ(small < int_big,   true);                                    \
                                                                          \
    CHECK_EQ(big < int_small,   false);                                   \
    CHECK_EQ(big < int_big,     false);                                   \
}                                                                         \
while (0)

#define signed_compare_lt(Z)                                              \
do                                                                        \
{                                                                         \
    static_assert(std::is_signed <Z>::value, "Type must be signed");      \
                                                                          \
    const Z small =  1;                                                   \
    const Z big = std::numeric_limits <Z>::max();                         \
                                                                          \
    const uint256_t int_small(small);                                     \
    const uint256_t int_big(big);                                         \
                                                                          \
    CHECK_EQ(small < int_small, false);                                   \
    CHECK_EQ(small < int_big,   true);                                    \
                                                                          \
    CHECK_EQ(big < int_small,   false);                                   \
    CHECK_EQ(big < int_big,     false);                                   \
}                                                                         \
while (0)

void test_lt()
{
    // Comparison less_than
    {
        const uint256_t big  (0xffffffffffffffffULL, 0xffffffffffffffffULL);
        const uint256_t small(0x0000000000000000ULL, 0x0000000000000000ULL);

        CHECK_EQ(small < small, false);
        CHECK_EQ(small < big,    true);

        CHECK_EQ(big < small,   false);
        CHECK_EQ(big < big,     false);
    }

    // External less_than
    {
        unsigned_compare_lt(bool);
        unsigned_compare_lt(uint8_t);
        unsigned_compare_lt(uint16_t);
        unsigned_compare_lt(uint32_t);
        unsigned_compare_lt(uint64_t);
        signed_compare_lt(int8_t);
        signed_compare_lt(int16_t);
        signed_compare_lt(int32_t);
        signed_compare_lt(int64_t);
    }
}

#undef unsigned_compare_lt
#undef signed_compare_lt

// ============================================================================
// test_lte
// ============================================================================
#define unsigned_compare_lte(Z)                                           \
do                                                                        \
{                                                                         \
    static_assert(std::is_unsigned <Z>::value, "Type must be signed");    \
                                                                          \
    const Z small = std::numeric_limits <Z>::min();                       \
    const Z big   = std::numeric_limits <Z>::max();                       \
                                                                          \
    const uint256_t int_small(small);                                     \
    const uint256_t int_big(big);                                         \
                                                                          \
    CHECK_EQ(small <= int_small, true);                                   \
    CHECK_EQ(small <= int_big,   true);                                   \
                                                                          \
    CHECK_EQ(big <= int_small,   false);                                  \
    CHECK_EQ(big <= int_big,     true);                                   \
}                                                                         \
while (0)

#define signed_compare_lte(Z)                                             \
do                                                                        \
{                                                                         \
    static_assert(std::is_signed <Z>::value, "Type must be signed");      \
                                                                          \
    const Z small =  1;                                                   \
    const Z big = std::numeric_limits <Z>::max();                         \
                                                                          \
    const uint256_t int_small(small);                                     \
    const uint256_t int_big(big);                                         \
                                                                          \
    CHECK_EQ(small <= int_small, true);                                   \
    CHECK_EQ(small <= int_big,   true);                                   \
                                                                          \
    CHECK_EQ(big <= int_small,   false);                                  \
    CHECK_EQ(big <= int_big,     true);                                   \
}                                                                         \
while (0)

void test_lte()
{
    // Comparison: less_than_or_equals
    const uint256_t big  (0xffffffffffffffffULL, 0xffffffffffffffffULL);
    const uint256_t small(0x0000000000000000ULL, 0x0000000000000000ULL);

    CHECK_EQ(small <= small,  true);
    CHECK_EQ(small <= big,    true);

    CHECK_EQ(big <= small,   false);
    CHECK_EQ(big <= big,      true);

    // External: less_than_or_equals
    unsigned_compare_lte(bool);
    unsigned_compare_lte(uint8_t);
    unsigned_compare_lte(uint16_t);
    unsigned_compare_lte(uint32_t);
    unsigned_compare_lte(uint64_t);
    signed_compare_lte(int8_t);
    signed_compare_lte(int16_t);
    signed_compare_lte(int32_t);
    signed_compare_lte(int64_t);
}

#undef unsigned_compare_lte
#undef signed_compare_lte

// ============================================================================
// test_equals
// ============================================================================
void test_equals()
{
    // Comparison: equals
    CHECK_EQ( (uint256_t(0xdeadbeefULL) == uint256_t(0xdeadbeefULL)), true);
    CHECK_EQ(!(uint256_t(0xdeadbeefULL) == uint256_t(0xfee1baadULL)), true);

    // External: equals
    const bool     t   = true;
    const bool     f   = false;
    const uint8_t  u8  = 0xaaULL;
    const uint16_t u16 = 0xaaaaULL;
    const uint32_t u32 = 0xaaaaaaaaULL;
    const uint64_t u64 = 0xaaaaaaaaaaaaaaaaULL;

    CHECK_EQ(t,   uint256_t(t));
    CHECK_EQ(f,   uint256_t(f));
    CHECK_EQ(u8,  uint256_t(u8));
    CHECK_EQ(u16, uint256_t(u16));
    CHECK_EQ(u32, uint256_t(u32));
    CHECK_EQ(u64, uint256_t(u64));
}

// ============================================================================
// test_notequals
// ============================================================================
void test_notequals()
{
    // Comparison: not_equals
    CHECK_EQ(!(uint256_t(0xdeadbeefULL) != uint256_t(0xdeadbeefULL)), true);
    CHECK_EQ( (uint256_t(0xdeadbeefULL) != uint256_t(0xfee1baadULL)), true);

    // External: not_equals
    const bool     t   = true;
    const bool     f   = false;
    const uint8_t  u8  = 0xaaULL;
    const uint16_t u16 = 0xaaaaULL;
    const uint32_t u32 = 0xaaaaaaaaULL;
    const uint64_t u64 = 0xaaaaaaaaaaaaaaaaULL;

    CHECK_EQ((t   != uint256_t(f)),   true);
    CHECK_EQ((f   != uint256_t(t)),   true);
    CHECK_EQ((u8  != uint256_t(u64)), true);
    CHECK_EQ((u16 != uint256_t(u32)), true);
    CHECK_EQ((u32 != uint256_t(u16)), true);
    CHECK_EQ((u64 != uint256_t(u8)),  true);

    CHECK_EQ((t   != uint256_t(t)),   false);
    CHECK_EQ((f   != uint256_t(f)),   false);
    CHECK_EQ((u8  != uint256_t(u8)),  false);
    CHECK_EQ((u16 != uint256_t(u16)), false);
    CHECK_EQ((u32 != uint256_t(u32)), false);
    CHECK_EQ((u64 != uint256_t(u64)), false);
}

// ============================================================================
// test_add
// ============================================================================
void test_add()
{
    // Arithmetic: add
    uint256_t low (0, 1);
    uint256_t high(1, 0);

    CHECK_EQ(low  + low,  2);
    CHECK_EQ(low  + high, uint256_t(1, 1));
    CHECK_EQ(high + high, uint256_t(2, 0));

    CHECK_EQ(low  += low,  2);
    CHECK_EQ(low  += high, uint256_t(1, 2));
    CHECK_EQ(high += low,  uint256_t(2, 2));

    // External: add
    bool     t     = true;
    bool     f     = false;
    uint8_t  u8    = 0xaaULL;
    uint16_t u16   = 0xaaaaULL;
    uint32_t u32   = 0xaaaaaaaaULL;
    uint64_t u64   = 0xaaaaaaaaaaaaaaaaULL;
    uint128_t u128  (0xaaaaaaaaaaaaaaaaULL, 0xaaaaaaaaaaaaaaaaULL);

    const uint256_t val(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL);

    CHECK_EQ(t    +  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f1ULL));
    CHECK_EQ(f    +  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL));
    CHECK_EQ(u8   +  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f19aULL));
    CHECK_EQ(u16  +  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f19b9aULL));
    CHECK_EQ(u32  +  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f19b9b9b9aULL));
    CHECK_EQ(u64  +  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f1ULL, 0x9b9b9b9b9b9b9b9aULL));
    CHECK_EQ(u128 +  val, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f1ULL, 0x9b9b9b9b9b9b9b9bULL, 0x9b9b9b9b9b9b9b9aULL));

    CHECK_EQ(t    += val, true);
    CHECK_EQ(f    += val, true);
    CHECK_EQ(u8   += val, (uint8_t)  0x9aULL);
    CHECK_EQ(u16  += val, (uint16_t) 0x9b9aULL);
    CHECK_EQ(u32  += val, (uint32_t) 0x9b9b9b9aULL);
    CHECK_EQ(u64  += val, (uint64_t) 0x9b9b9b9b9b9b9b9aULL);
    CHECK_EQ(u128 += val, uint128_t (0x9b9b9b9b9b9b9b9bULL, 0x9b9b9b9b9b9b9b9aULL));
}

// ============================================================================
// test_sub
// ============================================================================
void test_sub()
{
    // Arithmetic: subtract
    uint256_t big  (0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL);
    const uint256_t small(0x0000000000000000ULL, 0x0000000000000001ULL);

    CHECK_EQ(small - small, 0);
    CHECK_EQ(small - big,   uint256_t(0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000002ULL));
    CHECK_EQ(big   - small, uint256_t(0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xfffffffffffffffeULL));
    CHECK_EQ(big   - big,   0);

    // External: subtract
    bool     t    = true;
    bool     f    = false;
    uint8_t  u8   = 0xaaULL;
    uint16_t u16  = 0xaaaaULL;
    uint32_t u32  = 0xaaaaaaaaULL;
    uint64_t u64  = 0xaaaaaaaaaaaaaaaaULL;
    uint128_t u128 (0xaaaaaaaaaaaaaaaaULL, 0xaaaaaaaaaaaaaaaaULL);

    const uint256_t val(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL);

    CHECK_EQ(t    -  val, uint256_t(0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0f0f11ULL));
    CHECK_EQ(f    -  val, uint256_t(0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0f0f10ULL));
    CHECK_EQ(u8   -  val, uint256_t(0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0f0fbaULL));
    CHECK_EQ(u16  -  val, uint256_t(0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0fb9baULL));
    CHECK_EQ(u32  -  val, uint256_t(0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0fb9b9b9baULL));
    CHECK_EQ(u64  -  val, uint256_t(0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0f0f0fULL, 0xb9b9b9b9b9b9b9baULL));
    CHECK_EQ(u128 -  val, uint256_t(0x0f0f0f0f0f0f0f0fULL, 0x0f0f0f0f0f0f0f0fULL, 0xb9b9b9b9b9b9b9b9ULL, 0xb9b9b9b9b9b9b9baULL));

    CHECK_EQ(t    -= val, true);
    CHECK_EQ(f    -= val, true);
    CHECK_EQ(u8   -= val, (uint8_t)  0xbaULL);
    CHECK_EQ(u16  -= val, (uint16_t) 0xb9baULL);
    CHECK_EQ(u32  -= val, (uint32_t) 0xb9b9b9baULL);
    CHECK_EQ(u64  -= val, (uint64_t) 0xb9b9b9b9b9b9b9baULL);
    CHECK_EQ(u128 -= val,  uint128_t(0xb9b9b9b9b9b9b9b9ULL, 0xb9b9b9b9b9b9b9baULL));
}

// ============================================================================
// test_mult
// ============================================================================
void test_mult()
{
    // Arithmetic: multiply
    uint256_t val(0xfedbca9876543210ULL);

    CHECK_EQ(val * val, uint256_t(0x0000000000000000ULL, 0x0000000000000000ULL, 0xfdb8e2bacbfe7cefULL, 0x010e6cd7a44a4100ULL));

    const uint256_t zero = 0;
    CHECK_EQ(val  * zero, zero);
    CHECK_EQ(zero * val,  zero);

    const uint256_t one = 1;
    CHECK_EQ(val * one, val);
    CHECK_EQ(one * val, val);

    // External: multiply
    bool      t    = true;
    bool      f    = false;
    uint8_t   u8   = 0xaaULL;
    uint16_t  u16  = 0xaaaaULL;
    uint32_t  u32  = 0xaaaaaaaaULL;
    uint64_t  u64  = 0xaaaaaaaaaaaaaaaaULL;
    uint128_t u128  (0xaaaaaaaaaaaaaaaaULL, 0xaaaaaaaaaaaaaaaaULL);

    const uint256_t val2(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL);

    CHECK_EQ(t    *  val2, uint256_t(0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL, 0xf0f0f0f0f0f0f0f0ULL));
    CHECK_EQ(f    *  val2, uint256_t(0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL));
    CHECK_EQ(u8   *  val2, uint256_t(0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffff60ULL));
    CHECK_EQ(u16  *  val2, uint256_t(0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffff5f60ULL));
    CHECK_EQ(u32  *  val2, uint256_t(0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffff5f5f5f60ULL));
    CHECK_EQ(u64  *  val2, uint256_t(0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL, 0x5f5f5f5f5f5f5f60ULL));
    CHECK_EQ(u128 *  val2, uint256_t(0xffffffffffffffffULL, 0xffffffffffffffffULL, 0x5f5f5f5f5f5f5f5fULL, 0x5f5f5f5f5f5f5f60ULL));

    CHECK_EQ(t    *= val2, true);
    CHECK_EQ(f    *= val2, false);
    CHECK_EQ(u8   *= val2, (uint8_t)                0x60ULL);
    CHECK_EQ(u16  *= val2, (uint16_t)             0x5f60ULL);
    CHECK_EQ(u32  *= val2, (uint32_t)         0x5f5f5f60ULL);
    CHECK_EQ(u64  *= val2, (uint64_t) 0x5f5f5f5f5f5f5f60ULL);
    CHECK_EQ(u128 *= val2,  uint128_t(0x5f5f5f5f5f5f5f5fULL, 0x5f5f5f5f5f5f5f60ULL));
}

// ============================================================================
// test_div
// ============================================================================
void test_div()
{
    // Arithmetic: divide
    const uint256_t big    (0xfedbca9876543210ULL);
    const uint256_t small  (0xffffULL);
    const uint256_t res_val(0xfedcc9753fc9ULL);

    CHECK_EQ(small / small, 1);
    CHECK_EQ(small / big,   0);

    CHECK_EQ(big   / big,   1);

    CHECK_THROW(uint256_t(1) / uint256_t(0), std::domain_error);

    // External: divide
    bool      t    = true;
    bool      f    = false;
    uint8_t   u8   = 0xaaULL;
    uint16_t  u16  = 0xaaaaULL;
    uint32_t  u32  = 0xaaaaaaaaULL;
    uint64_t  u64  = 0xaaaaaaaaaaaaaaaaULL;
    uint128_t u128  (0xaaaaaaaaaaaaaaaaULL, 0xaaaaaaaaaaaaaaaaULL);

    const uint256_t val(0x7bULL);

    CHECK_EQ(t    /  val, false);
    CHECK_EQ(f    /  val, false);
    CHECK_EQ(u8   /  val, uint256_t(0x1ULL));
    CHECK_EQ(u16  /  val, uint256_t(0x163ULL));
    CHECK_EQ(u32  /  val, uint256_t(0x163356bULL));
    CHECK_EQ(u64  /  val, uint256_t(0x163356b88ac0de0ULL));
    CHECK_EQ(u128 /  val, uint256_t(0x0000000000000000ULL, 0x0000000000000000ULL, 0x163356b88ac0de0ULL, 0x163356b88ac0de01ULL));

    CHECK_EQ(t    /= val, false);
    CHECK_EQ(f    /= val, false);
    CHECK_EQ(u8   /= val, (uint8_t)  0x1ULL);
    CHECK_EQ(u16  /= val, (uint16_t) 0x163ULL);
    CHECK_EQ(u32  /= val, (uint32_t) 0x163356bULL);
    CHECK_EQ(u64  /= val, (uint64_t) 0x163356b88ac0de0ULL);
    CHECK_EQ(u128 /= val,  uint128_t(0x163356b88ac0de0ULL, 0x163356b88ac0de01ULL));
}

// ============================================================================
// test_mod
// ============================================================================
void test_mod()
{
    // Arithmetic: modulo
    // has remainder
    const uint256_t val    (0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL);
    const uint256_t val_mod(0xfedcba9876543210ULL);

    CHECK_EQ(val % val_mod, uint256_t(0x63794f9d55c8d29f));

    // no remainder
    const uint256_t val_0  (0xfedcba9876543210, 0, 0, 0);
    CHECK_EQ(val_0 % val_mod, 0);

    // mod 0
    CHECK_THROW(uint256_t(1) % uint256_t(0), std::domain_error);

    // External: modulo
    bool      t    = true;
    bool      f    = false;
    uint8_t   u8   = 0xaaULL;
    uint16_t  u16  = 0xaaaaULL;
    uint32_t  u32  = 0xaaaaaaaaULL;
    uint64_t  u64  = 0xaaaaaaaaaaaaaaaaULL;
    uint128_t u128  (0xaaaaaaaaaaaaaaaaULL, 0xaaaaaaaaaaaaaaaaULL);

    const uint256_t val2(0xd03ULL); // prime

    CHECK_EQ(t    %  val2, true);
    CHECK_EQ(f    %  val2, false);
    CHECK_EQ(u8   %  val2, uint256_t(0xaaULL));
    CHECK_EQ(u16  %  val2, uint256_t(0x183ULL));
    CHECK_EQ(u32  %  val2, uint256_t(0x249ULL));
    CHECK_EQ(u64  %  val2, uint256_t(0xc7fULL));
    CHECK_EQ(u128 %  val2, uint256_t(0x9fbULL));

    CHECK_EQ(t    %= val2, true);
    CHECK_EQ(f    %= val2, false);
    CHECK_EQ(u8   %= val2, (uint8_t)   0xaaULL);
    CHECK_EQ(u16  %= val2, (uint16_t)  0x183ULL);
    CHECK_EQ(u32  %= val2, (uint32_t)  0x249ULL);
    CHECK_EQ(u64  %= val2, (uint64_t)  0xc7fULL);
    CHECK_EQ(u128 %= val2, (uint256_t) 0x9fbULL);
}

// ============================================================================
// test_fix
// ============================================================================
void test_fix()
{
    // Arithmetic, increment
    {
        uint256_t value(0);
        CHECK_EQ(++value, 1);
        CHECK_EQ(value++, 1);
        CHECK_EQ(++value, 3);
    }

    // Arithmetic, decrement
    {
        uint256_t value(0);
        CHECK_EQ(--value, uint256_t(0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL));
        CHECK_EQ(value--, uint256_t(0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL));
        CHECK_EQ(--value, uint256_t(0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xfffffffffffffffdULL));
    }
}

// ============================================================================
// test_unary
// ============================================================================
void test_unary()
{
    // Arithmetic, unary_plus
    {
        const uint256_t value(0x12345ULL);
        CHECK_EQ(+value, value);
    }

    // Arithmetic, unary_minus
    {
        const uint256_t val(1);
        const uint256_t neg = -val;
        CHECK_EQ(-val, neg);
        CHECK_EQ(-neg, val);
        CHECK_EQ(neg, uint256_t(0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL, 0xffffffffffffffffULL));
    }
}

// ============================================================================
// test_type_traits
// ============================================================================
void test_type_traits()
{
    // Type_Traits, is_arithmetic_or_mytype
    {
        CHECK_EQ(std::is_arithmetic_or_mytype<uint256_t>::value, true);
    }

    // Type_Traits, is_integral_or_mytype
    {
        CHECK_EQ(std::is_integral_or_mytype<uint256_t>::value, true);
    }

    // Type_Traits, is_unsigned_or_mytype
    {
        CHECK_EQ(std::is_unsigned_or_mytype<uint256_t>::value, true);
    }
}

// ============================================================================
// test_uint128
// ============================================================================
void test_uint128()
{
    static const uint128_t uint128_max_local(uint64_t(-1), uint64_t(-1));

    // Constructors
    CHECK(uint128_t(0).upper() == 0ULL && uint128_t(0).lower() == 0ULL);

    {
        uint128_t orig(0x0123456789abcdefULL);
        uint128_t copy(orig);
        CHECK(copy == orig);
    }

    {
        uint128_t value(0x0123456789abcdefULL);
        uint128_t moved(std::move(value));
        CHECK(moved == uint128_t(0x0123456789abcdefULL));
    }

    {
        const std::string s = "0123456789abcdef";
        CHECK(uint128_t(s) == uint128_t(0x0123456789abcdefULL));
    }

    CHECK(uint128_t("0123456789abcdef") == uint128_t(0x0123456789abcdefULL));
    CHECK(uint128_t("0x0123456789abcdef") == uint128_t(0x0123456789abcdefULL));
    CHECK(uint128_t("0") == uint128_t(0));
    CHECK(uint128_t(true) == uint128_t(1));
    CHECK(uint128_t(false) == uint128_t(0));

    CHECK(uint128_t((uint8_t)0x42).lower() == 0x42ULL);
    CHECK(uint128_t((uint16_t)0x1234).lower() == 0x1234ULL);
    CHECK(uint128_t((uint32_t)0x12345678).lower() == 0x12345678ULL);
    CHECK(uint128_t((uint64_t)0x0123456789abcdefULL).lower() == 0x0123456789abcdefULL);
    CHECK(uint128_t((uint64_t)0x0123456789abcdefULL).upper() == 0ULL);

    {
        uint128_t value(0x0123456789abcdefULL, 0xfedcba9876543210ULL);
        CHECK(value.upper() == 0x0123456789abcdefULL);
        CHECK(value.lower() == 0xfedcba9876543210ULL);
    }

    // Arithmetic
    CHECK(uint128_t(0) + uint128_t(0) == uint128_t(0));
    CHECK(uint128_t(1) + uint128_t(1) == uint128_t(2));
    CHECK(uint128_max_local + uint128_t(1) == uint128_t(0));
    CHECK(uint128_max_local + uint128_max_local == uint128_max_local - uint128_t(1));

    CHECK(uint128_t(1) - uint128_t(1) == uint128_t(0));
    CHECK(uint128_t(0) - uint128_t(1) == uint128_max_local);
    CHECK(uint128_max_local - uint128_max_local == uint128_t(0));

    CHECK(uint128_t(0) * uint128_t(1) == uint128_t(0));
    CHECK(uint128_t(1) * uint128_t(1) == uint128_t(1));
    CHECK(uint128_t(100) * uint128_t(200) == uint128_t(20000));
    CHECK(uint128_max_local * uint128_t(2) == uint128_max_local - uint128_t(1));

    CHECK(uint128_t(100) / uint128_t(10) == uint128_t(10));
    CHECK(uint128_t(0) / uint128_t(1) == uint128_t(0));
    CHECK(uint128_max_local / uint128_t(1) == uint128_max_local);
    CHECK(uint128_t(7) / uint128_t(3) == uint128_t(2));

    CHECK(uint128_t(100) % uint128_t(10) == uint128_t(0));
    CHECK(uint128_t(7) % uint128_t(3) == uint128_t(1));
    CHECK(uint128_t(0) % uint128_t(1) == uint128_t(0));

    CHECK_THROW(uint128_t(1) / uint128_t(0), std::domain_error);
    CHECK_THROW(uint128_t(1) % uint128_t(0), std::domain_error);

    // Bitwise
    CHECK((uint128_t(0xFF) & uint128_t(0x0F)) == uint128_t(0x0F));
    CHECK((uint128_max_local & uint128_t(0)) == uint128_t(0));
    CHECK((uint128_max_local & uint128_max_local) == uint128_max_local);

    CHECK((uint128_t(0xF0) | uint128_t(0x0F)) == uint128_t(0xFF));
    CHECK((uint128_t(0) | uint128_t(0)) == uint128_t(0));
    CHECK((uint128_max_local | uint128_t(0)) == uint128_max_local);

    CHECK((uint128_t(0xFF) ^ uint128_t(0xFF)) == uint128_t(0));
    CHECK((uint128_t(0xFF) ^ uint128_t(0x00)) == uint128_t(0xFF));
    CHECK((uint128_max_local ^ uint128_max_local) == uint128_t(0));

    CHECK(~uint128_t(0) == uint128_max_local);
    CHECK(~uint128_max_local == uint128_t(0));

    // Shifts
    CHECK((uint128_t(1) << uint128_t(0)) == uint128_t(1));
    CHECK((uint128_t(1) << uint128_t(1)) == uint128_t(2));
    CHECK((uint128_t(1) << uint128_t(63)) == uint128_t(0, uint64_t(1) << 63));
    CHECK((uint128_t(1) << uint128_t(64)) == uint128_t(1, 0));
    CHECK((uint128_t(1) << uint128_t(65)) == uint128_t(2, 0));
    CHECK((uint128_t(1) << uint128_t(127)) == uint128_t(uint64_t(1) << 63, 0));
    CHECK((uint128_t(1) << uint128_t(128)) == uint128_t(0));

    {
        uint128_t high_bit(uint64_t(1) << 63, 0);
        CHECK((high_bit >> uint128_t(0)) == high_bit);
        CHECK((high_bit >> uint128_t(1)) == uint128_t(uint64_t(1) << 62, 0));
        CHECK((high_bit >> uint128_t(63)) == uint128_t(1, 0));
        CHECK((high_bit >> uint128_t(64)) == uint128_t(0, uint64_t(1) << 63));
        CHECK((high_bit >> uint128_t(65)) == uint128_t(0, uint64_t(1) << 62));
        CHECK((high_bit >> uint128_t(127)) == uint128_t(1));
        CHECK((high_bit >> uint128_t(128)) == uint128_t(0));
    }

    // Comparison
    CHECK(uint128_t(0) == uint128_t(0));
    CHECK(uint128_max_local == uint128_max_local);
    CHECK(!(uint128_t(0) == uint128_t(1)));

    CHECK(uint128_t(0) != uint128_t(1));
    CHECK(!(uint128_t(0) != uint128_t(0)));

    CHECK(uint128_t(0) < uint128_t(1));
    CHECK(uint128_t(0) < uint128_max_local);
    CHECK(!(uint128_t(1) < uint128_t(0)));
    CHECK(!(uint128_t(0) < uint128_t(0)));

    CHECK(uint128_t(1) > uint128_t(0));
    CHECK(uint128_max_local > uint128_t(0));
    CHECK(!(uint128_t(0) > uint128_t(1)));
    CHECK(!(uint128_t(0) > uint128_t(0)));

    CHECK(uint128_t(0) <= uint128_t(0));
    CHECK(uint128_t(0) <= uint128_t(1));
    CHECK(!(uint128_t(1) <= uint128_t(0)));

    CHECK(uint128_t(0) >= uint128_t(0));
    CHECK(uint128_t(1) >= uint128_t(0));
    CHECK(!(uint128_t(0) >= uint128_t(1)));

    CHECK(uint128_t(42) == 42);
    CHECK(uint128_t(42) != 43);
    CHECK(uint128_t(42) > 41);
    CHECK(uint128_t(42) < 43);
    CHECK(uint128_t(42) >= 42);
    CHECK(uint128_t(42) <= 42);

    // Unary
    CHECK(+uint128_t(42) == uint128_t(42));
    CHECK(-uint128_t(1) == uint128_max_local);
    CHECK(-uint128_t(0) == uint128_t(0));

    {
        uint128_t value(0);
        CHECK(++value == uint128_t(1));
        value = uint128_max_local;
        CHECK(++value == uint128_t(0));
    }

    {
        uint128_t value(0);
        CHECK(value++ == uint128_t(0));
        CHECK(value == uint128_t(1));
    }

    {
        uint128_t value(1);
        CHECK(--value == uint128_t(0));
        value = uint128_t(0);
        CHECK(--value == uint128_max_local);
    }

    {
        uint128_t value(1);
        CHECK(value-- == uint128_t(1));
        CHECK(value == uint128_t(0));
    }

    // Accessors
    CHECK(uint128_t(0).bits() == 0);
    CHECK(uint128_t(1).bits() == 1);
    CHECK(uint128_t(0xFF).bits() == 8);
    CHECK(uint128_t(0, uint64_t(-1)).bits() == 64);
    CHECK(uint128_t(1, 0).bits() == 65);
    CHECK(uint128_max_local.bits() == 128);

    // str()
    CHECK(uint128_t(0).str(10) == "0");
    CHECK(uint128_t(12345).str(10) == "12345");
    CHECK(uint128_t(0xFF).str(16) == "ff");
    CHECK(uint128_t(0).str(16) == "0");
    CHECK(uint128_t(0b1010).str(2) == "1010");
    CHECK(uint128_t(1).str(2) == "1");
    CHECK(uint128_t(0755).str(8) == "755");
    CHECK(uint128_t(35).str(36) == "z");
    CHECK(uint128_t(36).str(36) == "10");
    CHECK(uint128_t(0xFF).str(16, 8) == "000000ff");

    CHECK_THROW(uint128_t(42).str(0), std::invalid_argument);
    CHECK_THROW(uint128_t(42).str(1), std::invalid_argument);
    CHECK_THROW(uint128_t(42).str(37), std::invalid_argument);

    // export_bits
    {
        uint128_t value(0, 0x0123456789abcdefULL);
        std::vector<uint8_t> bits;
        value.export_bits(bits);
        CHECK(bits.size() == 16u);
        CHECK(bits[0] == 0x00);
        CHECK(bits[8] == 0x01);
        CHECK(bits[15] == 0xef);
    }

    // ostream
    {
        std::stringstream ss;
        ss << std::oct << uint128_t(0755);
        CHECK(ss.str() == "755");
    }
    {
        std::stringstream ss;
        ss << std::dec << uint128_t(12345);
        CHECK(ss.str() == "12345");
    }
    {
        std::stringstream ss;
        ss << std::hex << uint128_t(0xabcd);
        CHECK(ss.str() == "abcd");
    }
}

// ============================================================================
// test_uint256_boundary
// ============================================================================
void test_uint256_boundary()
{
    // Overflow wrapping
    CHECK(uint256_max + uint256_1 == uint256_0);
    CHECK(uint256_0 - uint256_1 == uint256_max);
    CHECK(uint256_max + uint256_max == uint256_max - uint256_1);
    CHECK(uint256_max * uint256_t(2) == uint256_max - uint256_1);

    // Shift left boundaries
    {
        uint256_t val(1);
        uint256_t result = val << uint256_t(64);
        CHECK(result.lower().upper() == 1ULL);
        CHECK(result.lower().lower() == 0ULL);
        CHECK(result.upper() == uint128_0);
    }

    {
        uint256_t val(1);
        uint256_t result = val << uint256_t(128);
        CHECK(result.upper().lower() == 1ULL);
        CHECK(result.upper().upper() == 0ULL);
        CHECK(result.lower() == uint128_0);
    }

    {
        uint256_t val(1);
        uint256_t result = val << uint256_t(255);
        CHECK(result.upper().upper() == (uint64_t(1) << 63));
        CHECK(result.upper().lower() == 0ULL);
        CHECK(result.lower() == uint128_0);
    }

    CHECK((uint256_t(1) << uint256_t(256)) == uint256_0);

    // Shift right boundaries
    {
        uint256_t val(uint128_t(1, 0), uint128_0);
        uint256_t result = val >> uint256_t(128);
        CHECK(result == uint256_t(uint128_t(1, 0)));
    }

    {
        // highest bit set
        uint256_t val(uint128_t(uint64_t(1) << 63, 0), uint128_0);
        uint256_t result = val >> uint256_t(255);
        CHECK(result == uint256_t(1));
    }

    CHECK((uint256_max >> uint256_t(256)) == uint256_0);

    // bits()
    CHECK(uint256_0.bits() == 0);
    CHECK(uint256_1.bits() == 1);
    CHECK(uint256_max.bits() == 256);

    {
        uint256_t val(uint128_t(1, 0), uint128_0);
        CHECK(val.bits() == 193);
    }
}

// ============================================================================
// test_uint256_error
// ============================================================================
void test_uint256_error()
{
    // uint256_t division/modulus by zero
    CHECK_THROW(uint256_t(1) / uint256_0, std::domain_error);
    CHECK_THROW(uint256_t(1) % uint256_0, std::domain_error);

    // uint256_t str() with invalid base
    CHECK_THROW(uint256_t(42).str(0), std::invalid_argument);
    CHECK_THROW(uint256_t(42).str(1), std::invalid_argument);
    CHECK_THROW(uint256_t(42).str(37), std::invalid_argument);

    // String constructor with empty/null
    CHECK(uint256_t("") == uint256_0);
    CHECK(uint256_t((const char *)nullptr) == uint256_0);

    // uint128_t division/modulus by zero
    CHECK_THROW(uint128_t(1) / uint128_t(0), std::domain_error);
    CHECK_THROW(uint128_t(1) % uint128_t(0), std::domain_error);

    // uint128_t str() with invalid base
    CHECK_THROW(uint128_t(42).str(0), std::invalid_argument);
    CHECK_THROW(uint128_t(42).str(1), std::invalid_argument);
    CHECK_THROW(uint128_t(42).str(37), std::invalid_argument);

    // uint128_t string constructor with empty/null
    CHECK(uint128_t("") == uint128_t(0));
    CHECK(uint128_t((const char *)nullptr) == uint128_t(0));
}

// ============================================================================
// test_uint256_string
// ============================================================================
void test_uint256_string()
{
    static const uint128_t uint128_max_str(uint64_t(-1), uint64_t(-1));

    // Very long hex strings (> 64 chars) — after fix, last 64 hex chars are used
    // 65 hex digits: leading '1' followed by 64 'f's — only last 64 used => uint256_max
    CHECK(uint256_t("1ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff") == uint256_max);

    // 80 hex digits of 'f' => uint256_max
    {
        std::string s(80, 'f');
        CHECK(uint256_t(s) == uint256_max);
    }

    // Short hex strings
    CHECK(uint256_t("F") == uint256_t(15));
    CHECK(uint256_t("FF") == uint256_t(255));
    CHECK(uint256_t("abc") == uint256_t(0xabc));

    // 0x prefix handling
    CHECK(uint256_t("0xFF") == uint256_t(255));
    CHECK(uint256_t("xFF") == uint256_t(255));
    CHECK(uint256_t("0x0") == uint256_0);

    // Mixed case hex
    CHECK(uint256_t("aAbBcCdDeEfF") == uint256_t("AABBCCDDEEFF"));

    // init_from_base with various bases
    CHECK(uint256_t("g", 17) == uint256_t(16));
    CHECK(uint256_t("z", 36) == uint256_t(35));
    CHECK(uint256_t("10", 36) == uint256_t(36));
    CHECK(uint256_t("11111111", 2) == uint256_t(255));
    CHECK(uint256_t("755", 8) == uint256_t(0x01ed));

    // uint128_t short strings
    CHECK(uint128_t("F") == uint128_t(15));
    CHECK(uint128_t("0xFF") == uint128_t(255));

    // uint128_t long hex string truncation (33 hex digits, only last 32 used)
    CHECK(uint128_t("1ffffffffffffffffffffffffffffffff") == uint128_max_str);

    // uint128_t empty string
    CHECK(uint128_t("") == uint128_t(0));
}

// ============================================================================
// test_uint256_functions
// ============================================================================
void test_uint256_functions()
{
    // export_bits_truncate for zero — should return {0x00} after fix
    {
        const uint256_t value(0);
        auto ret = value.export_bits_truncate();
        CHECK(ret.size() == 1u);
        CHECK(ret[0] == 0x00);
    }

    // export_bits_truncate for max — no leading zeros to strip
    {
        const std::vector<uint8_t> expected(32, 0xff);
        CHECK(uint256_max.export_bits_truncate() == expected);
    }

    // export_bits basic
    {
        const uint64_t u64 = 0x0123456789abcdefULL;
        const uint256_t value = u64;
        const std::vector<uint8_t> full = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
        CHECK(value.export_bits() == full);
    }

    // export_bits_truncate for non-zero value
    {
        const uint64_t u64 = 0x0123456789abcdefULL;
        const uint256_t value = u64;
        const std::vector<uint8_t> truncated = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
        CHECK(value.export_bits_truncate() == truncated);
    }

    // str() across all bases 2-36
    {
        const uint256_t original(2216002924);
        CHECK(original.str(10) == "2216002924");
        CHECK(original.str(16) == "8415856c");
        CHECK(original.str(2) == "10000100000101011000010101101100");
    }

    // ostream
    {
        const uint256_t value(0xfedcba9876543210ULL);
        std::stringstream oct;
        oct << std::oct << value;
        CHECK(oct.str() == "1773345651416625031020");

        std::stringstream dec;
        dec << std::dec << value;
        CHECK(dec.str() == "18364758544493064720");

        std::stringstream hex;
        hex << std::hex << value;
        CHECK(hex.str() == "fedcba9876543210");
    }
}

// ============================================================================
// main
// ============================================================================
int main()
{
    test_constructor();
    test_assignment();
    test_typecast();
    test_accessors();
    test_and();
    test_or();
    test_xor();
    test_invert();
    test_leftshift();
    test_rightshift();
    test_logical();
    test_gt();
    test_gte();
    test_lt();
    test_lte();
    test_equals();
    test_notequals();
    test_add();
    test_sub();
    test_mult();
    test_div();
    test_mod();
    test_fix();
    test_unary();
    test_type_traits();
    test_uint128();
    test_uint256_boundary();
    test_uint256_error();
    test_uint256_string();
    test_uint256_functions();

    TEST_RESULTS("all");
}
