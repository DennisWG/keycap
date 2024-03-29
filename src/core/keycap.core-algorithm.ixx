module;

#include <concepts>

export module keycap.core : algorithm;

namespace keycap
{
    /// <summary>
    /// Returns the given element's index
    /// </summary>
    export template <typename T>
    constexpr inline [[nodiscard]] auto array_index(T const& element, T const& begin) noexcept
    {
        return &element - &begin;
    }

    /// <summary>
    /// Returns whether the given value is odd
    /// </summary>
    export constexpr inline [[nodiscard]] auto is_odd(std::integral auto&& value) noexcept
    {
        return (value % 2) == 1;
    }

    /// <summary>
    /// Returns whether the given value is even
    /// </summary>
    export constexpr inline [[nodiscard]] auto is_even(std::integral auto&& value) noexcept
    {
        return !is_odd(std::forward<decltype(value)>(value));
    }
}
