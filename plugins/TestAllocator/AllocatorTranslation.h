#pragma once

//https://learn.microsoft.com/en-us/cpp/standard-library/allocators?view=msvc-170
#include "SC_PlugIn.hpp"

#include <stdlib.h> //size_t, malloc, free
#include <new> // bad_alloc, bad_array_new_length
#include <memory>


namespace memoryTranslation {

    extern World* g_pWorld;

    template <class T>
    struct RTAllocator
    {
        typedef T value_type;
        RTAllocator() noexcept {} //default ctor not required by C++ Standard Library

        // A converting copy constructor:
        template<class U> RTAllocator(const RTAllocator<U>&) noexcept {}
        template<class U> bool operator==(const RTAllocator<U>&) const noexcept
        {
            return true;
        }
        template<class U> bool operator!=(const RTAllocator<U>&) const noexcept
        {
            return false;
        }
        T* allocate(const size_t n) const;
        void deallocate(T* const p, size_t) const noexcept;
    };

    template <class T>
    T* RTAllocator<T>::allocate(const size_t n) const
    {
        if (n == 0)
        {
            return nullptr;
        }
        if (n > static_cast<size_t>(-1) / sizeof(T))
        {
            throw std::bad_array_new_length();
        }
        void* const pv = RTAlloc(g_pWorld, n * sizeof(T));// malloc(n * sizeof(T));
        if (!pv) { throw std::bad_alloc(); }
        return static_cast<T*>(pv);
    }

    template<class T>
    void RTAllocator<T>::deallocate(T* const p, size_t) const noexcept
    {
        RTFree(g_pWorld, p);
    }
}