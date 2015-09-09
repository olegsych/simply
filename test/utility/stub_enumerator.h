#pragma once

#include <functional>
#include <initializer_list>
#include <simply/utility/enumerator.h>

using namespace std;

namespace simply { namespace utility 
{
    template<typename element_t> class stub_enumerator : public enumerator<element_t>
    {
        typename initializer_list<element_t>::iterator current;
        typename initializer_list<element_t>::iterator last;
    public:
        stub_enumerator()
            : current { nullptr }, last { nullptr }
        {
        }

        stub_enumerator(initializer_list<element_t> elements)
            : current { elements.begin() }, last { elements.end() }
        {
        }

        function<bool(element_t*)> stub_get_next = [&](element_t* result) 
        { 
            if (current == last)
            {
                return false;
            }

            *result = *current;
            ++current;
            return true;
        };

        bool get_next(element_t* result) override
        {
            return stub_get_next(result);
        }
    };
}}
