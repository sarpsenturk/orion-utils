#pragma once

#include <concepts>    // std::convertible_to
#include <type_traits> // std::is_enum, std::underlying_type

namespace orion
{
    template<typename T>
    concept enumerator = std::is_enum_v<T>;

    template<enumerator Enum>
    [[nodiscard]] constexpr auto to_underlying(Enum value) noexcept -> std::underlying_type_t<Enum>
    {
        return static_cast<std::underlying_type_t<Enum>>(value);
    }

    template<enumerator Enum>
    struct default_enum_traits {
        static constexpr bool bitwise_enabled = false;
        static constexpr bool to_bool(Enum value) noexcept { return value != static_cast<Enum>(0); };
    };

    template<enumerator Enum>
    struct enum_traits : default_enum_traits<Enum> {
    };

    // clang-format off
    template<typename Enum>
    concept bool_convertible_enum = requires(Enum value) {
        { enum_traits<Enum>::to_bool(value) } -> std::convertible_to<bool>;
    };
    // clang format on

    template<bool_convertible_enum Enum>
    [[nodiscard]] constexpr bool to_bool(Enum value) noexcept(noexcept(enum_traits<Enum>::to_bool(value)))
    {
        return enum_traits<Enum>::to_bool(value);
    }
} // namespace orion

// Enable global bitwise operators if bitwise_enabled traits is true
template<orion::enumerator Enum>
constexpr Enum operator~(Enum value) noexcept
{
    return static_cast<Enum>(~orion::to_underlying(value));
}

template<orion::enumerator Enum>
constexpr Enum operator&(Enum lhs, Enum rhs) noexcept
{
    return static_cast<Enum>(orion::to_underlying(lhs) & orion::to_underlying(rhs));
}

template<orion::enumerator Enum>
constexpr Enum operator|(Enum lhs, Enum rhs) noexcept
{
    return static_cast<Enum>(orion::to_underlying(lhs) | orion::to_underlying(rhs));
}

template<orion::enumerator Enum>
constexpr Enum operator^(Enum lhs, Enum rhs) noexcept
{
    return static_cast<Enum>(orion::to_underlying(lhs) ^ orion::to_underlying(rhs));
}

template<orion::enumerator Enum, typename T>
constexpr Enum operator<<(Enum value, const T& shift) noexcept
{
    return static_cast<Enum>(orion::to_underlying(value) << shift);
}

template<orion::enumerator Enum, typename T>
constexpr Enum operator>>(Enum value, const T& shift) noexcept
{
    return static_cast<Enum>(orion::to_underlying(value) >> shift);
}
