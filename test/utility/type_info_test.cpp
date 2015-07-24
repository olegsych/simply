#include "stdafx.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace simply { namespace utility
{
    TEST_CLASS(type_name_test)
    {
    public:
        TEST_METHOD(type_name_returns_const_string)
        {
            Assert::IsTrue(typeid(string) == typeid(type_name<int>()));
            Assert::IsTrue(is_const<decltype(type_name<int>())>::value);
        }

        TEST_METHOD(type_name_returns_name_of_given_type)
        {
            Assert::AreEqual(string { "int" }, type_name<int>());
        }

        TEST_METHOD(type_name_returns_name_of_given_const_type)
        {
            Assert::AreEqual(string { "const int" }, type_name<const int>());
        }

        TEST_METHOD(type_name_return_name_of_given_volatile_type)
        {
            Assert::AreEqual(string { "volatile int" }, type_name<volatile int>());
        }
    };
}}