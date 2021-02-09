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


template <class T = void, bool B = !ft::is_arithmetic<T>::value >
struct is_input_iterator {};

template <class T>
struct is_input_iterator<T, true> {
	static const bool value =ft::is_same<typename T::iterator_category, std::input_iterator_tag>::value ||
		ft::is_same<typename T::iterator_category, std::forward_iterator_tag>::value ||
		ft::is_same<typename T::iterator_category, std::bidirectional_iterator_tag>::value ||
		ft::is_same<typename T::iterator_category, std::random_access_iterator_tag>::value;
};


}

#endif

