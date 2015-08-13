#include "stdafx.h"
#include <vector>

using namespace std;

namespace simply { namespace utility
{
    TEST_CLASS(range_test)
    {
    public:
        TEST_METHOD(begin_return_type_matches_const_iterator_of_its_container)
        {
            using expected = vector<char>::const_iterator;
            using actual = decltype(declval<range<vector<char>>>().begin());
            assert::is_same<expected, actual>();
        }

        TEST_METHOD(end_return_type_matches_const_iterator_of_its_container)
        {
            using expected = vector<char>::const_iterator;
            using actual = decltype(declval<range<vector<char>>>().end());
            assert::is_same<expected, actual>();
        }

        TEST_METHOD(range_can_be_used_in_for_loop)
        {
            vector<int> expected { 42, 43, 44 };
            vector<int> actual;
            range<vector<int>> sut { expected };

            for (int value : sut)
            {
                actual.push_back(value);
            }

            assert::is_true(expected == actual); // can't use is_equal because there is no << operator for vector
        }
    };
}}