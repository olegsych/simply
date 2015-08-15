#pragma once

#include <functional>
#include <Unknwnbase.h>

using namespace std;

namespace simply { namespace com 
{
    class stub_IUnknown : public IUnknown
    {
    public:
        function<HRESULT(const GUID&, void**)> query_interface = [](const GUID& interface_id, void** object) { return E_NOINTERFACE; };
        function<ULONG(void)> add_ref = [] { return 2; };
        function<ULONG(void)> release = [] { return 1; };

    private:
        virtual HRESULT __stdcall QueryInterface(const GUID& interface_id, void** object) override
        {
            return query_interface(interface_id, object);
        }

        virtual ULONG __stdcall AddRef(void) override
        {
            return add_ref();
        }

        virtual ULONG __stdcall Release(void) override
        {
            return release();
        }
    };
}}