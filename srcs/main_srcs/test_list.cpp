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
	lst.push_back(3);
	lst.push_front(5);
	lst.push_back(9);
	lst.push_front(10);
	lst.push_back(12);
	lst.push_front(15);
	lst.push_back(6);
	lst.push_front(20);
	header("BASICS TESTS", output);
	output << "\t\t== ITERATING THROUGH LIST USING ITERATOR AND REVERSE ==" << std::endl;
	print_container(lst.begin(), lst.end(), output, " -> ");
	print_container(lst.rbegin(), lst.rend(), output, " -> ");
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
	// std::cout << *stl.rbegin() << std::endl;
	basic_tests(ft, ft_output);
}