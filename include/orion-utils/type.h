#pragma once

#include <concepts> // std::same_as

namespace orion
{
    template<typename T, typename... Ts>
    concept any_of = (... || std::same_as<T, Ts>);

    template<typename T, typename... Ts>
    concept all_of = (... && std::same_as<T, Ts>);

    template<typename... Ts>
    concept not_empty = (sizeof...(Ts) > 0);
} // namespace orion