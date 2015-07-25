#pragma once

#include <sstream>
#include <simply/assert/fail.h>
#include <simply/utility.h>

namespace simply { namespace assert
{
    inline void null(const void* pointer)
    {
        if (pointer != nullptr)
        {
            std::ostringstream message;
            message << "Expected nullptr of type <void *>\n";
            message << "Actual pointer value <0x" << pointer << ">";
            fail(message);
        }
    }

    template<typename t>
    void null(const t* pointer)
    {
        if (pointer != nullptr)
        {
            std::ostringstream message;
            message << "Expected nullptr of type <" << utility::type_name<t*>() << ">\n";
            message << "Actual pointer <0x" << pointer << ">";           
            try
            {
                message << " to type <" << typeid(*pointer).name() << ">";
            }
            catch (...)
            {
                // Ignore potential access violation from dereferencing an invalid pointer
            }
            fail(message);
        }
    }
}}