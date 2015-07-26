#include "stdafx.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace simply
{
    TEST_CLASS(bool_test)
    {
        wstring output;
        utility::temporary<function<void(const wstring&)>> fail_stub {
            assert::implementation::fail,
            [&](const wstring& message) { output = message; }
        };

    public:
        #pragma region is_true(bool)

        TEST_METHOD(is_true_fails_when_given_value_is_false)
        {
            assert::is_true(false);

            Assert::AreNotEqual(wstring::npos, this->output.find(L"true"));
            Assert::AreNotEqual(wstring::npos, this->output.find(L"false"));
        }

        TEST_METHOD(is_true_doesnt_fail_when_given_value_is_true)
        {
            assert::is_true(true);
            
            Assert::AreEqual<size_t>(0, this->output.length());
        }

        #pragma endregion

        #pragma region is_false(bool)

        TEST_METHOD(is_false_fails_when_given_value_is_true)
        {
            assert::is_false(true);

            Assert::AreNotEqual(wstring::npos, this->output.find(L"false"));
            Assert::AreNotEqual(wstring::npos, this->output.find(L"true"));
        }

        TEST_METHOD(is_false_doesnt_fail_when_given_value_is_false)
        {
            assert::is_false(false);

            Assert::AreEqual<size_t>(0, this->output.length());
        }

        #pragma endregion
    };
}