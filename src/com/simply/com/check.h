#pragma once

#include <winerror.h>
#include <simply/com/com_error.h>

namespace simply { namespace com
{
    inline void check(HRESULT hresult)
    {
        if (FAILED(hresult))
        {
            throw com_error { hresult };
        }
    }
}}