#include <catch2/catch_test_macros.hpp>

#include <array>
#include <string>

import keycap.core;
import keycap.crypto;

TEST_CASE("OTP", "[keycap.crypto:otp]")
{
    using namespace keycap::crypto;
    std::string const key = "GEZDGNBVGY3TQOJQGEZDGNBVGY3TQOJQ";
    int constexpr num_tests = 10;
    int constexpr num_digits = 8;

    SECTION("HOTP - must generate correct consecutive one-time passwords")
    {
        std::array<char[num_digits + 1], num_tests> constexpr results = {
            "84755224", "94287082", "37359152", "26969429", "40338314",
            "68254676", "18287922", "82162583", "73399871", "45520489",
        };

        for (int i = 0; i < num_tests; ++i)
        {
            REQUIRE(results[i] == hotp::generate(key, i, num_digits));
        }
    }

    SECTION("TOTP - must generate correct consecutive one-time passwords")
    {
        time_t constexpr start = 0;
        time_t constexpr step = 30;

        time_t constexpr test_time[num_tests] = {59, 1111111109, 1111111111, 1234567890, 2000000000,
                                                 0,  2773937592, 5670,       465999,     90};
        std::array<char[num_digits + 1], num_tests> constexpr results = {
            "94287082", "07081804", "14050471", "89005924", "69279037",
            "84755224", "61240089", "26915604", "71304149", "26969429",
        };

        for (int i = 0; i < num_tests; ++i)
        {
            REQUIRE(results[i] == totp::generate(key, test_time[i], start, step, num_digits));
        }
    }

    SECTION("TOTP - validate must accept the previous, as well as the next code too")
    {
        const auto time = std::time(nullptr);
        const auto now = static_cast<u64>(time);

        for (int j = -1; j < 2; ++j)
        {
            auto step = static_cast<u64>((std::floor(now / 30))) + j;
            auto code = keycap::crypto::hotp::generate(key, step, num_digits);

            REQUIRE(totp::validate(key, code) == true);
        }
    }

    SECTION("TOTP - validate must return false when entered garbage values")
    {
        std::array<char[num_digits + 1], num_tests> constexpr codes = {
            "", "1", "00000000", "99999999", "23567aaa", "aaaaaaaa", "+#!§$%&/", "43575679", "01010101", "1010101",
        };

        for (auto&& code : codes)
        {
            REQUIRE(totp::validate(key, code) == false);
        }
    }
}
