#ifndef SFINAE_TEMPLATE_HPP
#define SFINAE_TEMPLATE_HPP

namespace ft {

template <bool B, class T = void>
struct enable_if {} ;

template <class T>
struct enable_if<true, T> {
	typedef void void_t;
	typedef T type;
};

template <bool B,class T = void>
struct is_const_if {
	typedef T value_type;
};

template <class T>
struct is_const_if<true, T> {
	typedef const T value_type;
};

template <typename T, typename U>
struct is_same { static const bool value = false; };

template <typename T>
struct is_same<T,T> { static const bool value = true; };

template <typename T>
struct is_integral { static const bool value = false; };

template <>
struct is_integral<bool> {static const bool value = true; };
template <>
struct is_integral<char> {static const bool value = true; };
template <>
struct is_integral<wchar_t> {static const bool value = true; };
template <>
struct is_integral<short> {static const bool value = true; };
template <>
struct is_integral<int> {static const bool value = true; };
template <>
struct is_integral<long> {static const bool value = true; };
template <>
struct is_integral<long long> {static const bool value = true; };

template <typename T>
struct is_floating {static const bool value = false; };

template <>
struct is_floating<float> { static const bool value = true; };
template <>
struct is_floating<double> { static const bool value = true; };
template <>
struct is_floating<long double> {static const bool value = true; };

template <typename T>
struct is_arithmetic { static const bool value = ft::is_floating<T>::value || ft::is_integral<T>::value; };

template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (*first1 < *first2) return true;
        if (*first2 < *first1) return false;
    }
    return (first1 == last1) && (first2 != last2);
}

template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2,
                             Compare comp)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (comp(*first1, *first2)) return true;
        if (comp(*first2, *first1)) return false;
    }
    return (first1 == last1) && (first2 != last2);
}

}

#endif

