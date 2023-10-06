#pragma once
#include <rsl/primitives>
#include <rsl/utilities>

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

        [[nodiscard]] rythe_always_inline constexpr const T* operator->() const noexcept { return ptr; }

        [[nodiscard]] rythe_always_inline constexpr const T& operator*() const noexcept { return *ptr; }

        [[nodiscard]] rythe_always_inline constexpr operator bool() const noexcept { return ptr; }
        [[nodiscard]] rythe_always_inline constexpr operator const T* () const noexcept { return ptr; }

        rythe_always_inline constexpr pointer& operator=(const T* src) noexcept { ptr = src; return *this; }

        [[nodiscard]] rythe_always_inline constexpr bool operator==(const pointer& other) const noexcept { return ptr == other.ptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator!=(const pointer& other) const noexcept { return ptr != other.ptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator<=(const pointer& other) const noexcept { return ptr <= other.ptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator> (const pointer& other) const noexcept { return ptr > other.ptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator>=(const pointer& other) const noexcept { return ptr >= other.ptr; }
                                
        [[nodiscard]] rythe_always_inline constexpr bool operator==(const T* other) const noexcept { return ptr == other; }
        [[nodiscard]] rythe_always_inline constexpr bool operator!=(const T* other) const noexcept { return ptr != other; }
        [[nodiscard]] rythe_always_inline constexpr bool operator< (const T* other) const noexcept { return ptr < other; }
        [[nodiscard]] rythe_always_inline constexpr bool operator<=(const T* other) const noexcept { return ptr <= other; }
        [[nodiscard]] rythe_always_inline constexpr bool operator> (const T* other) const noexcept { return ptr > other; }
        [[nodiscard]] rythe_always_inline constexpr bool operator>=(const T* other) const noexcept { return ptr >= other; }
                                
        [[nodiscard]] rythe_always_inline constexpr bool operator==(std::nullptr_t) const noexcept { return ptr == nullptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator!=(std::nullptr_t) const noexcept { return ptr != nullptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator< (const pointer& other) const noexcept { return ptr < other.ptr; }
        
        rythe_always_inline constexpr pointer& operator++() noexcept { ptr++; return *this; }
        rythe_always_inline constexpr pointer& operator--() noexcept { ptr--; return *this; }
        rythe_always_inline constexpr pointer operator++(int) noexcept { return { ++ptr }; }
        rythe_always_inline constexpr pointer operator--(int) noexcept { return { --ptr }; }
        [[nodiscard]] rythe_always_inline constexpr pointer operator+(rsl::diff_type n) const noexcept { return { ptr + n }; }
        [[nodiscard]] rythe_always_inline constexpr pointer operator-(rsl::diff_type n) const noexcept { return { ptr - n }; }
        rythe_always_inline constexpr pointer& operator+=(rsl::diff_type n) noexcept { ptr += n; return *this; }
        rythe_always_inline constexpr pointer& operator-=(rsl::diff_type n) noexcept { ptr -= n; return *this; }
    };

    template<typename T>
    struct pointer
    {
        T* ptr;

        [[nodiscard]] rythe_always_inline constexpr T* operator->() noexcept { return ptr; }
        [[nodiscard]] rythe_always_inline constexpr const T* operator->() const noexcept { return ptr; }
                                  
        [[nodiscard]] rythe_always_inline constexpr T& operator*() noexcept { return *ptr; }
        [[nodiscard]] rythe_always_inline constexpr const T& operator*() const noexcept { return *ptr; }
                                  
        [[nodiscard]] rythe_always_inline constexpr operator bool() const noexcept { return ptr; }
        [[nodiscard]] rythe_always_inline constexpr operator const T* () const noexcept { return ptr; }
        [[nodiscard]] rythe_always_inline constexpr operator T* () noexcept { return ptr; }
        [[nodiscard]] rythe_always_inline constexpr operator pointer<const T>() noexcept { return { ptr }; }
        
        rythe_always_inline constexpr pointer& operator=(T* src) noexcept { ptr = src; return *this; }
        
        [[nodiscard]] rythe_always_inline constexpr bool operator==(const pointer& other) const noexcept { return ptr == other.ptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator!=(const pointer& other) const noexcept { return ptr != other.ptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator< (const pointer& other) const noexcept { return ptr < other.ptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator<=(const pointer& other) const noexcept { return ptr <= other.ptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator> (const pointer& other) const noexcept { return ptr > other.ptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator>=(const pointer& other) const noexcept { return ptr >= other.ptr; }
                                  
        [[nodiscard]] rythe_always_inline constexpr bool operator==(const T* other) const noexcept { return ptr == other; }
        [[nodiscard]] rythe_always_inline constexpr bool operator!=(const T* other) const noexcept { return ptr != other; }
        [[nodiscard]] rythe_always_inline constexpr bool operator< (const T* other) const noexcept { return ptr < other; }
        [[nodiscard]] rythe_always_inline constexpr bool operator<=(const T* other) const noexcept { return ptr <= other; }
        [[nodiscard]] rythe_always_inline constexpr bool operator> (const T* other) const noexcept { return ptr > other; }
        [[nodiscard]] rythe_always_inline constexpr bool operator>=(const T* other) const noexcept { return ptr >= other; }
                                  
        [[nodiscard]] rythe_always_inline constexpr bool operator==(std::nullptr_t) const noexcept { return ptr == nullptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator!=(std::nullptr_t) const noexcept { return ptr != nullptr; }
        
        rythe_always_inline constexpr pointer& operator++() noexcept { ptr++; return *this; }
        rythe_always_inline constexpr pointer& operator--() noexcept { ptr--; return *this; }
        rythe_always_inline constexpr pointer operator++(int) noexcept { return { ++ptr }; }
        rythe_always_inline constexpr pointer operator--(int) noexcept { return { --ptr }; }
        [[nodiscard]] rythe_always_inline constexpr pointer operator+(rsl::diff_type n) const noexcept { return { ptr + n }; }
        [[nodiscard]] rythe_always_inline constexpr pointer operator-(rsl::diff_type n) const noexcept { return { ptr - n }; }
        rythe_always_inline constexpr pointer& operator+=(rsl::diff_type n) noexcept { ptr += n; return *this; }
        rythe_always_inline constexpr pointer& operator-=(rsl::diff_type n) noexcept { ptr -= n; return *this; }
    };

    template<>
    struct pointer<const void>
    {
        const void* ptr;

       [[nodiscard]] rythe_always_inline constexpr operator bool() const noexcept { return ptr; }
       [[nodiscard]] rythe_always_inline constexpr operator const void* () const noexcept { return ptr; }
       
       rythe_always_inline constexpr pointer& operator=(const void* src) noexcept { ptr = src; return *this; }
       
       [[nodiscard]] rythe_always_inline constexpr bool operator==(const pointer& other) const noexcept { return ptr == other.ptr; }
       [[nodiscard]] rythe_always_inline constexpr bool operator!=(const pointer& other) const noexcept { return ptr != other.ptr; }
       [[nodiscard]] rythe_always_inline constexpr bool operator< (const pointer& other) const noexcept { return ptr < other.ptr; }
       [[nodiscard]] rythe_always_inline constexpr bool operator<=(const pointer& other) const noexcept { return ptr <= other.ptr; }
       [[nodiscard]] rythe_always_inline constexpr bool operator> (const pointer& other) const noexcept { return ptr > other.ptr; }
       [[nodiscard]] rythe_always_inline constexpr bool operator>=(const pointer& other) const noexcept { return ptr >= other.ptr; }
       
       [[nodiscard]] rythe_always_inline constexpr bool operator==(const void* other) const noexcept { return ptr == other; }
       [[nodiscard]] rythe_always_inline constexpr bool operator!=(const void* other) const noexcept { return ptr != other; }
       [[nodiscard]] rythe_always_inline constexpr bool operator< (const void* other) const noexcept { return ptr < other; }
       [[nodiscard]] rythe_always_inline constexpr bool operator<=(const void* other) const noexcept { return ptr <= other; }
       [[nodiscard]] rythe_always_inline constexpr bool operator> (const void* other) const noexcept { return ptr > other; }
       [[nodiscard]] rythe_always_inline constexpr bool operator>=(const void* other) const noexcept { return ptr >= other; }
       
       [[nodiscard]] rythe_always_inline constexpr bool operator==(std::nullptr_t) const noexcept { return ptr == nullptr; }
       [[nodiscard]] rythe_always_inline constexpr bool operator!=(std::nullptr_t) const noexcept { return ptr != nullptr; }
    };

    template<>
    struct pointer<void>
    {
        void* ptr;

        [[nodiscard]] rythe_always_inline constexpr operator bool() const noexcept { return ptr; }
        [[nodiscard]] rythe_always_inline constexpr operator const void* () const noexcept { return ptr; }
        [[nodiscard]] rythe_always_inline constexpr operator void* () noexcept { return ptr; }
        [[nodiscard]] rythe_always_inline constexpr operator pointer<const void>() noexcept { return { ptr }; }

        rythe_always_inline constexpr pointer& operator=(void* src) noexcept { ptr = src; return *this; }

        [[nodiscard]] rythe_always_inline constexpr bool operator==(const pointer& other) const noexcept { return ptr == other.ptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator!=(const pointer& other) const noexcept { return ptr != other.ptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator< (const pointer& other) const noexcept { return ptr < other.ptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator<=(const pointer& other) const noexcept { return ptr <= other.ptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator> (const pointer& other) const noexcept { return ptr > other.ptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator>=(const pointer& other) const noexcept { return ptr >= other.ptr; }

        [[nodiscard]] rythe_always_inline constexpr bool operator==(const void* other) const noexcept { return ptr == other; }
        [[nodiscard]] rythe_always_inline constexpr bool operator!=(const void* other) const noexcept { return ptr != other; }
        [[nodiscard]] rythe_always_inline constexpr bool operator< (const void* other) const noexcept { return ptr < other; }
        [[nodiscard]] rythe_always_inline constexpr bool operator<=(const void* other) const noexcept { return ptr <= other; }
        [[nodiscard]] rythe_always_inline constexpr bool operator> (const void* other) const noexcept { return ptr > other; }
        [[nodiscard]] rythe_always_inline constexpr bool operator>=(const void* other) const noexcept { return ptr >= other; }

        [[nodiscard]] rythe_always_inline constexpr bool operator==(std::nullptr_t) const noexcept { return ptr == nullptr; }
        [[nodiscard]] rythe_always_inline constexpr bool operator!=(std::nullptr_t) const noexcept { return ptr != nullptr; }
    };
}