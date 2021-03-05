#include "Vector.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <stdlib.h>
#include "utils.hpp"
typedef int my_type;

// static Counter counter;

// void check()
// {
// 	counter.print();
// 	std::getchar();
// }

template <class T>
void	test_capacity(T& vec, std::ostream& output)
{
	header("CAPACITY", output);
	print_container(vec.begin(), vec.end(), output);
	output << "The vector class size is : " << vec.size() << std::endl;
	output << "And his capacity : " << vec.capacity() << std::endl;
	output << "So vec start empty : " << vec.empty() << std::endl;
	for (int i = 0; i < 10; i++) // Construct 10 object
		vec.push_back(i);
	output << "Added value from 0 to 10 using pushback\n";
	print_container(vec.begin(), vec.end(), output);
	output << "Size now : " << vec.size() << " and capacity : " << vec.capacity() << std::endl;
	output << "So vec empty : " << vec.empty() << std::endl;

	//#################################
	//###		RESERVE TEST		###
	//#################################

	output << "\t\t== Reserve 20 ==\n";
	vec.reserve(20); //Does not call construct
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

	output << "\t\t== RESIZE 5 ==" << std::endl;
	vec.resize(5);
	output << "Size now : " << vec.size() << " and capacity : " << vec.capacity() << std::endl;
	print_container(vec.begin(), vec.end(), output);

	output << "\t\t== RESIZE 10 WITH VALUE OF 4 ==" << std::endl;
	vec.resize(10, 4);
	output << "Size now : " << vec.size() << " and capacity : " << vec.capacity() << std::endl;
	print_container(vec.begin(), vec.end(), output);

	output << "\t\t== RESIZE 30 ==" << std::endl;
	vec.resize(30);
	output << "Size now : " << vec.size() << " and capacity : " << vec.capacity() << std::endl;
	print_container(vec.begin(), vec.end(), output);
}

template <class T>
void	test_modifiers(T& vec, std::ostream& output)
{
	T					tmp;
	my_type	array[] = {5, 2, 123, 52435, 9};

	header("MODIFIER", output);
	print_container(vec.begin(), vec.end(), output);
	output << "\t\t== CREATED EMPTY TMP ==\n";
	output << "New vec size is : " << tmp.size() << std::endl;
	print_container(tmp.begin(), tmp.end(), output);
	output << "\t\t== INSERTING FROM VEC TO TMP ==" << std::endl;
	tmp.insert(tmp.begin(), vec.begin(), vec.end());
	print_container(tmp.begin(), tmp.end(), output);
	output << "\t\t== INSERT SINGLE VALUE IN VEC ==" << std::endl;
	vec.insert(vec.begin(), 950);
	print_container(vec.begin(), vec.end(), output);
	vec.insert(vec.end(), 950);
	print_container(vec.begin(), vec.end(), output);
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
	output << "\t\t== TMP CONTENT ==" << std::endl;
	print_container(tmp.begin(), tmp.end(), output);
	output << "\t\t== ASSIGN RANGE VALUE ==" << std::endl;
	vec.assign(tmp.begin(), tmp.end());
	print_container(vec.begin(), vec.end(), output);
	output << "\t\t== POP _BACK ==" << std::endl;
	vec.pop_back();
	print_container(vec.begin(), vec.end(), output);

	output << "\t\t== ASSIGN VEC USING POINTER ==" << std::endl;
	vec.assign(array, array + 5);

	output << "\t\t== SWAP TMP AND VEC ==" << std::endl;
	output << "Vec : ";
	print_container(vec.begin(), vec.end(), output);
	output << "tmp : ";
	print_container(tmp.begin(), tmp.end(), output);
	vec.swap(tmp);
	output << "Vec after swap: ";
	print_container(vec.begin(), vec.end(), output);
	output << "tmp after swap: ";
	print_container(tmp.begin(), tmp.end(), output);
	output << "\t\t CLEAR TMP ==" << std::endl;
	tmp.clear();
	print_container(tmp.begin(), tmp.end(), output);
}

template <class T>
void	test_access(T& vec, std::ostream& output)
{
	header("ACCESS", output);
	output << "\t\t== ACCESSING VEC AT INDEX 3 ==" << std::endl;
	output << vec.at(3) << std::endl;
	output << vec[3] << std::endl;
	output << "\t\t== OUT OF BOUND ACCESS ==" << std::endl;
	try {
		output << vec.at(-1) << std::endl;
	}
	catch (std::exception &e) {
		output << e.what() << std::endl;
	}
	output << "\t\t== ACCESS BACK THEN FRONT ==" << std::endl;
	output << "Front element is : " << vec.front() << std::endl;
	output << "Back element is : " << vec.back()  << std::endl;

	output << "\t\t== PRINT VEC USING REVERSE ITERATOR ==" << std::endl;
	print_container(vec.rbegin(), vec.rend(), output);
}

template <class T>
void comparison_tests(T &, std::ostream& output)
{
	T foo (3,100);
	T bar (2,200);
	if (foo==bar) output << "foo and bar are equal\n";
	if (foo!=bar) output << "foo and bar are not equal\n";
	if (foo< bar) output << "foo is less than bar\n";
	if (foo> bar) output << "foo is greater than bar\n";
	if (foo<=bar) output << "foo is less than or equal to bar\n";
	if (foo>=bar) output << "foo is greater than or equal to bar\n";
}

void test_vector(void)
{
	ft::vector<my_type> ft(5);
	std::vector<my_type> stl(5);
	std::ofstream stl_output;
	std::ofstream ft_output;

	//#################################
	//###		OPENING OUTPUT		###
	//#################################

	stl_output.open(VEC_STL_OUTPUT);
	ft_output.open(VEC_FT_OUTPUT);
	//#########################
	//###		STL			###
	//#########################
	std::cout << std::endl;
	test_capacity(stl, stl_output);
	std::cout << std::endl;
	test_modifiers(stl, stl_output);
	std::cout << std::endl;
	test_access(stl, stl_output);
	std::cout << std::endl;

	//########################
	//###		FT			##
	//########################
	
	test_capacity(ft, ft_output);
	test_modifiers(ft, ft_output);
	test_access(ft, ft_output);
	std::cout << std::endl;

	stl.clear();
	ft.clear();

	comparison_tests(stl, stl_output);
	comparison_tests(ft, ft_output);

}

