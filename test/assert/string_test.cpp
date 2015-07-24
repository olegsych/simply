#include "stdafx.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace simply::utility;

namespace simply 
{
    TEST_CLASS(string_test)
    {
        wstring output;
        temporary<function<void(const wstring&)>> fail_stub {
            assert::implementation::fail,
            [&](const wstring& message) { output = message; }
        };

    public:
        #pragma region find<string>

        TEST_METHOD(find_fails_when_expected_string_is_not_found_in_actual_string)
        {
            const string sub_string { "expected" };
            const string actual_string { "actual" };

            size_t pos = assert::find(sub_string, actual_string);

            Assert::AreEqual(string::npos, pos);
            Assert::AreNotEqual(string::npos, this->output.find(L"expected"));
            Assert::AreNotEqual(string::npos, this->output.find(L"actual"));
        }

        TEST_METHOD(find_fails_when_expected_cstyle_string_is_not_found_in_actual_string)
        {
            const char* sub_string { "expected" };
            const string actual_string { "actual" };

            size_t pos = assert::find(sub_string, actual_string);

            Assert::AreEqual(string::npos, pos);
            Assert::AreNotEqual(string::npos, this->output.find(L"expected"));
            Assert::AreNotEqual(string::npos, this->output.find(L"actual"));
        }

        TEST_METHOD(find_fails_when_expected_string_is_not_found_in_actual_cstyle_string)
        {
            const string sub_string { "expected" };
            const char* actual_string { "actual" };

            size_t pos = assert::find(sub_string, actual_string);

            Assert::AreEqual(string::npos, pos);
            Assert::AreNotEqual(string::npos, this->output.find(L"expected"));
            Assert::AreNotEqual(string::npos, this->output.find(L"actual"));
        }

        TEST_METHOD(find_fails_when_expected_cstyle_string_is_not_found_in_actual_cstyle_string)
        {
            const char* sub_string { "expected" };
            const char* actual_string { "actual" };

            size_t pos = assert::find(sub_string, actual_string);

            Assert::AreEqual(string::npos, pos);
            Assert::AreNotEqual(string::npos, this->output.find(L"expected"));
            Assert::AreNotEqual(string::npos, this->output.find(L"actual"));
        }

        TEST_METHOD(find_returns_position_of_expected_string_found_in_actual_string)
        {
            const string sub_string { "expected" };
            const string actual_string { "actual with expected" };

            size_t pos = assert::find(sub_string, actual_string);

            Assert::AreEqual(actual_string.find(sub_string), pos);
            Assert::AreEqual(0ULL, this->output.length());
        }

        #pragma endregion

        #pragma region find<wstring>

        TEST_METHOD(find_fails_when_expected_wstring_is_not_found_in_actual_wstring)
        {
            const wstring sub_string { L"expected" };
            const wstring actual_string { L"actual" };

            size_t pos = assert::find(sub_string, actual_string);

            Assert::AreEqual(wstring::npos, pos);
            Assert::AreNotEqual(wstring::npos, this->output.find(sub_string));
            Assert::AreNotEqual(wstring::npos, this->output.find(actual_string));
        }

        TEST_METHOD(find_fails_when_expected_cstyle_wstring_is_not_found_in_actual_wstring)
        {
            const wchar_t* sub_string { L"expected" };
            const wstring actual_string { L"actual" };

            size_t pos = assert::find(sub_string, actual_string);

            Assert::AreEqual(wstring::npos, pos);
            Assert::AreNotEqual(wstring::npos, this->output.find(L"expected"));
            Assert::AreNotEqual(wstring::npos, this->output.find(L"actual"));
        }

        TEST_METHOD(find_fails_when_expected_wstring_is_not_found_in_actual_cstyle_wstring)
        {
            const wstring sub_string { L"expected" };
            const wchar_t* actual_string { L"actual" };

            size_t pos = assert::find(sub_string, actual_string);

            Assert::AreEqual(wstring::npos, pos);
            Assert::AreNotEqual(wstring::npos, this->output.find(L"expected"));
            Assert::AreNotEqual(wstring::npos, this->output.find(L"actual"));
        }

        TEST_METHOD(find_fails_when_expected_cstyle_wstring_is_not_found_in_actual_cstyle_wstring)
        {
            const wchar_t* sub_string { L"expected" };
            const wchar_t* actual_string { L"actual" };

            size_t pos = assert::find(sub_string, actual_string);

            Assert::AreEqual(wstring::npos, pos);
            Assert::AreNotEqual(string::npos, this->output.find(L"expected"));
            Assert::AreNotEqual(string::npos, this->output.find(L"actual"));
        }

        TEST_METHOD(find_doesnt_fail_when_expected_wstring_is_found_in_actual_wstring)
        {
            const wstring sub_string { L"expected" };
            const wstring actual_string { L"expected" };

            size_t pos = assert::find(sub_string, actual_string);

            Assert::AreEqual(actual_string.find(sub_string), pos);
            Assert::AreEqual(0ULL, this->output.length());
        }

        #pragma endregion
    };
}