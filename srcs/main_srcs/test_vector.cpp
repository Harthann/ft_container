#include "Vector.hpp"
#include <iostream>
#include <fstream>
#include <initializer_list>
#include <string>
#include <vector>
#include <list>

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
std::string	print_container(T start, T end, const std::string str)
{
	std::string tmp(str);

	while (start != end) {
		tmp.append(std::to_string(*start));
		start++;
		if (start != end)
			tmp.append(" : ");
	}
	tmp.append("\n");
	return (tmp);
}


template < class T, class L >
void test_insert_vector(T &vec, T cpy, std::ofstream &output, L list)
{
	for (size_t i = 0; i < 25; i++)
		list.push_back(i);
	std::cout << "\n\tINSERT NUMBER WITH SPECIFIC POSITION\n";
	output << "\n\tINSERT NUMBER WITH SPECIFIC POSITION\n";
	vec.insert(vec.begin() + 3, 5);
	vec.insert(vec.begin() + 3, 5);
	vec.insert(vec.begin() + 3, 5);
	vec.insert(vec.begin() + 3, 5);
	output << print_container(vec.begin(), vec.end(), "Vector after insert : \n");
	output << "Container vec's capacity after insert is : " << vec.capacity() << std::endl;

	std::cout << "\n\tINSERT WITH RANGE ELEMENTS FROM OTHER VEC\n";
	output << "\n\tINSERT WITH RANGE ELEMENTS FROM OTHER VEC\n";
	output << print_container(vec.begin(), vec.end(), "Vector before insert : \n");
	output << print_container(cpy.begin(), cpy.end(), "Cpy to insert : \n");
	output << "Insert output return value is : " << *vec.insert(vec.end(), cpy.begin(), cpy.end()) << std::endl;
	// vec.shrink_to_fit();
	output << print_container(vec.begin(), vec.end(), "Vector after insert : \n");
	output << "Container vec's capacity after insert is : " << vec.capacity() << std::endl;

	// std::cout << "\n\tINSERT WITH RANGE ELEMENTS FROM OTHER CONTAINER\n";
	// output << "\n\tINSERT WITH RANGE ELEMENTS FROM OTHER CONTAINER\n";
	// output << print_container(vec.begin(), vec.end(), "Vector before insert : \n");
	// output << print_container(list.begin(), list.end(), "List to insert : \n");
	// output << "Insert output return value is : " << *vec.insert(vec.end(), list.begin(), list.end()) << std::endl;
	// // vec.shrink_to_fit();
	// output << print_container(vec.begin(), vec.end(), "Vector after insert : \n");
	// output << "Container vec's capacity after insert is : " << vec.capacity() << std::endl;

	std::cout << "\n\tINSERT SPECIFIC VALUE AT SPECIFIC POS WITH SPECIFIC QUANTITY\n";
	output << "\n\tINSERT SPECIFIC VALUE AT SPECIFIC POS WITH SPECIFIC QUANTITY\n";
	output << print_container(vec.begin(), vec.end(), "Vector before insert count value : \n");
	output << "Insert output return value is : " << *vec.insert(vec.end(), 1, 34) << std::endl;
	// vec.shrink_to_fit();
	output << print_container(vec.begin(), vec.end(), "Vector after insert : \n");
	output << "Container vec's capacity after insert is : " << vec.capacity() << std::endl;
}

template < class T, class L >
void test_exec(T &vec, L list, std::string output_name)
{
	std::cout << "entered templated functionm test :\n\n";
	for (int i = 0; i < 10; i++)
		vec.push_back(i);
	std::ofstream output (output_name, std::ios::out | std::ios::ate);
	output << "Size of vector is : " << vec.size() << std::endl;
	output << "Container vec's capacity is : " << vec.capacity() << std::endl;
	output << print_container(vec.begin(), vec.end(), "Vector : \n");
	output << "Vec is empty : " << vec.empty() << std::endl;
	// output << "Max_size of vec is : " << vec.max_size() << std::endl;
	std::cout << "\n\tRESERVE\n";
	output << "\n\tRESERVE\n";
	vec.reserve(25);
	output << "Size of vector after reserve is : " << vec.size() << std::endl;
	output << "Container vec's capacity after reserve is : " << vec.capacity() << std::endl;
	output << print_container(vec.begin(), vec.end(), "Vector after reserve : \n");
	std::cout << "\n\tSHRINK\n";
	output << "\n\tSHRINK\n";
	vec.shrink_to_fit();
	output << "Container vec's capacity after shrink is : " << vec.capacity() << std::endl;
	output << print_container(vec.begin(), vec.end(), "Vector after shrink : \n");

	std::cout << "\n\tCLEAR\n";
	output << "\n\tCLEAR\n";
	vec.clear();
	output << print_container(vec.begin(), vec.end(), "Vector after clear : \n");
	output << "Container vec's capacity after clear is : " << vec.capacity() << std::endl;

	for (int i = 0; i < 10; i++)
		vec.push_back(i);
	std::cout << "\n\tERASE\n";
	output << "\n\tERASE\n";
	output << "Element returned by erase : " << *vec.erase(vec.begin() + 3) << std::endl;
	output << print_container(vec.begin(), vec.end(), "Vector after erase : \n");
	output << "Container vec's capacity after erase is : " << vec.capacity() << std::endl;

	std::cout << "\n\tERASE 2\n";
	output << "\n\tERASE 2\n";
	output << "Element returned by erase : " << *vec.erase(vec.begin() + 3, vec.begin() + 5) << std::endl;
	output << print_container(vec.begin(), vec.end(), "Vector after erase : \n");
	output << "Container vec's capacity after erase is : " << vec.capacity() << std::endl;

	std::cout << "\n\tERASE RANGE OF 0\n";
	output << "\n\tERASE RANGE OF 0\n";
	output << "Element returned by erase : " << *vec.erase(vec.begin() + 3, vec.begin() + 3) << std::endl;
	output << print_container(vec.begin(), vec.end(), "Vector after erase : \n");
	output << "Container vec's capacity after erase is : " << vec.capacity() << std::endl;

	test_insert_vector(vec, vec, output, list);

	output.close();
	std::cout << "Exiting templated function test\n\n";
}

typedef int my_type;

void test_vector(void)
{
	ft::Vector<my_type, test_alloc_red<my_type> > ft;
	std::vector<my_type, test_alloc_green<my_type> > stl;

	std::vector<my_type> to_insert;
	ft::Vector<my_type> to_insert2;

	// for (size_t i = 0; i < 25; i++)
	// 	ft.push_back(i);
	// for (size_t i = 0; i < 25; i++)
	// 	stl.push_back(i);
	// std::cout << "array address is : " << &*ft.begin() << std::endl;
	// std::cout << print_container(stl.begin(), stl.end(), "ft is : \n");
	// for (ft::Vector<my_type>::const_iterator it = ft.begin(); it != ft.end(); it++)
	// 	std::cout << *it;
	// std::cout << ft.size() << " " << (ft.begin() == ft.end()) << std::endl;
	// std::cout << print_container(ft.begin(), ft.end(), "ft is : \n");
	// getchar();
	// ft.reserve(50);
	// std::cout << "array address is : " << &*ft.begin() << std::endl;
	// std::cout << print_container(ft.begin(), ft.end(), "ft is after reserve : \n");

	// ft::Vector<int>::iterator it = ft.begin();
	// std::cout << *it << std::endl;
	// *it = 46;
	// std::cout << *it << std::endl;
	// std::cout << print_container(ft.begin(), ft.end(), "ft : ");
	// stl.insert(stl.begin(), ft.begin(), ft.end());
	// system ("sleep 1"); 

	// // getchar();
	test_exec(stl, to_insert, "outputs/vector/stl_vector_output");

	test_exec(ft, to_insert2,"outputs/vector/ft_vector_output");
	system ("diff outputs/vector/ft_vector_output outputs/vector/stl_vector_output > outputs/vector/diff_results");

	// getchar();
}