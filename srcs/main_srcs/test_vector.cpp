#include "vector.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <stdlib.h>

typedef int my_type;

template <class T>
struct test_alloc_green : std::allocator<T> {
	T *allocate(size_t size) {
		std::cout << "\033[0;32mAllocate request of size : " << size << std::endl;
		std::cout << "\033[0m";
		return (new T[size]);
	}
	void deallocate(T *ptr, size_t size) {
		std::cout << "\033[0;32mDeallocation request of size : " << size << std::endl;
		std::cout << "\033[0m";
		delete ptr;
	}
};

template <class T>
struct test_alloc_red : std::allocator<T> {
	T *allocate(size_t size) {
		std::cout << "\033[31mAllocate request of size : " << size << std::endl;
		std::cout << "\033[0m";
		std::cout << "\033[0m";
		return (new T[size]);
	}
	void deallocate(T *ptr, size_t size) {
		std::cout << "\033[31mDeallocation request of size : " << size << std::endl;
		std::cout << "\033[0m";
		delete ptr;
	}
};

template <class T>
void	print_container(T start, T end, const std::string str, std::ofstream &output)
{
	std::string tmp(str);

	while (start != end) {
		output << *start;
		if (start != end)
			output << " : ";
		start++;
	}
	output << "\n";
}

void test_vector(void)
{
	ft::vector<my_type, test_alloc_red<my_type> > ft;
	std::vector<my_type, test_alloc_green<my_type> > stl;

	std::vector<my_type> to_insert;
	ft::vector<my_type> to_insert2;

	// test_exec(stl, to_insert, "outputs/vector/stl_vector_output");

	// test_exec(ft, to_insert2,"outputs/vector/ft_vector_output");
	system ("diff outputs/vector/ft_vector_output outputs/vector/stl_vector_output > outputs/vector/diff_results");
}