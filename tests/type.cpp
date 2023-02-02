#include "orion-utils/type.h"

#include <gtest/gtest.h>

TEST(TypeAnyOf, ValidType)
{
    static_assert(orion::any_of<int, char, bool, int, float>);
}

TEST(TypeAnyOf, InvalidType)
{
    static_assert(!orion::any_of<int, char, bool, float>);
}
