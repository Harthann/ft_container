// #include "base_iterator.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>

//#include "Vector.hpp"
#include "sfinae_template.hpp"
#include "ft_iterator.hpp"
#include "base_iterator.hpp"
#include "Vector_iterator.hpp"

// template <class T>
// class false_it
// {
// 	public:

// 		false_it() : ptr(0) {};
// 		typedef T	value_type;
// 		typedef value_type*	pointer;
// 		typedef value_type&	reference;
// 		typedef std::ptrdiff_t		difference_type;
// 		typedef ft::input_iterator_tag iterator_category;

// 		T*	ptr;

// 		bool operator!=(false_it &itl) { return (itl.ptr != this->ptr); };

// 		false_it &operator++() { ptr++; return (*this);}
// 		false_it &operator++(int) { false_it tmp(*this); ptr++; return (tmp);}
// 		false_it &operator--() { return (*this);}
// 		false_it &operator--(int) { return (*this);}

// 		reference operator*() const { return (*ptr); };
// };

int main(void)
{
	std::vector<int> vec;
	int array[] = {1, 2, 3, 4, 5, 6, 7};
	std::vector<int>::iterator it;
	it->m;
	//is_input_it(input_it);
	return (0);
}
