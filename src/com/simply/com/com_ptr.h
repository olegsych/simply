#pragma once

#include <stdexcept>
#include <Unknwn.h>

namespace simply { namespace com 
{
    template <class T> class com_ptr
    {
    public:
        com_ptr() : object { nullptr }
        {
        }

        com_ptr(T* object) : object { object }
        {
            if (!object)
            {
                throw std::invalid_argument { "object must not be a nullptr." };
            }

            object->AddRef();
        }

        com_ptr(const com_ptr<T>& source) : object { source.object }
        {
            reference_object();
        }

        com_ptr(com_ptr<T>&& source) : object { source.object }
        {
            source.object = nullptr;
        }

        com_ptr<T>& operator=(const com_ptr<T>& source)
        {
            release_object();
            object = source.object;
            reference_object();
            return *this;
        }

        com_ptr<T>& operator=(com_ptr<T>&& source)
        {
            swap(object, source.object);
            return *this;
        }

        operator void**()
        {
            return reinterpret_cast<void**>(&object);
        }

        operator IUnknown**()
        {
            return reinterpret_cast<IUnknown**>(&object);
        }

        T* operator->() const
        {
            if (!object)
            {
                throw std::logic_error { "a nullptr cannot be dereferenced." };
            }

            return object;
        }

        ~com_ptr()
        {
            release_object();
        }

        T* get() const
        {
            return object;
        }

    private:
        T* object;

        void reference_object()
        {
            if (object)
            {
                object->AddRef();
            }
        }

        void release_object()
        {
            if (object)
            {
                object->Release();
            }
        }

        friend class com_ptr_test;
    };
}}