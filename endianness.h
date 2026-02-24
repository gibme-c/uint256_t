// The MIT License (MIT)
//
// Copyright (c) 2013 - 2017 Jason Lee @ calccrypto at gmail.com
// Copyright (c) 2021, Brandon Lehmann
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef ENDIANNESS_H
#define ENDIANNESS_H

#if (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __BIG_ENDIAN)                                                      \
    || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) || defined(__BIG_ENDIAN__)                \
    || defined(__ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__) || defined(_MIBSEB) || defined(__MIBSEB) \
    || defined(__MIBSEB__)
#ifndef __BIG_ENDIAN__
#define __BIG_ENDIAN__
#endif // __BIG_ENDIAN__

#elif (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __LITTLE_ENDIAN)                                                 \
    || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) || defined(__LITTLE_ENDIAN__)          \
    || defined(__ARMEL__) || defined(__THUMBEL__) || defined(__AARCH64EL__) || defined(_MIPSEL) || defined(__MIPSEL) \
    || defined(__MIPSEL__) || defined(_MSC_VER)
#ifndef __LITTLE_ENDIAN__
#define __LITTLE_ENDIAN__
#endif // __LITTLE_ENDIAN

#else // FALL_THROUGH
#error "I don't know what architecture this is!"
#endif // FALL_THROUGH

#endif // ENDIANNESS_H
