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
	
	vec.resize(5);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << std::endl;
	std::cout << std::vector<int>::value_type();
	return (0);
}