#pragma once
#include <deque>
#include <vector>
#include <list>
#include <string>
#include <array>
#include <queue>
#include <type_traits>

#include <rythe/primitives>

#include "core/platform/platform.hpp"

namespace rythe::core
{

#if !defined(DOXY_EXCLUDE)
#define HAS_FUNC(x)                                                                                                     \
    template<typename, typename T>                                                                                      \
    struct CONCAT(has_, x) {                                                                                            \
        static_assert(std::integral_constant<T, false>::value, "Second template param needs to be of function type.");  \
    };                                                                                                                  \
                                                                                                                        \
    template<typename C, typename Ret, typename... Args>                                                                \
    struct CONCAT(has_, x)<C, Ret(Args...)> {                                                                           \
    private:                                                                                                            \
        template<typename T>                                                                                            \
        static constexpr auto check(T*)                                                                                 \
            -> typename std::is_same<decltype(std::declval<T>(). x (std::declval<Args>()...)), Ret>::type;              \
                                                                                                                        \
        template <typename>                                                                                             \
        static constexpr auto check(...)                                                                                \
            ->std::false_type;                                                                                          \
                                                                                                                        \
        typedef decltype(check<C>(nullptr)) type;                                                                       \
    public:                                                                                                             \
        static constexpr bool value = type::value;                                                                      \
    };                                                                                                                  \
                                                                                                                        \
    template<typename C, typename F>                                                                                    \
    constexpr bool CONCAT(has_, CONCAT(x, _v)) = CONCAT(has_, x)<C, F>::value;                                   \
                                                                                                                        \
    template<typename, typename T>                                                                                      \
    struct CONCAT(has_static_, x) {                                                                                     \
        static_assert(std::integral_constant<T, false>::value, "Second template param needs to be of function type.");  \
    };                                                                                                                  \
                                                                                                                        \
    template<typename C, typename Ret, typename... Args>                                                                \
    struct CONCAT(has_static_, x)<C, Ret(Args...)> {                                                                    \
    private:                                                                                                            \
        template<typename T>                                                                                            \
        static constexpr auto check(T*)                                                                                 \
            -> typename std::is_same<decltype(T:: x (std::declval<Args>()...)), Ret>::type;                             \
                                                                                                                        \
        template <typename>                                                                                             \
        static constexpr auto check(...)                                                                                \
            ->std::false_type;                                                                                          \
                                                                                                                        \
        typedef decltype(check<C>(nullptr)) type;                                                                       \
    public:                                                                                                             \
        static constexpr bool value = type::value;                                                                      \
    };                                                                                                                  \
                                                                                                                        \
    template<typename C, typename F>                                                                                    \
    constexpr bool CONCAT(has_static_, CONCAT(x, _v)) = CONCAT(has_static_, x)<C, F>::value;
#else
#define HAS_FUNC(x)                                                                                                     \
    template<typename, typename T>                                                                                      \
    struct CONCAT(has_, x) {                                                                                            \
        static constexpr bool value = false;                                                                            \
    };                                                                                                                  \
                                                                                                                        \
    template<typename C, typename F>                                                                                    \
    constexpr bool CONCAT(has_, CONCAT(x, _v)) = CONCAT(has_, x)<C, F>::value;                                   \
                                                                                                                        \
    template<typename, typename T>                                                                                      \
    struct CONCAT(has_static_, x) {                                                                                     \
        static constexpr bool value = false;                                                                            \
    };                                                                                                                  \
                                                                                                                        \
    template<typename C, typename F>                                                                                    \
    constexpr bool CONCAT(has_static_, CONCAT(x, _v)) = CONCAT(has_static_, x)<C, F>::value;
#endif

#define  typename_1(x)                                                                    typename x
#define  typename_2(x, x2)                                                                typename x , typename x2
#define  typename_3(x, x2, x3)                                                            typename x , typename x2, typename x3
#define  typename_4(x, x2, x3, x4)                                                        typename x , typename x2, typename x3, typename x4
#define  typename_5(x, x2, x3, x4, x5)                                                    typename x , typename x2, typename x3, typename x4, typename x5
#define  typename_6(x, x2, x3, x4, x5, x6)                                                typename x , typename x2, typename x3, typename x4, typename x5, typename x6
#define  typename_7(x, x2, x3, x4, x5, x6, x7)                                            typename x , typename x2, typename x3, typename x4, typename x5, typename x6, typename x7
#define  typename_8(x, x2, x3, x4, x5, x6, x7, x8)                                        typename x , typename x2, typename x3, typename x4, typename x5, typename x6, typename x7, typename x8
#define  typename_9(x, x2, x3, x4, x5, x6, x7, x8, x9)                                    typename x , typename x2, typename x3, typename x4, typename x5, typename x6, typename x7, typename x8, typename x9
#define typename_10(x, x2, x3, x4, x5, x6, x7, x8, x9, x10)                               typename x , typename x2, typename x3, typename x4, typename x5, typename x6, typename x7, typename x8, typename x9, typename x10
#define typename_11(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11)                          typename x , typename x2, typename x3, typename x4, typename x5, typename x6, typename x7, typename x8, typename x9, typename x10, typename x11
#define typename_12(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12)                     typename x , typename x2, typename x3, typename x4, typename x5, typename x6, typename x7, typename x8, typename x9, typename x10, typename x11, typename x12
#define typename_13(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13)                typename x , typename x2, typename x3, typename x4, typename x5, typename x6, typename x7, typename x8, typename x9, typename x10, typename x11, typename x12, typename x13
#define typename_14(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14)           typename x , typename x2, typename x3, typename x4, typename x5, typename x6, typename x7, typename x8, typename x9, typename x10, typename x11, typename x12, typename x13, typename x14
#define typename_15(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15)      typename x , typename x2, typename x3, typename x4, typename x5, typename x6, typename x7, typename x8, typename x9, typename x10, typename x11, typename x12, typename x13, typename x14, typename x15
#define typename_16(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) typename x , typename x2, typename x3, typename x4, typename x5, typename x6, typename x7, typename x8, typename x9, typename x10, typename x11, typename x12, typename x13, typename x14, typename x15, typename x16

    // turn: a, b, ...c
    // into: typename a, typename b, typename ...c
#define typenames_count(count, ...) EXPAND(CONCAT(typename_, count)(__VA_ARGS__))
#define typenames(...) EXPAND(CONCAT(typename_, NARGS(__VA_ARGS__))(__VA_ARGS__))

#define COMBINE_SFINAE(name, predicate, templateArgs...)                                                                \
    template<typenames(CAT_PREFIX(_, templateArgs))>                                                                    \
    struct name                                                                                                         \
    {                                                                                                                   \
    private:                                                                                                            \
        template<typenames(templateArgs)>                                                                               \
        static constexpr auto check(void*)                                                                              \
            -> typename std::conditional<predicate, std::true_type, std::false_type>::type;                             \
                                                                                                                        \
        template <typename>                                                                                             \
        static constexpr auto check(...)                                                                                \
            ->std::false_type;                                                                                          \
                                                                                                                        \
        typedef decltype(check<EXPAND(CAT_PREFIX(_, templateArgs))>(nullptr)) type;                                     \
    public:                                                                                                             \
        static constexpr bool value = type::value;                                                                      \
    };                                                                                                                  \
                                                                                                                        \
    template<EXPAND(typenames(EXPAND(templateArgs)))>                                                                   \
    constexpr bool CONCAT(name, _v) = name<EXPAND(templateArgs)>::value;

    HAS_FUNC(begin);
    HAS_FUNC(end);

    COMBINE_SFINAE(is_container, has_begin_v<T L_COMMA typename T::iterator(void)>&& has_end_v<T L_COMMA typename T::iterator(void)>, T);

    HAS_FUNC(resize);

    COMBINE_SFINAE(is_resizable_container, has_begin_v<T L_COMMA typename T::iterator(void)>&& has_end_v<T L_COMMA typename T::iterator(void)>&& has_resize_v<T L_COMMA void(rsl::size_type)>, T);

    HAS_FUNC(setup);
    HAS_FUNC(shutdown);
    HAS_FUNC(update);

    template<typename derived_type, typename base_type>
    using inherits_from = typename std::enable_if<std::is_base_of<base_type, derived_type>::value, int>::type;

    template<typename derived_type, typename base_type>
    using doesnt_inherit_from = typename std::enable_if<!std::is_base_of<base_type, derived_type>::value, int>::type;

    template<typename T>
    using remove_cvr = std::remove_cv<std::remove_reference_t<T>>;

    template<typename T>
    using remove_cvr_t = typename remove_cvr<T>::type;

    template <class T>
    struct is_vector
        : public std::false_type
    {
    };

    template <class T>
    struct is_vector<std::vector<T>>
        : public std::true_type
    {
    };

    template<template<typename...>typename T, typename U, rsl::size_type I, typename... Args>
    struct make_sequence
#if !defined(DOXY_EXCLUDE)
        : make_sequence<T, U, I - 1, Args..., U>{};

    template<template<typename...>typename T, typename U, typename... Args>
    struct make_sequence<T, U, 0, Args...>
#endif
    {
        using type = T<Args...>;
    };

    template<template<typename...>typename T, typename U, rsl::size_type I, typename... Args>
    using make_sequence_t = typename make_sequence<T, U, I, Args...>::type;

    template<template<typename>typename Compare, typename T, T A, T B>
    struct do_compare
    {
        static constexpr inline Compare<T> comp{};
        static constexpr inline bool value = comp(A, B);
    };

    template<template<typename>typename Compare, typename T, T A, T B>
    inline constexpr bool do_compare_v = do_compare<Compare, T, A, B>::value;

    template<rsl::size_type I, typename Type, typename... Types>
    struct element_at
#if !defined(DOXY_EXCLUDE)
        : element_at<I - 1, Types...>
    {
    };

    template<typename Type, typename... Types>
    struct element_at<0, Type, Types...>
#endif
    {
        using type = Type;
    };

    template<rsl::size_type I, typename Type, typename... Types>
    using element_at_t = typename element_at<I, Type, Types...>::type;

    template<typename T, typename... Args>
    struct is_brace_constructible
    {
    private:
        template<typename _T, typename... _Args>
        static constexpr auto check(void*)
            -> decltype(void(_T{ std::declval<_Args>()... }), std::true_type());

        template <typename...>
        static constexpr auto check(...)
            -> std::false_type;

        using type = decltype(check<T, Args...>(nullptr));
    public:
        static constexpr bool value = type::value;
    };


    template<class T, typename... Args>
    inline constexpr bool is_brace_constructible_v = is_brace_constructible<T, Args...>::value;
}
