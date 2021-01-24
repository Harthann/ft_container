#include "vector.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <stdlib.h>

typedef int my_type;

#define STL_OUTPUT "outputs/vector/stl_vector_output"
#define FT_OUTPUT "outputs/vector/ft_vector_output"

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
void	print_container(T start, T end, std::ofstream &output)
{
	while (start != end) {
		output << *start;
		start++;
		if (start != end)
			output << " : ";
	}
	output << "\n";
}

template <class T>
void	test_capacity(T& vec, std::ofstream& output)
{

	output << "======\tCAPACITY\t======\n";
	print_container(vec.begin(), vec.end(), output);
	output << "The vector class size is : " << vec.size() << std::endl;
	output << "And his capacity : " << vec.capacity() << std::endl;
	output << "So vec start empty : " << vec.empty() << std::endl;
	for (int i = 0; i < 10; i++)
		vec.push_back(i);
	output << "Added value from 0 to 10 using pushback\n";
	print_container(vec.begin(), vec.end(), output);
	output << "Size now : " << vec.size() << " and capacity : " << vec.capacity() << std::endl;
	output << "So vec empty : " << vec.empty() << std::endl;

	//#################################
	//###		RESERVE TEST		###
	//#################################

	output << "\t== Reserve 20 ==\n";
	vec.reserve(20);
	output << "Size now : " << vec.size() << " and capacity : " << vec.capacity() << std::endl;
	output << "\t== Reserve 5 ==\n";
	vec.reserve(5);
	output << "Size now : " << vec.size() << " and capacity : " << vec.capacity() << std::endl;
	print_container(vec.begin(), vec.end(), output);
	output << "\t== Reserve -5 ==\n";
	try {
		vec.reserve(-5);
	}
	catch (std::length_error& error) {
		output << error.what() << std::endl;
	}
	output << "Size now : " << vec.size() << " and capacity : " << vec.capacity() << std::endl;
	print_container(vec.begin(), vec.end(), output);
}

void test_vector(void)
{
	ft::vector<my_type, test_alloc_red<my_type> > ft;
	std::vector<my_type, test_alloc_green<my_type> > stl;
	std::ofstream stl_output;
	std::ofstream ft_output;
	
	//#################################
	//###		OPENING OUTPUT		###
	//#################################

	stl_output.open(STL_OUTPUT);
	ft_output.open(FT_OUTPUT);

	//#################################
	//###		CAPACITY			###
	//#################################

	test_capacity(stl, stl_output);
	test_capacity(ft, ft_output);

	//#####################################
	//###		SEARCHING FOR DIFF		###
	//#####################################

	system ("diff outputs/vector/ft_vector_output outputs/vector/stl_vector_output > outputs/vector/diff_results");
}