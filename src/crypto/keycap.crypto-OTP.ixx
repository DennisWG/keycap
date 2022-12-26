module;

#include <botan/base32.h>
#include <botan/mac.h>

#include <fmt/format.h>

#include <array>
#include <cmath>
#include <string>

export module keycap.crypto:opt;

import keycap.core;
import :fragments;

namespace keycap::crypto
{
    namespace hotp
    {
        constexpr sz required_min_digits = 6;
        /// <summary>
        /// Implementation of the OATH HMAC-based One-Time Password algorithm.
        /// See: https://tools.ietf.org/html/rfc4226
        /// </summary>
        export [[nodiscard]] std::string generate(std::string const& key, u64 counter,
                                                  sz num_digits = required_min_digits)
        {
            if (num_digits < required_min_digits)
            {
                auto msg =
                    fmt::format("As required per RFC 4226, num_digits can not be smaller than `{}`!\n"
                                "See https://www.rfc-editor.org/rfc/rfc4226#section-13.2 Appendix A for more details.",
                                required_min_digits);
                throw exception{error_code::invalid_argument, module::crypto, fragment::otp, __LINE__, msg};
            }

            auto hmac = Botan::MessageAuthenticationCode::create("HMAC(SHA-1)");

            hmac->set_key(Botan::base32_decode(key));
            std::array<u8, 8> text;
            std::memcpy(text.data(), &counter, sizeof(counter));
            std::reverse(text.begin(), text.end());
            hmac->update(text.data(), text.size());
            auto hash = hmac->final();

            int offset = hash[hash.size() - 1] & 0x0F;

            // clang-format off
            int binary = ((hash[offset] & 0x7f) << 24)
                | ((hash[offset + 1] & 0xff) << 16)
                | ((hash[offset + 2] & 0xff) << 8)
                | (hash[offset + 3] & 0xff);
            // clang-format on

            int constexpr DIGITS_POWER[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
            auto result = std::to_string(binary % DIGITS_POWER[num_digits]);

            while (result.size() < num_digits)
                result = '0' + result;

            return result;
        }
    }

    namespace totp
    {
        /// <summary>
        /// Implementation of the OATH Time-based One-Time Password algorithm
        /// See: https://tools.ietf.org/html/rfc6238
        /// </summary>
        export [[nodiscard]] std::string generate(std::string const& key, time_t now, time_t start, time_t step,
                                                  sz num_digits = 6)
        {
            u64 counter = (now - start) / step;
            return hotp::generate(key, counter, num_digits);
        }

        /// <summary>
        /// Validates the given code for the given secret. This also checks the previous valid code as well as the next
        /// one, in case the user is a little out-of-sync
        /// </summary>
        export [[nodiscard]] bool validate(std::string const& key, std::string const& code)
        {
            const auto time = std::time(nullptr);
            const auto now = static_cast<u64>(time);

            for (int i = -1; i < 2; ++i)
            {
                auto step = static_cast<u64>((std::floor(now / 30))) + i;
                auto code_n = hotp::generate(key, step, code.size());

                if (code == code_n)
                    return true;
            }

            return false;
        }
    }
}