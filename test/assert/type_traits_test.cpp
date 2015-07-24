#include "stdafx.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace simply::utility;

namespace simply
{
    TEST_CLASS(type_traits_test)
    {
        wstring output;
        temporary<function<void(const wstring&)>> fail_stub {
            assert::implementation::fail,
            [&](const wstring& message) { output = message; }
        };
    public:
        TEST_METHOD(is_same_fails_when_types_are_different)
        {
            assert::is_same<int, double>();

            Assert::AreNotEqual(wstring::npos, this->output.find(L"int"));
            Assert::AreNotEqual(wstring::npos, this->output.find(L"double"));
        }

        TEST_METHOD(is_same_failure_message_includes_const_and_volatile_modifiers)
        {
            assert::is_same<volatile int, const int>();

            Assert::AreNotEqual(wstring::npos, this->output.find(L"volatile int"));
            Assert::AreNotEqual(wstring::npos, this->output.find(L"const int"));
        }
    };
}