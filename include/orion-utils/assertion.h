#pragma once

#include "orion-utils/format.h"

#include <cstdio>  // std::puts
#include <cstdlib> // std::abort

#if !defined(NDEBUG) || !defined(ORION_ENABLE_ASSERTIONS)
    #define ORION_ASSERT(condition)                                                                                              \
        do {                                                                                                                     \
            if (!(condition)) {                                                                                                  \
                std::puts(fmt_lib::format("Assertion failed ({}:{} {}): {}", __FILE__, __LINE__, __func__, #condition).c_str()); \
                std::abort();                                                                                                    \
            }                                                                                                                    \
        } while (0)
#else
    #define ORION_ASSERT(condition) ((void)0)
#endif