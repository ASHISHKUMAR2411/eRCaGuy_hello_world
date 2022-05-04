/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Apr. to May 2022

Add googletest sample1 from Google.
- See references below for where these files come from.
- This "*_unittest.cc" file is the main file to run and test this code.

STATUS: done; and works perfectly!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# 1. FIRST, follow the detailed clone and build steps here to clone the googletest repo and manually
# build the necessary *.a static library files for gtest and gmock:
# "eRCaGuy_hello_world/cpp/README.md"

# 2. THEN, build and run this unit test with this command!:
time ( \
    time g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread \
    -I"googletest/googletest/include" -I"googletest/googlemock/include" \
    gtest_demo__sample1_factorial_and_is_prime_unittest.cc \
    gtest_demo__sample1_factorial_and_is_prime.cc \
    bin/libgtest.a bin/libgtest_main.a \
    -o bin/a \
    && time bin/a \
)
```

References:
1. googletest sample1 sources:
  1. Locally-stored: "eRCaGuy_hello_world/cpp/googletest/googletest/samples/sample1*"
    1. See "eRCaGuy_hello_world/cpp/README.md" for googletest setup info.
  1. Online: "samples" folder: https://github.com/google/googletest/tree/main/googletest/samples

*/


// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A sample program demonstrating using Google C++ testing framework.

// This sample shows how to write a simple unit test for a function,
// using Google C++ testing framework.
//
// Writing a unit test using Google C++ testing framework is easy as 1-2-3:

// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

// Local headers
#include "gtest_demo__sample1_factorial_and_is_prime.h"

// 3rd-party libraries
#include "gtest/gtest.h"

// C and C++ includes
#include <limits.h>


namespace {

// Step 2. Use the TEST macro to define your tests.
//
// TEST has two parameters: the test case name and the test name.
// After using the macro, you should define your test logic between a
// pair of braces.  You can use a bunch of macros to indicate the
// success or failure of a test.  EXPECT_TRUE and EXPECT_EQ are
// examples of such macros.  For a complete list, see gtest.h.
//
// <TechnicalDetails>
//
// In Google Test, tests are grouped into test cases.  This is how we
// keep test code organized.  You should put logically related tests
// into the same test case.
//
// The test case name and the test name should both be valid C++
// identifiers.  And you should not use underscore (_) in the names.
//
// Google Test guarantees that each test you define is run exactly
// once, but it makes no guarantee on the order the tests are
// executed.  Therefore, you should write your tests in such a way
// that their results don't depend on their order.
//
// </TechnicalDetails>

// Tests Factorial().

// Tests factorial of negative numbers.
TEST(FactorialTest, Negative) {
  // This test is named "Negative", and belongs to the "FactorialTest"
  // test case.
  EXPECT_EQ(1, Factorial(-5));
  EXPECT_EQ(1, Factorial(-1));
  EXPECT_GT(Factorial(-10), 0);

  // <TechnicalDetails>
  //
  // EXPECT_EQ(expected, actual) is the same as
  //
  //   EXPECT_TRUE((expected) == (actual))
  //
  // except that it will print both the expected value and the actual
  // value when the assertion fails.  This is very helpful for
  // debugging.  Therefore in this case EXPECT_EQ is preferred.
  //
  // On the other hand, EXPECT_TRUE accepts any Boolean expression,
  // and is thus more general.
  //
  // </TechnicalDetails>
}

// Tests factorial of 0.
TEST(FactorialTest, Zero) { EXPECT_EQ(1, Factorial(0)); }

// Tests factorial of positive numbers.
TEST(FactorialTest, Positive) {
  EXPECT_EQ(1, Factorial(1));
  EXPECT_EQ(2, Factorial(2));
  EXPECT_EQ(6, Factorial(3));
  EXPECT_EQ(40320, Factorial(8));
}

// Tests IsPrime()

// Tests negative input.
TEST(IsPrimeTest, Negative) {
  // This test belongs to the IsPrimeTest test case.

  EXPECT_FALSE(IsPrime(-1));
  EXPECT_FALSE(IsPrime(-2));
  EXPECT_FALSE(IsPrime(INT_MIN));
}

// Tests some trivial cases.
TEST(IsPrimeTest, Trivial) {
  EXPECT_FALSE(IsPrime(0));
  EXPECT_FALSE(IsPrime(1));
  EXPECT_TRUE(IsPrime(2));
  EXPECT_TRUE(IsPrime(3));
}

// Tests positive input.
TEST(IsPrimeTest, Positive) {
  EXPECT_FALSE(IsPrime(4));
  EXPECT_TRUE(IsPrime(5));
  EXPECT_FALSE(IsPrime(6));
  EXPECT_TRUE(IsPrime(23));
}
}  // namespace

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.
//
// Did you notice that we didn't register the tests?  The
// RUN_ALL_TESTS() macro magically knows about all the tests we
// defined.  Isn't this convenient?




/*
Sample output:

    eRCaGuy_hello_world/cpp$ time ( \
    >     time g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread \
    >     -I"googletest/googletest/include" -I"googletest/googlemock/include" \
    >     gtest_demo__sample1_factorial_and_is_prime_unittest.cc \
    >     gtest_demo__sample1_factorial_and_is_prime.cc \
    >     bin/libgtest.a bin/libgtest_main.a \
    >     -o bin/a \
    >     && time bin/a \
    > )

    real    0m1.621s
    user    0m1.259s
    sys 0m0.147s
    Running main() from googletest/googletest/src/gtest_main.cc
    [==========] Running 6 tests from 2 test suites.
    [----------] Global test environment set-up.
    [----------] 3 tests from FactorialTest
    [ RUN      ] FactorialTest.Negative
    [       OK ] FactorialTest.Negative (0 ms)
    [ RUN      ] FactorialTest.Zero
    [       OK ] FactorialTest.Zero (0 ms)
    [ RUN      ] FactorialTest.Positive
    [       OK ] FactorialTest.Positive (0 ms)
    [----------] 3 tests from FactorialTest (0 ms total)

    [----------] 3 tests from IsPrimeTest
    [ RUN      ] IsPrimeTest.Negative
    [       OK ] IsPrimeTest.Negative (0 ms)
    [ RUN      ] IsPrimeTest.Trivial
    [       OK ] IsPrimeTest.Trivial (0 ms)
    [ RUN      ] IsPrimeTest.Positive
    [       OK ] IsPrimeTest.Positive (0 ms)
    [----------] 3 tests from IsPrimeTest (0 ms total)

    [----------] Global test environment tear-down
    [==========] 6 tests from 2 test suites ran. (0 ms total)
    [  PASSED  ] 6 tests.

    real    0m0.002s
    user    0m0.000s
    sys 0m0.002s

    real    0m1.623s
    user    0m1.259s
    sys 0m0.149s


*/
