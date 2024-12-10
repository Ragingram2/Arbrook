#pragma once
#include <type_traits>

namespace rythe::core::common
{
	// Primary template
	template <typename T, typename U = int>
	struct has_m_owner : std::false_type { };

	// Specialization for U = int
	template <typename T>
	struct has_m_owner <T, decltype((void)T::m_owner, 0)> : std::true_type { };

	template<typename T>
	constexpr bool has_m_owner_v = has_m_owner<T>::value;

//#define HAS_MEMBER(x)                                                                                                                                    
//    template<typename T, typename = int>                                                                                                               
//    struct RYTHE_CONCAT(has_,x)                                                                                                                       
//    {                                                                                                                                                                         
//        static_assert(                                                                                                                                                
//            std::integral_constant<T, false>::value,                                                                                                      
//            "Second template parameter needs to be of function type.");                                                                   
//    };                                                                                                                                                                        
//    template<typename T>                                                                                                                                        
//    struct RYTHE_CONCAT(has_,x)<T, decltype((void) T:: x, 0)> {                                                                         
//    private:                                                                                                                                                              
//        template<typename T>                                                                                                                                    
//        static constexpr auto check(T*) -> std::true_type;                                                                                
//                                                                                                                                                                              
//        template<typename>                                                                                                                                       
//        static constexpr std::false_type check(...);                                                                                                   
//                                                                                                                                                                              
//        typedef decltype(check<T>(0)) type;                                                                                                             
//                                                                                                                                                                              
//    public:                                                                                                                                                                
//        static constexpr bool value = type::value;                                                                                                      
//    };                                                                                                                                                                        
//    template<typename T>                                                                                                                                        
//    constexpr bool RYTHE_CONCAT(has_, RYTHE_CONCAT(x, _v)) = RYTHE_CONCAT(has_, x) < T > ::value;     

}