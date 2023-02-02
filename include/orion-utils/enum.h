#pragma once

#include "orion-utils/format.h"

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
    struct enum_traits {
        static constexpr bool bitwise_enabled = false;
        static constexpr bool to_bool(Enum value) noexcept { return value != static_cast<Enum>(0); };
        static auto to_string(Enum value) { return fmt_lib::format("{}", to_underlying(value)); }
    };

    template<enumerator Enum>
    [[nodiscard]] constexpr bool to_bool(Enum value) noexcept(noexcept(enum_traits<Enum>::to_bool(value)))
    {
        return enum_traits<Enum>::to_bool(value);
    }
} // namespace orion

template<orion::enumerator Enum>
struct fmt_lib::formatter<Enum> : fmt_lib::formatter<const char*> { // NOLINT(cert-dcl58-cpp)
    template<typename FormatContext>
    auto format(Enum value, FormatContext& ctx) const
    {
        return fmt_lib::format_to(ctx.out(), "{}", orion::enum_traits<Enum>::to_string(value));
    }
};
