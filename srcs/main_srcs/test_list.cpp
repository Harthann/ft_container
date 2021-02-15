#include "List.hpp"
#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "utils.hpp"

typedef int my_type;
static Counter counter;

void test_lists(void)
{
    ft::list<my_type> ft;
    std::list<my_type> stl;

    std::ofstream stl_output;
	std::ofstream ft_output;

	stl_output.open(LIST_STL_OUTPUT);
	ft_output.open(LIST_FT_OUTPUT);

	ft.push_front(5);
	ft::list<my_type>::iterator it = ft.begin();
	std::cout << *it << std::endl;

}