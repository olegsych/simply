#pragma once

#include <simply/assert/fail.h>

namespace simply { namespace assert
{
    inline void is_true(bool actual)
    {
        if (!actual)
        {
            fail("Expected value: <true>\nActual value: <false>");
        }
    }

    inline void is_false(bool actual)
    {
        if (actual)
        {
            fail("Expected value: <false>\nActual value: <true>");
        }
    }
}}