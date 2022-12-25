#include <catch2/catch_test_macros.hpp>

import keycap.core;

TEST_CASE("Splitting strings", "[keycap.core:string]")
{
    std::string input{"This is a random string, promise!"};

    SECTION("Splitting a string does not modify the input string")
    {
        constexpr std::size_t expected_size{33};

        [[maybe_unused]] auto _ = keycap::split(input, " ");

        REQUIRE(input.size() == expected_size);
    }

    SECTION("Splitting a string must split at the given delimiter")
    {
        constexpr std::size_t expected_split_count{6};
        std::vector<std::string> const expected_tokens{"This", "is", "a", "random", "string,", "promise!"};

        auto&& tokens = keycap::split(input, " ");

        REQUIRE(tokens.size() == expected_split_count);
        for (std::size_t i = 0; i < tokens.size(); ++i)
        {
            REQUIRE(tokens[i] == expected_tokens[i]);
        }
    }
}

TEST_CASE("Converting strings", "[keycap.core:string]")
{
    std::string input{"We HaVe UnIt TEsTs!"};

    SECTION("to_lower converts to lowercase")
    {
        REQUIRE(keycap::to_lower(input) == "we have unit tests!");
    }

    SECTION("to_upper converts to uppercase")
    {
        REQUIRE(keycap::to_upper(input) == "WE HAVE UNIT TESTS!");
    }
}

TEST_CASE("Hashing strings", "[keycap.core:string]")
{
    SECTION("Hashing an empty string")
    {
        std::string input;
        REQUIRE(keycap::hash_u64(input.data(), input.size()) == 0);
    }

    SECTION("Hashing a small string")
    {
        std::string input{"This is a string!"};
        REQUIRE(keycap::hash_u64(input.data(), input.size()) == 2414454848);
    }

    SECTION("Hashing a big string")
    {
        std::string input{
            R"(Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris luctus feugiat sem eget elementum. Sed semper rhoncus odio sit amet porttitor. Vivamus ligula lorem, tempor vel nulla eu, faucibus cursus tortor. Donec eget lorem nunc. Praesent tristique tortor et nulla mattis pulvinar a id nunc. Proin tincidunt justo sit amet est blandit, id pulvinar lacus tempor. Praesent pretium, nulla congue tempus cursus, diam mauris ullamcorper lectus, et iaculis quam leo at odio. Sed pellentesque suscipit metus. Vivamus non erat sit amet mi pretium fringilla nec at metus. Vestibulum aliquet rhoncus metus sit amet vulputate.

Nunc ac bibendum nibh, vitae vulputate enim. Quisque et feugiat magna, eu malesuada orci. Integer et felis nisl. Curabitur vitae consectetur odio. Donec nisi lacus, pharetra nec massa sit amet, pulvinar feugiat turpis. Integer non odio eget velit malesuada dictum. Donec luctus id enim sed convallis. Phasellus non elit pellentesque, iaculis lorem non, ornare enim. Integer pretium lacus ac ante tempus, nec scelerisque felis porta.

Duis posuere, ante quis blandit pellentesque, arcu tortor fringilla justo, id tristique neque mauris id diam. Vestibulum nec dui sagittis, facilisis risus dignissim, scelerisque lectus. Vivamus aliquam urna ac pellentesque laoreet. Nunc luctus turpis quis sapien congue, a rhoncus libero placerat. Quisque sagittis et arcu sed scelerisque. In a neque quis enim lacinia pulvinar. Maecenas metus ipsum, bibendum in dolor ut, condimentum aliquam risus. Fusce dictum fringilla enim. Mauris accumsan turpis sit amet quam hendrerit, ut euismod mi dignissim. Pellentesque at molestie tellus. Aliquam rutrum ipsum a dapibus dignissim. Quisque aliquam maximus vulputate. Curabitur dictum facilisis neque, ut fermentum turpis consectetur id. Cras finibus nunc eu purus posuere vehicula. Mauris nisl turpis, mollis nec porta nec, placerat eget dolor. Sed sodales, risus sed porttitor tincidunt, quam justo ultrices nunc, blandit vehicula nibh libero ac lorem.

Phasellus interdum odio a nunc rhoncus, quis volutpat lorem mattis. Mauris vestibulum mauris sed purus pellentesque tempus. Vivamus vel diam suscipit, pretium ex et, rhoncus urna. Praesent laoreet, erat sed malesuada maximus, odio nunc placerat justo, at scelerisque tellus leo eget urna. Curabitur mollis congue felis, sit amet lobortis nunc tincidunt nec. Cras lobortis pulvinar vestibulum. Pellentesque id porta nunc. Vestibulum eu euismod lacus. Aliquam purus tortor, efficitur sit amet bibendum ultrices, molestie sit amet massa. Donec vel dignissim leo. Suspendisse venenatis, mi et lacinia posuere, ex lectus consectetur enim, in dapibus urna risus sit amet libero. In hac habitasse platea dictumst. Integer egestas neque et nisl ullamcorper, eu lacinia libero ultrices.

Vivamus posuere ultrices augue quis volutpat. Phasellus eu massa porta, faucibus nisl sit amet, tincidunt elit. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Morbi quis ultrices dolor. Donec id odio aliquet, pharetra lectus sed, tincidunt ipsum. Nullam varius quam quis sagittis sodales. Fusce vel luctus diam. Nam diam nulla, eleifend eu quam ut, rutrum vestibulum leo. Nam commodo urna sit amet arcu varius tristique.

Curabitur tristique quam commodo, placerat erat eu, scelerisque orci. In eget imperdiet sem. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac.

)"};
        REQUIRE(keycap::hash_u64(input.data(), input.size()) == 937791235);
    }
}

TEST_CASE("Joining strings", "[keycap.core:string]")
{
    std::string input{"This is a random string, promise!"};

    SECTION("Joining an empty container with an empty delimiter must yield an empty string")
    {
        REQUIRE(keycap::join(std::vector<std::string>{}, "").empty() == true);
    }

    SECTION("Joining an empty container with a non-empty delimiter must yield an empty string")
    {
        REQUIRE(keycap::join(std::vector<std::string>{}, " ").empty() == true);
    }

    SECTION("Joining a container of strings with a delimiter must yield a non-empty string")
    {
        auto&& splits = keycap::split(input, " ");
        auto&& value = keycap::join(splits, " ");

        REQUIRE(value.empty() == false);
        REQUIRE(value == input);
    }
}

TEST_CASE("Calling get_index", "[keycap.core:math]")
{
    REQUIRE(keycap::get_index(0, 0, 15) == 0);
    REQUIRE(keycap::get_index(0, 1, 15) == 15);
    REQUIRE(keycap::get_index(1, 0, 15) == 1);
    REQUIRE(keycap::get_index(10, 10, 0) == 10);
    REQUIRE(keycap::get_index(10, 10, 15) == 160);
}

TEST_CASE("Calling get_coordinates", "[keycap.core:math]")
{
    REQUIRE(keycap::get_coordinates(0, 15) == std::pair<int, int>{0, 0});
    REQUIRE(keycap::get_coordinates(10, 15) == std::pair<int, int>{10, 0});
}

TEST_CASE("Calling map", "[keycap.core:math]")
{
    REQUIRE(keycap::map(0, 0, 10, 0, 100) == 0);
    REQUIRE(keycap::map(5, 0, 10, 0, 100) == 50);
    REQUIRE(keycap::map(10, 0, 10, 0, 100) == 100);
}

#include <array>

TEST_CASE("array_index", "[keycap.core:algorithm]")
{
    SECTION("c-arrays")
    {
        constexpr int index = 2;
        int array[] = {0, 1, 2, 3};
        REQUIRE(keycap::array_index(array[index], array[0]) == index);
    }

    SECTION("std::array")
    {
        constexpr int index = 2;
        std::array<int, 4> array{0, 1, 2, 3};
        REQUIRE(keycap::array_index(array[index], array[0]) == index);
    }

    SECTION("std::vector")
    {
        constexpr int index = 2;
        std::vector<int> array{0, 1, 2, 3};
        REQUIRE(keycap::array_index(array[index], array[0]) == index);
    }
}

TEST_CASE("is_odd", "[keycap.core:algorithm]")
{
    SECTION("0 is even")
    {
        REQUIRE(keycap::is_odd(0u) == false);
    }

    SECTION("1 is odd")
    {
        REQUIRE(keycap::is_odd(1u) == true);
    }
}

TEST_CASE("is_even", "[keycap.core:algorithm]")
{
    SECTION("0 is even")
    {
        REQUIRE(keycap::is_even(0) == true);
    }

    SECTION("1 is odd")
    {
        REQUIRE(keycap::is_even(1) == false);
    }
}

#include <fmt/format.h>

TEST_CASE("exception::to_string", "[keycap.core:error]")
{
    using namespace keycap;
    auto const line = __LINE__;
    keycap::exception e{error_code::bad_file_content, module::core, 15, line, "Yo"};

    std::string const expected_error_message =
        fmt::format("Error [{}-{}-15-{}]: \"Yo\"", static_cast<u64>(error_code::bad_file_content),
                    static_cast<u64>(module::core), line);

    SECTION("exception::to_string(false) must yield only the error-code and error-message")
    {
        REQUIRE(e.to_string() == expected_error_message);
        REQUIRE(e.to_string().size() == expected_error_message.size());
    }

    SECTION("exception::to_string(true) must yield the error-code, the error-message and a stack-trace")
    {
        auto&& error_string = e.to_string(true);
        auto itr = error_string.find(expected_error_message);

        REQUIRE(itr != std::string::npos);
        REQUIRE(error_string.size() != expected_error_message.size());
        REQUIRE(error_string.substr(expected_error_message.size()).starts_with("\nStack-trace:"));
    }
}

TEST_CASE("to_byte_array", "[keycap.core:array]")
{
    SECTION("i16")
    {
        constexpr i16 value = 0x0BEE;
        constexpr std::array<u8, 2> expected = {0xEE, 0x0B};

        REQUIRE(keycap::to_byte_array(value) == expected);
    }

    SECTION("u16")
    {
        constexpr u16 value = 0xBEEF;
        constexpr std::array<u8, 2> expected = {0xEF, 0xBE};

        REQUIRE(keycap::to_byte_array(value) == expected);
    }

    SECTION("i32")
    {
        constexpr i32 value = 0x0D15EA5E;
        constexpr std::array<u8, 4> expected = {0x5E, 0xEA, 0x15, 0x0D};

        REQUIRE(keycap::to_byte_array(value) == expected);
    }

    SECTION("u32")
    {
        constexpr u32 value = 0xC0CAC01A;
        constexpr std::array<u8, 4> expected = {0x1A, 0xC0, 0xCA, 0xC0};

        REQUIRE(keycap::to_byte_array(value) == expected);
    }

    SECTION("i64")
    {
        constexpr i64 value = 0x0F1CECAFEBADF00D;
        constexpr std::array<u8, 8> expected = {0x0D, 0xF0, 0xAD, 0xEB, 0xAF, 0xEC, 0x1C, 0x0F};

        REQUIRE(keycap::to_byte_array(value) == expected);
    }

    SECTION("u64")
    {
        constexpr u64 value = 0xFACEFEEDBABEBEEF;
        constexpr std::array<u8, 8> expected = {0xEF, 0xBE, 0xBE, 0xBA, 0xED, 0xFE, 0xCE, 0xFA};

        REQUIRE(keycap::to_byte_array(value) == expected);
    }
}

TEST_CASE("from_byte_array", "[keycap.core:array]")
{
    SECTION("Converting bytes to u32 must yield expected result")
    {
        constexpr std::array<u8, 4> value = {0x1A, 0xC0, 0xCA, 0xC0};
        constexpr u32 expected = 0xC0CAC01A;

        REQUIRE(keycap::from_byte_array<u32>(value) == expected);
    }
}

TEST_CASE("from_byte_vector", "[keycap.core:array]")
{
    SECTION("Converting bytes to u32 must yield expected result")
    {
        std::vector<u8> const value = {0x1A, 0xC0, 0xCA, 0xC0};
        constexpr u32 expected = 0xC0CAC01A;

        REQUIRE(keycap::from_byte_vector<u32>(value) == expected);
    }
}

TEST_CASE("keycap::random", "keycap.core:random")
{
    // Do not add new tests here! These tests will run back to back, modifying the prng state. Adding tests up here
    // will make all the tests below fail. Only add to the bottom!

    SECTION("u64")
    {
        constexpr u64 expected = 0xb0c41f6c3353405d;
        REQUIRE(keycap::random::random_u64() == expected);
    }

    SECTION("i64")
    {
        constexpr i64 expected = -7376994870862721386;
        REQUIRE(keycap::random::random_i64() == expected);
    }

    SECTION("u32")
    {
        constexpr u32 expected = 0x503b03a4;
        REQUIRE(keycap::random::random_u32() == expected);
    }

    SECTION("i32")
    {
        constexpr i32 expected = 0x67c75170;
        REQUIRE(keycap::random::random_i32() == expected);
    }

    SECTION("u16")
    {
        constexpr u16 expected = 4669;
        REQUIRE(keycap::random::random_u16() == expected);
    }

    SECTION("i16")
    {
        constexpr i16 expected = 3320;
        REQUIRE(keycap::random::random_i16() == expected);
    }

    SECTION("u8")
    {
        constexpr u8 expected = 88;
        REQUIRE((int)keycap::random::random_u8() == (int)expected);
    }

    SECTION("i8")
    {
        constexpr i8 expected = 102;
        REQUIRE((int)keycap::random::random_i8() == (int)expected);
    }

    SECTION("seeded u64")
    {
        keycap::random::seed(0xABBAB33FAC1D4689);

        constexpr u64 expected = 0x2596b32dc4a79b6a;
        REQUIRE(keycap::random::random_u64() == expected);
    }

    SECTION("seeded i64")
    {
        keycap::random::seed(0xABBAB33FAC1D4689);

        constexpr i64 expected = -6514822801790624918;
        REQUIRE(keycap::random::random_i64() == expected);
    }

    SECTION("seeded u32")
    {
        keycap::random::seed(0xABBAB33FAC1D4689);

        constexpr u32 expected = 0xc4a79b6a;
        REQUIRE(keycap::random::random_u32() == expected);
    }

    SECTION("seeded i32")
    {
        keycap::random::seed(0xABBAB33FAC1D4689);

        constexpr i32 expected = 0x44a79b6a;
        REQUIRE(keycap::random::random_i32() == expected);
    }

    SECTION("seeded u16")
    {
        keycap::random::seed(0xABBAB33FAC1D4689);

        constexpr u16 expected = 39786;
        REQUIRE(keycap::random::random_u16() == expected);
    }

    SECTION("seeded i16")
    {
        keycap::random::seed(0xABBAB33FAC1D4689);

        constexpr i16 expected = 7018;
        REQUIRE(keycap::random::random_i16() == expected);
    }

    SECTION("seeded u8")
    {
        keycap::random::seed(0xABBAB33FAC1D4689);

        constexpr u8 expected = 37;
        REQUIRE((int)keycap::random::random_u8() == (int)expected);
    }

    SECTION("seeded i8")
    {
        keycap::random::seed(0xABBAB33FAC1D4689);

        constexpr i8 expected = -91;
        REQUIRE((int)keycap::random::random_i8() == (int)expected);
    }
}