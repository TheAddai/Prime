#pragma once

#include "logger.h"
#include "core.h"
#include "platform.h"

/** @brief debug breakpoint */
#ifdef PPLATFORM_WINDOWS
#define PBREAK  __debugbreak();
#else
#define PBREAK  void()0
#endif // PPLATFORM_WINDOWS

#ifdef PCONFIG_DEBUG

#define PASSERT(expr)                                              \
    {                                                                \
        if (expr) {                                                  \
        } else {                                                     \
            PERROR("Assertion {0} failed in {1} at line {2}", P_STR(expr), P_FILE, P_LINE);                \
            PBREAK;                                                \
        }                                                            \
    }

#define PASSERT_MSG(expr, message)                                 \
    {                                                                \
        if (expr) {                                                  \
        } else {                                                     \
            PERROR("Assertion {0} failed in {1} at line {2} \n{3}", P_STR(expr), P_FILE, P_LINE, message);                \
            PBREAK;                                                \
        }                                                            \
    }
#else
#define PASSERT(expr)               void()0
#define PASSERT_MSG(expr, message)  void()0
#endif // PCONFIG_DEBUG
