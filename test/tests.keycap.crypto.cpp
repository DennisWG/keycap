#include <catch2/catch_test_macros.hpp>

#include <array>
#include <string>

import keycap.core;
import keycap.crypto;

TEST_CASE("OTP", "[keycap.crypto:otp]")
{
    SECTION("HOTP must generate correct consecutive one-time passwords")
    {
        std::string const key = "GEZDGNBVGY3TQOJQGEZDGNBVGY3TQOJQ";
        int constexpr num_tests = 10;
        int constexpr num_digits = 6;
        std::array<char[num_digits + 1], num_tests> constexpr results = {
            "755224", "287082", "359152", "969429", "338314", "254676", "287922", "162583", "399871", "520489",
        };

        for (int i = 0; i < num_tests; ++i)
        {
            REQUIRE(results[i] == keycap::crypto::hotp::generate(key, i, num_digits));
        }
    }

    SECTION("TOTP must generate correct consecutive one-time passwords")
    {
        std::string const key = "GEZDGNBVGY3TQOJQGEZDGNBVGY3TQOJQ";
        time_t constexpr start = 0;
        time_t constexpr step = 30;

        int constexpr num_tests = 6;
        sz constexpr num_digits = 8;

        time_t constexpr test_time[num_tests] = {59, 1111111109, 1111111111, 1234567890, 2000000000, 20000000000};
        std::array<char[num_digits + 1], num_tests> constexpr results = {
            "94287082", "07081804", "14050471", "89005924", "69279037", "65353130",
        };

        for (int i = 0; i < num_tests; ++i)
        {
            REQUIRE(results[i] == keycap::crypto::totp::generate(key, test_time[i], start, step, num_digits));
        }
    }

    SECTION("TOTP validate must accept the previous, as well as the next code too")
    {
        std::string const key = "GEZDGNBVGY3TQOJQGEZDGNBVGY3TQOJQ";

        int constexpr num_tests = 6;
        sz constexpr num_digits = 8;

        const auto time = std::time(nullptr);
        const auto now = static_cast<u64>(time);

        for (int i = 0; i < num_tests; ++i)
        {
            for (int j = -1; j < 2; ++j)
            {
                auto step = static_cast<u64>((std::floor(now / 30))) + j;
                auto code = keycap::crypto::hotp::generate(key, step, num_digits);

                REQUIRE(keycap::crypto::totp::validate(key, code) == true);
            }
        }
    }

    SECTION("TOTP validate return false when entered garbage values")
    {
        std::string const key = "GEZDGNBVGY3TQOJQGEZDGNBVGY3TQOJQ";
        int constexpr num_tests = 6;
        sz constexpr num_digits = 8;

        std::array<char[num_digits + 1], num_tests> constexpr codes = {
            "", "1", "00000000", "99999999", "23567aaa", "aaaaaaaa",
        };

        for (auto&& code : codes)
        {
            REQUIRE(keycap::crypto::totp::validate(key, code) == false);
        }
    }
}
