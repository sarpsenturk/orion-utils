#pragma once

#include <cstddef> // std::size_t, std::byte
#include <new>     // std::bad_alloc
#include <utility> // std::exchange

namespace orion
{
    class LinearAllocator final
    {
    public:
        constexpr explicit LinearAllocator(size_t max_size)
            : begin_(static_cast<std::byte*>(::operator new(max_size)))
            , end_(begin_ + max_size)
            , current_(begin_)
        {
        }

        constexpr LinearAllocator(const LinearAllocator&) {}

        constexpr LinearAllocator(LinearAllocator&& other) noexcept
            : begin_(std::exchange(other.begin_, nullptr))
            , end_(other.end_)
            , current_(other.end_)
        {
        }

        constexpr LinearAllocator& operator=(const LinearAllocator&)
        {
            return *this;
        }

        constexpr LinearAllocator& operator=(LinearAllocator&& other) noexcept
        {
            begin_ = std::exchange(other.begin_, nullptr);
            return *this;
        }

        constexpr ~LinearAllocator()
        {
            if (begin_) {
                ::operator delete(begin_, static_cast<size_t>(end_ - begin_));
            }
        }

        constexpr void* allocate(std::size_t size)
        {
            if (current_ + size > end_) {
                throw std::bad_alloc();
            }
            void* ptr = current_;
            current_ += size;
            return ptr;
        }

        constexpr void deallocate(void*, std::size_t)
        {
            // No-op. deallocation must be done via reset to reset all memory
        }

        constexpr void reset()
        {
            current_ = begin_;
        }

        [[nodiscard]] constexpr std::size_t max_size() const noexcept { return static_cast<size_t>(end_ - begin_); }

        [[nodiscard]] constexpr std::size_t available() const noexcept { return static_cast<size_t>(end_ - current_); }

        [[nodiscard]] constexpr std::size_t in_use() const noexcept { return static_cast<size_t>(current_ - begin_); }

        [[nodiscard]] constexpr bool operator==(const LinearAllocator& other) const { return begin_ == other.begin_; }

    private:
        std::byte* begin_ = nullptr;
        std::byte* end_ = nullptr;
        std::byte* current_ = nullptr;
    };
} // namespace orion