#pragma once
#include <string>
#include <type_traits>

namespace simply { namespace utility 
{
    template<typename t> const std::string type_name()
    {
        string result { typeid(t).name() };
        
        if (std::is_const<t>::value)
        {
            result.insert(0, "const ");
        }

        if (std::is_volatile<t>::value)
        {
            result.insert(0, "volatile ");
        }

        return result;
    }
}}
