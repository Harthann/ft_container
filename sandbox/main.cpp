// #include "base_iterator.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "Vector.hpp"
#include "base_iterator.hpp"
#include "Vector_iterator.hpp"


template <class T>
class false_it
{
	public:

		typedef T	value_type;
		typedef value_type*	pointer;
		typedef value_type&	reference;
		typedef std::ptrdiff_t		difference_type;
		typedef std::input_iterator_tag iterator_category;

		T*	ptr;

		bool operator!=(false_it &itl) { return (itl.ptr != this->ptr); };

		false_it &operator++() { return (*this);}
		false_it &operator++(int) { return (*this);}
		false_it &operator--() { return (*this);}
		false_it &operator--(int) { return (*this);}

		reference operator*() const { return (*ptr); };
};

int main(void)
{
	ft::vector<int> vec;

	false_it<int> false_ite;
	false_it<int> false_its;
	vec.insert(vec.begin(), false_its, false_ite);

	//is_input_it(input_it);
	return (0);
}
