#pragma once

#include <stdexcept>
#include <windows.h>

namespace simply { namespace com 
{
    class com_error : public std::runtime_error
    {
    public:
        inline com_error(HRESULT hresult) : 
            runtime_error { format_message(hresult) },
            _hresult { hresult }
        {
        }

        inline HRESULT hresult()
        {
            return _hresult;
        }

    private:
        const HRESULT _hresult;
        
        inline static std::string format_message(HRESULT hresult)
        {
            char buffer[4096];
            FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hresult, 0, buffer, sizeof(buffer), nullptr);
            return std::string { buffer };
        }
    };
}}
