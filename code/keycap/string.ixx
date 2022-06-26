module;

#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

export module keycap.string;

import keycap.concepts;

export namespace keycap
{
    /// <summary>
    /// Returns a vector of strings that contains the substrings in the given string that are delimited by elements of
    /// the specified string.
    /// </summary>
    export std::vector<std::string> split(std::string string, std::string delimiter = " ");

    /// <summary>
    /// Joins the given vector of strings into one single string seperated by the given delimiter
    /// </summary>
    export std::string join(std_container auto const& container, std::string delimiter = " ")
    {
        std::size_t buffer_size = 0;
        for (auto&& str : container)
        {
            buffer_size += str.size();
        }

        std::string str;
        str.reserve(buffer_size);

        bool first = true;

        for (auto&& s : container)
        {
            if (!first)
                str += delimiter;

            str += s;

            first = false;
        }

        return str;
    }

    /// <summary>
    /// Returns a copy of the given string converted to lowercase.
    /// </summary>
    export std::string to_lower(std::string string);

    /// <summary>
    /// Returns a copy of the given string converted to uppercase.
    /// </summary>
    export std::string to_upper(std::string string);

    /// <summary>
    /// Returns a hash of the given string with the given size
    /// </summary>
    export constexpr std::uint64_t hash_u64(char const* string, std::size_t size)
    {
        if (size == 0)
            return 0;

        std::uint64_t const p = 131;
        std::uint64_t const m = 4294967291;

        std::uint64_t hash = 0;
        std::uint64_t multiplier = 1;

        for (std::size_t i = 0; i < size - 1; ++i)
        {
            hash = (hash + multiplier * string[i]) % m;
            multiplier = (multiplier * p) % m;
        }

        return hash;
    }

    /// <summary>
    /// Returns a hash of the given string with the given size
    /// </summary>
    consteval std::uint64_t operator"" _hash_u64(const char* string, std::size_t size)
    {
        return hash_u64(string, size);
    }
}

module : private;

namespace keycap
{
    std::vector<std::string> split(std::string string, std::string delimiter)
    {
        std::vector<std::string> tokens;

        size_t pos = 0;
        std::string token;
        while ((pos = string.find(delimiter)) != std::string::npos)
        {
            tokens.emplace_back(string.substr(0, pos));
            string.erase(0, pos + delimiter.length());
        }
        tokens.emplace_back(string);

        return tokens;
    }

    std::string to_lower(std::string string)
    {
        std::for_each(string.begin(), string.end(), [](char& c) {
            c = static_cast<char>(::tolower(c));
        });

        return string;
    }

    std::string to_upper(std::string string)
    {
        std::for_each(string.begin(), string.end(), [](char& c) {
            c = static_cast<char>(::toupper(c));
        });

        return string;
    }
}