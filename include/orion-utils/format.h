#pragma once

#if __has_include(<fmt/format.h>)
    #include <fmt/format.h>
    #define ORION_FORMAT_NS fmt
#elif __has_include(<format>)
    #include <format>
    #define ORION_FORMAT_NS std
#else
    #error "No formatting library available"
#endif

namespace fmt_lib = ORION_FORMAT_NS;
