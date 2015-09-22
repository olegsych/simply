#include "stdafx.h"
#include <CppUnitTest.h>
#include <simply/utility/temporary.h>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace simply { namespace utility 
{
    TEST_CLASS(temporary_test)
    {
    public:
        TEST_METHOD(constructor_replaces_target_with_given_lvalue)
        {
            int target;

            temporary<int> sut { target, 42 };
            
            Assert::AreEqual(42, target);
        }

        TEST_METHOD(destructor_replaces_target_with_original_value)
        {
            int target { 42 };
            temporary<int> sut { target, 0 };

            sut.~temporary();
            
            Assert::AreEqual(42, target);
        }
    };
}}