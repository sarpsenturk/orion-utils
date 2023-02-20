#include "orion-utils/enum.h"

#include <gtest/gtest.h>
#include <type_traits> // std::is_same_v

enum class Bitflags : std::uint8_t {
    One = 1,
    Two = 2,
    Four = 4,
};

template<>
struct orion::enum_traits<Bitflags> : orion::default_enum_traits<Bitflags> {
    static constexpr bool bitwise_enabled = true;
};

namespace
{
    TEST(Enum, ToUnderlying)
    {
        using underlying = std::uint8_t;
        enum class Enum : underlying {};
        static_assert(std::is_same_v<underlying, decltype(orion::to_underlying(std::declval<Enum>()))>);
    }

    TEST(Enum, BitwiseOperators)
    {
        EXPECT_EQ(orion::to_underlying(~Bitflags::One), 254);

        EXPECT_EQ(orion::to_underlying(Bitflags::Two & Bitflags::Two), 2);
        EXPECT_EQ(orion::to_underlying(Bitflags::Two & Bitflags::One), 0);

        EXPECT_EQ(orion::to_underlying(Bitflags::One | Bitflags::Two), 3);
        EXPECT_EQ(orion::to_underlying(Bitflags::Two | Bitflags::Two), 2);

        EXPECT_EQ(orion::to_underlying(Bitflags::Four ^ Bitflags::Four), 0);
        EXPECT_EQ(orion::to_underlying(Bitflags::One ^ Bitflags::Two), 3);

        EXPECT_EQ(Bitflags::One << 1, Bitflags::Two);
        EXPECT_EQ(Bitflags::Two >> 1, Bitflags::One);
    }
} // namespace
