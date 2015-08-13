#pragma once

#include <utility>

namespace simply { namespace utility
{
    template<typename container_t> class range
    {
        const container_t& container;
    public:
        range(const container_t& container) : container { container }
        {
        }

        decltype(std::declval<container_t>().cbegin()) begin() const
        {
            return container.cbegin();
        }

        decltype(std::declval<container_t>().cend()) end() const
        {
            return container.cend();
        }
    };
}}