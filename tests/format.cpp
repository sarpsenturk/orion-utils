#include "orion-utils/format.h"

#include <gtest/gtest.h>

struct S {
    int x;
    int y;
};

template<>
struct fmt_lib::formatter<S> : fmt_lib::formatter<int> {
    template<typename FormatContext>
    auto format(const S& s, FormatContext& ctx) const
    {
        return fmt_lib::format_to(ctx.out(), "{} {}", s.x, s.y);
    }
};

namespace
{
    TEST(Format, UserDefined)
    {
        EXPECT_EQ(fmt_lib::format("{}", S{42, 40}), "42 40");
    }
} // namespace
