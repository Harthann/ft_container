// #include "base_iterator.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <list>


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

namespace ft {

template <class It>
struct iterator_trait<It> {
	typedef It::value_type value_type;
	typedef It::difference_type difference_type;
	typedef It::pointer pointer;
	typedef It::reference reference;
	typedef It::iterator_category iterator_category;
};

template <class It>
struct is_iterator {static const bool value = false; };

}

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


int main(void)
{
	std::vector<int> vec;
	std::vector<int>::iterator input_its;
	std::vector<int>::iterator input_ite;
//	is_input_it(input_its, input_ite);
//	is_input_it(5, 9);
	if (ft::iterator_trait<typename std::vector<int>::iterator>::value)
		std::cout << "is input iterator\n";
	if (ft::iterator_trait<typename std::vector<int>::iterator>::value)
		std::cout << "is input iterator\n";

	//is_input_it(input_it);
	return (0);
}
