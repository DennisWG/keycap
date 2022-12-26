module;

#include <array>
#include <cstring>
#include <vector>

export module keycap.core:array;

import :types;

namespace keycap
{
    template <typename PTR, typename T>
    void to_byte_array(PTR data, T value)
    {
        std::memcpy(data, &value, sizeof(value));
    }

    /// <summary>
    /// Converts the given number to a std::array containing its bytes
    /// </summary>
    /// <param name="number">The number to convert</param>
    /// <returns>A std::array containing the number represented as individual bytes</returns>
    export [[nodiscard]] std::array<u8, 2> to_byte_array(i16 number)
    {
        std::array<u8, 2> value;
        to_byte_array(value.data(), number);
        return value;
    }

    /// <summary>
    /// Converts the given number to a std::array containing its bytes
    /// </summary>
    /// <param name="number">The number to convert</param>
    /// <returns>A std::array containing the number represented as individual bytes</returns>
    export [[nodiscard]] std::array<u8, 4> to_byte_array(i32 number)
    {
        std::array<u8, 4> value;
        to_byte_array(value.data(), number);
        return value;
    }

    /// <summary>
    /// Converts the given number to a std::array containing its bytes
    /// </summary>
    /// <param name="number">The number to convert</param>
    /// <returns>A std::array containing the number represented as individual bytes</returns>
    export [[nodiscard]] std::array<u8, 8> to_byte_array(i64 number)
    {
        std::array<u8, 8> value;
        to_byte_array(value.data(), number);
        return value;
    }

    /// <summary>
    /// Converts the given number to a std::array containing its bytes
    /// </summary>
    /// <param name="number">The number to convert</param>
    /// <returns>A std::array containing the number represented as individual bytes</returns>
    export [[nodiscard]] std::array<u8, 2> to_byte_array(u16 number)
    {
        std::array<u8, 2> value;
        to_byte_array(value.data(), number);
        return value;
    }

    /// <summary>
    /// Converts the given number to a std::array containing its bytes
    /// </summary>
    /// <param name="number">The number to convert</param>
    /// <returns>A std::array containing the number represented as individual bytes</returns>
    export [[nodiscard]] std::array<u8, 4> to_byte_array(u32 number)
    {
        std::array<u8, 4> value;
        to_byte_array(value.data(), number);
        return value;
    }

    /// <summary>
    /// Converts the given number to a std::array containing its bytes
    /// </summary>
    /// <param name="number">The number to convert</param>
    /// <returns>A std::array containing the number represented as individual bytes</returns>
    export [[nodiscard]] std::array<u8, 8> to_byte_array(u64 number)
    {
        std::array<u8, 8> value;
        to_byte_array(value.data(), number);
        return value;
    }

    /// <summary>
    /// Converts an array of bytes to the given RESULT_TYPE. This does not do any type-checking and will invoke
    /// undefined behaviour, if invoked with an incorrect type!
    /// </summary>
    /// <typeparam name="RESULT_TYPE">The type to convert to</typeparam>
    /// <typeparam name="SIZE">The size of the given array</typeparam>
    /// <param name="array">The array of bytes to convert</param>
    /// <returns>The converted bytes in the required format</returns>
    export template <typename RESULT_TYPE, size_t SIZE>
    [[nodiscard]] RESULT_TYPE from_byte_array(std::array<u8, SIZE> const& array)
    {
        static_assert(SIZE == sizeof(RESULT_TYPE), "Size mismatch!");
        RESULT_TYPE value = 0;
        std::memcpy(&value, array.data(), std::min(array.size(), sizeof(RESULT_TYPE)));

        return value;
    }

    /// <summary>
    /// Converts a vector of bytes to the given RESULT_TYPE. This does not do any-type checking and will invoke
    /// undefined behaviour, if invoked with an incorrect type!
    /// </summary>
    /// <typeparam name="RESULT_TYPE">The type to convert to</typeparam>
    /// <param name="vector">The vector of bytes to convert</param>
    /// <returns>The converted bytes in the required format</returns>
    export template <typename RESULT_TYPE>
    [[nodiscard]] RESULT_TYPE from_byte_vector(std::vector<u8> const& vector)
    {
        RESULT_TYPE value = 0;
        std::memcpy(&value, vector.data(), std::min(vector.size(), sizeof(RESULT_TYPE)));
        return value;
    }
}