#include "List.hpp"
// #include "Map.hpp"
// #include "Queue.hpp"
// #include "Stack.hpp"
// #include "Vector.hpp"
#include <list>
#include <string>
#include <vector>
#include <iostream>

template <typename T>
struct Myalloc : std::allocator<T> {
	T *allocate(size_t size) {
		std::cout << "Allocating memory size => " << size << std::endl;
		return (new T[size]);
	}
};

template <class T>
void init_list(T *test)
{
	test->push_front(50);
	test->push_front(45);
	test->push_back(2);
	test->push_back(445);
	test->push_back(56);
	test->push_back(4);
}

template <class T>
void print_list(T start, T end, const std::string str)
{
	std::cout << str;
	while (start != end)
	{
		std::cout << *start << " --> ";
		start++;
	}
	std::cout << "\n";
}

template < class T>
void test_const(T it, const std::string str)
{
	std::cout << str << std::endl;
	std::cout << "\tValue of *it : " << *it << std::endl;
	*it = 0;
	std::cout << "\tModified value of *it : " << *it << std::endl;
}

int main(void)
{
	ftc::List<int> my_list;
	std::list<int> real_list;

	init_list(&real_list);
	init_list(&my_list);

	print_list(real_list.begin(), real_list.end(), "STL : ");
	print_list(my_list.begin(), my_list.end(), "FTC : ");

	test_const(real_list.begin(), "STL : ");
	test_const(my_list.begin(), "FTC : ");

	std::list<int>::const_iterator it_start = real_list.begin();
	std::list<int>::const_iterator it_end = real_list.end();
	ftc::List<int>::const_iterator i_start = my_list.begin();
	ftc::List<int>::const_iterator i_end = my_list.end();
	print_list(it_start, it_end, "STL : ");
	// print_list(i_start, i_end, "FTC : ");
	// *it_start = 9;
	// *i_start = 9;
	// print_list(i_start, i_end, "FTC : ");


	return (0);
}