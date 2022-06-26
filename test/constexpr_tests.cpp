#include <catch2/catch_test_macros.hpp>

import keycap.core;

TEST_CASE("Hashing constexpr strings", "[keycap.core:string]")
{
    using namespace keycap;

    SECTION("Hashing an empty string")
    {
        STATIC_REQUIRE(""_hash_u64 == 0);
    }

    SECTION("Hashing a small string")
    {
        STATIC_REQUIRE("This is a string!"_hash_u64 == 2414454848);
    }

    SECTION("Hashing a big string")
    {
        STATIC_REQUIRE(
            R"(Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris luctus feugiat sem eget elementum. Sed semper rhoncus odio sit amet porttitor. Vivamus ligula lorem, tempor vel nulla eu, faucibus cursus tortor. Donec eget lorem nunc. Praesent tristique tortor et nulla mattis pulvinar a id nunc. Proin tincidunt justo sit amet est blandit, id pulvinar lacus tempor. Praesent pretium, nulla congue tempus cursus, diam mauris ullamcorper lectus, et iaculis quam leo at odio. Sed pellentesque suscipit metus. Vivamus non erat sit amet mi pretium fringilla nec at metus. Vestibulum aliquet rhoncus metus sit amet vulputate.

Nunc ac bibendum nibh, vitae vulputate enim. Quisque et feugiat magna, eu malesuada orci. Integer et felis nisl. Curabitur vitae consectetur odio. Donec nisi lacus, pharetra nec massa sit amet, pulvinar feugiat turpis. Integer non odio eget velit malesuada dictum. Donec luctus id enim sed convallis. Phasellus non elit pellentesque, iaculis lorem non, ornare enim. Integer pretium lacus ac ante tempus, nec scelerisque felis porta.

Duis posuere, ante quis blandit pellentesque, arcu tortor fringilla justo, id tristique neque mauris id diam. Vestibulum nec dui sagittis, facilisis risus dignissim, scelerisque lectus. Vivamus aliquam urna ac pellentesque laoreet. Nunc luctus turpis quis sapien congue, a rhoncus libero placerat. Quisque sagittis et arcu sed scelerisque. In a neque quis enim lacinia pulvinar. Maecenas metus ipsum, bibendum in dolor ut, condimentum aliquam risus. Fusce dictum fringilla enim. Mauris accumsan turpis sit amet quam hendrerit, ut euismod mi dignissim. Pellentesque at molestie tellus. Aliquam rutrum ipsum a dapibus dignissim. Quisque aliquam maximus vulputate. Curabitur dictum facilisis neque, ut fermentum turpis consectetur id. Cras finibus nunc eu purus posuere vehicula. Mauris nisl turpis, mollis nec porta nec, placerat eget dolor. Sed sodales, risus sed porttitor tincidunt, quam justo ultrices nunc, blandit vehicula nibh libero ac lorem.

Phasellus interdum odio a nunc rhoncus, quis volutpat lorem mattis. Mauris vestibulum mauris sed purus pellentesque tempus. Vivamus vel diam suscipit, pretium ex et, rhoncus urna. Praesent laoreet, erat sed malesuada maximus, odio nunc placerat justo, at scelerisque tellus leo eget urna. Curabitur mollis congue felis, sit amet lobortis nunc tincidunt nec. Cras lobortis pulvinar vestibulum. Pellentesque id porta nunc. Vestibulum eu euismod lacus. Aliquam purus tortor, efficitur sit amet bibendum ultrices, molestie sit amet massa. Donec vel dignissim leo. Suspendisse venenatis, mi et lacinia posuere, ex lectus consectetur enim, in dapibus urna risus sit amet libero. In hac habitasse platea dictumst. Integer egestas neque et nisl ullamcorper, eu lacinia libero ultrices.

Vivamus posuere ultrices augue quis volutpat. Phasellus eu massa porta, faucibus nisl sit amet, tincidunt elit. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Morbi quis ultrices dolor. Donec id odio aliquet, pharetra lectus sed, tincidunt ipsum. Nullam varius quam quis sagittis sodales. Fusce vel luctus diam. Nam diam nulla, eleifend eu quam ut, rutrum vestibulum leo. Nam commodo urna sit amet arcu varius tristique.

Curabitur tristique quam commodo, placerat erat eu, scelerisque orci. In eget imperdiet sem. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac.

)"_hash_u64 == 937791235);
    }
}

TEST_CASE("Calling constexpr get_index", "[keycap.core:math]")
{
    STATIC_REQUIRE(keycap::get_index(0, 0, 15) == 0);
    STATIC_REQUIRE(keycap::get_index(0, 1, 15) == 15);
    STATIC_REQUIRE(keycap::get_index(1, 0, 15) == 1);
    STATIC_REQUIRE(keycap::get_index(10, 10, 0) == 10);
    STATIC_REQUIRE(keycap::get_index(10, 10, 15) == 160);
}

TEST_CASE("Calling constexpr get_coordinates", "[keycap.core:math]")
{
    STATIC_REQUIRE(keycap::get_coordinates(0, 15) == std::pair<int, int>{0, 0});
    STATIC_REQUIRE(keycap::get_coordinates(10, 15) == std::pair<int, int>{10, 0});
}

TEST_CASE("Calling constexpr map", "[keycap.core:math]")
{
    STATIC_REQUIRE(keycap::map(0, 0, 10, 0, 100) == 0);
    STATIC_REQUIRE(keycap::map(5, 0, 10, 0, 100) == 50);
    STATIC_REQUIRE(keycap::map(10, 0, 10, 0, 100) == 100);
}

#include <array>

TEST_CASE("array_index", "[keycap.core:algorithm]")
{
    SECTION("c-arrays")
    {
        constexpr int index = 2;
        constexpr int array[] = {0, 1, 2, 3};
        STATIC_REQUIRE(keycap::array_index(array[index], array[0]) == index);
    }

    SECTION("std::array")
    {
        constexpr int index = 2;
        constexpr std::array<int, 4> array{0, 1, 2, 3};
        STATIC_REQUIRE(keycap::array_index(array[index], array[0]) == index);
    }
}

TEST_CASE("is_odd", "[keycap.core:algorithm]")
{
    SECTION("0 is even")
    {
        STATIC_REQUIRE(keycap::is_odd(0u) == false);
    }

    SECTION("1 is odd")
    {
        STATIC_REQUIRE(keycap::is_odd(1u) == true);
    }
}

TEST_CASE("is_even", "[keycap.core:algorithm]")
{
    SECTION("0 is even")
    {
        STATIC_REQUIRE(keycap::is_even(0) == true);
    }

    SECTION("1 is odd")
    {
        STATIC_REQUIRE(keycap::is_even(1) == false);
    }
}
