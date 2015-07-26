#pragma once

#include <type_traits>
#include <simply/assert/fail.h>
#include <simply/utility/type_name.h>

namespace simply { namespace assert
{
    template<typename actual_t>
    void is_abstract()
    {
        if (!std::is_abstract<actual_t>::value)
        {
            std::ostringstream message;
            message << "Expected abstract type\n";
            message << "Actual concrete type: <" << utility::type_name<actual_t>() << ">";
            fail(message);
        }
    }

    template<typename actual_t>
    void is_concrete()
    {
        if (std::is_abstract<actual_t>::value)
        {
            std::ostringstream message;
            message << "Expected concrete type\n";
            message << "Actual abstract type: <" << utility::type_name<actual_t>() << ">";
            fail(message);
        }
    }

    template<typename expected_t, typename actual_t>
    void is_same()
    {      
        if (!std::is_same<expected_t, actual_t>::value)
        {
            std::ostringstream message;
            message << "Expected type: <" << utility::type_name<expected_t>() << ">\n";
            message << "Actual type: <" << utility::type_name<actual_t>() << ">";
            fail(message);
        }
    }
}}