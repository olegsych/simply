#pragma once

#include <functional>
#include <initializer_list>
#include <simply/utility/enumerable.h>
#include "stub_enumerator.h"

using namespace std;

namespace simply { namespace utility 
{
    template<typename element_t> class stub_enumerable : public enumerable<element_t>
    {
        initializer_list<element_t> elements;
    public:
        stub_enumerable()
        {
        }

        stub_enumerable(initializer_list<element_t> elements) 
            : elements(elements.begin(), elements.end())
        {
        }

        function<unique_ptr<enumerator<element_t>>(void)> stub_create_enumerator = [&] 
        { 
            return unique_ptr<enumerator<element_t>> { new stub_enumerator<element_t>(elements) }; 
        };

        unique_ptr<enumerator<element_t>> create_enumerator() override
        {
            return stub_create_enumerator();
        }
    };
}}
