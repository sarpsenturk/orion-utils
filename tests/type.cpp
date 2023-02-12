#include "orion-utils/type.h"

#include <gtest/gtest.h>

TEST(Type, AnyOfValid)
{
    static_assert(orion::any_of<int, char, bool, int, float>);
}

TEST(Type, AnyOfInvalid)
{
    static_assert(!orion::any_of<int, char, bool, float>);
}

TEST(Type, AllOfValid)
{
    static_assert(orion::all_of<int, int, int, int>);
}

TEST(Type, AllOfInvalid)
{
    static_assert(!orion::all_of<int, int, int, bool>);
}

TEST(Type, NotEmptyValid)
{
    static_assert(orion::not_empty<int>);
}

TEST(Type, NotEmptyInvalid)
{
    static_assert(!orion::not_empty<>);
}
