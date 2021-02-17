#include "List.hpp"
#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "utils.hpp"

typedef int my_type;
static Counter counter;

template <class T>
void	basic_tests(T &lst, std::ostream &output)
{
	header("BASICS TESTS", output);
	output << "List size before push is = " << lst.size() << std::endl;
	lst.push_back(3);
	lst.push_front(5);
	lst.push_back(9);
	lst.push_front(10);
	output << "\t\t== SIZE TESTS ==\n";
	output << "List max size = " << lst.max_size() << std::endl;
	output << "List actual size is = " << lst.size() << std::endl;
	lst.push_back(12);
	lst.push_front(15);
	lst.push_back(6);
	lst.push_front(20);
	output << "\t\t== ITERATING THROUGH LIST USING ITERATOR AND REVERSE ==" << std::endl;
	print_container(lst.begin(), lst.end(), output, " -> ");
	print_container(lst.rbegin(), lst.rend(), output, " -> ");
	output << "\t\t== PRINT FRONT AND END ELEM ==\n";
	output << "Front : " << lst.front() << std::endl;
	output << "Back : " << lst.back() << std::endl;
	output << "\t\t== MODIFYIONG FRONT AND BACK THROUGH REFERENCE ==\n";
	lst.front() = 999;
	lst.back() = 123;
	output << "Front after modifying : " << lst.front() << std::endl;
	output << "Back after modifying : " << lst.back() << std::endl;	
	output << "\t\t== POP FRONT AND BACK ==\n";
	print_container(lst.begin(), lst.end(), output, " -> ");
	lst.pop_front();
	lst.pop_back();
	print_container(lst.begin(), lst.end(), output, " -> ");
	output << "\t\t== POP FRONT WHILE NOT EMPTY ==\n";
	while (!lst.empty())
		lst.pop_back();
	print_container(lst.begin(), lst.end(), output, " -> ");
}

void test_lists(void)
{
    ft::list<my_type> ft;
    std::list<my_type> stl;

    std::ofstream stl_output;
	std::ofstream ft_output;

	stl_output.open(LIST_STL_OUTPUT);
	ft_output.open(LIST_FT_OUTPUT);


	basic_tests(stl, stl_output);
	basic_tests(ft, ft_output);

	// getchar();
	// basic_tests(stl, std::cout);
	// basic_tests(ft, std::cout);
}