// #include "base_iterator.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <list>

namespace ft {

template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> { typedef T type; } ;

template <typename T, typename U>
struct is_same { static const bool value = false ; };

template <typename T>
struct is_same<T,T> { static const bool value = true; } ;

template <class T>
struct my_input_it {
	typedef std::input_iterator_tag iterator_category;
};

template <class T>
struct my_it {
	typedef std::output_iterator_tag iterator_category;
};

template <class InputIT>
void	is_input_it(InputIT its, InputIT ite)
{
//	typename enable_if<is_same<typename InputIT::iterator_category, std::input_iterator_tag>::value, InputIT>::type it;
	std::cout << "Is input it\n";
}

void	is_input_it(int a, int b)
{
	(void)a;
	(void)b;
	std::cout << "Isn't input it\n";
}

}

int main(void)
{
	std::vector<int> vec;
	std::vector<int>::iterator input_its;
	std::vector<int>::iterator input_ite;
//	is_input_it(input_its, input_ite);
//	is_input_it(5, 9);
	if (ft::is_same<typename std::iterator_traits<std::vector<int>::iterator>::iterator_category, std::random_access_iterator_tag>::value)
		std::cout << "is input iterator\n";

	//is_input_it(input_it);
	return (0);
}
