module;

#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

export module keycap.core:string;

import :concepts;
import :types;

namespace keycap
{
    /// <summary>
    /// Returns a vector of strings that contains the substrings in the given string that are delimited by elements of
    /// the specified string.
    /// </summary>
    export std::vector<std::string> split(std::string string, std::string delimiter = " ")
    {
        std::vector<std::string> tokens;

        sz pos = 0;
        std::string token;
        while ((pos = string.find(delimiter)) != std::string::npos)
        {
            tokens.emplace_back(string.substr(0, pos));
            string.erase(0, pos + delimiter.length());
        }
        tokens.emplace_back(string);

        return tokens;
    }

    /// <summary>
    /// Joins the given vector of strings into one single string seperated by the given delimiter
    /// </summary>
    export std::string join(std_container auto const& container, std::string delimiter = " ")
    {
        sz buffer_size = 0;
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
    export std::string to_lower(std::string string)
    {
        std::for_each(string.begin(), string.end(), [](char& c) {
            c = static_cast<char>(::tolower(c));
        });

        return string;
    }

    /// <summary>
    /// Returns a copy of the given string converted to uppercase.
    /// </summary>
    export std::string to_upper(std::string string)
    {
        std::for_each(string.begin(), string.end(), [](char& c) {
            c = static_cast<char>(::toupper(c));
        });

        return string;
    }

    /// <summary>
    /// Returns a hash of the given string with the given size
    /// </summary>
    export constexpr u64 hash_u64(char const* string, std::size_t size)
    {
        if (size == 0)
            return 0;

        u64 const p = 131;
        u64 const m = 4294967291;

        u64 hash = 0;
        u64 multiplier = 1;

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
    export consteval u64 operator"" _hash_u64(const char* string, std::size_t size)
    {
        return hash_u64(string, size);
    }
}
