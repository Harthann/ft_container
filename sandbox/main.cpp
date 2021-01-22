// #include "base_iterator.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <list>

namespace Alpha {
template <class T>
class A
{
	public:
		typedef int my_type;
};
}

template <class T>
class B
{
	public:
		typedef T my_class;
		typedef typename my_class::my_type my_type;
};

class C
{
	public:
};


int main(void)
{
	std::vector<int> vec;
	std::vector<int>::size_type i = -1;

	try {
	vec.resize(i);
	}
	catch (const std::length_error& e){
		std::cout << e.what();
	}
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << std::endl;
	return (0);
}