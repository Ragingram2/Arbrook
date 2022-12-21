#pragma once
/**
 * @file platform.hpp
 */

#pragma region //////////////////////////////////////// Utils ///////////////////////////////////////////

#if !defined(PROJECT_NAME)
#   define PROJECT_NAME user_project
#endif

#define L_COMMA ,

#define EXPAND(x) x
#define CALL(x, y) x(y)

#define NARGS_(_1, _2, _3, _4, _5 , _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, N, ...) N
#define NARGS(...) EXPAND(NARGS_(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))

#define _CONCAT_IMPL_(A, B) A ## B

#define CONCAT(A, B) _CONCAT_IMPL_(A, B)

#define STRINGIFY_IMPL(x) #x
#define STRINGIFY(x) STRINGIFY_IMPL(x)

#define  R_NAME_1(x)                                                                    #x
#define  R_NAME_2(x, x2)                                                                #x , #x2
#define  R_NAME_3(x, x2, x3)                                                            #x , #x2 , #x3
#define  R_NAME_4(x, x2, x3, x4)                                                        #x , #x2 , #x3 , #x4
#define  R_NAME_5(x, x2, x3, x4, x5)                                                    #x , #x2 , #x3 , #x4 , #x5
#define  R_NAME_6(x, x2, x3, x4, x5, x6)                                                #x , #x2 , #x3 , #x4 , #x5 , #x6
#define  R_NAME_7(x, x2, x3, x4, x5, x6, x7)                                            #x , #x2 , #x3 , #x4 , #x5 , #x6 , #x7
#define  R_NAME_8(x, x2, x3, x4, x5, x6, x7, x8)                                        #x , #x2 , #x3 , #x4 , #x5 , #x6 , #x7 , #x8
#define  R_NAME_9(x, x2, x3, x4, x5, x6, x7, x8, x9)                                    #x , #x2 , #x3 , #x4 , #x5 , #x6 , #x7 , #x8 , #x9
#define R_NAME_10(x, x2, x3, x4, x5, x6, x7, x8, x9, x10)                               #x , #x2 , #x3 , #x4 , #x5 , #x6 , #x7 , #x8 , #x9 , #x10
#define R_NAME_11(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11)                          #x , #x2 , #x3 , #x4 , #x5 , #x6 , #x7 , #x8 , #x9 , #x10 , #x11
#define R_NAME_12(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12)                     #x , #x2 , #x3 , #x4 , #x5 , #x6 , #x7 , #x8 , #x9 , #x10 , #x11 , #x12
#define R_NAME_13(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13)                #x , #x2 , #x3 , #x4 , #x5 , #x6 , #x7 , #x8 , #x9 , #x10 , #x11 , #x12 , #x13
#define R_NAME_14(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14)           #x , #x2 , #x3 , #x4 , #x5 , #x6 , #x7 , #x8 , #x9 , #x10 , #x11 , #x12 , #x13 , #x14
#define R_NAME_15(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15)      #x , #x2 , #x3 , #x4 , #x5 , #x6 , #x7 , #x8 , #x9 , #x10 , #x11 , #x12 , #x13 , #x14 , #x15
#define R_NAME_16(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) #x , #x2 , #x3 , #x4 , #x5 , #x6 , #x7 , #x8 , #x9 , #x10 , #x11 , #x12 , #x13 , #x14 , #x15 , #x16

 // turn: value0, value1, value2
 // into: "value0", "value1", "value2"
#define STRINGIFY_SEPERATE(...) EXPAND(CONCAT(L_NAME_, NARGS(__VA_ARGS__))(__VA_ARGS__))

#define  pre_1(prefix, x)                                                                    prefix##x
#define  pre_2(prefix, x, x2)                                                                prefix##x , prefix##x2
#define  pre_3(prefix, x, x2, x3)                                                            prefix##x , prefix##x2, prefix##x3
#define  pre_4(prefix, x, x2, x3, x4)                                                        prefix##x , prefix##x2, prefix##x3, prefix##x4
#define  pre_5(prefix, x, x2, x3, x4, x5)                                                    prefix##x , prefix##x2, prefix##x3, prefix##x4, prefix##x5
#define  pre_6(prefix, x, x2, x3, x4, x5, x6)                                                prefix##x , prefix##x2, prefix##x3, prefix##x4, prefix##x5, prefix##x6
#define  pre_7(prefix, x, x2, x3, x4, x5, x6, x7)                                            prefix##x , prefix##x2, prefix##x3, prefix##x4, prefix##x5, prefix##x6, prefix##x7
#define  pre_8(prefix, x, x2, x3, x4, x5, x6, x7, x8)                                        prefix##x , prefix##x2, prefix##x3, prefix##x4, prefix##x5, prefix##x6, prefix##x7, prefix##x8
#define  pre_9(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9)                                    prefix##x , prefix##x2, prefix##x3, prefix##x4, prefix##x5, prefix##x6, prefix##x7, prefix##x8, prefix##x9
#define pre_10(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10)                               prefix##x , prefix##x2, prefix##x3, prefix##x4, prefix##x5, prefix##x6, prefix##x7, prefix##x8, prefix##x9, prefix##x10
#define pre_11(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11)                          prefix##x , prefix##x2, prefix##x3, prefix##x4, prefix##x5, prefix##x6, prefix##x7, prefix##x8, prefix##x9, prefix##x10, prefix##x11
#define pre_12(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12)                     prefix##x , prefix##x2, prefix##x3, prefix##x4, prefix##x5, prefix##x6, prefix##x7, prefix##x8, prefix##x9, prefix##x10, prefix##x11, prefix##x12
#define pre_13(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13)                prefix##x , prefix##x2, prefix##x3, prefix##x4, prefix##x5, prefix##x6, prefix##x7, prefix##x8, prefix##x9, prefix##x10, prefix##x11, prefix##x12, prefix##x13
#define pre_14(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14)           prefix##x , prefix##x2, prefix##x3, prefix##x4, prefix##x5, prefix##x6, prefix##x7, prefix##x8, prefix##x9, prefix##x10, prefix##x11, prefix##x12, prefix##x13, prefix##x14
#define pre_15(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15)      prefix##x , prefix##x2, prefix##x3, prefix##x4, prefix##x5, prefix##x6, prefix##x7, prefix##x8, prefix##x9, prefix##x10, prefix##x11, prefix##x12, prefix##x13, prefix##x14, prefix##x15
#define pre_16(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) prefix##x , prefix##x2, prefix##x3, prefix##x4, prefix##x5, prefix##x6, prefix##x7, prefix##x8, prefix##x9, prefix##x10, prefix##x11, prefix##x12, prefix##x13, prefix##x14, prefix##x15, prefix##x16

#define prepost_1(prefix, postfix, x)                             CAT(prefix##x, postfix)
#define prepost_2(prefix, postfix, x, x2)                         CAT(prefix##x, postfix) , CAT(prefix##x2, postfix)
#define prepost_3(prefix, postfix, x, x2, x3)                     CAT(prefix##x, postfix) , CAT(prefix##x2, postfix), CAT(prefix##x3, postfix)
#define prepost_4(prefix, postfix, x, x2, x3, x4)                 CAT(prefix##x, postfix) , CAT(prefix##x2, postfix), CAT(prefix##x3, postfix), CAT(prefix##x4, postfix)
#define prepost_5(prefix, postfix, x, x2, x3, x4, x5)             CAT(prefix##x, postfix) , CAT(prefix##x2, postfix), CAT(prefix##x3, postfix), CAT(prefix##x4, postfix), CAT(prefix##x5, postfix)
#define prepost_6(prefix, postfix, x, x2, x3, x4, x5, x6)         CAT(prefix##x, postfix) , CAT(prefix##x2, postfix), CAT(prefix##x3, postfix), CAT(prefix##x4, postfix), CAT(prefix##x5, postfix), CAT(prefix##x6, postfix)
#define prepost_7(prefix, postfix, x, x2, x3, x4, x5, x6, x7)     CAT(prefix##x, postfix) , CAT(prefix##x2, postfix), CAT(prefix##x3, postfix), CAT(prefix##x4, postfix), CAT(prefix##x5, postfix), CAT(prefix##x6, postfix), CAT(prefix##x7, postfix)
#define prepost_8(prefix, postfix, x, x2, x3, x4, x5, x6, x7, x8) CAT(prefix##x, postfix) , CAT(prefix##x2, postfix), CAT(prefix##x3, postfix), CAT(prefix##x4, postfix), CAT(prefix##x5, postfix), CAT(prefix##x6, postfix), CAT(prefix##x7, postfix), CAT(prefix##x8, postfix)

#define  decltype_1(x)                                                                    decltype(x)
#define  decltype_2(x, x2)                                                                decltype(x) , decltype(x2)
#define  decltype_3(x, x2, x3)                                                            decltype(x) , decltype(x2), decltype(x3)
#define  decltype_4(x, x2, x3, x4)                                                        decltype(x) , decltype(x2), decltype(x3), decltype(x4)
#define  decltype_5(x, x2, x3, x4, x5)                                                    decltype(x) , decltype(x2), decltype(x3), decltype(x4), decltype(x5)
#define  decltype_6(x, x2, x3, x4, x5, x6)                                                decltype(x) , decltype(x2), decltype(x3), decltype(x4), decltype(x5), decltype(x6)
#define  decltype_7(x, x2, x3, x4, x5, x6, x7)                                            decltype(x) , decltype(x2), decltype(x3), decltype(x4), decltype(x5), decltype(x6), decltype(x7)
#define  decltype_8(x, x2, x3, x4, x5, x6, x7, x8)                                        decltype(x) , decltype(x2), decltype(x3), decltype(x4), decltype(x5), decltype(x6), decltype(x7), decltype(x8)
#define  decltype_9(x, x2, x3, x4, x5, x6, x7, x8, x9)                                    decltype(x) , decltype(x2), decltype(x3), decltype(x4), decltype(x5), decltype(x6), decltype(x7), decltype(x8), decltype(x9)
#define decltype_10(x, x2, x3, x4, x5, x6, x7, x8, x9, x10)                               decltype(x) , decltype(x2), decltype(x3), decltype(x4), decltype(x5), decltype(x6), decltype(x7), decltype(x8), decltype(x9) , decltype(x10)
#define decltype_11(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11)                          decltype(x) , decltype(x2), decltype(x3), decltype(x4), decltype(x5), decltype(x6), decltype(x7), decltype(x8), decltype(x9) , decltype(x10), decltype(x11)
#define decltype_12(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12)                     decltype(x) , decltype(x2), decltype(x3), decltype(x4), decltype(x5), decltype(x6), decltype(x7), decltype(x8), decltype(x9) , decltype(x10), decltype(x11), decltype(x12)
#define decltype_13(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13)                decltype(x) , decltype(x2), decltype(x3), decltype(x4), decltype(x5), decltype(x6), decltype(x7), decltype(x8), decltype(x9) , decltype(x10), decltype(x11), decltype(x12), decltype(x13)
#define decltype_14(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14)           decltype(x) , decltype(x2), decltype(x3), decltype(x4), decltype(x5), decltype(x6), decltype(x7), decltype(x8), decltype(x9) , decltype(x10), decltype(x11), decltype(x12), decltype(x13), decltype(x14)
#define decltype_15(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15)      decltype(x) , decltype(x2), decltype(x3), decltype(x4), decltype(x5), decltype(x6), decltype(x7), decltype(x8), decltype(x9) , decltype(x10), decltype(x11), decltype(x12), decltype(x13), decltype(x14), decltype(x15)
#define decltype_16(x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) decltype(x) , decltype(x2), decltype(x3), decltype(x4), decltype(x5), decltype(x6), decltype(x7), decltype(x8), decltype(x9) , decltype(x10), decltype(x11), decltype(x12), decltype(x13), decltype(x14), decltype(x15), decltype(x16)

#define  colon_1(prefix, x)                                                                    prefix::x
#define  colon_2(prefix, x, x2)                                                                prefix::x , prefix::x2
#define  colon_3(prefix, x, x2, x3)                                                            prefix::x , prefix::x2, prefix::x3
#define  colon_4(prefix, x, x2, x3, x4)                                                        prefix::x , prefix::x2, prefix::x3, prefix::x4
#define  colon_5(prefix, x, x2, x3, x4, x5)                                                    prefix::x , prefix::x2, prefix::x3, prefix::x4, prefix::x5
#define  colon_6(prefix, x, x2, x3, x4, x5, x6)                                                prefix::x , prefix::x2, prefix::x3, prefix::x4, prefix::x5, prefix::x6
#define  colon_7(prefix, x, x2, x3, x4, x5, x6, x7)                                            prefix::x , prefix::x2, prefix::x3, prefix::x4, prefix::x5, prefix::x6, prefix::x7
#define  colon_8(prefix, x, x2, x3, x4, x5, x6, x7, x8)                                        prefix::x , prefix::x2, prefix::x3, prefix::x4, prefix::x5, prefix::x6, prefix::x7, prefix::x8
#define  colon_9(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9)                                    prefix::x , prefix::x2, prefix::x3, prefix::x4, prefix::x5, prefix::x6, prefix::x7, prefix::x8, prefix::x9
#define colon_10(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10)                               prefix::x , prefix::x2, prefix::x3, prefix::x4, prefix::x5, prefix::x6, prefix::x7, prefix::x8, prefix::x9, prefix::x10
#define colon_11(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11)                          prefix::x , prefix::x2, prefix::x3, prefix::x4, prefix::x5, prefix::x6, prefix::x7, prefix::x8, prefix::x9, prefix::x10, prefix::x11
#define colon_12(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12)                     prefix::x , prefix::x2, prefix::x3, prefix::x4, prefix::x5, prefix::x6, prefix::x7, prefix::x8, prefix::x9, prefix::x10, prefix::x11, prefix::x12
#define colon_13(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13)                prefix::x , prefix::x2, prefix::x3, prefix::x4, prefix::x5, prefix::x6, prefix::x7, prefix::x8, prefix::x9, prefix::x10, prefix::x11, prefix::x12, prefix::x13
#define colon_14(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14)           prefix::x , prefix::x2, prefix::x3, prefix::x4, prefix::x5, prefix::x6, prefix::x7, prefix::x8, prefix::x9, prefix::x10, prefix::x11, prefix::x12, prefix::x13, prefix::x14
#define colon_15(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15)      prefix::x , prefix::x2, prefix::x3, prefix::x4, prefix::x5, prefix::x6, prefix::x7, prefix::x8, prefix::x9, prefix::x10, prefix::x11, prefix::x12, prefix::x13, prefix::x14, prefix::x15
#define colon_16(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) prefix::x , prefix::x2, prefix::x3, prefix::x4, prefix::x5, prefix::x6, prefix::x7, prefix::x8, prefix::x9, prefix::x10, prefix::x11, prefix::x12, prefix::x13, prefix::x14, prefix::x15, prefix::x16

#define  dot_1(prefix, x)                                                                    prefix.x
#define  dot_2(prefix, x, x2)                                                                prefix.x , prefix.x2
#define  dot_3(prefix, x, x2, x3)                                                            prefix.x , prefix.x2, prefix.x3
#define  dot_4(prefix, x, x2, x3, x4)                                                        prefix.x , prefix.x2, prefix.x3, prefix.x4
#define  dot_5(prefix, x, x2, x3, x4, x5)                                                    prefix.x , prefix.x2, prefix.x3, prefix.x4, prefix.x5
#define  dot_6(prefix, x, x2, x3, x4, x5, x6)                                                prefix.x , prefix.x2, prefix.x3, prefix.x4, prefix.x5, prefix.x6
#define  dot_7(prefix, x, x2, x3, x4, x5, x6, x7)                                            prefix.x , prefix.x2, prefix.x3, prefix.x4, prefix.x5, prefix.x6, prefix.x7
#define  dot_8(prefix, x, x2, x3, x4, x5, x6, x7, x8)                                        prefix.x , prefix.x2, prefix.x3, prefix.x4, prefix.x5, prefix.x6, prefix.x7, prefix.x8
#define  dot_9(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9)                                    prefix.x , prefix.x2, prefix.x3, prefix.x4, prefix.x5, prefix.x6, prefix.x7, prefix.x8, prefix.x9
#define dot_10(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10)                               prefix.x , prefix.x2, prefix.x3, prefix.x4, prefix.x5, prefix.x6, prefix.x7, prefix.x8, prefix.x9, prefix.x10
#define dot_11(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11)                          prefix.x , prefix.x2, prefix.x3, prefix.x4, prefix.x5, prefix.x6, prefix.x7, prefix.x8, prefix.x9, prefix.x10, prefix.x11
#define dot_12(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12)                     prefix.x , prefix.x2, prefix.x3, prefix.x4, prefix.x5, prefix.x6, prefix.x7, prefix.x8, prefix.x9, prefix.x10, prefix.x11, prefix.x12
#define dot_13(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13)                prefix.x , prefix.x2, prefix.x3, prefix.x4, prefix.x5, prefix.x6, prefix.x7, prefix.x8, prefix.x9, prefix.x10, prefix.x11, prefix.x12, prefix.x13
#define dot_14(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14)           prefix.x , prefix.x2, prefix.x3, prefix.x4, prefix.x5, prefix.x6, prefix.x7, prefix.x8, prefix.x9, prefix.x10, prefix.x11, prefix.x12, prefix.x13, prefix.x14
#define dot_15(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15)      prefix.x , prefix.x2, prefix.x3, prefix.x4, prefix.x5, prefix.x6, prefix.x7, prefix.x8, prefix.x9, prefix.x10, prefix.x11, prefix.x12, prefix.x13, prefix.x14, prefix.x15
#define dot_16(prefix, x, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) prefix.x , prefix.x2, prefix.x3, prefix.x4, prefix.x5, prefix.x6, prefix.x7, prefix.x8, prefix.x9, prefix.x10, prefix.x11, prefix.x12, prefix.x13, prefix.x14, prefix.x15, prefix.x16

 // turn: value, 0, 1, 2
 // into: value0, value1, value2
#define CAT_PREFIX(prefix, ...) EXPAND(CONCAT(pre_, NARGS(__VA_ARGS__))(prefix, __VA_ARGS__))

// turn: value, p, 0, 1, 2
// into: value0p, value1p, value2p
#define CAT_PREPOSTFIX(prefix, postfix, ...) EXPAND(CONCAT(prepost_, NARGS(__VA_ARGS__))(prefix, postfix, __VA_ARGS__))

// turn: 0, 1, 2
// into: decltype(0), decltype(1), decltype(2)
#define decltypes_count(count, ...) EXPAND(CONCAT(decltype_, count)(__VA_ARGS__))
#define decltypes(...) EXPAND(CONCAT(decltype_, NARGS(__VA_ARGS__))(__VA_ARGS__))

// turn: Foo, x, y, z
// into: Foo::x, Foo::y, Foo::z
#define colon_access_count(count, prefix, ...) EXPAND(CONCAT(colon_, count)(prefix, __VA_ARGS__))
#define colon_access(prefix, ...) EXPAND(CONCAT(colon_, NARGS(__VA_ARGS__))(prefix, __VA_ARGS__))

// turn: foo, x, y, z
// into: foo.x, foo.y, foo.z
#define dot_access_count(count, prefix, ...) EXPAND(CONCAT(dot_, count)(prefix, __VA_ARGS__))
#define dot_access(prefix, ...) EXPAND(CONCAT(dot_, NARGS(__VA_ARGS__))(prefix, __VA_ARGS__))

#define RULE_OF_5(type)\
type() = default;\
type(const type&) = default;\
type(type&&) = default;\
type& operator=(const type&) = default;\
type& operator=(type&&) = default;\
~type() = default;

#define RULE_OF_5_NOEXCEPT(type)\
type() noexcept = default;\
type(const type&) noexcept = default;\
type(type&&) noexcept = default;\
type& operator=(const type&) noexcept = default;\
type& operator=(type&&) noexcept = default;\
~type() = default;

#define NO_DEF_CTOR_RULE5(type)\
type(const type&) = default;\
type(type&&) = default;\
type& operator=(const type&) = default;\
type& operator=(type&&) = default;\
~type() = default;

#define NO_DEF_CTOR_RULE5_NOEXCEPT(type)\
type(const type&) noexcept = default;\
type(type&&) noexcept = default;\
type& operator=(const type&) noexcept = default;\
type& operator=(type&&) noexcept = default;\
~type() = default;

#define NO_DTOR_RULE5(type)\
type() = default;\
type(const type&) = default;\
type(type&&) = default;\
type& operator=(const type&) = default;\
type& operator=(type&&) = default;

#define NO_DTOR_RULE5_NOEXCEPT(type)\
type() noexcept = default;\
type(const type&) noexcept = default;\
type(type&&) noexcept = default;\
type& operator=(const type&) noexcept = default;\
type& operator=(type&&) noexcept = default;

#define COPY_FUNCS(type)\
type(const type&) = default;\
type& operator=(const type&) = default;

#define COPY_FUNCS_NOEXCEPT(type)\
type(const type&) noexcept = default;\
type& operator=(const type&) noexcept = default;

#define MOVE_FUNCS(type)\
type(type&&) = default;\
type& operator=(type&&) = default;

#define MOVE_FUNCS_NOEXCEPT(type)\
type(type&&) noexcept = default;\
type& operator=(type&&) noexcept = default;

#define RYTHE_DEBUG_VALUE 1
#define RYTHE_RELEASE_VALUE 2

#if defined(DOXY_EXCLUDE)
#   define NDOXY(...)
#   define CNDOXY(...)
#else
#   define NDOXY(args...) args
#   define CNDOXY(args...) , args
#endif

#if defined(_DEBUG) || defined(DEBUG)
    /**@def RYTHE_DEBUG
     * @brief Defined in debug mode.
     */
#   define RYTHE_DEBUG
#   define RYTHE_CONFIGURATION RYTHE_DEBUG_VALUE
#else
    /**@def RYTHE_RELEASE
     * @brief Defined in release mode.
     */
#   define RYTHE_RELEASE 
#   define RYTHE_CONFIGURATION RYTHE_RELEASE_VALUE
#endif

#if (!defined(RYTHE_LOW_POWER) && !defined(RYTHE_HIGH_PERFORMANCE))
     /**@def RYTHE_HIGH_PERFORMANCE
      * @brief Automatically defined if RYTHE_LOW_POWER was not defined. It makes Legion ask the hardware's full attention to run as fast as possible.
      * @note Define RYTHE_LOW_POWER to run Legion with minimal resources instead.
      */
#   define RYTHE_HIGH_PERFORMANCE
#endif

      /**@def RYTHE_PURE
       * @brief Marks a function as pure virtual.
       */
#define RYTHE_PURE =0

       /**@def RYTHE_IMPURE
        * @brief Marks a function as overridable but default implemented.
        */
#define RYTHE_IMPURE {}

        /**@def RYTHE_IMPURE_RETURN
         * @brief Marks a function as overridable but default implemented with certain default return value.
         * @param x value the function should return.
         */
#define RYTHE_IMPURE_RETURN(x) { return (x); }

#if !defined(RYTHE_MIN_THREADS)
#   define RYTHE_MIN_THREADS 2
#endif

#define ANONYMOUS_NAME(x) CONCAT(x, __LINE__)

#define ANON_VAR(Type, Category) inline static Type EXPAND(ANONYMOUS_NAME(Category))

#pragma endregion

#pragma region /////////////////////////////////// Operating system /////////////////////////////////////

#if defined(_WIN64)
         /**@def RYTHe_WINDOWS
          * @brief Defined when compiling for Windows.
          */
#   define RYTHE_WINDOWS

#   define WIN32_LEAN_AND_MEAN
#   define VC_EXTRALEAN
#   define NOMINMAX
#   include <Windows.h>
#   include <shellapi.h>
#   include <shlobj.h>
#   include <shlwapi.h>
#   include <objbase.h>
#elif defined(__linux__)
         /**@def RYTHE_LINUX
          * @brief Defined when compiling for Linux.
          */
#   define RYTHE_LINUX

#   include <sys/prctl.h>
#   include <sys/resource.h>
#   include <sys/types.h>
#   include <sys/wait.h>
#   include <unistd.h>
#   include <sched.h>
#   include <errno.h>
#endif

#pragma endregion

#pragma region //////////////////////////////////// Detect compiler /////////////////////////////////////

#if defined(__clang__)
          // clang
#   define RYTHE_CLANG
#   if defined(__GNUG__) || (defined(__GNUC__) && defined(__cplusplus))
#       define RYTHE_CLANG_GCC
#   elif defined(_MSC_VER)
#       define RYTHE_CLANG_MSVC
#   endif
#elif defined(__GNUG__) || (defined(__GNUC__) && defined(__cplusplus))
          // gcc
#   define RYTHE_GCC
#elif defined(_MSC_VER)
          // msvc
#   define RYTHE_MSVC
#endif

#pragma endregion

#pragma region ////////////////////////////////// Compiler specifics ////////////////////////////////////

#if defined(RYTHE_CLANG) || defined(RYTHE_GCC)
#   define R_NULLOP() asm volatile("nop");
#elif defined(RYTHE_MSVC)
#   include <intrin.h>
#   define R_NULLOP() __nop();
#else
#   define R_NULLOP() ;
#endif

#if defined(RYTHE_CLANG) || defined(RYTHE_GCC)
#   define R_PAUSE_INSTRUCTION __builtin_ia32_pause
#elif defined(RYTHE_MSVC)
#   define R_PAUSE_INSTRUCTION _mm_pause
#else
#   define R_PAUSE_INSTRUCTION L_NULLOP
#endif

#if !defined(__FULL_FUNC__)
#   if defined(RYTHE_CLANG) || defined(RYTHE_GCC)
#       define __FULL_FUNC__ __PRETTY_FUNCTION__
#   elif defined(RYTHE_MSVC)
#       define __FULL_FUNC__ __FUNCSIG__
#   else
#       define __FULL_FUNC__ __func__
#   endif
#endif

#if defined(RYTHE_CLANG)
#   define RYTHE_PRAGMA_TO_STR(x) _Pragma(#x)
#   define RYTHE_CLANG_SUPPRESS_WARNING_PUSH _Pragma("clang diagnostic push")
#   define RYTHE_CLANG_SUPPRESS_WARNING(w) RYTHE_PRAGMA_TO_STR(clang diagnostic ignored w)
#   define RYTHE_CLANG_SUPPRESS_WARNING_POP _Pragma("clang diagnostic pop")
#   define RYTHE_CLANG_SUPPRESS_WARNING_WITH_PUSH(w) RYTHE_CLANG_SUPPRESS_WARNING_PUSH RYTHE_CLANG_SUPPRESS_WARNING(w)
#else
#   define RYTHE_CLANG_SUPPRESS_WARNING_PUSH
#   define RYTHE_CLANG_SUPPRESS_WARNING(w)
#   define RYTHE_CLANG_SUPPRESS_WARNING_POP
#   define RYTHE_CLANG_SUPPRESS_WARNING_WITH_PUSH(w)
#endif

#if defined(LEGION_GCC)
#   define RYTHE_PRAGMA_TO_STR(x) _Pragma(#x)
#   define RYTHE_GCC_SUPPRESS_WARNING_PUSH _Pragma("GCC diagnostic push")
#   define RYTHE_GCC_SUPPRESS_WARNING(w) RYTHE_PRAGMA_TO_STR(GCC diagnostic ignored w)
#   define RYTHE_GCC_SUPPRESS_WARNING_POP _Pragma("GCC diagnostic pop")
#   define RYTHE_GCC_SUPPRESS_WARNING_WITH_PUSH(w) RYTHE_GCC_SUPPRESS_WARNING_PUSH RYTHE_GCC_SUPPRESS_WARNING(w)
#else
#   define RYTHE_GCC_SUPPRESS_WARNING_PUSH
#   define RYTHE_GCC_SUPPRESS_WARNING(w)
#   define RYTHE_GCC_SUPPRESS_WARNING_POP
#   define RYTHE_GCC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif

#if defined(RYTHE_MSVC)
#   define RYTHE_MSVC_SUPPRESS_WARNING_PUSH __pragma(warning(push))
#   define RYTHE_MSVC_SUPPRESS_WARNING(w) __pragma(warning(disable : w))
#   define RYTHE_MSVC_SUPPRESS_WARNING_POP __pragma(warning(pop))
#   define RYTHE_MSVC_SUPPRESS_WARNING_WITH_PUSH(w) RYTHE_MSVC_SUPPRESS_WARNING_PUSH RYTHE_MSVC_SUPPRESS_WARNING(w)
#else
#   define RYTHE_MSVC_SUPPRESS_WARNING_PUSH
#   define RYTHE_MSVC_SUPPRESS_WARNING(w)
#   define RYTHE_MSVC_SUPPRESS_WARNING_POP
#   define RYTHE_MSVC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif

#if defined (RYTHE_MSVC)
#   define R_WARNING(desc) __pragma(message(__FILE__ "(" STRINGIFY(__LINE__) ") : warning: " #desc))
#   define R_ERROR(desc) __pragma(message(__FILE__ "(" STRINGIFY(__LINE__) ") : error: " #desc))
#elif defined(RYTHE_GCC) || defined(RYTHE_CLANG)
#   define R_WARNING(desc) _Pragma(STRINGIFY(GCC warning desc))
#   define R_ERROR(desc) _Pragma(STRINGIFY(GCC error desc))
#endif


RYTHE_CLANG_SUPPRESS_WARNING("-Wdocumentation-unknown-command")
RYTHE_CLANG_SUPPRESS_WARNING("-Wdocumentation")
RYTHE_CLANG_SUPPRESS_WARNING("-Wextra-semi-stmt")
RYTHE_CLANG_SUPPRESS_WARNING("-Wextra-semi")
RYTHE_CLANG_SUPPRESS_WARNING("-Wunused-function")
RYTHE_CLANG_SUPPRESS_WARNING("-Wcovered-switch-default")
RYTHE_CLANG_SUPPRESS_WARNING("-Wexit-time-destructors")
RYTHE_CLANG_SUPPRESS_WARNING("-Wglobal-constructors")
RYTHE_CLANG_SUPPRESS_WARNING("-Wgnu-anonymous-struct")
RYTHE_CLANG_SUPPRESS_WARNING("-Wnested-anon-types")
RYTHE_CLANG_SUPPRESS_WARNING("-Wunused-macros")
RYTHE_CLANG_SUPPRESS_WARNING("-Wunused-member-function")
RYTHE_CLANG_SUPPRESS_WARNING("-Wc++98-c++11-c++14-compat")
RYTHE_CLANG_SUPPRESS_WARNING("-Wc++98-c++11-compat")
RYTHE_CLANG_SUPPRESS_WARNING("-Wc++98-compat-pedantic")
RYTHE_CLANG_SUPPRESS_WARNING("-Wc++98-compat")
RYTHE_CLANG_SUPPRESS_WARNING("-Wc++11-compat")
RYTHE_CLANG_SUPPRESS_WARNING("-Wc++14-compat")

RYTHE_GCC_SUPPRESS_WARNING("-Wc++11-compat")
RYTHE_GCC_SUPPRESS_WARNING("-Wc++14-compat")


#if defined(RYTHE_GCC) || defined(RYTHE_CLANG)
#   define R_ALWAYS_INLINE __attribute__((always_inline))
#elif defined(RYTHE_MSVC)
#   define R_ALWAYS_INLINE __forceinline
#else
#   define R_ALWAYS_INLINE
#endif

#if (defined(RYTHE_WINDOWS) && !defined(RYTHE_WINDOWS_USE_CDECL)) || defined(DOXY_INCLUDE)
/**@def RYTHE_CCONV
 * @brief the calling convention exported functions will use in the args engine
 */
#   define RYTHE_CCONV __fastcall
#elif defined(RYTHE_MSVC)
#   define RYTHE_CCONV __cdecl
#else
#   define RYTHE_CCONV
#endif

#pragma endregion

#pragma region ////////////////////////////////// Language convention ///////////////////////////////////

/**@def RYTHE_CPP17V
 * @brief the version number of c++17 as long
 */
#define RYTHE_CPP17V 201703L

 /**@def NO_MANGLING
  * @brief exports functions with C style names instead of C++ mangled names
  */
#define NO_MANGLING extern "C"

  /**@def RYTHE_FUNC
   * @brief export setting + calling convention used by the engine
   */
#define RYTHE_FUNC RYTHE_CCONV

   /**@def RYTHE_INTERFACE
    * @brief un-mangled function name +  export setting + calling convention used by the engine
    */
#define RYTHE_INTERFACE NO_MANGLING RYTHE_CCONV 

#if !defined(__FUNC__)
#   define __FUNC__ __func__ 
#endif

#pragma endregion

#pragma region ///////////////////////////////////// Attributes /////////////////////////////////////////

#if defined(__has_cpp_attribute) || defined(DOXY_INCLUDE) 
    /**@def R_HASCPPATTRIB
     * @brief checks if a certain attribute exists in this version of c++
     * @param x attribute you want to test for
     * @return true if attribute exists
     */
#   define R_HASCPPATTRIB(x) __has_cpp_attribute(x)
#else
#   define R_HASCPPATTRIB(x) 0
#endif

#if __cplusplus >= RYTHE_CPP17V || R_HASCPPATTRIB(fallthrough) || defined(DOXY_INCLUDE)
#   define R_FALLTHROUGH [[fallthrough]]
#else
#   define R_FALLTHROUGH
#endif

#if __cplusplus >= RYTHE_CPP17V || R_HASCPPATTRIB(maybe_unused) || defined(DOXY_INCLUDE)
    /**@def R_MAYBEUNUSED
     * @brief [[maybe_unused]]
     */
#   define R_MAYBEUNUSED [[maybe_unused]]
#else
#   define R_MAYBEUNUSED
#endif

#if __cplusplus >= RYTHE_CPP17V || R_HASCPPATTRIB(nodiscard) || defined(DOXY_INCLUDE)
    /**@def R_NODISCARD
     * @brief Marks a function as "nodiscard" meaning that result must be captured and should not be discarded.
     */
#   define R_NODISCARD [[nodiscard]]
#else
#   define R_NODISCARD
#endif

#if __cplusplus > RYTHE_CPP17V || R_HASCPPATTRIB(noreturn) || defined(DOXY_INCLUDE)
    /**@def R_NORETURN
     * @brief Marks a function as "noreturn" meaning that the function will never finish, or terminate the application
     */
#   define R_NORETURN [[noreturn]]
#else
#   define R_NORETURN
#endif

#pragma endregion