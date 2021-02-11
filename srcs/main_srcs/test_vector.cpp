#include "Vector.hpp"
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
struct test_alloc_green{
	typedef T	value_type;
	typedef T*	pointer;
	typedef T&	reference;
	typedef const T*	const_pointer;
	typedef const T&	const_reference;
	typedef size_t		size_type;
	typedef std::ptrdiff_t	difference_type;
	template <class Type> struct rebind {
		typedef test_alloc_green<Type> other;
	};	

	test_alloc_green() {};
	test_alloc_green(test_alloc_green const &) {};
	~test_alloc_green() {};

	T *allocate(size_t size) {
		std::cout << "\033[32mAllocate request of size : " << size << std::endl;
		std::cout << "\033[0m";
		return (new T[size]);
	}
	void deallocate(T *ptr, size_t size) {
		std::cout << "\033[32mDeallocation request of size : " << size << std::endl;
		std::cout << "\033[0m";
		delete [] ptr;
	}
	
	pointer address(reference X) { return (&X); };
	const_pointer address(const_reference X) const { return (&X); };
	void	construct(pointer p, const_reference val) {new(p) value_type(val);};
	void	destroy(pointer p) {p->~value_type(); };
	size_t	max_size() const {return (std::numeric_limits<size_type>::max());}; 
};

template <class T>
struct test_alloc_red{
	typedef T	value_type;
	typedef T*	pointer;
	typedef T&	reference;
	typedef const T*	const_pointer;
	typedef const T&	const_reference;
	typedef size_t		size_type;
	typedef std::ptrdiff_t	difference_type;
	template <class Type> struct rebind {
		typedef test_alloc_red<Type> other;
	};	

	test_alloc_red() {};
	test_alloc_red(test_alloc_red const &) {};
	~test_alloc_red() {};

	T *allocate(size_t size) {
		std::cout << "\033[31mAllocate request of size : " << size << std::endl;
		std::cout << "\033[0m";
		return (new T[size]);
	}
	void deallocate(T *ptr, size_t size) {
		std::cout << "\033[31mDeallocation request of size : " << size << std::endl;
		std::cout << "\033[0m";
		delete [] ptr;
	}
	
	pointer address(reference X) { return (&X); };
	const_pointer address(const_reference X) const { return (&X); };
	void	construct(pointer p, const_reference val) {new(p) value_type(val);};
	void	destroy(pointer p) {p->~value_type(); };
	size_t	max_size() const {return (std::numeric_limits<size_type>::max());}; 
};

void	header(std::string str, std::ofstream& output)
{
	std::string tmp(14 + str.length(), '=');
	output << "\t\t" << tmp << std::endl;
	output << "\t\t====== " << str << " ======" << std::endl;
	output << "\t\t" << tmp << std::endl;
}

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

	header("CAPACITY", output);
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

	output << "\t\t== Reserve 20 ==\n";
	vec.reserve(20);
	output << "Size now : " << vec.size() << " and capacity : " << vec.capacity() << std::endl;
	output << "\t\t== Reserve 5 ==\n";
	vec.reserve(5);
	output << "Size now : " << vec.size() << " and capacity : " << vec.capacity() << std::endl;
	print_container(vec.begin(), vec.end(), output);
	output << "\t\t== Reserve -5 ==\n";
	try {
		vec.reserve(-5);
	}
	catch (std::exception &error) {
		output << error.what() << std::endl;
	}
	output << "Size now : " << vec.size() << " and capacity : " << vec.capacity() << std::endl;
	print_container(vec.begin(), vec.end(), output);
	output << "Max size for the container is : " << vec.max_size() << std::endl;
}

template <class T>
void	test_modifiers(T& vec, std::ofstream& output)
{
	std::vector<my_type> tmp_stl;
	ft::vector<my_type> tmp_ft;
	T					tmp;

	header("MODIFIER", output);
	print_container(vec.begin(), vec.end(), output);
	output << "\t\t== CREATING NEW VEC ==\n";
	output << "New stl::vec size is : " << tmp_stl.size() << std::endl;
	output << "New ft::vec size is : " << tmp_ft.size() << std::endl;
	output << "\t\t== INSERTING FROM VEC TO TMP_STL ==" << std::endl;
	tmp_stl.insert(tmp_stl.begin(), vec.begin(), vec.end());
	output << "New stl::vec size is : " << tmp_stl.size() << std::endl;
	print_container(tmp_stl.begin(), tmp_stl.end(), output);
	output << "\t\t== INSERTING FROM VEC TO TMP_FT ==" << std::endl;
	tmp_ft.insert(tmp_ft.begin(), vec.begin(), vec.end());
	output << "New stl::vec size is : " << tmp_ft.size() << std::endl;
	print_container(tmp_ft.begin(), tmp_ft.end(), output);
	output << "\t\t== INSERT SINGLE VALUE IN VEC ==" << std::endl;
	vec.insert(vec.begin(), 950);
	print_container(vec.begin(), vec.end(), output);
	vec.insert(vec.end(), 950);
	print_container(vec.begin(), vec.end(), output);
	output << "\t\t== INSERT VALUE AT BEGIN OF EMPTY VEC ==" << std::endl;
	tmp.insert(tmp.begin(), 950);
	print_container(tmp.begin(), tmp.end(), output);
	output << "\t\t== INSERT MULTIPLE VALUE ==" << std::endl;
	tmp.insert(tmp.end(), 3, 9);
	print_container(tmp.begin(), tmp.end(), output);
	output << "\t\t== ERASE SIMPLE DATA ==" << std::endl;
	output << "Erase returned index : " << ft::distance(vec.begin(), vec.erase(vec.begin() + 4)) << std::endl;
	print_container(vec.begin(), vec.end(), output);
	output << "\t\t== ERASE END ELEMENT ==" << std::endl;
	output << "Erase returned index : " << ft::distance(vec.begin(), vec.erase(vec.end() - 1)) << std::endl;
	print_container(vec.begin(), vec.end(), output);
	output << "\t\t== ERASE RANGE ELEMENT ==" << std::endl;
	output << "Erase returned index : " << ft::distance(vec.begin(), vec.erase(vec.begin() + 2, vec.begin() + 5)) << std::endl;
	print_container(vec.begin(), vec.end(), output);
	output << "\t\t== ERASE RANGE ELEMENT OF SIZE 0 ==" << std::endl;
	output << "Erase returned index : " << ft::distance(vec.begin(), vec.erase(vec.begin() + 2, vec.begin() + 2)) << std::endl;
	print_container(vec.begin(), vec.end(), output);
	output << "\t\t== ERASE RANGE ALL ELEMENT ==" << std::endl;
	output << "Erase returned index : " << ft::distance(vec.begin(), vec.erase(vec.begin(), vec.end())) << std::endl;
	print_container(vec.begin(), vec.end(), output);
	output << "\t\t== ASSIGN MULTIPLE TIME A VALUE ==" << std::endl;
	vec.assign(5, 345);
	print_container(vec.begin(), vec.end(), output);
	output << "\t\t== TMP STL CONTENT ==" << std::endl;
	print_container(tmp_stl.begin(), tmp_stl.end(), output);
	output << "\t\t== TMP FT CONTENT ==" << std::endl;
	print_container(tmp_ft.begin(), tmp_ft.end(), output);
	output << "\t\t== ASSIGN RANGE VALUE FROM STL ==" << std::endl;
	vec.assign(tmp_stl.begin(), tmp_stl.end());
	print_container(vec.begin(), vec.end(), output);
	vec.assign(tmp_stl.begin() + 4, tmp_stl.end() - 2);
	print_container(vec.begin(), vec.end(), output);
	output << "\t\t== ASSIGN RANGE VALUE FROM FT ==" << std::endl;
	vec.assign(tmp_ft.begin(), tmp_ft.end());
	print_container(vec.begin(), vec.end(), output);
	vec.assign(tmp_ft.begin() + 4, tmp_ft.end() - 2);
	print_container(vec.begin(), vec.end(), output);

}

void test_vector(void)
{
	ft::vector<my_type, test_alloc_green<my_type> > ft;
	//std::vector<my_type> stl;
	std::vector<my_type, test_alloc_red<my_type> > stl;
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

	//################################
	//###		MODIFIERS			##
	//################################
	
	test_modifiers(stl, stl_output);
	test_modifiers(ft, ft_output);

	//#####################################
	//###		SEARCHING FOR DIFF		###
	//#####################################

	//system ("diff outputs/vector/ft_vector_output outputs/vector/stl_vector_output > outputs/vector/diff_results");
}
