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


template < class T, class L >
void test_insert_vector(T &vec, T cpy, std::ofstream &output, L list)
{
	for (size_t i = 0; i < 25; i++)
		list.push_back(i);
	std::cout << "\n======INSERT NUMBER WITH SPECIFIC POSITION======\n";
	output << "\n======INSERT NUMBER WITH SPECIFIC POSITION======\n";
	vec.insert(vec.begin() + 3, 5);
	vec.insert(vec.begin() + 3, 5);
	vec.insert(vec.begin() + 3, 5);
	vec.insert(vec.begin() + 3, 5);
	print_container(vec.begin(), vec.end(), "Vector after insert : \n", output);
	output << "Container vec's capacity after insert is : " << vec.capacity() << std::endl;

	std::cout << "\n======INSERT WITH RANGE ELEMENTS FROM OTHER VEC======\n";
	output << "\n======INSERT WITH RANGE ELEMENTS FROM OTHER VEC======\n";
	print_container(vec.begin(), vec.end(), "Vector before insert : \n", output);
	print_container(cpy.begin(), cpy.end(), "Cpy to insert : \n", output);
	vec.insert(vec.end(), cpy.begin(), cpy.end());
	print_container(vec.begin(), vec.end(), "Vector after insert : \n", output);
	output << "Container vec's capacity after insert is : " << vec.capacity() << std::endl;

	std::cout << "\n======INSERT SPECIFIC VALUE AT SPECIFIC POS WITH SPECIFIC QUANTITY======\n";
	output << "\n======INSERT SPECIFIC VALUE AT SPECIFIC POS WITH SPECIFIC QUANTITY======\n";
	print_container(vec.begin(), vec.end(), "Vector before insert count value : \n", output);
	vec.insert(vec.end(), 1, 34);
	print_container(vec.begin(), vec.end(), "Vector after insert : \n", output);
	output << "Container vec's capacity after insert is : " << vec.capacity() << std::endl;
}

template < class T, class L >
void test_exec(T &vec, L list, std::string output_name)
{
	std::cout << "entered templated functionm test :\n\n";
	for (int i = 0; i < 10; i++)
		vec.push_back(i);
	std::ofstream output (output_name.c_str(), std::ios::out | std::ios::ate);
	output << "Size of vector is : " << vec.size() << std::endl;
	output << "Container vec's capacity is : " << vec.capacity() << std::endl;
	print_container(vec.begin(), vec.end(), "Vector : \n", output);
	output << "Vec is empty : " << vec.empty() << std::endl;
	// output << "Max_size of vec is : " << vec.max_size() << std::endl;
	std::cout << "\n======RESERVE======\n";
	output << "\n======RESERVE======\n";
	vec.reserve(25);
	output << "Size of vector after reserve is : " << vec.size() << std::endl;
	output << "Container vec's capacity after reserve is : " << vec.capacity() << std::endl;
	print_container(vec.begin(), vec.end(), "Vector after reserve : \n", output);

	std::cout << "\n======CLEAR======\n";
	output << "\n======CLEAR======\n";
	vec.clear();
	print_container(vec.begin(), vec.end(), "Vector after clear : \n", output);
	output << "Container vec's capacity after clear is : " << vec.capacity() << std::endl;

	for (int i = 0; i < 10; i++)
		vec.push_back(i);
	std::cout << "\n======ERASE======\n";
	output << "\n======ERASE======\n";
	output << "Element returned by erase : " << *vec.erase(vec.begin() + 3) << std::endl;
	print_container(vec.begin(), vec.end(), "Vector after erase : \n", output);
	output << "Container vec's capacity after erase is : " << vec.capacity() << std::endl;

	std::cout << "\n======ERASE 2======\n";
	output << "\n======ERASE 2======\n";
	output << "Element returned by erase : " << *vec.erase(vec.begin() + 3, vec.begin() + 5) << std::endl;
	print_container(vec.begin(), vec.end(), "Vector after erase : \n", output);
	output << "Container vec's capacity after erase is : " << vec.capacity() << std::endl;

	std::cout << "\n======ERASE RANGE OF 0======\n";
	output << "\n======ERASE RANGE OF 0======\n";
	output << "Element returned by erase : " << *vec.erase(vec.begin() + 3, vec.begin() + 3) << std::endl;
	print_container(vec.begin(), vec.end(), "Vector after erase : \n", output);
	output << "Container vec's capacity after erase is : " << vec.capacity() << std::endl;

	test_insert_vector(vec, vec, output, list);

	// std::cout << "\n======RESIZE======\n";
	// output << "\n======RESIZE======\n";
	// vec.resize(30);
	// print_container(vec.begin(), vec.end(), "Vector after resize : \n", output);
	// output << "Container vec's capacity after resize is : " << vec.capacity() << std::endl;

	output.close();
	std::cout << "Exiting templated function test\n\n";
}


void test_vector(void)
{
	ft::vector<my_type, test_alloc_red<my_type> > ft;
	std::vector<my_type, test_alloc_green<my_type> > stl;

	std::vector<my_type> to_insert;
	ft::vector<my_type> to_insert2;

	test_exec(stl, to_insert, "outputs/vector/stl_vector_output");

	test_exec(ft, to_insert2,"outputs/vector/ft_vector_output");
	system ("diff outputs/vector/ft_vector_output outputs/vector/stl_vector_output > outputs/vector/diff_results");
}