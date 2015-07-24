#pragma once

#include <type_traits>
#include <simply/assert/fail.h>
#include <simply/utility/type_name.h>

namespace simply { namespace assert
{
    template<typename expected_t, typename actual_t>
    void is_same()
    {      
        using simply::utility::type_name;

        if (!std::is_same<expected_t, actual_t>::value)
        {
            std::ostringstream message;
            message << "Expected type: <" << type_name<expected_t>() << ">\n";
            message << "Actual type: <" << type_name<actual_t>() << ">.";
            fail(message);
        }
    }
}}