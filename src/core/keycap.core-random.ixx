module;

#include <array>
#include <limits>
#include <random>

export module keycap.core:random;

import :types;

namespace keycap::random
{
    // adapted from https://prng.di.unimi.it/splitmix64.c
    constexpr [[nodiscard]] std::array<u64, 2> split_mix_64(u64 seed) noexcept
    {
        constexpr auto mix = [](u64& seed) noexcept -> u64 {
            u64 z = (seed += 0x9e3779b97f4a7c15);
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
            z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
            return z ^ (z >> 31);
        };

        return {mix(seed), mix(seed)};
    }

    // adapted from https://prng.di.unimi.it/xoroshiro128plus.c
    struct xoroshiro128plus
    {
        constexpr [[nodiscard]] xoroshiro128plus(u64 seed) noexcept
          : state_{split_mix_64(seed)}
        {
        }

        constexpr [[nodiscard]] xoroshiro128plus() noexcept
          : state_{split_mix_64(0x0F1E2D3C4B5A6978)}
        {
        }

        void seed(u64 seed)
        {
            state_ = split_mix_64(seed);
        }

        constexpr [[nodiscard]] u64 operator()() noexcept
        {
            constexpr auto rotl = [](u64 const x, int const k) noexcept -> u64 {
                return (x << k) | (x >> (64 - k));
            };

            u64 const s0 = state_[0];
            u64 s1 = state_[1];
            u64 const result = s0 + s1;

            s1 ^= s0;
            state_[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16);
            state_[1] = rotl(s1, 37);

            return result;
        }

        static constexpr [[nodiscard]] u64 min() noexcept
        {
            return std::numeric_limits<u64>::lowest();
        }

        static constexpr [[nodiscard]] u64 max() noexcept
        {
            return std::numeric_limits<u64>::max();
        }

      private:
        std::array<u64, 2> state_;
    };

    static thread_local xoroshiro128plus prng;

    /// <summary>
    /// Seeds the PRNG's with the given value
    /// </summary>
    /// <param name="seed">The value to seed the PRNG with</param>
    export void seed(u64 seed)
    {
        prng.seed(seed);
    }

    /// <summary>
    /// Generates a pseudo-random i8 between min and max (inclusive). Very fast, thread-safe, not cryptographically safe.
    /// </summary>
    /// <param name="min">The lower bound (inclusive)</param>
    /// <param name="max">The upper bound (inclusive)</param>
    /// <returns>A random value between min and max (inclusive)</returns>
    export i8 random_i8(i8 const min = std::numeric_limits<i8>::min(), i8 const max = std::numeric_limits<i8>::max())
    {
        std::uniform_int_distribution<i16> dist(min, max);
        return static_cast<i8>(dist(prng));
    }

    /// <summary>
    /// Generates a pseudo-random u8 between min and max (inclusive). Very fast, thread-safe, not cryptographically
    /// safe.
    /// </summary>
    /// <param name="min">The lower bound (inclusive)</param>
    /// <param name="max">The upper bound (inclusive)</param>
    /// <returns>A random value between min and max (inclusive)</returns>
    export u8 random_u8(u8 const min = std::numeric_limits<u8>::min(), u8 const max = std::numeric_limits<u8>::max())
    {
        std::uniform_int_distribution<u16> dist(min, max);
        return static_cast<u8>(dist(prng));
    }

    /// <summary>
    /// Generates a pseudo-random i16 between min and max (inclusive). Very fast, thread-safe, not cryptographically
    /// safe.
    /// </summary>
    /// <param name="min">The lower bound (inclusive)</param>
    /// <param name="max">The upper bound (inclusive)</param>
    /// <returns>A random value between min and max (inclusive)</returns>
    export i16 random_i16(i16 const min = std::numeric_limits<i16>::min(),
                          i16 const max = std::numeric_limits<i16>::max())
    {
        std::uniform_int_distribution<i16> dist(min, max);
        return dist(prng);
    }

    /// <summary>
    /// Generates a pseudo-random u16 between min and max (inclusive). Very fast, thread-safe, not cryptographically
    /// safe.
    /// </summary>
    /// <param name="min">The lower bound (inclusive)</param>
    /// <param name="max">The upper bound (inclusive)</param>
    /// <returns>A random value between min and max (inclusive)</returns>
    export u16 random_u16(u16 const min = std::numeric_limits<u16>::min(),
                          u16 const max = std::numeric_limits<u16>::max())
    {
        std::uniform_int_distribution<u16> dist(min, max);
        return dist(prng);
    }

    /// <summary>
    /// Generates a pseudo-random i32 between min and max (inclusive). Very fast, thread-safe, not cryptographically
    /// safe.
    /// </summary>
    /// <param name="min">The lower bound (inclusive)</param>
    /// <param name="max">The upper bound (inclusive)</param>
    /// <returns>A random value between min and max (inclusive)</returns>
    export i32 random_i32(i32 const min = std::numeric_limits<i32>::min(),
                          i32 const max = std::numeric_limits<i32>::max())
    {
        std::uniform_int_distribution<i32> dist(min, max);
        return dist(prng);
    }

    /// <summary>
    /// Generates a pseudo-random u32 between min and max (inclusive). Very fast, thread-safe, not cryptographically
    /// safe.
    /// </summary>
    /// <param name="min">The lower bound (inclusive)</param>
    /// <param name="max">The upper bound (inclusive)</param>
    /// <returns>A random value between min and max (inclusive)</returns>
    export u32 random_u32(u32 const min = std::numeric_limits<u32>::min(),
                          u32 const max = std::numeric_limits<u32>::max())
    {
        std::uniform_int_distribution<u32> dist(min, max);
        return dist(prng);
    }

    /// <summary>
    /// Generates a pseudo-random i64 between min and max (inclusive). Very fast, thread-safe, not cryptographically
    /// safe.
    /// </summary>
    /// <param name="min">The lower bound (inclusive)</param>
    /// <param name="max">The upper bound (inclusive)</param>
    /// <returns>A random value between min and max (inclusive)</returns>
    export i64 random_i64(i64 const min = std::numeric_limits<i64>::min(),
                          i64 const max = std::numeric_limits<i64>::max())
    {
        std::uniform_int_distribution<i64> dist(min, max);
        return dist(prng);
    }

    /// <summary>
    /// Generates a pseudo-random u64 between min and max (inclusive). Very fast, thread-safe, not cryptographically
    /// safe.
    /// </summary>
    /// <param name="min">The lower bound (inclusive)</param>
    /// <param name="max">The upper bound (inclusive)</param>
    /// <returns>A random value between min and max (inclusive)</returns>
    export u64 random_u64(u64 const min = std::numeric_limits<u64>::min(),
                          u64 const max = std::numeric_limits<u64>::max())
    {
        std::uniform_int_distribution<u64> dist(min, max);
        return dist(prng);
    }
}