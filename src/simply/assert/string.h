#pragma once

#include <string>
#include <sstream>
#include <simply/assert/fail.h>

namespace simply { namespace assert
{
    template <typename char_t>
    size_t find(const std::basic_string<char_t>& expected, const std::basic_string<char_t>& actual)
    {
        size_t position = actual.find(expected);
        if (position == std::basic_string<char_t>::npos)
        {
            std::basic_ostringstream<char_t> message;
            message << "Not found: <" << expected << ">\n";
            message << "In value: <" << actual << ">.";
            fail(message);
        }

        return position;
    }

    template <typename char_t>
    size_t find(const char_t* expected, const std::basic_string<char_t>& actual)
    {
        return find(std::basic_string<char_t> { expected }, actual);
    }

    template <typename char_t>
    size_t find(const std::basic_string<char_t>& expected, const char_t* actual)
    {
        return find(expected, std::basic_string<char_t> { actual });
    }

    template <typename char_t>
    size_t find(const char_t* expected, const char_t* actual)
    {
        return find(std::basic_string<char_t> { expected }, std::basic_string<char_t> { actual });
    }
}}

// TODO: define equal(char*, string)
// TODO: define equal(string, char*)