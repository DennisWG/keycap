module;

#include <utility>

export module keycap.core : math;

namespace keycap
{
    /// <summary>
    /// Returns the index within an array of one dimension at the given X- and Y-Coordinates with the given width
    /// </summary>
    export template <typename T>
    constexpr [[nodiscard]] T get_index(T x, T y, T width) noexcept
    {
        return x + width * y;
    }

    /// <summary>
    /// Returns the X- and Y-Coordinates of the given index into an array of the given width
    /// </summary>
    export template <typename T>
    constexpr [[nodiscard]] std::pair<T, T> get_coordinates(T index, T width) noexcept
    {
        return {index % width, (index / width) % width};
    }

    /// <summary>
    /// Maps the given value from the given {in_min, in_max} bounds to a corresponding value within the given {out_min,
    /// out_max}` bounds
    /// </summary>
    export template <typename T>
    constexpr [[nodiscard]] T map(T value, T in_min, T in_max, T out_min, T out_max) noexcept
    {
        return ((value - in_min) * (out_max - out_min) / (in_max - in_min)) + out_min;
    }
}
