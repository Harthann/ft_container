#ifndef SFINAE_TEMPLATE_HPP
#define SFINAE_TEMPLATE_HPP

namespace ft {

	template <bool B, class T = void>
	struct enable_if {};

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
	template <>
	struct is_integral<unsigned char> {static const bool value = true; };
	template <>
	struct is_integral<unsigned short> {static const bool value = true; };
	template <>
	struct is_integral<unsigned int> {static const bool value = true; };
	template <>
	struct is_integral<unsigned long> {static const bool value = true; };
	template <>
	struct is_integral<unsigned long long> {static const bool value = true; };


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

}

#endif

