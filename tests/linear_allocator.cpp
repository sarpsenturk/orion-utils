#include "orion-utils/allocators/linear_allocator.h"

#include <gtest/gtest.h>

namespace
{
    TEST(LinearAllocator, Ctor)
    {
        constexpr auto size = 2048;
        const orion::LinearAllocator allocator(size);
        EXPECT_EQ(allocator.max_size(), size);
        EXPECT_EQ(allocator.available(), size);
        EXPECT_EQ(allocator.in_use(), 0);
    }

    TEST(LinearAllocator, Allocate)
    {
        constexpr auto size = 2048;
        struct S {
            int i;
        };
        orion::LinearAllocator allocator(size);
        void* ptr = allocator.allocate(sizeof(S));
        EXPECT_EQ(allocator.in_use(), sizeof(S));
        EXPECT_EQ(allocator.available(), size - sizeof(S));
        EXPECT_NE(ptr, nullptr);
    }

    TEST(LinearAllocator, AllocateOutOfMemory)
    {
        constexpr auto size = 10;
        orion::LinearAllocator allocator(size);
        EXPECT_THROW(allocator.allocate(size + 1), std::bad_alloc);
    }

    TEST(LinearAllocator, Reset)
    {
        constexpr auto size = 32;
        orion::LinearAllocator allocator(size);
        allocator.allocate(2);
        ASSERT_LT(allocator.available(), size);
        allocator.allocate(4);
        ASSERT_LT(allocator.available(), size);
        allocator.reset();
        EXPECT_EQ(allocator.available(), size);
    }
} // namespace
