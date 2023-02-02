#include "orion-utils/enum.h"

#include <gtest/gtest.h>
#include <type_traits> // std::is_same_v

enum class StringEnum {
    First,
    Second
};

template<>
struct orion::enum_traits<StringEnum> {
    static constexpr auto to_string(StringEnum value) noexcept
    {
        switch (value) {
            case StringEnum::First:
                return "First";
            case StringEnum::Second:
                return "Second";
        }
        return "Unknown";
    }
};

namespace
{
    TEST(Enum, ToUnderlying)
    {
        using underlying = std::uint8_t;
        enum class Enum : underlying {};
        static_assert(std::is_same_v<underlying, decltype(orion::to_underlying(std::declval<Enum>()))>);
    }

    TEST(Enum, ToStringDefault)
    {
        enum class Enum {
            Zero,
            One
        };

        EXPECT_EQ(fmt_lib::format("{}", Enum::Zero), "0");
        EXPECT_EQ(fmt_lib::format("{}", Enum::One), "1");
    }

    TEST(Enum, ToStringOverloaded)
    {
        EXPECT_EQ(fmt_lib::format("{}", StringEnum::First), "First");
        EXPECT_EQ(fmt_lib::format("{}", StringEnum::Second), "Second");
        EXPECT_EQ(fmt_lib::format("{}", static_cast<StringEnum>(-1)), "Unknown");
    }
} // namespace