#pragma once
#include <rythe/primitives>

#include "core/platform/platform.hpp"

/**
 * @file pointer.hpp
 */

namespace rythe::core
{
    /**@class pointer
     * @brief Non owning pointer wrapper.
     * @tparam T Type of the underlying pointer.
     */
    template<typename T>
    struct pointer;

    template<typename T>
    struct pointer<const T>
    {
        const T* ptr;

        R_NODISCARD R_ALWAYS_INLINE constexpr const T* operator->() const noexcept { return ptr; }

        R_NODISCARD R_ALWAYS_INLINE constexpr const T& operator*() const noexcept { return *ptr; }

        R_NODISCARD R_ALWAYS_INLINE constexpr operator bool() const noexcept { return ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr operator const T* () const noexcept { return ptr; }

        R_ALWAYS_INLINE constexpr pointer& operator=(const T* src) noexcept { ptr = src; return *this; }

        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator==(const pointer& other) const noexcept { return ptr == other.ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator!=(const pointer& other) const noexcept { return ptr != other.ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator<=(const pointer& other) const noexcept { return ptr <= other.ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator> (const pointer& other) const noexcept { return ptr > other.ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator>=(const pointer& other) const noexcept { return ptr >= other.ptr; }
                                
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator==(const T* other) const noexcept { return ptr == other; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator!=(const T* other) const noexcept { return ptr != other; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator< (const T* other) const noexcept { return ptr < other; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator<=(const T* other) const noexcept { return ptr <= other; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator> (const T* other) const noexcept { return ptr > other; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator>=(const T* other) const noexcept { return ptr >= other; }
                                
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator==(std::nullptr_t) const noexcept { return ptr == nullptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator!=(std::nullptr_t) const noexcept { return ptr != nullptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator< (const pointer& other) const noexcept { return ptr < other.ptr; }
        
        R_ALWAYS_INLINE constexpr pointer& operator++() noexcept { ptr++; return *this; }
        R_ALWAYS_INLINE constexpr pointer& operator--() noexcept { ptr--; return *this; }
        R_ALWAYS_INLINE constexpr pointer operator++(int) noexcept { return { ++ptr }; }
        R_ALWAYS_INLINE constexpr pointer operator--(int) noexcept { return { --ptr }; }
        R_NODISCARD R_ALWAYS_INLINE constexpr pointer operator+(rsl::diff_type n) const noexcept { return { ptr + n }; }
        R_NODISCARD R_ALWAYS_INLINE constexpr pointer operator-(rsl::diff_type n) const noexcept { return { ptr - n }; }
        R_ALWAYS_INLINE constexpr pointer& operator+=(rsl::diff_type n) noexcept { ptr += n; return *this; }
        R_ALWAYS_INLINE constexpr pointer& operator-=(rsl::diff_type n) noexcept { ptr -= n; return *this; }
    };

    template<typename T>
    struct pointer
    {
        T* ptr;

        R_NODISCARD R_ALWAYS_INLINE constexpr T* operator->() noexcept { return ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr const T* operator->() const noexcept { return ptr; }
                                  
        R_NODISCARD R_ALWAYS_INLINE constexpr T& operator*() noexcept { return *ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr const T& operator*() const noexcept { return *ptr; }
                                  
        R_NODISCARD R_ALWAYS_INLINE constexpr operator bool() const noexcept { return ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr operator const T* () const noexcept { return ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr operator T* () noexcept { return ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr operator pointer<const T>() noexcept { return { ptr }; }
        
        R_ALWAYS_INLINE constexpr pointer& operator=(T* src) noexcept { ptr = src; return *this; }
        
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator==(const pointer& other) const noexcept { return ptr == other.ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator!=(const pointer& other) const noexcept { return ptr != other.ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator< (const pointer& other) const noexcept { return ptr < other.ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator<=(const pointer& other) const noexcept { return ptr <= other.ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator> (const pointer& other) const noexcept { return ptr > other.ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator>=(const pointer& other) const noexcept { return ptr >= other.ptr; }
                                  
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator==(const T* other) const noexcept { return ptr == other; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator!=(const T* other) const noexcept { return ptr != other; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator< (const T* other) const noexcept { return ptr < other; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator<=(const T* other) const noexcept { return ptr <= other; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator> (const T* other) const noexcept { return ptr > other; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator>=(const T* other) const noexcept { return ptr >= other; }
                                  
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator==(std::nullptr_t) const noexcept { return ptr == nullptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator!=(std::nullptr_t) const noexcept { return ptr != nullptr; }
        
        R_ALWAYS_INLINE constexpr pointer& operator++() noexcept { ptr++; return *this; }
        R_ALWAYS_INLINE constexpr pointer& operator--() noexcept { ptr--; return *this; }
        R_ALWAYS_INLINE constexpr pointer operator++(int) noexcept { return { ++ptr }; }
        R_ALWAYS_INLINE constexpr pointer operator--(int) noexcept { return { --ptr }; }
        R_NODISCARD R_ALWAYS_INLINE constexpr pointer operator+(rsl::diff_type n) const noexcept { return { ptr + n }; }
        R_NODISCARD R_ALWAYS_INLINE constexpr pointer operator-(rsl::diff_type n) const noexcept { return { ptr - n }; }
        R_ALWAYS_INLINE constexpr pointer& operator+=(rsl::diff_type n) noexcept { ptr += n; return *this; }
        R_ALWAYS_INLINE constexpr pointer& operator-=(rsl::diff_type n) noexcept { ptr -= n; return *this; }
    };

    template<>
    struct pointer<const void>
    {
        const void* ptr;

       R_NODISCARD R_ALWAYS_INLINE constexpr operator bool() const noexcept { return ptr; }
       R_NODISCARD R_ALWAYS_INLINE constexpr operator const void* () const noexcept { return ptr; }
       
       R_ALWAYS_INLINE constexpr pointer& operator=(const void* src) noexcept { ptr = src; return *this; }
       
       R_NODISCARD R_ALWAYS_INLINE constexpr bool operator==(const pointer& other) const noexcept { return ptr == other.ptr; }
       R_NODISCARD R_ALWAYS_INLINE constexpr bool operator!=(const pointer& other) const noexcept { return ptr != other.ptr; }
       R_NODISCARD R_ALWAYS_INLINE constexpr bool operator< (const pointer& other) const noexcept { return ptr < other.ptr; }
       R_NODISCARD R_ALWAYS_INLINE constexpr bool operator<=(const pointer& other) const noexcept { return ptr <= other.ptr; }
       R_NODISCARD R_ALWAYS_INLINE constexpr bool operator> (const pointer& other) const noexcept { return ptr > other.ptr; }
       R_NODISCARD R_ALWAYS_INLINE constexpr bool operator>=(const pointer& other) const noexcept { return ptr >= other.ptr; }
       
       R_NODISCARD R_ALWAYS_INLINE constexpr bool operator==(const void* other) const noexcept { return ptr == other; }
       R_NODISCARD R_ALWAYS_INLINE constexpr bool operator!=(const void* other) const noexcept { return ptr != other; }
       R_NODISCARD R_ALWAYS_INLINE constexpr bool operator< (const void* other) const noexcept { return ptr < other; }
       R_NODISCARD R_ALWAYS_INLINE constexpr bool operator<=(const void* other) const noexcept { return ptr <= other; }
       R_NODISCARD R_ALWAYS_INLINE constexpr bool operator> (const void* other) const noexcept { return ptr > other; }
       R_NODISCARD R_ALWAYS_INLINE constexpr bool operator>=(const void* other) const noexcept { return ptr >= other; }
       
       R_NODISCARD R_ALWAYS_INLINE constexpr bool operator==(std::nullptr_t) const noexcept { return ptr == nullptr; }
       R_NODISCARD R_ALWAYS_INLINE constexpr bool operator!=(std::nullptr_t) const noexcept { return ptr != nullptr; }
    };

    template<>
    struct pointer<void>
    {
        void* ptr;

        R_NODISCARD R_ALWAYS_INLINE constexpr operator bool() const noexcept { return ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr operator const void* () const noexcept { return ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr operator void* () noexcept { return ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr operator pointer<const void>() noexcept { return { ptr }; }

        R_ALWAYS_INLINE constexpr pointer& operator=(void* src) noexcept { ptr = src; return *this; }

        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator==(const pointer& other) const noexcept { return ptr == other.ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator!=(const pointer& other) const noexcept { return ptr != other.ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator< (const pointer& other) const noexcept { return ptr < other.ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator<=(const pointer& other) const noexcept { return ptr <= other.ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator> (const pointer& other) const noexcept { return ptr > other.ptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator>=(const pointer& other) const noexcept { return ptr >= other.ptr; }

        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator==(const void* other) const noexcept { return ptr == other; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator!=(const void* other) const noexcept { return ptr != other; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator< (const void* other) const noexcept { return ptr < other; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator<=(const void* other) const noexcept { return ptr <= other; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator> (const void* other) const noexcept { return ptr > other; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator>=(const void* other) const noexcept { return ptr >= other; }

        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator==(std::nullptr_t) const noexcept { return ptr == nullptr; }
        R_NODISCARD R_ALWAYS_INLINE constexpr bool operator!=(std::nullptr_t) const noexcept { return ptr != nullptr; }
    };
}